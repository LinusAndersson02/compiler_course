#include "CFG.h"

#include <algorithm>
#include <set>
#include <unordered_map>

namespace {

static bool isTerminator(const IRInstr &in) {
  return in.kind == IRKind::Jump || in.kind == IRKind::CJump ||
         in.kind == IRKind::Return;
}

} // namespace

CFGProgram buildCFG(const IRProgram &ir) {
  CFGProgram out;

  for (size_t fi = 0; fi < ir.functions.size(); ++fi) {
    const IRFunction &fn = ir.functions[fi];
    FunctionCFG cfg;
    cfg.functionName = fn.name;

    const int n = static_cast<int>(fn.code.size());
    if (n == 0) {
      out.functions.push_back(cfg);
      continue;
    }

    std::set<int> leaderSet;
    leaderSet.insert(0);

    for (int i = 0; i < n; ++i) {
      const IRInstr &in = fn.code[i];
      if (in.kind == IRKind::Label)
        leaderSet.insert(i);
      if (isTerminator(in) && i + 1 < n)
        leaderSet.insert(i + 1);
    }

    std::vector<int> leaders(leaderSet.begin(), leaderSet.end());

    for (size_t bi = 0; bi < leaders.size(); ++bi) {
      int start = leaders[bi];
      int end = (bi + 1 < leaders.size()) ? (leaders[bi + 1] - 1) : (n - 1);

      BasicBlock bb;
      bb.id = static_cast<int>(bi);
      bb.start = start;
      bb.end = end;

      for (int i = start; i <= end; ++i)
        bb.instrIndices.push_back(i);

      cfg.blocks.push_back(bb);
    }

    std::unordered_map<std::string, int> labelToBlock;
    for (size_t bi = 0; bi < cfg.blocks.size(); ++bi) {
      const BasicBlock &bb = cfg.blocks[bi];
      for (size_t k = 0; k < bb.instrIndices.size(); ++k) {
        int idx = bb.instrIndices[k];
        const IRInstr &in = fn.code[idx];
        if (in.kind == IRKind::Label)
          labelToBlock[in.a] = bb.id;
      }
    }

    for (size_t bi = 0; bi < cfg.blocks.size(); ++bi) {
      BasicBlock &bb = cfg.blocks[bi];
      if (bb.instrIndices.empty()) {
        if (bi + 1 < cfg.blocks.size())
          bb.successors.push_back(static_cast<int>(bi + 1));
        continue;
      }

      const IRInstr &last = fn.code[bb.instrIndices.back()];
      if (last.kind == IRKind::Jump) {
        std::unordered_map<std::string, int>::const_iterator it =
            labelToBlock.find(last.a);
        if (it != labelToBlock.end())
          bb.successors.push_back(it->second);
      } else if (last.kind == IRKind::CJump) {
        std::unordered_map<std::string, int>::const_iterator t =
            labelToBlock.find(last.b);
        std::unordered_map<std::string, int>::const_iterator f =
            labelToBlock.find(last.c);
        if (t != labelToBlock.end())
          bb.successors.push_back(t->second);
        if (f != labelToBlock.end() && (t == labelToBlock.end() || f->second != t->second))
          bb.successors.push_back(f->second);
      } else if (last.kind == IRKind::Return) {
        // no successor
      } else {
        if (bi + 1 < cfg.blocks.size())
          bb.successors.push_back(static_cast<int>(bi + 1));
      }
    }

    out.functions.push_back(cfg);
  }

  return out;
}
