#ifndef DOT_CFG_PRINTER_H
#define DOT_CFG_PRINTER_H

#include "CFG.h"

#include <string>
#include <vector>

std::vector<std::string> writeCFGDotFiles(const CFGProgram &cfg,
                                          const IRProgram &ir,
                                          const std::string &outDir);

#endif
