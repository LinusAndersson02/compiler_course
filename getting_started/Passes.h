#ifndef PASSES_H
#define PASSES_H

#include "Node.h"
#include "ErrorReporter.h"
#include "SymbolTable.h"

SymbolTable buildSymbolTable(Node* root, ErrorReporter& errors);
void semanticAnalyze(Node* root, const SymbolTable& st, ErrorReporter& errors);

#endif
