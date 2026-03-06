#ifndef IR_H
#define IR_H

#include "../frontend/Node.h"

#include <string>
#include <vector>

enum class IRKind {
  Label,
  Assign,
  BinOp,
  UnOp,
  Jump,
  CJump,
  Print,
  Read,
  Return,
  Call,
  NewObject,
  ArrayLit,
  ArrayGet,
  ArraySet,
  ArrayLen,
  FieldGet,
  FieldSet,
  Nop
};

struct IRInstr {
  IRKind kind = IRKind::Nop;
  std::string dst;
  std::string a;
  std::string b;
  std::string c;
  std::string op;
  std::vector<std::string> args;
};

struct IRFunction {
  std::string name;
  std::vector<std::string> params;
  std::vector<IRInstr> code;
};

struct IRProgram {
  std::vector<IRFunction> functions;
  int entryIndex = -1;
  std::vector<std::string> warnings;
};

IRProgram buildIR(Node *root);
std::string irInstrToString(const IRInstr &in);
std::string dumpIR(const IRProgram &prog);

#endif
