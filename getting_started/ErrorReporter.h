#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct SemanticError {
  int line;
  string message;
};

class ErrorReporter {
private:
  vector<SemanticError> errors;

public:
  void add(int line, const string &msg) { errors.push_back({line, msg}); }

  void add(const string &msg) {
    // If no line number available, use -1
    errors.push_back({-1, msg});
  }

  bool hasErrors() const { return !errors.empty(); }

  size_t count() const { return errors.size(); }

  void print(ostream &os) const {
    for (const auto &e : errors) {
      if (e.line >= 0) {
        os << "[line " << e.line << "] " << e.message << "\n";
      } else {
        os << e.message << "\n";
      }
    }
  }
};

#endif
