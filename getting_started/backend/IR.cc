#include "IR.h"

#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

namespace {

struct ClassInfo {
  std::unordered_set<std::string> fields;
  std::unordered_map<std::string, std::string> methodByShort;
};

struct LoopCtx {
  std::string breakLabel;
  std::string continueLabel;
};

class IRBuilder {
public:
  IRProgram run(Node *root) {
    root_ = root;
    collectMetadata();
    buildMethods();
    buildMain();
    return program_;
  }

private:
  Node *root_ = nullptr;
  IRProgram program_;

  std::unordered_map<std::string, ClassInfo> classes_;
  std::unordered_map<std::string, std::vector<std::string>> methodLookup_;
  std::unordered_set<std::string> globals_;

  IRFunction *fn_ = nullptr;
  std::string currentClass_;
  std::vector<std::unordered_map<std::string, std::string>> scopes_;
  std::vector<LoopCtx> loops_;
  int tempCounter_ = 0;
  int labelCounter_ = 0;
  bool sawReturn_ = false;

  static bool isNull(Node *n) { return n == nullptr; }

  void collectMetadata() {
    if (!root_ || root_->type != "Program")
      return;

    Node *globals = root_->child(0);
    if (globals && globals->type == "Globals") {
      for (Node *g : globals->children) {
        if (!g || g->type != "GlobalVar")
          continue;
        Node *vd = g->child(0);
        Node *id = vd ? vd->child(1) : nullptr;
        if (id && id->type == "Id")
          globals_.insert(id->value);
      }
    }

    Node *classes = root_->child(1);
    if (!classes || classes->type != "Classes")
      return;

    for (Node *cd : classes->children) {
      if (!cd || cd->type != "ClassDecl")
        continue;
      Node *id = cd->child(0);
      Node *body = cd->child(1);
      if (!id || id->type != "Id" || !body || body->type != "ClassBody")
        continue;

      std::string cname = id->value;
      ClassInfo &ci = classes_[cname];

      for (Node *mem : body->children) {
        if (!mem)
          continue;
        if (mem->type == "ClassVar") {
          Node *vd = mem->child(0);
          Node *fid = vd ? vd->child(1) : nullptr;
          if (fid && fid->type == "Id")
            ci.fields.insert(fid->value);
          continue;
        }

        if (mem->type == "MethodDecl") {
          Node *mid = mem->child(0);
          if (!mid || mid->type != "Id")
            continue;
          std::string full = cname + "." + mid->value;
          ci.methodByShort[mid->value] = full;
          methodLookup_[mid->value].push_back(full);
        }
      }
    }
  }

  void buildMethods() {
    if (!root_ || root_->type != "Program")
      return;

    Node *classes = root_->child(1);
    if (!classes || classes->type != "Classes")
      return;

    for (Node *cd : classes->children) {
      if (!cd || cd->type != "ClassDecl")
        continue;

      Node *cid = cd->child(0);
      Node *body = cd->child(1);
      if (!cid || cid->type != "Id" || !body || body->type != "ClassBody")
        continue;

      currentClass_ = cid->value;

      for (Node *mem : body->children) {
        if (!mem || mem->type != "MethodDecl")
          continue;
        buildMethod(mem);
      }

      currentClass_.clear();
    }
  }

  std::string parseReturnDefault(Node *rt) {
    if (!rt)
      return "#N";

    if (!rt->value.empty()) {
      if (rt->value == "void")
        return "#N";
      return "#I:0";
    }

    Node *child = rt->child(0);
    if (!child)
      return "#N";
    if (child->type == "Type" && child->value == "void")
      return "#N";
    return "#I:0";
  }

  void buildMethod(Node *method) {
    Node *id = method->child(0);
    Node *params = method->child(1);
    Node *rt = method->child(2);
    Node *body = method->child(3);
    if (!id || id->type != "Id" || !body)
      return;

    std::string fullName = currentClass_ + "." + id->value;

    std::vector<std::string> paramNames;
    paramNames.push_back("this");
    if (params && params->type == "Params") {
      for (Node *p : params->children) {
        if (!p || p->type != "Param")
          continue;
        Node *pid = p->child(0);
        if (pid && pid->type == "Id")
          paramNames.push_back(pid->value);
      }
    }

    beginFunction(fullName, paramNames);
    compileStmt(body);
    if (!sawReturn_)
      emit(IRKind::Return, "", parseReturnDefault(rt));
    endFunction();
  }

