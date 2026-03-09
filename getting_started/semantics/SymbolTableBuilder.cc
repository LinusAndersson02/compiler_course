#include "../Passes.h"

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

  // User-defined type names map to class types.
  if (n->type == "TypeName") {
    return Type::ClassTy(n->value);
  }

  // `void` is represented as a Type node with value "void".
  if (n->type == "Type" && n->value == "void") {
    return Type::VoidTy();
  }

  // Primitive type, optionally marked as an array.
  if (n->type == "Type") {
    Node *base = n->child(0);
    Node *arr = n->child(1);

    Type b = parseBaseType(base);
    if (!arr)
      return b;

    if (arr->type == "Array" && arr->value == "true") {
      return Type::ArrayOf(b);
    }
    return b;
  }

  // Some AST shapes provide BaseType directly.
  if (n->type == "BaseType") {
    return parseBaseType(n);
  }

  return Type::UnknownTy();
}

static Type parseReturnType(Node *rt) {
  if (!rt)
    return Type::UnknownTy();

  // Entry nodes store return type directly in ReturnType.value.
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

  // Methods store ReturnType as a child type node.
  Node *t = rt->child(0);
  return parseTypeNode(t);
}

// Statement traversal used while collecting declarations in pass 1.
static void visitStmt(SymbolTable &st, Node *stmt, ErrorReporter &errors);

// Insert one VarDecl into the current scope and report duplicates.
static void declareVarDecl(SymbolTable &st, Node *varDecl, SymbolKind kind,
                           ErrorReporter &errors) {
  if (!varDecl || varDecl->type != "VarDecl")
    return;

  Node *volNode = varDecl->child(0);
  Node *idNode = varDecl->child(1);
  Node *tyNode = varDecl->child(2);

  if (!idNode || idNode->type != "Id")
    return;

  Symbol sym;
  sym.name = idNode->value;
  sym.kind = kind;
  sym.declaredLine = idNode->lineno;
  sym.isVolatile = (volNode && volNode->value == "true");
  sym.type = parseTypeNode(tyNode);

  if (st.existsInChain(sym.name)) {
    errors.add(idNode->lineno,
               "Redeclaration of identifier '" + sym.name +
                   "' in the same or enclosing scope");
    return;
  }

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

  // Blocks own their own declaration scope.
  if (stmt->type == "StmtBlock") {
    st.enterScope(Scope::Kind::Block, "block");
    Node *stmts = stmt->child(0);
    visitStmtList(st, stmts, errors);
    st.exitScope();
    return;
  }

  // Variable statements add one local symbol to the current scope.
  if (stmt->type == "VarStmt") {
    Node *varDecl = stmt->child(0);
    declareVarDecl(st, varDecl, SymbolKind::Var, errors);
    return;
  }

  // Branch statements can contain nested declarations in their bodies.
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

  // `for` introduces a scope so init declarations are loop-local.
  if (stmt->type == "ForStmt") {
    st.enterScope(Scope::Kind::For, "for");

    Node *init = stmt->child(0);
    if (init && init->type == "ForInitVar") {
      Node *varDecl = init->child(0);
      declareVarDecl(st, varDecl, SymbolKind::Var, errors);
    }

    Node *body = stmt->child(3);
    visitStmt(st, body, errors);

    st.exitScope();
    return;
  }

  // Other statements do not introduce declarations in pass 1.
}

SymbolTable buildSymbolTable(Node *root, ErrorReporter &errors) {
  SymbolTable st;
  if (!root)
    return st;

  // Expected AST shape: Program -> Globals, Classes, Entry.
  Node *globals = root->child(0);
  Node *classes = root->child(1);
  Node *entry = root->child(2);

  // Global declarations are inserted in the root scope.
  if (globals && globals->type == "Globals") {
    for (Node *gv : globals->children) {
      if (!gv || gv->type != "GlobalVar")
        continue;
      Node *varDecl = gv->child(0);
      declareVarDecl(st, varDecl, SymbolKind::Var, errors);
    }
  }

  // Classes are declared in the root scope; members go in class scopes.
  if (classes && classes->type == "Classes") {
    for (Node *cd : classes->children) {
      if (!cd || cd->type != "ClassDecl")
        continue;

      Node *classId = cd->child(0);
      Node *body = cd->child(1);
      if (!classId || classId->type != "Id")
        continue;

      // Register class symbol in global scope.
      {
        Symbol cls;
        cls.name = classId->value;
        cls.kind = SymbolKind::Class;
        cls.declaredLine = classId->lineno;
        cls.type = Type::ClassTy(cls.name);

        if (st.existsInChain(cls.name) || !st.declareLocal(cls)) {
          errors.add(classId->lineno,
                     "Duplicate class '" + cls.name + "' in global scope");
        }
      }

      // Collect class members inside a dedicated class scope.
      st.enterScope(Scope::Kind::Class, classId->value);

      if (body && body->type == "ClassBody") {
        for (Node *mem : body->children) {
          if (!mem)
            continue;

          // Field declaration.
          if (mem->type == "ClassVar") {
            Node *varDecl = mem->child(0);
            declareVarDecl(st, varDecl, SymbolKind::Field, errors);
            continue;
          }

          // Method declaration plus its parameter list and body scope.
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

            // Store parameter types on the method symbol for call checking.
            if (params && params->type == "Params") {
              for (Node *p : params->children) {
                if (!p || p->type != "Param")
                  continue;
                Node *pty = p->child(1);
                m.paramTypes.push_back(parseTypeNode(pty));
              }
            }

            if (st.existsInChain(m.name)) {
              errors.add(mid->lineno,
                         "Redeclaration of identifier '" + m.name +
                             "' in the same or enclosing scope");
            } else if (!st.declareLocal(m)) {
              errors.add(mid->lineno, "Duplicate method '" + m.name +
                                          "' in the same class scope");
            }

            // Enter method-local scope.
            st.enterScope(Scope::Kind::Method, m.name);

            // Parameters are local symbols in the method scope.
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

                if (st.existsInChain(ps.name)) {
                  errors.add(pid->lineno,
                             "Redeclaration of identifier '" + ps.name +
                                 "' in the same or enclosing scope");
                } else if (!st.declareLocal(ps)) {
                  errors.add(pid->lineno, "Duplicate parameter '" + ps.name +
                                              "' in method '" + m.name + "'");
                }
              }
            }

            // Walk the body to collect nested local declarations.
            visitStmt(st, mbody, errors);

            st.exitScope();
          }
        }
      }

      st.exitScope();
    }
  }

  // Entry `main` is represented as a method symbol with its own scope.
  if (entry && entry->type == "Entry") {
    Symbol mainSym;
    mainSym.name = "main";
    mainSym.kind = SymbolKind::Method;
    mainSym.declaredLine = entry->lineno;
    mainSym.returnType = Type::IntTy();

    if (st.existsInChain(mainSym.name) || !st.declareLocal(mainSym)) {
      errors.add(entry->lineno,
                 "Duplicate entry method 'main' in global scope");
    }

    st.enterScope(Scope::Kind::Method, "main");
    Node *body = entry->child(1);
    visitStmt(st, body, errors);
    st.exitScope();
  }

  return st;
}
