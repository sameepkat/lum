#pragma once
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {
  std::string expand_tilde(const std::string &p);
  Value __read_file(Interpreter &interpreter, const std::vector<Value> &args);
  Value __write_file(Interpreter &interpreter, const std::vector<Value> &args);
  Value __append_file(Interpreter &interpreter, const std::vector<Value> &args);
}