  void buildMain() {
    if (!root_ || root_->type != "Program")
      return;

    Node *entry = root_->child(2);
    if (!entry || entry->type != "Entry")
      return;

    beginFunction("main", std::vector<std::string>());
    program_.entryIndex = static_cast<int>(program_.functions.size()) - 1;

    Node *globals = root_->child(0);
    if (globals && globals->type == "Globals") {
      for (Node *g : globals->children) {
        if (!g || g->type != "GlobalVar")
          continue;
        Node *vd = g->child(0);
        if (vd)
          compileVarDecl(vd, true);
      }
    }

    compileStmt(entry->child(1));
    if (!sawReturn_)
      emit(IRKind::Return, "", "#I:0");
    endFunction();
  }

  void beginFunction(const std::string &name,
                     const std::vector<std::string> &params) {
    program_.functions.push_back(IRFunction());
    fn_ = &program_.functions.back();
    fn_->name = name;

    scopes_.clear();
    loops_.clear();
    tempCounter_ = 0;
    labelCounter_ = 0;
    sawReturn_ = false;

    pushScope();
    for (size_t i = 0; i < params.size(); ++i) {
      std::string unique = declareName(params[i]);
      fn_->params.push_back(unique);
    }
  }

  void endFunction() {
    popScope();
    fn_ = nullptr;
  }

  void pushScope() { scopes_.push_back(std::unordered_map<std::string, std::string>()); }

  void popScope() {
    if (!scopes_.empty())
      scopes_.pop_back();
  }

  std::string declareName(const std::string &name) {
    if (scopes_.empty())
      pushScope();

    std::string unique = name;
    int salt = 1;
    while (scopes_.back().find(unique) != scopes_.back().end()) {
      unique = name + "$" + std::to_string(salt++);
    }
    scopes_.back()[name] = unique;
    return unique;
  }

  std::string resolveName(const std::string &name) const {
    for (int i = static_cast<int>(scopes_.size()) - 1; i >= 0; --i) {
      std::unordered_map<std::string, std::string>::const_iterator it =
          scopes_[i].find(name);
      if (it != scopes_[i].end())
        return it->second;
    }
    return "";
  }

  bool currentClassHasField(const std::string &name) const {
    std::unordered_map<std::string, ClassInfo>::const_iterator it =
        classes_.find(currentClass_);
    if (it == classes_.end())
      return false;
    return it->second.fields.find(name) != it->second.fields.end();
  }

  std::string resolveCallable(const std::string &shortName) const {
    if (!currentClass_.empty()) {
      std::unordered_map<std::string, ClassInfo>::const_iterator ci =
          classes_.find(currentClass_);
      if (ci != classes_.end()) {
        std::unordered_map<std::string, std::string>::const_iterator own =
            ci->second.methodByShort.find(shortName);
        if (own != ci->second.methodByShort.end())
          return own->second;
      }
    }

    std::unordered_map<std::string, std::vector<std::string>>::const_iterator it =
        methodLookup_.find(shortName);
    if (it != methodLookup_.end() && it->second.size() == 1)
      return it->second.front();

    return shortName;
  }

  std::string newTemp() { return "_t" + std::to_string(tempCounter_++); }

  std::string newLabel(const std::string &base) {
    return base + "_" + std::to_string(labelCounter_++);
  }

  void emit(IRKind kind, const std::string &dst = "", const std::string &a = "",
            const std::string &b = "", const std::string &c = "",
            const std::string &op = "", const std::vector<std::string> &args =
                                          std::vector<std::string>()) {
    IRInstr in;
    in.kind = kind;
    in.dst = dst;
    in.a = a;
    in.b = b;
    in.c = c;
    in.op = op;
    in.args = args;
    fn_->code.push_back(in);
  }

  static bool isEmptyForCond(Node *n) { return n && n->type == "ForCondEmpty"; }

