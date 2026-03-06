CXXFLAGS = -g -w -std=c++14 -I. -Ibackend -Ifrontend

compiler: lex.yy.c parser.tab.o main.cc semantics/SymbolTableBuilder.cc semantics/SemanticAnalyzer.cc backend/IR.cc backend/CFG.cc backend/DotCFGPrinter.cc backend/Bytecode.cc backend/BytecodeEmitter.cc backend/BytecodeIO.cc backend/VM.cc
		g++ $(CXXFLAGS) -ocompiler parser.tab.o lex.yy.c main.cc semantics/SymbolTableBuilder.cc semantics/SemanticAnalyzer.cc backend/IR.cc backend/CFG.cc backend/DotCFGPrinter.cc backend/Bytecode.cc backend/BytecodeEmitter.cc backend/BytecodeIO.cc backend/VM.cc
interpreter: backend/interpreter_main.cc backend/Bytecode.cc backend/BytecodeIO.cc backend/VM.cc
		g++ $(CXXFLAGS) -ointerpreter backend/interpreter_main.cc backend/Bytecode.cc backend/BytecodeIO.cc backend/VM.cc
parser.tab.o: parser.tab.cc
		g++ $(CXXFLAGS) -c parser.tab.cc
parser.tab.cc: frontend/parser.yy
		bison -o parser.tab.cc --defines=parser.tab.hh frontend/parser.yy
lex.yy.c: frontend/lexer.flex parser.tab.cc
		flex -olex.yy.c frontend/lexer.flex
tree: 
		 dot -Tpdf tree.dot -otree.pdf
clean:
		rm -f parser.tab.* lex.yy.c* compiler interpreter stack.hh position.hh location.hh tree.dot tree.pdf ir.txt bytecode.txt cfg_*.dot program.bc
