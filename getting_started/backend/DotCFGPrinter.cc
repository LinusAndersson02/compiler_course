#include "DotCFGPrinter.h"

#include <fstream>

namespace {

std::string escapeDot(const std::string &s) {
  std::string out;
  out.reserve(s.size() + 8);
  for (size_t i = 0; i < s.size(); ++i) {
    char c = s[i];
    if (c == '\\' || c == '"')
      out.push_back('\\');
    out.push_back(c);
  }
  return out;
}

std::string sanitize(const std::string &s) {
  std::string out;
  out.reserve(s.size());
  for (size_t i = 0; i < s.size(); ++i) {
    char c = s[i];
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '_') {
      out.push_back(c);
    } else {
      out.push_back('_');
    }
  }
  if (out.empty())
    out = "fn";
  return out;
}

} // namespace

std::vector<std::string> writeCFGDotFiles(const CFGProgram &cfg,
                                          const IRProgram &ir,
                                          const std::string &outDir) {
  std::vector<std::string> files;

  for (size_t fi = 0; fi < cfg.functions.size() && fi < ir.functions.size(); ++fi) {
    const FunctionCFG &fcfg = cfg.functions[fi];
    const IRFunction &fn = ir.functions[fi];

    std::string file = outDir + "/cfg_" + sanitize(fcfg.functionName) + ".dot";
    std::ofstream os(file.c_str());
    if (!os)
      continue;

    os << "digraph CFG_" << sanitize(fcfg.functionName) << " {\n";
    os << "  node [shape=box, fontname=\"monospace\"];\n";

    for (size_t bi = 0; bi < fcfg.blocks.size(); ++bi) {
      const BasicBlock &bb = fcfg.blocks[bi];
      os << "  bb" << bb.id << " [label=\"BB" << bb.id << ":\\l";
      for (size_t ii = 0; ii < bb.instrIndices.size(); ++ii) {
        int idx = bb.instrIndices[ii];
        if (idx < 0 || idx >= static_cast<int>(fn.code.size()))
          continue;
        std::string line = irInstrToString(fn.code[idx]);
        os << escapeDot(line) << "\\l";
      }
      os << "\"];\n";
    }

    for (size_t bi = 0; bi < fcfg.blocks.size(); ++bi) {
      const BasicBlock &bb = fcfg.blocks[bi];
      for (size_t si = 0; si < bb.successors.size(); ++si)
        os << "  bb" << bb.id << " -> bb" << bb.successors[si] << ";\n";
    }

    os << "}\n";
    files.push_back(file);
  }

  return files;
}
