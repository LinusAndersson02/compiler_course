#include "VM.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace {

struct Object;

struct Value {
  enum class Kind { Int, Float, Bool, Array, Object, Nil } kind;
  long long i;
  double f;
  bool b;
  std::shared_ptr<std::vector<Value> > arr;
  std::shared_ptr<Object> obj;

  Value() : kind(Kind::Nil), i(0), f(0.0), b(false) {}

  static Value Int(long long v) {
    Value x;
    x.kind = Kind::Int;
    x.i = v;
    return x;
  }

  static Value Float(double v) {
    Value x;
    x.kind = Kind::Float;
    x.f = v;
    return x;
  }

  static Value Bool(bool v) {
    Value x;
    x.kind = Kind::Bool;
    x.b = v;
    return x;
  }

  static Value Array(const std::shared_ptr<std::vector<Value> > &v) {
    Value x;
    x.kind = Kind::Array;
    x.arr = v;
    return x;
  }

  static Value Obj(const std::shared_ptr<Object> &v) {
    Value x;
    x.kind = Kind::Object;
    x.obj = v;
    return x;
  }

  static Value Nil() { return Value(); }
};

struct Object {
  std::string className;
  std::unordered_map<std::string, Value> fields;
};

struct Frame {
  int func = -1;
  int pc = 0;
  std::vector<Value> slots;
};

static bool truthy(const Value &v) {
  switch (v.kind) {
  case Value::Kind::Bool:
    return v.b;
  case Value::Kind::Int:
    return v.i != 0;
  case Value::Kind::Float:
    return v.f != 0.0;
  case Value::Kind::Array:
  case Value::Kind::Object:
    return true;
  case Value::Kind::Nil:
    return false;
  }
  return false;
}

static bool asNumber(const Value &v, double &out, bool &isFloat) {
  switch (v.kind) {
  case Value::Kind::Int:
    out = static_cast<double>(v.i);
    isFloat = false;
    return true;
  case Value::Kind::Float:
    out = v.f;
    isFloat = true;
    return true;
  case Value::Kind::Bool:
    out = v.b ? 1.0 : 0.0;
    isFloat = false;
    return true;
  default:
    return false;
  }
}

static std::string toString(const Value &v) {
  std::ostringstream os;
  switch (v.kind) {
  case Value::Kind::Int:
    os << v.i;
    return os.str();
  case Value::Kind::Float: {
    os << std::setprecision(15) << v.f;
    std::string s = os.str();
    if (s.find('.') != std::string::npos) {
      while (!s.empty() && s.back() == '0')
        s.pop_back();
      if (!s.empty() && s.back() == '.')
        s.push_back('0');
    }
    return s;
  }
  case Value::Kind::Bool:
    return v.b ? "true" : "false";
  case Value::Kind::Array:
    return "<array>";
  case Value::Kind::Object:
    return "<object " + (v.obj ? v.obj->className : std::string("?")) + ">";
  case Value::Kind::Nil:
    return "nil";
  }
  return "nil";
}

static bool popValue(std::vector<Value> &stack, Value &out) {
  if (stack.empty())
    return false;
  out = stack.back();
  stack.pop_back();
  return true;
}

static Value parseInputToken(const std::string &tok) {
  if (tok == "true")
    return Value::Bool(true);
  if (tok == "false")
    return Value::Bool(false);

  bool hasDot = false;
  bool hasExp = false;
  for (size_t i = 0; i < tok.size(); ++i) {
    if (tok[i] == '.')
      hasDot = true;
    if (tok[i] == 'e' || tok[i] == 'E')
      hasExp = true;
  }

  if (hasDot || hasExp)
    return Value::Float(std::atof(tok.c_str()));
  return Value::Int(std::atoll(tok.c_str()));
}

static VMResult vmError(const std::string &msg) {
  VMResult r;
  r.exitCode = 1;
  r.error = msg;
  std::cerr << "VM error: " << msg << "\n";
  return r;
}

} // namespace

