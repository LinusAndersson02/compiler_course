#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Type.h"

enum class SymbolKind { Class, Field, Method, Var, Param };

inline const char *symbolKindToString(SymbolKind k) {
  switch (k) {
  case SymbolKind::Class:
    return "class";
  case SymbolKind::Field:
    return "field";
  case SymbolKind::Method:
    return "method";
  case SymbolKind::Var:
    return "var";
  case SymbolKind::Param:
    return "param";
  }
  return "?";
}

struct Symbol {
  std::string name;
  SymbolKind kind = SymbolKind::Var;

  // For vars/fields/params: the symbol's type
  Type type = Type::UnknownTy();

  // For methods:
  Type returnType = Type::UnknownTy();
  std::vector<Type> paramTypes;

  // Extra metadata (useful later)
  bool isVolatile = false;
  int declaredLine = -1;
};

struct Scope {
  enum class Kind { Global, Class, Method, Block, For };

  Kind kind = Kind::Block;
  std::string label; // e.g., class name or method name for debugging

  Scope *parent = nullptr;

  std::unordered_map<std::string, Symbol> symbols;
  std::vector<std::unique_ptr<Scope>> children;
};

inline const char *scopeKindToString(Scope::Kind k) {
  switch (k) {
  case Scope::Kind::Global:
    return "global";
  case Scope::Kind::Class:
    return "class";
  case Scope::Kind::Method:
    return "method";
  case Scope::Kind::Block:
    return "block";
  case Scope::Kind::For:
    return "for";
  }
  return "?";
}

class SymbolTable {
private:
  std::unique_ptr<Scope> root_;
  Scope *current_ = nullptr;

  void printScope(std::ostream &os, const Scope *s, int depth) const {
    for (int i = 0; i < depth; i++)
      os << "  ";
    os << "[" << scopeKindToString(s->kind) << "]";
    if (!s->label.empty())
      os << " " << s->label;
    os << "\n";

    for (const auto &kv : s->symbols) {
      const Symbol &sym = kv.second;
      for (int i = 0; i < depth + 1; i++)
        os << "  ";
      os << sym.name << " : " << symbolKindToString(sym.kind);

      if (sym.kind == SymbolKind::Method) {
        os << " -> " << sym.returnType.str() << " (";
        for (size_t i = 0; i < sym.paramTypes.size(); i++) {
          if (i)
            os << ", ";
          os << sym.paramTypes[i].str();
        }
        os << ")";
      } else {
        os << " -> " << sym.type.str();
        if (sym.isVolatile)
          os << " volatile";
      }

      if (sym.declaredLine >= 0)
        os << " @line " << sym.declaredLine;
      os << "\n";
    }

    for (const auto &child : s->children) {
      printScope(os, child.get(), depth + 1);
    }
  }

public:
  SymbolTable() {
    root_ = std::make_unique<Scope>();
    root_->kind = Scope::Kind::Global;
    root_->label = "Program";
    root_->parent = nullptr;
    current_ = root_.get();
  }

  Scope *current() const { return current_; }
  Scope *root() const { return root_.get(); }

  Scope *enterScope(Scope::Kind kind, const std::string &label = "") {
    auto child = std::make_unique<Scope>();
    child->kind = kind;
    child->label = label;
    child->parent = current_;

    Scope *raw = child.get();
    current_->children.push_back(std::move(child));
    current_ = raw;
    return current_;
  }

  void exitScope() {
    if (current_ && current_->parent)
      current_ = current_->parent;
  }

  bool declareLocal(const Symbol &sym) {
    auto [it, inserted] = current_->symbols.emplace(sym.name, sym);
    return inserted;
  }

  Symbol *lookupLocal(const std::string &name) {
    auto it = current_->symbols.find(name);
    if (it == current_->symbols.end())
      return nullptr;
    return &it->second;
  }

  Symbol *lookup(const std::string &name) {
    for (Scope *s = current_; s != nullptr; s = s->parent) {
      auto it = s->symbols.find(name);
      if (it != s->symbols.end())
        return &it->second;
    }
    return nullptr;
  }

  bool existsInChain(const std::string &name) const {
    for (Scope *s = current_; s != nullptr; s = s->parent) {
      if (s->symbols.find(name) != s->symbols.end())
        return true;
    }
    return false;
  }

  void print(std::ostream &os) const { printScope(os, root_.get(), 0); }
};

#endif
