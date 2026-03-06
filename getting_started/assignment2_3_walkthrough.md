# Assignment 2 and 3 Walkthrough

This document explains how the current implementation completes Assignment 2 (symbol table + semantic analysis) and Assignment 3 Option 1 (IR + CFG + bytecode + interpreter).

## Build and Run

Build both programs:

```bash
make
make interpreter
```

Run compiler directly on source:

```bash
./compiler < test_files/valid/test1.cpm
```

Generate bytecode file without executing VM in compiler:

```bash
./compiler --emit-bc program.bc --no-vm < test_files/valid/test1.cpm
```

Run standalone interpreter from serialized bytecode:

```bash
./interpreter program.bc
```

---

## Assignment 2: Symbol Table + Semantic Analysis

### 1. Symbol Table Construction (Pass 1)

Implemented in `SymbolTableBuilder.cc`.

What it does:
- Walks AST declarations left-to-right.
- Creates nested scopes for:
  - global program scope
  - class scope
  - method scope
  - block scope
  - `for` scope
- Inserts symbols for:
  - classes
  - methods
  - fields
  - parameters
  - local variables
- Detects duplicate declarations in the same scope.

Key data structures:
- `Symbol`, `Scope`, `SymbolTable` in `SymbolTable.h`.
- Type model in `Type.h`.

### 2. Semantic Analysis (Pass 2)

Implemented in `SemanticAnalyzer.cc`.

What it does (minimum requirements and practical checks):
- Traverses statements/expressions in scope order.
- Verifies identifier usage (declared-before-use).
- Keeps reporting multiple errors instead of stopping at first error.
- Handles method/field access in expressions/calls by class-member lookup.
- Rejects plain method/class names used as value expressions.

Important implementation pieces:
- `ScopeCursor` tracks semantic traversal against symbol-table scope tree.
- `lookupInChain` resolves symbols in parent chain.
- `lookupClassMember` resolves members on class type receivers.
- `checkExpr` has dedicated logic for `CallExpr` and `FieldExpr`.

### 3. Minimum Requirement Coverage (Assignment 2)

Minimum required in assignment PDF:
- Correct symbol table construction
- Detect duplicate identifiers in same scope
- Detect undeclared identifier usage

Current code satisfies those.

---

## Assignment 3 Option 1: IR + CFG + Bytecode + Interpreter

### 1. IR Generation from AST

Implemented in `IR.h` and `IR.cc`.

What it does:
- Converts AST into TAC-like IR instructions.
- Builds function IR for:
  - `main`
  - each class method (`ClassName.methodName`)
- Lowers control flow (`if`, `if-else`, `for`, `break`, `continue`) with labels/jumps.
- Lowers expressions (binary/unary ops, calls, arrays, fields, returns, I/O).

### 2. Basic Blocks and CFG

Implemented in `CFG.h`, `CFG.cc`, `DotCFGPrinter.h`, `DotCFGPrinter.cc`.

What it does:
- Splits IR into basic blocks using leaders.
- Builds CFG successor edges from terminators.
- Writes Graphviz `.dot` files (`cfg_<function>.dot`).

### 3. Bytecode Generation

Implemented in `Bytecode.h`, `Bytecode.cc`, `BytecodeEmitter.h`, `BytecodeEmitter.cc`.

What it does:
- Translates IR instructions to custom stack-based bytecode.
- Patches jump targets from labels.
- Supports globals, locals, arithmetic, comparisons, control-flow, calls, arrays, objects/fields, print/read, return.

### 4. Serialized Bytecode File I/O

Implemented in `BytecodeIO.h` and `BytecodeIO.cc`.

What it does:
- Saves bytecode program to file (`BC1` format).
- Loads bytecode back into runtime program structure.

### 5. Interpreter (Standalone Program)

Runtime VM in `VM.h` and `VM.cc`.
Standalone executable entry in `interpreter_main.cc`.

What it does:
- Parses/deserializes bytecode file.
- Maintains:
  - data stack
  - activation stack (call frames)
- Executes sequentially with jumps/calls/returns.
- Handles runtime errors cleanly.

### 6. Compiler Pipeline Wiring

Orchestrated in `main.cc`:
- Parse
- Build symbol table
- Semantic analysis
- Build IR
- Build CFG + emit dot
- Emit bytecode
- Optionally serialize bytecode (`--emit-bc`)
- Optionally run VM (default unless `--no-vm`)

Make targets in `Makefile`:
- `make` -> builds `compiler`
- `make interpreter` -> builds `interpreter`

### 7. Minimum Requirement Coverage (Assignment 3, Option 1)

Minimum required in assignment PDF:
- IR generation for all valid C+- programs
- Pretty-printed CFG
- Working bytecode generation and interpreter for simple program (`test1.cpm`)

Current code satisfies these:
- Valid set (`test1.cpm` ... `test8.cpm`) passes semantic + IR path with `--no-vm`.
- CFG `.dot` files are produced.
- `test1.cpm` executes correctly (prints `508.5`) both direct and via standalone interpreter.

---

## Quick Demo Script

```bash
make && make interpreter

# Assignment 2 style check
./compiler --no-vm test_files/semantic_errors/DuplicateIdentifier.cpm

# Assignment 3 IR/CFG and standalone interpreter flow
./compiler --emit-bc program.bc --no-vm < test_files/valid/test1.cpm
./interpreter program.bc
```

Expected runtime output for test1:

```text
508.5
```
