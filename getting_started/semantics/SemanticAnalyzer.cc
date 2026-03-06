#include "../Passes.h"

#include <string>
#include <vector>

// Returns true when a name exists in the current scope chain.
static bool isDeclared(const Scope *scope, const std::string &name) {
  for (const Scope *s = scope; s != nullptr; s = s->parent) {
    if (s->symbols.find(name) != s->symbols.end())
      return true;
  }
  return false;
}

// Resolves a symbol by walking current scope -> parent scopes.
static const Symbol *lookupInChain(const Scope *scope, const std::string &name) {
  for (const Scope *s = scope; s != nullptr; s = s->parent) {
    std::unordered_map<std::string, Symbol>::const_iterator it = s->symbols.find(name);
    if (it != s->symbols.end())
      return &it->second;
  }
  return nullptr;
}

static const Scope *findClassScope(const Scope *scope, const std::string &className) {
  if (!scope)
    return nullptr;

  if (scope->kind == Scope::Kind::Class && scope->label == className)
    return scope;

  for (const auto &child : scope->children) {
    const Scope *found = findClassScope(child.get(), className);
    if (found)
      return found;
  }
  return nullptr;
}

static const Symbol *lookupClassMember(const SymbolTable &st,
                                       const std::string &className,
                                       const std::string &memberName) {
  const Scope *cls = findClassScope(st.root(), className);
  if (!cls)
    return nullptr;

  std::unordered_map<std::string, Symbol>::const_iterator it =
      cls->symbols.find(memberName);
  if (it == cls->symbols.end())
    return nullptr;
  return &it->second;
}

// Mirrors pass-1 scope creation order so semantic traversal can stay aligned.
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

// Forward declarations for recursive statement/expression checks.
static void checkStmt(Node *s, const SymbolTable &st, ScopeCursor &sc,
                      ErrorReporter &errors);
static void checkExpr(Node *e, const SymbolTable &st, ScopeCursor &sc,
                      ErrorReporter &errors);

static Type inferExprType(Node *e, const SymbolTable &st, ScopeCursor &sc) {
  if (!e)
    return Type::UnknownTy();

  if (e->type == "Int")
    return Type::IntTy();
  if (e->type == "Float")
    return Type::FloatTy();
  if (e->type == "Bool")
    return Type::BoolTy();
  if (e->type == "LengthExpr")
    return Type::IntTy();

  if (e->type == "Id") {
    const Symbol *sym = lookupInChain(sc.cur, e->value);
    if (!sym)
      return Type::UnknownTy();
    if (sym->kind == SymbolKind::Method)
      return sym->returnType;
    if (sym->kind == SymbolKind::Class)
      return Type::ClassTy(sym->name);
    return sym->type;
  }

  if (e->type == "ArrayLiteral") {
    Node *base = e->child(0);
    if (!base || base->type != "BaseType")
      return Type::ArrayOf(Type::UnknownTy());
    if (base->value == "int")
      return Type::ArrayOf(Type::IntTy());
    if (base->value == "float")
      return Type::ArrayOf(Type::FloatTy());
    if (base->value == "boolean")
      return Type::ArrayOf(Type::BoolTy());
    return Type::ArrayOf(Type::UnknownTy());
  }

  if (e->type == "IndexExpr") {
    Type t = inferExprType(e->child(0), st, sc);
    if (t.isArray())
      return t.base();
    return Type::UnknownTy();
  }

  if (e->type == "FieldExpr") {
    Type recv = inferExprType(e->child(0), st, sc);
    Node *mid = e->child(1);
    if (!recv.isClass() || !mid || mid->type != "Id")
      return Type::UnknownTy();

    const Symbol *mem = lookupClassMember(st, recv.className, mid->value);
    if (!mem)
      return Type::UnknownTy();
    if (mem->kind == SymbolKind::Method)
      return mem->returnType;
    return mem->type;
  }

  if (e->type == "CallExpr") {
    Node *callee = e->child(0);
    if (!callee)
      return Type::UnknownTy();

    if (callee->type == "Id") {
      const Symbol *sym = lookupInChain(sc.cur, callee->value);
      if (!sym)
        return Type::UnknownTy();
      if (sym->kind == SymbolKind::Method)
        return sym->returnType;
      if (sym->kind == SymbolKind::Class)
        return Type::ClassTy(sym->name);
      return Type::UnknownTy();
    }

    if (callee->type == "FieldExpr") {
      Type recv = inferExprType(callee->child(0), st, sc);
      Node *mid = callee->child(1);
      if (!recv.isClass() || !mid || mid->type != "Id")
        return Type::UnknownTy();
      const Symbol *mem = lookupClassMember(st, recv.className, mid->value);
      if (!mem || mem->kind != SymbolKind::Method)
        return Type::UnknownTy();
      return mem->returnType;
    }
  }

  return Type::UnknownTy();
}

