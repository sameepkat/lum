#pragma once
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {

  Value __sin(Interpreter &interpreter, const std::vector<Value> &args);
  Value __cos(Interpreter &interpreter, const std::vector<Value> &args);
  Value __tan(Interpreter &interpreter, const std::vector<Value> &args);
  Value __floor(Interpreter &interpreter, const std::vector<Value> &args);
  Value __ceil(Interpreter &interpreter, const std::vector<Value> &args);
}
