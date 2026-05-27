#pragma once
#include <functional>
#include <string>
#include <vector>
#include "lum/runtime/value.hpp"

namespace lum{
    class Interpreter;
    class NativeFunction{
    public:
      using NativeBody = std::function<Value(Interpreter&, const std::vector<Value>&)>;

      NativeFunction(std::string name, int arity, NativeBody body);

      int arity() const;
      Value call(Interpreter &interpreter, const std::vector<Value> &arguments);
      std::string toString() const;

    private:
      std::string name;
      int arity_value;
      NativeBody body;
    };
}
