#include "Passes.h"

#include <string>

static Type parseBaseType(Node *n) {
  if (!n)
    return Type::UnknownTy();
  if (n->type != "BaseType")
    return Type::UnknownTy();

  if (n->value == "int")
    return Type::IntTy();
  if (n->value == "float")
    return Type::FloatTy();
  if (n->value == "boolean")
    return Type::BoolTy();
  return Type::UnknownTy();
}

static Type parseTypeNode(Node *n) {
  if (!n)
    return Type::UnknownTy();

  // class type
  if (n->type == "TypeName") {
    return Type::ClassTy(n->value);
  }

  // void type (your grammar creates mk("Type","void"))
  if (n->type == "Type" && n->value == "void") {
    return Type::VoidTy();
  }

  // primitive (with optional array)
  if (n->type == "Type") {
    Node *base = n->child(0); // BaseType
    Node *arr = n->child(1);  // Array true|false

    Type b = parseBaseType(base);
    if (!arr)
      return b;

    if (arr->type == "Array" && arr->value == "true") {
      return Type::ArrayOf(b);
    }
    return b;
  }

  // sometimes you might get BaseType directly
  if (n->type == "BaseType") {
    return parseBaseType(n);
  }

  return Type::UnknownTy();
}

static Type parseReturnType(Node *rt) {
  if (!rt)
    return Type::UnknownTy();

  // Entry uses ReturnType("int") with value set
  if (!rt->value.empty()) {
    if (rt->value == "int")
      return Type::IntTy();
    if (rt->value == "float")
      return Type::FloatTy();
    if (rt->value == "boolean")
      return Type::BoolTy();
    if (rt->value == "void")
      return Type::VoidTy();
  }

  // Methods use ReturnType with a child node
  Node *t = rt->child(0);
  return parseTypeNode(t);
}

// Forward decl: statement traversal for local declarations
static void visitStmt(SymbolTable &st, Node *stmt, ErrorReporter &errors);

// Declare a VarDecl node into current scope (as var/field/param depending on
// kind)
static void declareVarDecl(SymbolTable &st, Node *varDecl, SymbolKind kind,
                           ErrorReporter &errors) {
  if (!varDecl || varDecl->type != "VarDecl")
    return;

  Node *volNode = varDecl->child(0); // Volatile true/false
  Node *idNode = varDecl->child(1);  // Id
  Node *tyNode = varDecl->child(2);  // type node

  if (!idNode || idNode->type != "Id")
    return;

  Symbol sym;
  sym.name = idNode->value;
  sym.kind = kind;
  sym.declaredLine = idNode->lineno;
  sym.isVolatile = (volNode && volNode->value == "true");
  sym.type = parseTypeNode(tyNode);

  if (!st.declareLocal(sym)) {
    errors.add(idNode->lineno,
               "Duplicate identifier '" + sym.name + "' in the same scope");
  }
}

static void visitStmtList(SymbolTable &st, Node *stmtsNode,
                          ErrorReporter &errors) {
  if (!stmtsNode || stmtsNode->type != "Stmts")
    return;
  for (Node *s : stmtsNode->children) {
    visitStmt(st, s, errors);
  }
}

static void visitStmt(SymbolTable &st, Node *stmt, ErrorReporter &errors) {
  if (!stmt)
    return;

  // A block creates a new scope
  if (stmt->type == "StmtBlock") {
    st.enterScope(Scope::Kind::Block, "block");
    Node *stmts = stmt->child(0); // Stmts
    visitStmtList(st, stmts, errors);
    st.exitScope();
    return;
  }

  // Var statement: declare local var in CURRENT scope
  if (stmt->type == "VarStmt") {
    Node *varDecl = stmt->child(0);
    declareVarDecl(st, varDecl, SymbolKind::Var, errors);
    return;
  }

  // If / IfElse: recurse into bodies
  if (stmt->type == "IfStmt") {
    Node *thenBody = stmt->child(1);
    visitStmt(st, thenBody, errors);
    return;
  }

  if (stmt->type == "IfElseStmt") {
    Node *thenBody = stmt->child(1);
    Node *elseBody = stmt->child(2);
    visitStmt(st, thenBody, errors);
    visitStmt(st, elseBody, errors);
    return;
  }

  // ForStmt: create a dedicated loop scope (so init var can live there)
  if (stmt->type == "ForStmt") {
    st.enterScope(Scope::Kind::For, "for");

    Node *init = stmt->child(0); // ForInitEmpty | ForInitVar | ForInitAssign
    if (init && init->type == "ForInitVar") {
      Node *varDecl = init->child(0);
      declareVarDecl(st, varDecl, SymbolKind::Var, errors);
    }

    Node *body = stmt->child(3);
    visitStmt(st, body, errors);

    st.exitScope();
    return;
  }

  // Everything else: no declarations to add in pass 1
}

