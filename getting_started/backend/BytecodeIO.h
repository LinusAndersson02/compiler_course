#ifndef BYTECODE_IO_H
#define BYTECODE_IO_H

#include "Bytecode.h"

#include <string>

bool saveBytecode(const BytecodeProgram &prog, const std::string &path,
                  std::string &err);
bool loadBytecode(const std::string &path, BytecodeProgram &prog,
                  std::string &err);

#endif
