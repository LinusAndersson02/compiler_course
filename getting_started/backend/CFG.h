#ifndef CFG_H
#define CFG_H

#include "IR.h"

#include <string>
#include <vector>

struct BasicBlock {
  int id = -1;
  int start = 0;
  int end = -1;
  std::vector<int> instrIndices;
  std::vector<int> successors;
};

struct FunctionCFG {
  std::string functionName;
  std::vector<BasicBlock> blocks;
};

struct CFGProgram {
  std::vector<FunctionCFG> functions;
};

CFGProgram buildCFG(const IRProgram &ir);

#endif
