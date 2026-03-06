#include "BytecodeIO.h"
#include "VM.h"

#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string input = "program.bc";
  if (argc > 1)
    input = argv[1];

  BytecodeProgram prog;
  std::string err;
  if (!loadBytecode(input, prog, err)) {
    std::cerr << "Failed to load bytecode: " << err << "\n";
    return 1;
  }

  VMResult res = runBytecode(prog);
  if (!res.error.empty())
    return 1;
  return res.exitCode;
}
