#pragma once
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {
  lum::Value __clear(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);

  lum::Value __cursor_up(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);

  lum::Value __hide_cursor(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);

  lum::Value __show_cursor(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);

  lum::Value __flush(lum::Interpreter &interpreter, const std::vector<lum::Value> &args);
}
