#include "BytecodeEmitter.h"

#include <cstdlib>
#include <sstream>
#include <unordered_map>

namespace {

bool startsWith(const std::string &s, const std::string &p) {
  return s.size() >= p.size() && s.compare(0, p.size(), p) == 0;
}

bool isGlobalName(const std::string &s) { return startsWith(s, "@g::"); }

bool parseIntImm(const std::string &s, int &out) {
  if (!startsWith(s, "#I:"))
    return false;
  out = std::atoi(s.substr(3).c_str());
  return true;
}

bool parseFloatImm(const std::string &s, double &out) {
  if (!startsWith(s, "#F:"))
    return false;
  out = std::atof(s.substr(3).c_str());
  return true;
}

bool parseBoolImm(const std::string &s, int &out) {
  if (!startsWith(s, "#B:"))
    return false;
  std::string v = s.substr(3);
  out = (v == "true") ? 1 : 0;
  return true;
}

bool isNilImm(const std::string &s) { return s == "#N"; }

struct Fixup {
  int instrIndex;
  std::string label;
};

class Emitter {
public:
  Emitter(const IRProgram &ir, const CFGProgram &cfg) : ir_(ir), cfg_(cfg) {
    for (size_t i = 0; i < ir_.functions.size(); ++i)
      program_.functionIndex[ir_.functions[i].name] = static_cast<int>(i);
  }

  BytecodeProgram run() {
    if (cfg_.functions.size() != ir_.functions.size()) {
      program_.warnings.push_back("CFG/function count mismatch during bytecode emission");
    }

    const size_t limit =
        (cfg_.functions.size() < ir_.functions.size()) ? cfg_.functions.size()
                                                       : ir_.functions.size();
    for (size_t i = 0; i < limit; ++i)
      emitFunction(ir_.functions[i], cfg_.functions[i]);

    if (ir_.entryIndex >= 0 && ir_.entryIndex < static_cast<int>(program_.functions.size())) {
      program_.entryIndex = ir_.entryIndex;
    } else {
      std::unordered_map<std::string, int>::const_iterator it =
          program_.functionIndex.find("main");
      if (it != program_.functionIndex.end())
        program_.entryIndex = it->second;
    }

    return program_;
  }

private:
  const IRProgram &ir_;
  const CFGProgram &cfg_;
  BytecodeProgram program_;
  std::unordered_map<std::string, int> globalSlots_;

  int ensureGlobal(const std::string &name) {
    std::unordered_map<std::string, int>::const_iterator it = globalSlots_.find(name);
    if (it != globalSlots_.end())
      return it->second;

    int idx = static_cast<int>(program_.globalNames.size());
    program_.globalNames.push_back(name);
    globalSlots_[name] = idx;
    return idx;
  }

  int resolveCallee(const std::string &name) {
    std::unordered_map<std::string, int>::const_iterator it =
        program_.functionIndex.find(name);
    if (it != program_.functionIndex.end())
      return it->second;

    int found = -1;
    for (std::unordered_map<std::string, int>::const_iterator p =
             program_.functionIndex.begin();
         p != program_.functionIndex.end(); ++p) {
      const std::string &full = p->first;
      size_t dot = full.rfind('.');
      std::string shortName = (dot == std::string::npos) ? full : full.substr(dot + 1);
      if (shortName == name) {
        if (found != -1)
          return -2; // ambiguous
        found = p->second;
      }
    }
    return found;
  }

  void emitLoad(BytecodeFunction &out,
                std::unordered_map<std::string, int> &slots,
                const std::string &operand) {
    int iv = 0;
    double fv = 0.0;

    if (parseIntImm(operand, iv)) {
      BCInstr in;
      in.op = OpCode::PushInt;
      in.a = iv;
      out.code.push_back(in);
      return;
    }

    if (parseFloatImm(operand, fv)) {
      BCInstr in;
      in.op = OpCode::PushFloat;
      in.f = fv;
      out.code.push_back(in);
      return;
    }

    if (parseBoolImm(operand, iv)) {
      BCInstr in;
      in.op = OpCode::PushBool;
      in.a = iv;
      out.code.push_back(in);
      return;
    }

    if (isNilImm(operand)) {
      BCInstr in;
      in.op = OpCode::PushNil;
      out.code.push_back(in);
      return;
    }

    if (isGlobalName(operand)) {
      BCInstr in;
      in.op = OpCode::LoadGlobal;
      in.a = ensureGlobal(operand);
      out.code.push_back(in);
      return;
    }

    std::unordered_map<std::string, int>::const_iterator it = slots.find(operand);
    if (it == slots.end()) {
      int idx = static_cast<int>(slots.size());
      slots[operand] = idx;
      it = slots.find(operand);
    }

    BCInstr in;
    in.op = OpCode::LoadSlot;
    in.a = it->second;
    out.code.push_back(in);
  }

