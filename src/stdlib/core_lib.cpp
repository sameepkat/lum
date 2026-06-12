#include "lum/stdlib/core_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/native_function.hpp"
#include "lum/stdlib/array_lib.hpp"
#include "lum/stdlib/io_lib.hpp"
#include <memory>

namespace lum {
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
      std::shared_ptr<NativeFunction> native_emit = std::make_shared<NativeFunction>(NativeFunction("__emit", 3, __emit));
      std::shared_ptr<NativeFunction> len_func = std::make_shared<NativeFunction>(NativeFunction("__len", 1, __len));
      std::shared_ptr<NativeFunction> push_func = std::make_shared<NativeFunction>(NativeFunction("__push", 2, __push));
      std::shared_ptr<NativeFunction> pop_func = std::make_shared<NativeFunction>(NativeFunction("__pop", 1, __pop));
      std::shared_ptr<NativeFunction> in_func = std::make_shared<NativeFunction>(NativeFunction("__input", 0, __input));


      globals->define("__emit", Value(native_emit));
      globals->define("__len", Value(len_func));
      globals->define("__push", Value(push_func));
      globals->define("__pop", Value(pop_func));
      globals->define("__input", Value(in_func));
    }
}
