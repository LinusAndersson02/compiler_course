#include "BytecodeIO.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace {

std::string hex2(unsigned char c) {
  const char *k = "0123456789ABCDEF";
  std::string out;
  out.push_back(k[(c >> 4) & 0xF]);
  out.push_back(k[c & 0xF]);
  return out;
}

int fromHex(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'f')
    return 10 + (c - 'a');
  if (c >= 'A' && c <= 'F')
    return 10 + (c - 'A');
  return -1;
}

std::string encode(const std::string &s) {
  std::string out;
  for (size_t i = 0; i < s.size(); ++i) {
    unsigned char c = static_cast<unsigned char>(s[i]);
    if (std::isalnum(c) || c == '_' || c == '.' || c == ':' || c == '@' || c == '$') {
      out.push_back(static_cast<char>(c));
    } else {
      out.push_back('%');
      out += hex2(c);
    }
  }
  if (out.empty())
    return "-";
  return out;
}

bool decode(const std::string &s, std::string &out) {
  if (s == "-") {
    out.clear();
    return true;
  }

  out.clear();
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] != '%') {
      out.push_back(s[i]);
      continue;
    }
    if (i + 2 >= s.size())
      return false;
    int hi = fromHex(s[i + 1]);
    int lo = fromHex(s[i + 2]);
    if (hi < 0 || lo < 0)
      return false;
    out.push_back(static_cast<char>((hi << 4) | lo));
    i += 2;
  }
  return true;
}

} // namespace

bool saveBytecode(const BytecodeProgram &prog, const std::string &path,
                  std::string &err) {
  std::ofstream os(path.c_str());
  if (!os) {
    err = "failed to open output file: " + path;
    return false;
  }

  os << "BC1\n";
  os << "ENTRY " << prog.entryIndex << "\n";
  os << "GLOBALS " << prog.globalNames.size() << "\n";
  for (size_t i = 0; i < prog.globalNames.size(); ++i)
    os << "G " << encode(prog.globalNames[i]) << "\n";

  os << "FUNCS " << prog.functions.size() << "\n";
  for (size_t fi = 0; fi < prog.functions.size(); ++fi) {
    const BytecodeFunction &fn = prog.functions[fi];
    os << "FUNC " << encode(fn.name) << " " << fn.paramCount << " "
       << fn.slotCount << " " << fn.code.size() << "\n";

    for (size_t i = 0; i < fn.code.size(); ++i) {
      const BCInstr &in = fn.code[i];
      os << "I " << static_cast<int>(in.op) << " " << in.a << " " << in.b
         << " " << std::setprecision(17) << in.f << " " << encode(in.s)
         << "\n";
    }
  }

  if (!os.good()) {
    err = "failed while writing bytecode file: " + path;
    return false;
  }

  return true;
}

bool loadBytecode(const std::string &path, BytecodeProgram &prog,
                  std::string &err) {
  std::ifstream is(path.c_str());
  if (!is) {
    err = "failed to open bytecode file: " + path;
    return false;
  }

  prog = BytecodeProgram();

  std::string tok;
  if (!(is >> tok) || tok != "BC1") {
    err = "invalid bytecode magic";
    return false;
  }

  if (!(is >> tok) || tok != "ENTRY") {
    err = "missing ENTRY section";
    return false;
  }
  if (!(is >> prog.entryIndex)) {
    err = "invalid ENTRY value";
    return false;
  }

  if (!(is >> tok) || tok != "GLOBALS") {
    err = "missing GLOBALS section";
    return false;
  }

  int gcount = 0;
  if (!(is >> gcount) || gcount < 0) {
    err = "invalid GLOBALS count";
    return false;
  }

  for (int i = 0; i < gcount; ++i) {
    std::string enc;
    if (!(is >> tok) || tok != "G" || !(is >> enc)) {
      err = "invalid global entry";
      return false;
    }
    std::string dec;
    if (!decode(enc, dec)) {
      err = "invalid escaped global name";
      return false;
    }
    prog.globalNames.push_back(dec);
  }

  if (!(is >> tok) || tok != "FUNCS") {
    err = "missing FUNCS section";
    return false;
  }

  int fcount = 0;
  if (!(is >> fcount) || fcount < 0) {
    err = "invalid FUNCS count";
    return false;
  }

  for (int fi = 0; fi < fcount; ++fi) {
    std::string encName;
    int paramCount = 0;
    int slotCount = 0;
    int icount = 0;

    if (!(is >> tok) || tok != "FUNC" || !(is >> encName) ||
        !(is >> paramCount) || !(is >> slotCount) || !(is >> icount)) {
      err = "invalid FUNC header";
      return false;
    }

    std::string fnName;
    if (!decode(encName, fnName)) {
      err = "invalid escaped function name";
      return false;
    }

    if (paramCount < 0 || slotCount < 0 || icount < 0) {
      err = "negative counts in FUNC header";
      return false;
    }

    BytecodeFunction fn;
    fn.name = fnName;
    fn.paramCount = paramCount;
    fn.slotCount = slotCount;
    fn.code.reserve(icount);

    for (int i = 0; i < icount; ++i) {
      int op = 0;
      BCInstr in;
      std::string encStr;
      if (!(is >> tok) || tok != "I" || !(is >> op) || !(is >> in.a) ||
          !(is >> in.b) || !(is >> in.f) || !(is >> encStr)) {
        err = "invalid instruction entry";
        return false;
      }

      std::string s;
      if (!decode(encStr, s)) {
        err = "invalid escaped instruction string";
        return false;
      }

      in.op = static_cast<OpCode>(op);
      in.s = s;
      fn.code.push_back(in);
    }

    int idx = static_cast<int>(prog.functions.size());
    prog.functionIndex[fn.name] = idx;
    prog.functions.push_back(fn);
  }

  if (prog.entryIndex < 0 || prog.entryIndex >= static_cast<int>(prog.functions.size())) {
    err = "entry function index out of range";
    return false;
  }

  return true;
}
