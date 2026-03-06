#include "Bytecode.h"

#include <sstream>

std::string opcodeName(OpCode op) {
  switch (op) {
  case OpCode::Nop:
    return "NOP";
  case OpCode::PushInt:
    return "PUSH_I";
  case OpCode::PushFloat:
    return "PUSH_F";
  case OpCode::PushBool:
    return "PUSH_B";
  case OpCode::PushNil:
    return "PUSH_N";
  case OpCode::LoadSlot:
    return "LOAD";
  case OpCode::StoreSlot:
    return "STORE";
  case OpCode::LoadGlobal:
    return "LOAD_G";
  case OpCode::StoreGlobal:
    return "STORE_G";
  case OpCode::Add:
    return "ADD";
  case OpCode::Sub:
    return "SUB";
  case OpCode::Mul:
    return "MUL";
  case OpCode::Div:
    return "DIV";
  case OpCode::Pow:
    return "POW";
  case OpCode::Lt:
    return "LT";
  case OpCode::Gt:
    return "GT";
  case OpCode::Le:
    return "LE";
  case OpCode::Ge:
    return "GE";
  case OpCode::Eq:
    return "EQ";
  case OpCode::Ne:
    return "NE";
  case OpCode::And:
    return "AND";
  case OpCode::Or:
    return "OR";
  case OpCode::Not:
    return "NOT";
  case OpCode::Neg:
    return "NEG";
  case OpCode::Jump:
    return "JMP";
  case OpCode::JumpFalse:
    return "JMP_F";
  case OpCode::Print:
    return "PRINT";
  case OpCode::Read:
    return "READ";
  case OpCode::Call:
    return "CALL";
  case OpCode::Ret:
    return "RET";
  case OpCode::Halt:
    return "HALT";
  case OpCode::MakeArray:
    return "ARR_MK";
  case OpCode::ArrayGet:
    return "ARR_GET";
  case OpCode::ArraySet:
    return "ARR_SET";
  case OpCode::ArrayLen:
    return "ARR_LEN";
  case OpCode::NewObject:
    return "NEW_OBJ";
  case OpCode::GetField:
    return "GET_F";
  case OpCode::SetField:
    return "SET_F";
  }
  return "?";
}

std::string disassembleBytecode(const BytecodeProgram &prog) {
  std::ostringstream os;

  os << "entry=" << prog.entryIndex << "\n";
  if (!prog.globalNames.empty()) {
    os << "globals:\n";
    for (size_t i = 0; i < prog.globalNames.size(); ++i)
      os << "  [" << i << "] " << prog.globalNames[i] << "\n";
  }

  for (size_t fi = 0; fi < prog.functions.size(); ++fi) {
    const BytecodeFunction &fn = prog.functions[fi];
    os << "\nfn " << fi << " " << fn.name << " params=" << fn.paramCount
       << " slots=" << fn.slotCount << "\n";
    for (size_t i = 0; i < fn.code.size(); ++i) {
      const BCInstr &in = fn.code[i];
      os << "  " << i << ": " << opcodeName(in.op);

      switch (in.op) {
      case OpCode::PushInt:
      case OpCode::PushBool:
      case OpCode::LoadSlot:
      case OpCode::StoreSlot:
      case OpCode::LoadGlobal:
      case OpCode::StoreGlobal:
      case OpCode::Jump:
      case OpCode::JumpFalse:
      case OpCode::Read:
      case OpCode::ArrayLen:
      case OpCode::MakeArray:
      case OpCode::Call:
        os << " " << in.a;
        if (in.op == OpCode::Call)
          os << " " << in.b;
        break;
      case OpCode::PushFloat:
        os << " " << in.f;
        break;
      case OpCode::NewObject:
      case OpCode::GetField:
      case OpCode::SetField:
        os << " " << in.s;
        break;
      default:
        break;
      }

      os << "\n";
    }
  }

  if (!prog.warnings.empty()) {
    os << "\nwarnings:\n";
    for (size_t i = 0; i < prog.warnings.size(); ++i)
      os << "  - " << prog.warnings[i] << "\n";
  }

  return os.str();
}
