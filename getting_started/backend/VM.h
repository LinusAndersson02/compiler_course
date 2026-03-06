#ifndef VM_H
#define VM_H

#include "Bytecode.h"

#include <string>

struct VMResult {
  int exitCode = 0;
  std::string error;
};

VMResult runBytecode(const BytecodeProgram &program);

#endif
