#include "Passes.h"

#include <string>

// Returns true if `name` is declared in `scope` or any parent scope.
static bool isDeclared(const Scope *scope, const std::string &name) {
  for (const Scope *s = scope; s != nullptr; s = s->parent) {
    if (s->symbols.find(name) != s->symbols.end())
      return true;
  }
  return false;
}

// Walk the scope tree in the same order it was built in pass 1.
struct ScopeCursor {
  const Scope *cur;
  std::vector<size_t> nextChildIndex;

  explicit ScopeCursor(const SymbolTable &st)
      : cur(st.root()), nextChildIndex{0} {}

  void enterNext(ErrorReporter &errors, int line) {
    if (!cur)
      return;
    size_t &idx = nextChildIndex.back();
    if (idx >= cur->children.size()) {
      errors.add(line, "Internal: scope mismatch (no child scope available)");
      return;
    }
    const Scope *child = cur->children[idx].get();
    idx++;
    cur = child;
    nextChildIndex.push_back(0);
  }

  void exit() {
    if (!cur)
      return;
    if (nextChildIndex.size() > 1)
      nextChildIndex.pop_back();
    cur = cur->parent;
  }
};

// Forward decls
static void checkStmt(Node *s, const SymbolTable &st, ScopeCursor &sc,
                      ErrorReporter &errors);
static void checkExpr(Node *e, const SymbolTable &st, ScopeCursor &sc,
                      ErrorReporter &errors);

// Check identifier usage: only for Id nodes that appear in expressions.
static void checkIdUse(Node *idNode, const SymbolTable &st, ScopeCursor &sc,
                       ErrorReporter &errors) {
  if (!idNode || idNode->type != "Id")
    return;

  if (!isDeclared(sc.cur, idNode->value)) {
    errors.add(idNode->lineno, "Undeclared identifier '" + idNode->value + "'");
  }
}

static void checkExpr(Node *e, const SymbolTable &st, ScopeCursor &sc,
                      ErrorReporter &errors) {
  if (!e)
    return;

  if (e->type == "Id") {
    checkIdUse(e, st, sc, errors);
    return;
  }

  // For everything else, just recurse
  for (Node *c : e->children)
    checkExpr(c, st, sc, errors);
}

static void checkStmtList(Node *stmts, const SymbolTable &st, ScopeCursor &sc,
                          ErrorReporter &errors) {
  if (!stmts || stmts->type != "Stmts")
    return;
  for (Node *s : stmts->children)
    checkStmt(s, st, sc, errors);
}

static void checkStmt(Node *s, const SymbolTable &st, ScopeCursor &sc,
                      ErrorReporter &errors) {
  if (!s)
    return;

  if (s->type == "StmtBlock") {
    // Enter the block scope created in pass 1
    sc.enterNext(errors, s->lineno);
    checkStmtList(s->child(0), st, sc, errors);
    sc.exit();
    return;
  }

  if (s->type == "VarStmt") {
    // VarDecl is a declaration. We do NOT treat its Id as usage.
    // But we SHOULD check initializer expression (it may contain Id uses).
    Node *vd = s->child(0);                   // VarDecl
    Node *init = vd ? vd->child(3) : nullptr; // Init?
    if (init && init->type == "Init") {
      checkExpr(init->child(0), st, sc, errors);
    }
    return;
  }

  if (s->type == "AssignStmt") {
    checkExpr(s->child(0), st, sc,
              errors); // lhs expression may contain Id uses
    checkExpr(s->child(2), st, sc, errors); // rhs
    return;
  }

  if (s->type == "ExprStmt") {
    checkExpr(s->child(0), st, sc, errors);
    return;
  }

  if (s->type == "IfStmt") {
    checkExpr(s->child(0), st, sc, errors);
    checkStmt(s->child(1), st, sc, errors);
    return;
  }

  if (s->type == "IfElseStmt") {
    checkExpr(s->child(0), st, sc, errors);
    checkStmt(s->child(1), st, sc, errors);
    checkStmt(s->child(2), st, sc, errors);
    return;
  }

  if (s->type == "ForStmt") {
    // Enter the for scope created in pass 1
    sc.enterNext(errors, s->lineno);

    // init: may have assignment expr (use) or var init expr (use)
    Node *init = s->child(0);
    if (init) {
      if (init->type == "ForInitAssign") {
        checkExpr(init->child(0), st, sc, errors);
        checkExpr(init->child(2), st, sc, errors);
      } else if (init->type == "ForInitVar") {
        Node *vd = init->child(0);
        Node *init2 = vd ? vd->child(3) : nullptr;
        if (init2 && init2->type == "Init")
          checkExpr(init2->child(0), st, sc, errors);
      }
    }

    // condition (if present)
    Node *cond = s->child(1);
    if (cond && cond->type != "ForCondEmpty")
      checkExpr(cond, st, sc, errors);

    // update: Update -> expr, Op, expr
    Node *upd = s->child(2);
    if (upd && upd->type == "Update") {
      checkExpr(upd->child(0), st, sc, errors);
      checkExpr(upd->child(2), st, sc, errors);
    }

    // body
    checkStmt(s->child(3), st, sc, errors);

    sc.exit();
    return;
  }

  if (s->type == "PrintStmt" || s->type == "ReadStmt" ||
      s->type == "ReturnStmt") {
    checkExpr(s->child(0), st, sc, errors);
    return;
  }

  // BreakStmt / ContinueStmt: nothing to check
}

void semanticAnalyze(Node *root, const SymbolTable &st, ErrorReporter &errors) {
  if (!root || root->type != "Program")
    return;

  ScopeCursor sc(st);

  Node *globals = root->child(0);
  Node *classes = root->child(1);
  Node *entry = root->child(2);

  // Globals: check initializer expressions (if any)
  if (globals && globals->type == "Globals") {
    for (Node *gv : globals->children) {
      if (!gv || gv->type != "GlobalVar")
        continue;
      Node *vd = gv->child(0);
      Node *init = vd ? vd->child(3) : nullptr;
      if (init && init->type == "Init")
        checkExpr(init->child(0), st, sc, errors);
    }
  }

  // Classes: enter each class scope, then each method scope, then body blocks
  if (classes && classes->type == "Classes") {
    for (Node *cd : classes->children) {
      if (!cd || cd->type != "ClassDecl")
        continue;

      sc.enterNext(errors, cd->lineno); // class scope

      Node *body = cd->child(1); // ClassBody
      if (body && body->type == "ClassBody") {
        for (Node *mem : body->children) {
          if (!mem)
            continue;

          // Field init? (ClassVar -> VarDecl -> Init)
          if (mem->type == "ClassVar") {
            Node *vd = mem->child(0);
            Node *init = vd ? vd->child(3) : nullptr;
            if (init && init->type == "Init")
              checkExpr(init->child(0), st, sc, errors);
            continue;
          }

          // Method body
          if (mem->type == "MethodDecl") {
            sc.enterNext(errors, mem->lineno);        // method scope
            checkStmt(mem->child(3), st, sc, errors); // StmtBlock
            sc.exit();
          }
        }
      }

      sc.exit();
    }
  }

  // Entry main
  if (entry && entry->type == "Entry") {
    sc.enterNext(errors, entry->lineno); // main method scope
    checkStmt(entry->child(1), st, sc, errors);
    sc.exit();
  }
}
