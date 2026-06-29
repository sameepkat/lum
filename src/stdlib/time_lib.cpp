#include "lum/stdlib/time_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"
#include <chrono>
#include <thread>

namespace lum {

  Value __sleep_ms(Interpreter &interpreter, const std::vector<Value> &args) {
    if(!(args.size() == 1))
      lum::Error::throw_internal("expected 1 argument. found " + std::to_string(args.size()));

    int val = args[0].asNumber();
    std::this_thread::sleep_for(std::chrono::milliseconds(val));
    return Value();
  }
}
