#pragma once
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {
  lum::Value __to_string(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);
  lum::Value __to_number(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);
  lum::Value __to_ord(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);
  lum::Value __to_chr(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);
}


