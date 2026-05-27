#include "lum/runtime/native_function.hpp"
#include "lum/visitors/interpreter.hpp"
namespace lum {
  NativeFunction::NativeFunction(std::string name, int arity, NativeBody body) {
    this->name = name;
    this->arity_value = arity;
    this->body = body;
}

int NativeFunction::arity() const {
  return this->arity_value;
}

std::string NativeFunction::toString() const {
  return "<native fn " + this->name + ">";
}

Value NativeFunction::call(Interpreter &interpreter,
                           const std::vector<Value> &arguments) {
  return body(interpreter, arguments);
}
}
