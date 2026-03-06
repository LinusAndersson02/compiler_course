#ifndef BYTECODE_EMITTER_H
#define BYTECODE_EMITTER_H

#include "Bytecode.h"
#include "IR.h"

BytecodeProgram emitBytecode(const IRProgram &ir);

#endif