  void compileStmt(Node *s) {
    if (!s)
      return;

    if (s->type == "StmtBlock") {
      pushScope();
      Node *stmts = s->child(0);
      if (stmts && stmts->type == "Stmts") {
        for (Node *c : stmts->children)
          compileStmt(c);
      }
      popScope();
      return;
    }

    if (s->type == "VarStmt") {
      Node *vd = s->child(0);
      compileVarDecl(vd, false);
      return;
    }

    if (s->type == "AssignStmt") {
      std::string rhs = compileExpr(s->child(2));
      compileLValueAssign(s->child(0), rhs);
      return;
    }

    if (s->type == "ExprStmt") {
      (void)compileExpr(s->child(0));
      return;
    }

    if (s->type == "PrintStmt") {
      emit(IRKind::Print, "", compileExpr(s->child(0)));
      return;
    }

    if (s->type == "ReadStmt") {
      Node *target = s->child(0);
      if (!target)
        return;
      if (target->type == "Id") {
        std::string local = resolveName(target->value);
        if (!local.empty()) {
          emit(IRKind::Read, "", local);
          return;
        }
        if (globals_.find(target->value) != globals_.end()) {
          emit(IRKind::Read, "", "@g::" + target->value);
          return;
        }
      }

      std::string tmp = newTemp();
      emit(IRKind::Read, "", tmp);
      compileLValueAssign(target, tmp);
      return;
    }

    if (s->type == "ReturnStmt") {
      emit(IRKind::Return, "", compileExpr(s->child(0)));
      sawReturn_ = true;
      return;
    }

    if (s->type == "BreakStmt") {
      if (!loops_.empty())
        emit(IRKind::Jump, "", loops_.back().breakLabel);
      return;
    }

    if (s->type == "ContinueStmt") {
      if (!loops_.empty())
        emit(IRKind::Jump, "", loops_.back().continueLabel);
      return;
    }

    if (s->type == "IfStmt") {
      std::string cond = compileExpr(s->child(0));
      std::string lThen = newLabel("if_then");
      std::string lEnd = newLabel("if_end");
      emit(IRKind::CJump, "", cond, lThen, lEnd);
      emit(IRKind::Label, "", lThen);
      compileStmt(s->child(1));
      emit(IRKind::Label, "", lEnd);
      return;
    }

    if (s->type == "IfElseStmt") {
      std::string cond = compileExpr(s->child(0));
      std::string lThen = newLabel("if_then");
      std::string lElse = newLabel("if_else");
      std::string lEnd = newLabel("if_end");
      emit(IRKind::CJump, "", cond, lThen, lElse);

      emit(IRKind::Label, "", lThen);
      compileStmt(s->child(1));
      emit(IRKind::Jump, "", lEnd);

      emit(IRKind::Label, "", lElse);
      compileStmt(s->child(2));

      emit(IRKind::Label, "", lEnd);
      return;
    }

    if (s->type == "ForStmt") {
      pushScope();

      Node *init = s->child(0);
      if (init && init->type == "ForInitVar") {
        compileVarDecl(init->child(0), false);
      } else if (init && init->type == "ForInitAssign") {
        std::string rhs = compileExpr(init->child(2));
        compileLValueAssign(init->child(0), rhs);
      }

      std::string lCond = newLabel("for_cond");
      std::string lBody = newLabel("for_body");
      std::string lUpdate = newLabel("for_update");
      std::string lEnd = newLabel("for_end");

      emit(IRKind::Label, "", lCond);
      Node *cond = s->child(1);
      if (cond && !isEmptyForCond(cond)) {
        std::string c = compileExpr(cond);
        emit(IRKind::CJump, "", c, lBody, lEnd);
      } else {
        emit(IRKind::Jump, "", lBody);
      }

      emit(IRKind::Label, "", lBody);
      loops_.push_back(LoopCtx{lEnd, lUpdate});
      compileStmt(s->child(3));
      loops_.pop_back();

      emit(IRKind::Label, "", lUpdate);
      Node *upd = s->child(2);
      if (upd && upd->type == "Update") {
        std::string rhs = compileExpr(upd->child(2));
        compileLValueAssign(upd->child(0), rhs);
      }

      emit(IRKind::Jump, "", lCond);
      emit(IRKind::Label, "", lEnd);

      popScope();
      return;
    }
  }

  void compileVarDecl(Node *vd, bool forceGlobal) {
    if (!vd || vd->type != "VarDecl")
      return;

    Node *id = vd->child(1);
    Node *init = vd->child(3);
    if (!id || id->type != "Id")
      return;

    std::string sym;
    if (forceGlobal)
      sym = "@g::" + id->value;
    else
      sym = declareName(id->value);

    if (init && init->type == "Init") {
      std::string val = compileExpr(init->child(0));
      emit(IRKind::Assign, sym, val);
    }
  }

