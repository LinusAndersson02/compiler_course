#ifndef BYTECODE_EMITTER_H
#define BYTECODE_EMITTER_H

#include "Bytecode.h"
#include "CFG.h"
#include "IR.h"

BytecodeProgram emitBytecode(const IRProgram &ir, const CFGProgram &cfg);

#endif
