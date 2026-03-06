#include "backend/Bytecode.h"
#include "backend/BytecodeEmitter.h"
#include "backend/BytecodeIO.h"
#include "backend/CFG.h"
#include "backend/DotCFGPrinter.h"
#include "ErrorReporter.h"
#include "backend/IR.h"
#include "Passes.h"
#include "backend/VM.h"
#include "parser.tab.hh"

#include <fstream>
#include <iostream>
#include <string>

extern Node *root;
extern FILE *yyin;
extern int yylineno;
extern int lexical_errors;
extern yy::parser::symbol_type yylex();

enum errCodes {
  SUCCESS = 0,
  LEXICAL_ERROR = 1,
  SYNTAX_ERROR = 2,
  AST_ERROR = 3,
  SEMANTIC_ERROR = 4,
  VM_ERROR = 5,
  SEGMENTATION_FAULT = 139
};

int errCode = errCodes::SUCCESS;

void yy::parser::error(std::string const &err) {
  if (!lexical_errors) {
    std::cerr << "Syntax errors found! See the logs below:" << std::endl;
    std::cerr << "\t@error at line " << yylineno
              << ". Cannot generate a syntax for this input:" << err.c_str()
              << std::endl;
    std::cerr << "End of syntax errors!" << std::endl;
    errCode = errCodes::SYNTAX_ERROR;
  }
}

int main(int argc, char **argv) {
  bool flagAst = false;
  bool flagDumpIr = false;
  bool flagDumpBytecode = false;
  bool flagEmitBC = false;
  bool flagNoVm = false;
  std::string bcOutPath = "program.bc";
  std::string inputPath;

  for (int i = 1; i < argc; ++i) {
    std::string a = argv[i];
    if (a == "--ast") {
      flagAst = true;
    } else if (a == "--ir") {
      flagDumpIr = true;
    } else if (a == "--bytecode") {
      flagDumpBytecode = true;
    } else if (a == "--emit-bc") {
      if (i + 1 >= argc) {
        std::cerr << "--emit-bc expects a path\n";
        return 1;
      }
      flagEmitBC = true;
      bcOutPath = argv[++i];
    } else if (a == "--no-vm") {
      flagNoVm = true;
    } else if (a.size() > 0 && a[0] == '-') {
      std::cerr << "Unknown flag: " << a << "\n";
      return 1;
    } else if (inputPath.empty()) {
      inputPath = a;
    } else {
      std::cerr << "Only one input file is supported\n";
      return 1;
    }
  }

  if (!inputPath.empty()) {
    if (!(yyin = fopen(inputPath.c_str(), "r"))) {
      perror(inputPath.c_str());
      return 1;
    }
  }

  if (USE_LEX_ONLY) {
    yylex();
    return lexical_errors ? errCodes::LEXICAL_ERROR : errCodes::SUCCESS;
  }

  yy::parser parser;
  bool parseSuccess = !parser.parse();

  if (lexical_errors)
    errCode = errCodes::LEXICAL_ERROR;

  if (parseSuccess && !lexical_errors) {
    if (flagAst) {
      bool astOk = false;
      try {
        root->print_tree();
        root->generate_tree();
        astOk = true;
      } catch (...) {
        errCode = errCodes::AST_ERROR;
      }
      if (!astOk)
        return errCode;
    }

    ErrorReporter semErrors;
    SymbolTable st = buildSymbolTable(root, semErrors);
    semanticAnalyze(root, st, semErrors);

    if (semErrors.hasErrors()) {
      semErrors.print(std::cerr);
      errCode = errCodes::SEMANTIC_ERROR;
      return errCode;
    }

    IRProgram ir = buildIR(root);
    if (flagDumpIr) {
      std::ofstream irOut("ir.txt");
      irOut << dumpIR(ir);
    }

    CFGProgram cfg = buildCFG(ir);
    writeCFGDotFiles(cfg, ir, ".");

    BytecodeProgram bc = emitBytecode(ir);

    if (flagDumpBytecode) {
      std::ofstream bcOut("bytecode.txt");
      bcOut << disassembleBytecode(bc);
    }

    if (flagEmitBC) {
      std::string ioErr;
      if (!saveBytecode(bc, bcOutPath, ioErr)) {
        std::cerr << "Bytecode write error: " << ioErr << "\n";
        return 1;
      }
    }

    if (!ir.warnings.empty()) {
      for (size_t i = 0; i < ir.warnings.size(); ++i)
        std::cerr << "IR warning: " << ir.warnings[i] << "\n";
    }

    if (!bc.warnings.empty()) {
      for (size_t i = 0; i < bc.warnings.size(); ++i)
        std::cerr << "Bytecode warning: " << bc.warnings[i] << "\n";
    }

    if (!flagNoVm) {
      VMResult res = runBytecode(bc);
      if (!res.error.empty()) {
        errCode = errCodes::VM_ERROR;
      } else {
        errCode = res.exitCode;
      }
    }
  }

  return errCode;
}