// Validates an identifier used as an expression value.
static void checkIdUse(Node *idNode, const SymbolTable &st, ScopeCursor &sc,
                       ErrorReporter &errors) {
  if (!idNode || idNode->type != "Id")
    return;

  const Symbol *sym = lookupInChain(sc.cur, idNode->value);
  if (!sym) {
    errors.add(idNode->lineno, "Undeclared identifier '" + idNode->value + "'");
    return;
  }

  // Method/class names are valid symbols, but not standalone runtime values.
  if (sym->kind == SymbolKind::Method || sym->kind == SymbolKind::Class) {
    errors.add(idNode->lineno,
               "Identifier '" + idNode->value + "' is not a value expression");
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

  if (e->type == "FieldExpr") {
    Node *recv = e->child(0);
    Node *member = e->child(1);

    checkExpr(recv, st, sc, errors);

    Type recvTy = inferExprType(recv, st, sc);
    if (recvTy.isClass() && member && member->type == "Id") {
      if (!lookupClassMember(st, recvTy.className, member->value)) {
        errors.add(member->lineno,
                   "Undeclared identifier '" + member->value + "'");
      }
    }
    return;
  }

  if (e->type == "CallExpr") {
    Node *callee = e->child(0);
    Node *args = e->child(1);

    if (callee) {
      if (callee->type == "Id") {
        const Symbol *sym = lookupInChain(sc.cur, callee->value);
        if (!sym) {
          errors.add(callee->lineno,
                     "Undeclared identifier '" + callee->value + "'");
        }
      } else if (callee->type == "FieldExpr") {
        Node *recv = callee->child(0);
        Node *member = callee->child(1);
        checkExpr(recv, st, sc, errors);

        Type recvTy = inferExprType(recv, st, sc);
        if (recvTy.isClass() && member && member->type == "Id") {
          const Symbol *mem =
              lookupClassMember(st, recvTy.className, member->value);
          if (!mem || mem->kind != SymbolKind::Method) {
            errors.add(member->lineno,
                       "Undeclared identifier '" + member->value + "'");
          }
        }
      } else {
        checkExpr(callee, st, sc, errors);
      }
    }

    if (args && args->type == "Args") {
      for (Node *a : args->children)
        checkExpr(a, st, sc, errors);
    }
    return;
  }

  // Default case: recurse through children and validate identifiers there.
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
    // Enter the corresponding block scope from pass 1.
    sc.enterNext(errors, s->lineno);
    checkStmtList(s->child(0), st, sc, errors);
    sc.exit();
    return;
  }

  if (s->type == "VarStmt") {
    // Declaration identifier is not a usage, but initializer expressions are.
    Node *vd = s->child(0);
    Node *init = vd ? vd->child(3) : nullptr;
    if (init && init->type == "Init") {
      checkExpr(init->child(0), st, sc, errors);
    }
    return;
  }

  if (s->type == "AssignStmt") {
    // Validate both assignment target expression and source expression.
    checkExpr(s->child(0), st, sc, errors);
    checkExpr(s->child(2), st, sc, errors);
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
    // `for` has its own scope in pass 1; enter the matching scope here.
    sc.enterNext(errors, s->lineno);

    // Init can be either assignment-style or declaration-style.
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

    // Check condition expression when present.
    Node *cond = s->child(1);
    if (cond && cond->type != "ForCondEmpty")
      checkExpr(cond, st, sc, errors);

    // Update contains assignment target/source expressions.
    Node *upd = s->child(2);
    if (upd && upd->type == "Update") {
      checkExpr(upd->child(0), st, sc, errors);
      checkExpr(upd->child(2), st, sc, errors);
    }

    // Loop body may contain nested scopes/usages.
    checkStmt(s->child(3), st, sc, errors);

    sc.exit();
    return;
  }

  if (s->type == "PrintStmt" || s->type == "ReadStmt" ||
      s->type == "ReturnStmt") {
    checkExpr(s->child(0), st, sc, errors);
    return;
  }

  // Break/continue have no identifier usage.
}

void semanticAnalyze(Node *root, const SymbolTable &st, ErrorReporter &errors) {
  if (!root || root->type != "Program")
    return;

  ScopeCursor sc(st);

  Node *globals = root->child(0);
  Node *classes = root->child(1);
  Node *entry = root->child(2);

  // Globals only need initializer-expression validation in this pass.
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

  // Traverse class scopes and method scopes in the same order as pass 1.
  if (classes && classes->type == "Classes") {
    for (Node *cd : classes->children) {
      if (!cd || cd->type != "ClassDecl")
        continue;

      sc.enterNext(errors, cd->lineno);

      Node *body = cd->child(1);
      if (body && body->type == "ClassBody") {
        for (Node *mem : body->children) {
          if (!mem)
            continue;

          // Validate field initializer expressions.
          if (mem->type == "ClassVar") {
            Node *vd = mem->child(0);
            Node *init = vd ? vd->child(3) : nullptr;
            if (init && init->type == "Init")
              checkExpr(init->child(0), st, sc, errors);
            continue;
          }

          // Validate method body with method scope active.
          if (mem->type == "MethodDecl") {
            sc.enterNext(errors, mem->lineno);
            checkStmt(mem->child(3), st, sc, errors);
            sc.exit();
          }
        }
      }

      sc.exit();
    }
  }

  // Validate entry-point body in its method scope.
  if (entry && entry->type == "Entry") {
    sc.enterNext(errors, entry->lineno);
    checkStmt(entry->child(1), st, sc, errors);
    sc.exit();
  }
}
