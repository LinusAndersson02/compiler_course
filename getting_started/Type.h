#ifndef TYPE_H
#define TYPE_H

#include <memory>
#include <sstream>
#include <string>

struct Type {
  enum class Kind { Int, Float, Bool, Void, Class, Array, Error, Unknown };

  Kind kind = Kind::Unknown;

  // For Kind::Class
  std::string className;

  // For Kind::Array
  std::shared_ptr<Type> elem;

  // --- Constructors / factories ---
  static Type IntTy() {
    Type t;
    t.kind = Kind::Int;
    return t;
  }
  static Type FloatTy() {
    Type t;
    t.kind = Kind::Float;
    return t;
  }
  static Type BoolTy() {
    Type t;
    t.kind = Kind::Bool;
    return t;
  }
  static Type VoidTy() {
    Type t;
    t.kind = Kind::Void;
    return t;
  }
  static Type ErrorTy() {
    Type t;
    t.kind = Kind::Error;
    return t;
  }
  static Type UnknownTy() {
    Type t;
    t.kind = Kind::Unknown;
    return t;
  }

  static Type ClassTy(const std::string &name) {
    Type t;
    t.kind = Kind::Class;
    t.className = name;
    return t;
  }

  static Type ArrayOf(const Type &base) {
    Type t;
    t.kind = Kind::Array;
    t.elem = std::make_shared<Type>(base);
    return t;
  }

  // --- Predicates ---
  bool isNumeric() const { return kind == Kind::Int || kind == Kind::Float; }
  bool isBool() const { return kind == Kind::Bool; }
  bool isVoid() const { return kind == Kind::Void; }
  bool isArray() const { return kind == Kind::Array; }
  bool isClass() const { return kind == Kind::Class; }
  bool isError() const { return kind == Kind::Error; }
  bool isUnknown() const { return kind == Kind::Unknown; }

  // For arrays; caller must ensure isArray()
  const Type &base() const { return *elem; }

  std::string str() const {
    switch (kind) {
    case Kind::Int:
      return "int";
    case Kind::Float:
      return "float";
    case Kind::Bool:
      return "boolean";
    case Kind::Void:
      return "void";
    case Kind::Class:
      return className;
    case Kind::Array:
      return elem ? (elem->str() + "[]") : "<?>[]";
    case Kind::Error:
      return "<error>";
    case Kind::Unknown:
      return "<unknown>";
    }
    return "<unknown>";
  }
};

inline bool operator==(const Type &a, const Type &b) {
  if (a.kind != b.kind)
    return false;
  switch (a.kind) {
  case Type::Kind::Int:
  case Type::Kind::Float:
  case Type::Kind::Bool:
  case Type::Kind::Void:
  case Type::Kind::Error:
  case Type::Kind::Unknown:
    return true;
  case Type::Kind::Class:
    return a.className == b.className;
  case Type::Kind::Array:
    if (!a.elem || !b.elem)
      return a.elem == b.elem;
    return *a.elem == *b.elem;
  }
  return false;
}

inline bool operator!=(const Type &a, const Type &b) { return !(a == b); }

#endif
