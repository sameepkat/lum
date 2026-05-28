#include "lum/stdlib/core_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/native_function.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace lum {
  Value print_func(Interpreter &interpreter, const std::vector<Value> &args) {
    interpreter.emit(args[0], true, false);
    return Value();
}

    Value __emit(Interpreter &interpreter, const std::vector<Value> &args) {
      if (args.size() == 3) {
        if (!(args[1].isBool() && args[2].isBool())) {
          lum::Error::throw_internal("expected bools in arg[1] and arg[2]. found" + args[1].toString() + " and " + args[2].toString());
        }
        interpreter.emit(args[0], args[1].asBool(), args[2].asBool());
      } else {
        // lum::Error::throw_and_return("expected 3 arguments: found)" + args.size(), args, int)
        lum::Error::throw_internal("expected 3 arguments. found " + std::to_string(args.size()) );
      }
      return Value();
    }

    void installCoreLib(std::shared_ptr<Environment> globals) {
      std::shared_ptr<NativeFunction> native_print =
    std::make_shared<NativeFunction>(NativeFunction("__emit", 3, __emit));
      std::shared_ptr<NativeFunction> native_print2 =
    std::make_shared<NativeFunction>(NativeFunction("print", 1, print_func));


      globals->define("__emit", Value(native_print));
      globals->define("print", Value(native_print2));
    }
}