SymbolTable buildSymbolTable(Node *root, ErrorReporter &errors) {
  SymbolTable st;
  if (!root)
    return st;

  // Program -> Globals, Classes, Entry
  Node *globals = root->child(0);
  Node *classes = root->child(1);
  Node *entry = root->child(2);

  // --- Globals ---
  if (globals && globals->type == "Globals") {
    for (Node *gv : globals->children) { // GlobalVar nodes
      if (!gv || gv->type != "GlobalVar")
        continue;
      Node *varDecl = gv->child(0);
      declareVarDecl(st, varDecl, SymbolKind::Var, errors);
    }
  }

  // --- Classes ---
  if (classes && classes->type == "Classes") {
    for (Node *cd : classes->children) { // ClassDecl nodes
      if (!cd || cd->type != "ClassDecl")
        continue;

      Node *classId = cd->child(0); // Id
      Node *body = cd->child(1);    // ClassBody
      if (!classId || classId->type != "Id")
        continue;

      // declare class in global scope
      {
        Symbol cls;
        cls.name = classId->value;
        cls.kind = SymbolKind::Class;
        cls.declaredLine = classId->lineno;
        cls.type = Type::ClassTy(cls.name);

        if (!st.declareLocal(cls)) {
          errors.add(classId->lineno,
                     "Duplicate class '" + cls.name + "' in global scope");
        }
      }

      // enter class scope
      st.enterScope(Scope::Kind::Class, classId->value);

      if (body && body->type == "ClassBody") {
        for (Node *mem : body->children) {
          if (!mem)
            continue;

          // field: ClassVar -> VarDecl
          if (mem->type == "ClassVar") {
            Node *varDecl = mem->child(0);
            declareVarDecl(st, varDecl, SymbolKind::Field, errors);
            continue;
          }

          // method: MethodDecl -> Id, Params, ReturnType, StmtBlock
          if (mem->type == "MethodDecl") {
            Node *mid = mem->child(0);
            Node *params = mem->child(1);
            Node *rt = mem->child(2);
            Node *mbody = mem->child(3);

            if (!mid || mid->type != "Id")
              continue;

            Symbol m;
            m.name = mid->value;
            m.kind = SymbolKind::Method;
            m.declaredLine = mid->lineno;
            m.returnType = parseReturnType(rt);

            // collect param types (and declare later inside method scope)
            if (params && params->type == "Params") {
              for (Node *p : params->children) { // Param nodes
                if (!p || p->type != "Param")
                  continue;
                Node *pty = p->child(1);
                m.paramTypes.push_back(parseTypeNode(pty));
              }
            }

            if (!st.declareLocal(m)) {
              errors.add(mid->lineno, "Duplicate method '" + m.name +
                                          "' in the same class scope");
            }

            // method scope
            st.enterScope(Scope::Kind::Method, m.name);

            // declare params as symbols in method scope
            if (params && params->type == "Params") {
              for (Node *p : params->children) {
                if (!p || p->type != "Param")
                  continue;
                Node *pid = p->child(0);
                Node *pty = p->child(1);
                if (!pid || pid->type != "Id")
                  continue;

                Symbol ps;
                ps.name = pid->value;
                ps.kind = SymbolKind::Param;
                ps.declaredLine = pid->lineno;
                ps.type = parseTypeNode(pty);

                if (!st.declareLocal(ps)) {
                  errors.add(pid->lineno, "Duplicate parameter '" + ps.name +
                                              "' in method '" + m.name + "'");
                }
              }
            }

            // method body (declares locals in nested block scopes)
            visitStmt(st, mbody, errors);

            st.exitScope(); // method
          }
        }
      }

      st.exitScope(); // class
    }
  }

  // --- Entry main() ---
  // Entry -> ReturnType("int"), StmtBlock
  if (entry && entry->type == "Entry") {
    Symbol mainSym;
    mainSym.name = "main";
    mainSym.kind = SymbolKind::Method;
    mainSym.declaredLine = entry->lineno;
    mainSym.returnType = Type::IntTy();

    if (!st.declareLocal(mainSym)) {
      errors.add(entry->lineno,
                 "Duplicate entry method 'main' in global scope");
    }

    st.enterScope(Scope::Kind::Method, "main");
    Node *body = entry->child(1); // StmtBlock
    visitStmt(st, body, errors);
    st.exitScope();
  }

  return st;
}