  void emitStore(BytecodeFunction &out,
                 std::unordered_map<std::string, int> &slots,
                 const std::string &target) {
    if (target.empty())
      return;

    if (isGlobalName(target)) {
      BCInstr in;
      in.op = OpCode::StoreGlobal;
      in.a = ensureGlobal(target);
      out.code.push_back(in);
      return;
    }

    std::unordered_map<std::string, int>::const_iterator it = slots.find(target);
    if (it == slots.end()) {
      int idx = static_cast<int>(slots.size());
      slots[target] = idx;
      it = slots.find(target);
    }

    BCInstr in;
    in.op = OpCode::StoreSlot;
    in.a = it->second;
    out.code.push_back(in);
  }

  OpCode mapBinOp(const std::string &op) {
    if (op == "+")
      return OpCode::Add;
    if (op == "-")
      return OpCode::Sub;
    if (op == "*")
      return OpCode::Mul;
    if (op == "/")
      return OpCode::Div;
    if (op == "^")
      return OpCode::Pow;
    if (op == "<")
      return OpCode::Lt;
    if (op == ">")
      return OpCode::Gt;
    if (op == "<=")
      return OpCode::Le;
    if (op == ">=")
      return OpCode::Ge;
    if (op == "==")
      return OpCode::Eq;
    if (op == "!=")
      return OpCode::Ne;
    if (op == "&&")
      return OpCode::And;
    if (op == "||")
      return OpCode::Or;
    return OpCode::Nop;
  }

  OpCode mapUnOp(const std::string &op) {
    if (op == "neg")
      return OpCode::Neg;
    if (op == "not")
      return OpCode::Not;
    return OpCode::Nop;
  }

  void emitOneInstr(const IRInstr &in, const std::string &fnName,
                    BytecodeFunction &out,
                    std::unordered_map<std::string, int> &slots,
                    std::unordered_map<std::string, int> &labels,
                    std::vector<Fixup> &fixups) {
    switch (in.kind) {
    case IRKind::Label:
      labels[in.a] = static_cast<int>(out.code.size());
      break;

    case IRKind::Assign:
      emitLoad(out, slots, in.a);
      emitStore(out, slots, in.dst);
      break;

    case IRKind::BinOp: {
      emitLoad(out, slots, in.a);
      emitLoad(out, slots, in.b);
      OpCode op = mapBinOp(in.op);
      if (op == OpCode::Nop) {
        program_.warnings.push_back("Unsupported binop '" + in.op + "' in function " +
                                    fnName);
        break;
      }
      BCInstr b;
      b.op = op;
      out.code.push_back(b);
      emitStore(out, slots, in.dst);
      break;
    }

    case IRKind::UnOp: {
      emitLoad(out, slots, in.a);
      OpCode op = mapUnOp(in.op);
      if (op == OpCode::Nop) {
        program_.warnings.push_back("Unsupported unop '" + in.op + "' in function " +
                                    fnName);
        break;
      }
      BCInstr b;
      b.op = op;
      out.code.push_back(b);
      emitStore(out, slots, in.dst);
      break;
    }

    case IRKind::Jump: {
      BCInstr b;
      b.op = OpCode::Jump;
      b.a = 0;
      out.code.push_back(b);
      fixups.push_back(Fixup{static_cast<int>(out.code.size()) - 1, in.a});
      break;
    }

    case IRKind::CJump: {
      emitLoad(out, slots, in.a);

      BCInstr jf;
      jf.op = OpCode::JumpFalse;
      jf.a = 0;
      out.code.push_back(jf);
      fixups.push_back(Fixup{static_cast<int>(out.code.size()) - 1, in.c});

      BCInstr jt;
      jt.op = OpCode::Jump;
      jt.a = 0;
      out.code.push_back(jt);
      fixups.push_back(Fixup{static_cast<int>(out.code.size()) - 1, in.b});
      break;
    }

    case IRKind::Print: {
      emitLoad(out, slots, in.a);
      BCInstr b;
      b.op = OpCode::Print;
      out.code.push_back(b);
      break;
    }

    case IRKind::Read: {
      BCInstr b;
      b.op = OpCode::Read;
      out.code.push_back(b);
      emitStore(out, slots, in.a);
      break;
    }

    case IRKind::Return: {
      emitLoad(out, slots, in.a.empty() ? "#N" : in.a);
      BCInstr b;
      b.op = OpCode::Ret;
      out.code.push_back(b);
      break;
    }

    case IRKind::Call: {
      for (size_t k = 0; k < in.args.size(); ++k)
        emitLoad(out, slots, in.args[k]);

      int callee = resolveCallee(in.op);
      if (callee == -2) {
        program_.warnings.push_back("Ambiguous call target '" + in.op +
                                    "' in function " + fnName);
        BCInstr p;
        p.op = OpCode::PushNil;
        out.code.push_back(p);
      } else if (callee < 0) {
        program_.warnings.push_back("Unknown call target '" + in.op +
                                    "' in function " + fnName);
        BCInstr p;
        p.op = OpCode::PushNil;
        out.code.push_back(p);
      } else {
        BCInstr b;
        b.op = OpCode::Call;
        b.a = callee;
        b.b = static_cast<int>(in.args.size());
        out.code.push_back(b);
      }

      emitStore(out, slots, in.dst);
      break;
    }

    case IRKind::NewObject: {
      BCInstr b;
      b.op = OpCode::NewObject;
      b.s = in.op;
      out.code.push_back(b);
      emitStore(out, slots, in.dst);
      break;
    }

    case IRKind::ArrayLit: {
      for (size_t k = 0; k < in.args.size(); ++k)
        emitLoad(out, slots, in.args[k]);

      BCInstr b;
      b.op = OpCode::MakeArray;
      b.a = static_cast<int>(in.args.size());
      out.code.push_back(b);
      emitStore(out, slots, in.dst);
      break;
    }

    case IRKind::ArrayGet: {
      emitLoad(out, slots, in.a);
      emitLoad(out, slots, in.b);
      BCInstr b;
      b.op = OpCode::ArrayGet;
      out.code.push_back(b);
      emitStore(out, slots, in.dst);
      break;
    }

    case IRKind::ArraySet: {
      emitLoad(out, slots, in.a);
      emitLoad(out, slots, in.b);
      emitLoad(out, slots, in.c);
      BCInstr b;
      b.op = OpCode::ArraySet;
      out.code.push_back(b);
      break;
    }

    case IRKind::ArrayLen: {
      emitLoad(out, slots, in.a);
      BCInstr b;
      b.op = OpCode::ArrayLen;
      out.code.push_back(b);
      emitStore(out, slots, in.dst);
      break;
    }

    case IRKind::FieldGet: {
      emitLoad(out, slots, in.a);
      BCInstr b;
      b.op = OpCode::GetField;
      b.s = in.op;
      out.code.push_back(b);
      emitStore(out, slots, in.dst);
      break;
    }

    case IRKind::FieldSet: {
      emitLoad(out, slots, in.a);
      emitLoad(out, slots, in.b);
      BCInstr b;
      b.op = OpCode::SetField;
      b.s = in.op;
      out.code.push_back(b);
      break;
    }

    case IRKind::Nop:
      break;
    }
  }