VMResult runBytecode(const BytecodeProgram &program) {
  if (program.entryIndex < 0 || program.entryIndex >= static_cast<int>(program.functions.size()))
    return vmError("missing entry function");

  std::vector<Value> stack;
  std::vector<Frame> callStack;
  std::vector<Value> globals(program.globalNames.size(), Value::Nil());

  Frame entry;
  entry.func = program.entryIndex;
  entry.pc = 0;
  entry.slots.resize(program.functions[program.entryIndex].slotCount, Value::Nil());
  callStack.push_back(entry);

  while (!callStack.empty()) {
    Frame &fr = callStack.back();
    if (fr.func < 0 || fr.func >= static_cast<int>(program.functions.size()))
      return vmError("invalid frame function index");

    const BytecodeFunction &fn = program.functions[fr.func];
    if (fr.pc < 0 || fr.pc >= static_cast<int>(fn.code.size()))
      return vmError("program counter out of range in function " + fn.name);

    const BCInstr &in = fn.code[fr.pc++];

    switch (in.op) {
    case OpCode::Nop:
      break;

    case OpCode::PushInt:
      stack.push_back(Value::Int(in.a));
      break;

    case OpCode::PushFloat:
      stack.push_back(Value::Float(in.f));
      break;

    case OpCode::PushBool:
      stack.push_back(Value::Bool(in.a != 0));
      break;

    case OpCode::PushNil:
      stack.push_back(Value::Nil());
      break;

    case OpCode::LoadSlot:
      if (in.a < 0 || in.a >= static_cast<int>(fr.slots.size()))
        return vmError("LOAD slot out of range");
      stack.push_back(fr.slots[in.a]);
      break;

    case OpCode::StoreSlot: {
      if (in.a < 0 || in.a >= static_cast<int>(fr.slots.size()))
        return vmError("STORE slot out of range");
      Value v;
      if (!popValue(stack, v))
        return vmError("stack underflow on STORE");
      fr.slots[in.a] = v;
      break;
    }

    case OpCode::LoadGlobal:
      if (in.a < 0 || in.a >= static_cast<int>(globals.size()))
        return vmError("LOAD_G index out of range");
      stack.push_back(globals[in.a]);
      break;

    case OpCode::StoreGlobal: {
      if (in.a < 0 || in.a >= static_cast<int>(globals.size()))
        return vmError("STORE_G index out of range");
      Value v;
      if (!popValue(stack, v))
        return vmError("stack underflow on STORE_G");
      globals[in.a] = v;
      break;
    }

    case OpCode::Add:
    case OpCode::Sub:
    case OpCode::Mul:
    case OpCode::Div:
    case OpCode::Pow: {
      Value b, a;
      if (!popValue(stack, b) || !popValue(stack, a))
        return vmError("stack underflow on arithmetic op");

      double da = 0.0, db = 0.0;
      bool af = false, bf = false;
      if (!asNumber(a, da, af) || !asNumber(b, db, bf))
        return vmError("non-numeric operand in arithmetic op");

      if (in.op == OpCode::Div && db == 0.0)
        return vmError("division by zero");

      double dr = 0.0;
      if (in.op == OpCode::Add)
        dr = da + db;
      else if (in.op == OpCode::Sub)
        dr = da - db;
      else if (in.op == OpCode::Mul)
        dr = da * db;
      else if (in.op == OpCode::Div)
        dr = da / db;
      else if (in.op == OpCode::Pow)
        dr = std::pow(da, db);

      if (!af && !bf && in.op != OpCode::Div)
        stack.push_back(Value::Int(static_cast<long long>(dr)));
      else
        stack.push_back(Value::Float(dr));

      break;
    }

    case OpCode::Lt:
    case OpCode::Gt:
    case OpCode::Le:
    case OpCode::Ge:
    case OpCode::Eq:
    case OpCode::Ne: {
      Value b, a;
      if (!popValue(stack, b) || !popValue(stack, a))
        return vmError("stack underflow on comparison op");

      bool result = false;
      if (in.op == OpCode::Eq || in.op == OpCode::Ne) {
        if ((a.kind == Value::Kind::Int || a.kind == Value::Kind::Float ||
             a.kind == Value::Kind::Bool) &&
            (b.kind == Value::Kind::Int || b.kind == Value::Kind::Float ||
             b.kind == Value::Kind::Bool)) {
          double da = 0.0, db = 0.0;
          bool af = false, bf = false;
          asNumber(a, da, af);
          asNumber(b, db, bf);
          result = (da == db);
        } else if (a.kind == Value::Kind::Nil && b.kind == Value::Kind::Nil) {
          result = true;
        } else if (a.kind == Value::Kind::Array && b.kind == Value::Kind::Array) {
          result = a.arr == b.arr;
        } else if (a.kind == Value::Kind::Object && b.kind == Value::Kind::Object) {
          result = a.obj == b.obj;
        } else if (a.kind == Value::Kind::Bool && b.kind == Value::Kind::Bool) {
          result = a.b == b.b;
        } else {
          result = false;
        }
        if (in.op == OpCode::Ne)
          result = !result;
      } else {
        double da = 0.0, db = 0.0;
        bool af = false, bf = false;
        if (!asNumber(a, da, af) || !asNumber(b, db, bf))
          return vmError("non-numeric operand in relational op");

        if (in.op == OpCode::Lt)
          result = da < db;
        else if (in.op == OpCode::Gt)
          result = da > db;
        else if (in.op == OpCode::Le)
          result = da <= db;
        else if (in.op == OpCode::Ge)
          result = da >= db;
      }

      stack.push_back(Value::Bool(result));
      break;
    }

    case OpCode::And:
    case OpCode::Or: {
      Value b, a;
      if (!popValue(stack, b) || !popValue(stack, a))
        return vmError("stack underflow on boolean op");
      bool va = truthy(a);
      bool vb = truthy(b);
      stack.push_back(Value::Bool(in.op == OpCode::And ? (va && vb) : (va || vb)));
      break;
    }

    case OpCode::Not: {
      Value v;
      if (!popValue(stack, v))
        return vmError("stack underflow on NOT");
      stack.push_back(Value::Bool(!truthy(v)));
      break;
    }

    case OpCode::Neg: {
      Value v;
      if (!popValue(stack, v))
        return vmError("stack underflow on NEG");
      double d = 0.0;
      bool isFloat = false;
      if (!asNumber(v, d, isFloat))
        return vmError("non-numeric operand on NEG");
      if (isFloat)
        stack.push_back(Value::Float(-d));
      else
        stack.push_back(Value::Int(-static_cast<long long>(d)));
      break;
    }

    case OpCode::Jump:
      if (in.a < 0 || in.a >= static_cast<int>(fn.code.size()))
        return vmError("invalid JMP target");
      fr.pc = in.a;
      break;

    case OpCode::JumpFalse: {
      Value v;
      if (!popValue(stack, v))
        return vmError("stack underflow on JMP_F");
      if (!truthy(v)) {
        if (in.a < 0 || in.a >= static_cast<int>(fn.code.size()))
          return vmError("invalid JMP_F target");
        fr.pc = in.a;
      }
      break;
    }

    case OpCode::Print: {
      Value v;
      if (!popValue(stack, v))
        return vmError("stack underflow on PRINT");
      std::cout << toString(v) << "\n";
      break;
    }

    case OpCode::Read: {
      std::string tok;
      if (!(std::cin >> tok)) {
        stack.push_back(Value::Nil());
      } else {
        stack.push_back(parseInputToken(tok));
      }
      break;
    }

    case OpCode::Call: {
      if (in.a < 0 || in.a >= static_cast<int>(program.functions.size()))
        return vmError("invalid CALL target");

      const BytecodeFunction &callee = program.functions[in.a];
      if (in.b < 0)
        return vmError("negative CALL arg count");

      std::vector<Value> args(in.b, Value::Nil());
      for (int i = in.b - 1; i >= 0; --i) {
        if (!popValue(stack, args[i]))
          return vmError("stack underflow while collecting call args");
      }

      Frame nf;
      nf.func = in.a;
      nf.pc = 0;
      nf.slots.resize(callee.slotCount, Value::Nil());
      for (int i = 0; i < in.b && i < callee.paramCount &&
                      i < static_cast<int>(nf.slots.size());
           ++i) {
        nf.slots[i] = args[i];
      }

      callStack.push_back(nf);
      break;
    }

    case OpCode::Ret: {
      Value ret = Value::Nil();
      if (!popValue(stack, ret))
        ret = Value::Nil();

      callStack.pop_back();
      if (callStack.empty()) {
        VMResult done;
        if (ret.kind == Value::Kind::Int)
          done.exitCode = static_cast<int>(ret.i);
        else
          done.exitCode = 0;
        return done;
      }

      stack.push_back(ret);
      break;
    }

    case OpCode::Halt: {
      VMResult done;
      done.exitCode = 0;
      return done;
    }

    case OpCode::MakeArray: {
      if (in.a < 0)
        return vmError("negative array size in ARR_MK");
      std::shared_ptr<std::vector<Value> > arr(new std::vector<Value>(in.a));
      for (int i = in.a - 1; i >= 0; --i) {
        if (!popValue(stack, (*arr)[i]))
          return vmError("stack underflow on ARR_MK");
      }
      stack.push_back(Value::Array(arr));
      break;
    }

    case OpCode::ArrayGet: {
      Value idx, arr;
      if (!popValue(stack, idx) || !popValue(stack, arr))
        return vmError("stack underflow on ARR_GET");
      if (arr.kind != Value::Kind::Array || !arr.arr)
        return vmError("ARR_GET on non-array value");
      if (idx.kind != Value::Kind::Int)
        return vmError("ARR_GET index must be int");
      if (idx.i < 0 || idx.i >= static_cast<long long>(arr.arr->size()))
        return vmError("ARR_GET index out of bounds");
      stack.push_back((*arr.arr)[static_cast<size_t>(idx.i)]);
      break;
    }

    case OpCode::ArraySet: {
      Value val, idx, arr;
      if (!popValue(stack, val) || !popValue(stack, idx) || !popValue(stack, arr))
        return vmError("stack underflow on ARR_SET");
      if (arr.kind != Value::Kind::Array || !arr.arr)
        return vmError("ARR_SET on non-array value");
      if (idx.kind != Value::Kind::Int)
        return vmError("ARR_SET index must be int");
      if (idx.i < 0 || idx.i >= static_cast<long long>(arr.arr->size()))
        return vmError("ARR_SET index out of bounds");
      (*arr.arr)[static_cast<size_t>(idx.i)] = val;
      break;
    }

    case OpCode::ArrayLen: {
      Value arr;
      if (!popValue(stack, arr))
        return vmError("stack underflow on ARR_LEN");
      if (arr.kind != Value::Kind::Array || !arr.arr)
        return vmError("ARR_LEN on non-array value");
      stack.push_back(Value::Int(static_cast<long long>(arr.arr->size())));
      break;
    }

    case OpCode::NewObject: {
      std::shared_ptr<Object> obj(new Object());
      obj->className = in.s;
      stack.push_back(Value::Obj(obj));
      break;
    }

    case OpCode::GetField: {
      Value obj;
      if (!popValue(stack, obj))
        return vmError("stack underflow on GET_F");
      if (obj.kind != Value::Kind::Object || !obj.obj)
        return vmError("GET_F on non-object value");
      std::unordered_map<std::string, Value>::const_iterator it =
          obj.obj->fields.find(in.s);
      if (it == obj.obj->fields.end())
        stack.push_back(Value::Nil());
      else
        stack.push_back(it->second);
      break;
    }

    case OpCode::SetField: {
      Value val, obj;
      if (!popValue(stack, val) || !popValue(stack, obj))
        return vmError("stack underflow on SET_F");
      if (obj.kind != Value::Kind::Object || !obj.obj)
        return vmError("SET_F on non-object value");
      obj.obj->fields[in.s] = val;
      break;
    }
    }
  }

  VMResult done;
  done.exitCode = 0;
  return done;
}