  std::string compileExpr(Node *e) {
    if (!e)
      return "#N";

    if (e->type == "Int")
      return "#I:" + e->value;
    if (e->type == "Float")
      return "#F:" + e->value;
    if (e->type == "Bool")
      return std::string("#B:") + (e->value == "true" ? "true" : "false");

    if (e->type == "Id")
      return compileIdExpr(e->value);

    if (e->type == "AddExpr" || e->type == "SubExpr" || e->type == "MulExpr" ||
        e->type == "DivExpr" || e->type == "PowExpr" || e->type == "LtExpr" ||
        e->type == "GtExpr" || e->type == "LeExpr" || e->type == "GeExpr" ||
        e->type == "EqExpr" || e->type == "NeExpr" || e->type == "AndExpr" ||
        e->type == "OrExpr") {
      std::string lhs = compileExpr(e->child(0));
      std::string rhs = compileExpr(e->child(1));
      std::string t = newTemp();
      emit(IRKind::BinOp, t, lhs, rhs, "", mapBinOp(e->type));
      return t;
    }

    if (e->type == "NegExpr" || e->type == "NotExpr") {
      std::string x = compileExpr(e->child(0));
      std::string t = newTemp();
      emit(IRKind::UnOp, t, x, "", "", mapUnOp(e->type));
      return t;
    }

    if (e->type == "ArrayLiteral") {
      Node *args = e->child(1);
      std::vector<std::string> vals;
      if (args && args->type == "Args") {
        for (Node *a : args->children)
          vals.push_back(compileExpr(a));
      }
      std::string t = newTemp();
      emit(IRKind::ArrayLit, t, "", "", "", "", vals);
      return t;
    }

    if (e->type == "IndexExpr") {
      std::string arr = compileExpr(e->child(0));
      std::string idx = compileExpr(e->child(1));
      std::string t = newTemp();
      emit(IRKind::ArrayGet, t, arr, idx);
      return t;
    }

    if (e->type == "LengthExpr") {
      std::string arr = compileExpr(e->child(0));
      std::string t = newTemp();
      emit(IRKind::ArrayLen, t, arr);
      return t;
    }

    if (e->type == "FieldExpr") {
      std::string obj = compileExpr(e->child(0));
      Node *fid = e->child(1);
      std::string field = (fid && fid->type == "Id") ? fid->value : "";
      std::string t = newTemp();
      emit(IRKind::FieldGet, t, obj, "", "", field);
      return t;
    }

    if (e->type == "CallExpr")
      return compileCallExpr(e);

    std::string last = "#N";
    for (Node *c : e->children)
      last = compileExpr(c);
    return last;
  }

  std::string compileCallExpr(Node *e) {
    Node *callee = e->child(0);
    Node *argsNode = e->child(1);

    std::vector<std::string> args;
    if (argsNode && argsNode->type == "Args") {
      for (Node *a : argsNode->children)
        args.push_back(compileExpr(a));
    }

    if (!callee)
      return "#N";

    if (callee->type == "Id") {
      std::string name = callee->value;

      if (classes_.find(name) != classes_.end()) {
        std::string t = newTemp();
        emit(IRKind::NewObject, t, "", "", "", name);
        return t;
      }

      if (!currentClass_.empty()) {
        std::unordered_map<std::string, ClassInfo>::const_iterator it =
            classes_.find(currentClass_);
        if (it != classes_.end() &&
            it->second.methodByShort.find(name) != it->second.methodByShort.end()) {
          std::string thisSym = resolveName("this");
          if (!thisSym.empty())
            args.insert(args.begin(), thisSym);
        }
      }

      std::string t = newTemp();
      emit(IRKind::Call, t, "", "", "", resolveCallable(name), args);
      return t;
    }

    if (callee->type == "FieldExpr") {
      Node *objExpr = callee->child(0);
      Node *mid = callee->child(1);
      std::string obj = compileExpr(objExpr);
      std::string method = (mid && mid->type == "Id") ? mid->value : "";

      std::vector<std::string> callArgs;
      callArgs.push_back(obj);
      callArgs.insert(callArgs.end(), args.begin(), args.end());

      std::string t = newTemp();
      emit(IRKind::Call, t, "", "", "", resolveCallable(method), callArgs);
      return t;
    }

    return "#N";
  }

  std::string compileIdExpr(const std::string &name) {
    std::string local = resolveName(name);
    if (!local.empty())
      return local;

    if (globals_.find(name) != globals_.end())
      return "@g::" + name;

    if (currentClassHasField(name)) {
      std::string self = resolveName("this");
      if (!self.empty()) {
        std::string t = newTemp();
        emit(IRKind::FieldGet, t, self, "", "", name);
        return t;
      }
    }

    return name;
  }

