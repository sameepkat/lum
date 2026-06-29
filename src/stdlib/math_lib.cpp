#include "lum/stdlib/math_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"
#include <cassert>
#include <cmath>


namespace lum {
  Value __sin(Interpreter &interpreter, const std::vector<Value> &args) {
    if(!(args.size() == 1))
      lum::Error::throw_internal("expected 1 argument. found " + std::to_string(args.size()));

    double val = args[0].asNumber();

    return Value(std::sin(val));
  }
  Value __cos(Interpreter &interpreter, const std::vector<Value> &args) {
    if(!(args.size() == 1))
      lum::Error::throw_internal("expected 1 argument. found " + std::to_string(args.size()));

    double val = args[0].asNumber();

    return Value(std::cos(val));
  }
  Value __tan(Interpreter &interpreter, const std::vector<Value> &args) {
    if(!(args.size() == 1))
      lum::Error::throw_internal("expected 1 argument. found " + std::to_string(args.size()));

    double val = args[0].asNumber();

    return Value(std::tan(val));
  }
  Value __floor(Interpreter &interpreter, const std::vector<Value> &args) {
    if(!(args.size() == 1))
      lum::Error::throw_internal("expected 1 argument. found " + std::to_string(args.size()));

    double val = args[0].asNumber();

    return Value(floor(val));
 }
 Value __ceil(Interpreter &interpreter, const std::vector<Value> &args) {
    if(!(args.size() == 1))
      lum::Error::throw_internal("expected 1 argument. found " + std::to_string(args.size()));

    double val = args[0].asNumber();

    return Value(ceil(val));
 }
}
