#pragma once
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {

  Value __sleep_ms(Interpreter &interpreter, const std::vector<Value> &args);
}