  void compileLValueAssign(Node *lhs, const std::string &rhs) {
    if (!lhs)
      return;

    if (lhs->type == "Id") {
      std::string local = resolveName(lhs->value);
      if (!local.empty()) {
        emit(IRKind::Assign, local, rhs);
        return;
      }

      if (globals_.find(lhs->value) != globals_.end()) {
        emit(IRKind::Assign, "@g::" + lhs->value, rhs);
        return;
      }

      if (currentClassHasField(lhs->value)) {
        std::string self = resolveName("this");
        if (!self.empty()) {
          emit(IRKind::FieldSet, "", self, rhs, "", lhs->value);
          return;
        }
      }

      emit(IRKind::Assign, lhs->value, rhs);
      return;
    }

    if (lhs->type == "IndexExpr") {
      std::string arr = compileExpr(lhs->child(0));
      std::string idx = compileExpr(lhs->child(1));
      emit(IRKind::ArraySet, "", arr, idx, rhs);
      return;
    }

    if (lhs->type == "FieldExpr") {
      std::string obj = compileExpr(lhs->child(0));
      Node *fid = lhs->child(1);
      std::string field = (fid && fid->type == "Id") ? fid->value : "";
      emit(IRKind::FieldSet, "", obj, rhs, "", field);
      return;
    }
  }

  static std::string mapBinOp(const std::string &type) {
    if (type == "AddExpr")
      return "+";
    if (type == "SubExpr")
      return "-";
    if (type == "MulExpr")
      return "*";
    if (type == "DivExpr")
      return "/";
    if (type == "PowExpr")
      return "^";
    if (type == "LtExpr")
      return "<";
    if (type == "GtExpr")
      return ">";
    if (type == "LeExpr")
      return "<=";
    if (type == "GeExpr")
      return ">=";
    if (type == "EqExpr")
      return "==";
    if (type == "NeExpr")
      return "!=";
    if (type == "AndExpr")
      return "&&";
    if (type == "OrExpr")
      return "||";
    return "?";
  }

  static std::string mapUnOp(const std::string &type) {
    if (type == "NegExpr")
      return "neg";
    if (type == "NotExpr")
      return "not";
    return "?";
  }
};

} // namespace

IRProgram buildIR(Node *root) {
  IRBuilder b;
  return b.run(root);
}

std::string irInstrToString(const IRInstr &in) {
  std::ostringstream os;
  switch (in.kind) {
  case IRKind::Label:
    os << in.a << ":";
    break;
  case IRKind::Assign:
    os << in.dst << " = " << in.a;
    break;
  case IRKind::BinOp:
    os << in.dst << " = " << in.a << " " << in.op << " " << in.b;
    break;
  case IRKind::UnOp:
    os << in.dst << " = " << in.op << " " << in.a;
    break;
  case IRKind::Jump:
    os << "jmp " << in.a;
    break;
  case IRKind::CJump:
    os << "cjmp " << in.a << " ? " << in.b << " : " << in.c;
    break;
  case IRKind::Print:
    os << "print " << in.a;
    break;
  case IRKind::Read:
    os << "read " << in.a;
    break;
  case IRKind::Return:
    os << "ret " << in.a;
    break;
  case IRKind::Call: {
    os << in.dst << " = call " << in.op << "(";
    for (size_t i = 0; i < in.args.size(); ++i) {
      if (i)
        os << ", ";
      os << in.args[i];
    }
    os << ")";
    break;
  }
  case IRKind::NewObject:
    os << in.dst << " = new " << in.op;
    break;
  case IRKind::ArrayLit:
    os << in.dst << " = [";
    for (size_t i = 0; i < in.args.size(); ++i) {
      if (i)
        os << ", ";
      os << in.args[i];
    }
    os << "]";
    break;
  case IRKind::ArrayGet:
    os << in.dst << " = " << in.a << "[" << in.b << "]";
    break;
  case IRKind::ArraySet:
    os << in.a << "[" << in.b << "] = " << in.c;
    break;
  case IRKind::ArrayLen:
    os << in.dst << " = len " << in.a;
    break;
  case IRKind::FieldGet:
    os << in.dst << " = " << in.a << "." << in.op;
    break;
  case IRKind::FieldSet:
    os << in.a << "." << in.op << " = " << in.b;
    break;
  case IRKind::Nop:
    os << "nop";
    break;
  }
  return os.str();
}

std::string dumpIR(const IRProgram &prog) {
  std::ostringstream os;
  for (size_t i = 0; i < prog.functions.size(); ++i) {
    const IRFunction &fn = prog.functions[i];
    os << "function " << fn.name << "(";
    for (size_t p = 0; p < fn.params.size(); ++p) {
      if (p)
        os << ", ";
      os << fn.params[p];
    }
    os << ")\n";
    for (size_t j = 0; j < fn.code.size(); ++j)
      os << "  " << j << ": " << irInstrToString(fn.code[j]) << "\n";
    os << "\n";
  }

  if (!prog.warnings.empty()) {
    os << "warnings:\n";
    for (size_t i = 0; i < prog.warnings.size(); ++i)
      os << "  - " << prog.warnings[i] << "\n";
  }

  return os.str();
}