  void emitFunction(const IRFunction &fn, const FunctionCFG &cfg) {
    BytecodeFunction out;
    out.name = fn.name;

    std::unordered_map<std::string, int> slots;
    for (size_t i = 0; i < fn.params.size(); ++i) {
      slots[fn.params[i]] = static_cast<int>(i);
      out.paramCount++;
    }

    std::unordered_map<std::string, int> labels;
    std::vector<Fixup> fixups;

    for (size_t bi = 0; bi < cfg.blocks.size(); ++bi) {
      const BasicBlock &bb = cfg.blocks[bi];
      for (size_t ii = 0; ii < bb.instrIndices.size(); ++ii) {
        int irIndex = bb.instrIndices[ii];
        if (irIndex < 0 || irIndex >= static_cast<int>(fn.code.size())) {
          program_.warnings.push_back("Invalid IR index in CFG block for function " +
                                      fn.name);
          continue;
        }
        emitOneInstr(fn.code[irIndex], fn.name, out, slots, labels, fixups);
      }
    }

    for (size_t i = 0; i < fixups.size(); ++i) {
      std::unordered_map<std::string, int>::const_iterator it =
          labels.find(fixups[i].label);
      if (it == labels.end()) {
        program_.warnings.push_back("Unresolved label '" + fixups[i].label +
                                    "' in function " + fn.name);
        out.code[fixups[i].instrIndex].a = 0;
      } else {
        out.code[fixups[i].instrIndex].a = it->second;
      }
    }

    if (out.code.empty() || out.code.back().op != OpCode::Ret) {
      BCInstr p;
      p.op = OpCode::PushNil;
      out.code.push_back(p);
      BCInstr r;
      r.op = OpCode::Ret;
      out.code.push_back(r);
    }

    out.slotCount = static_cast<int>(slots.size());
    program_.functions.push_back(out);
  }
};

} // namespace

BytecodeProgram emitBytecode(const IRProgram &ir, const CFGProgram &cfg) {
  Emitter e(ir, cfg);
  return e.run();
}
