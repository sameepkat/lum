#pragma once
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {

  Value __len(Interpreter &interpreter, const std::vector<Value> &args);
  Value __push(Interpreter &interpreter, const std::vector<Value> &args);
  Value __pop(Interpreter &interpreter, const std::vector<Value> &args);
}
