#ifndef BYTECODE_H
#define BYTECODE_H

#include <string>
#include <unordered_map>
#include <vector>

enum class OpCode {
  Nop,
  PushInt,
  PushFloat,
  PushBool,
  PushNil,
  LoadSlot,
  StoreSlot,
  LoadGlobal,
  StoreGlobal,
  Add,
  Sub,
  Mul,
  Div,
  Pow,
  Lt,
  Gt,
  Le,
  Ge,
  Eq,
  Ne,
  And,
  Or,
  Not,
  Neg,
  Jump,
  JumpFalse,
  Print,
  Read,
  Call,
  Ret,
  Halt,
  MakeArray,
  ArrayGet,
  ArraySet,
  ArrayLen,
  NewObject,
  GetField,
  SetField
};

struct BCInstr {
  OpCode op = OpCode::Nop;
  int a = 0;
  int b = 0;
  double f = 0.0;
  std::string s;
};

struct BytecodeFunction {
  std::string name;
  int paramCount = 0;
  int slotCount = 0;
  std::vector<BCInstr> code;
};

struct BytecodeProgram {
  std::vector<BytecodeFunction> functions;
  std::unordered_map<std::string, int> functionIndex;
  std::vector<std::string> globalNames;
  int entryIndex = -1;
  std::vector<std::string> warnings;
};

std::string opcodeName(OpCode op);
std::string disassembleBytecode(const BytecodeProgram &prog);

#endif
