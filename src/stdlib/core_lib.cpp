#include "lum/stdlib/core_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/native_function.hpp"
#include "lum/stdlib/array_lib.hpp"
#include "lum/stdlib/io_lib.hpp"
#include "lum/stdlib/math_lib.hpp"
#include "lum/stdlib/time_lib.hpp"
#include "lum/stdlib/terminal_lib.hpp"
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
      std::shared_ptr<NativeFunction> sin_func = std::make_shared<NativeFunction>(NativeFunction("__sin", 1, __sin));
      std::shared_ptr<NativeFunction> cos_func = std::make_shared<NativeFunction>(NativeFunction("__cos", 1, __cos));
      std::shared_ptr<NativeFunction> tan_func = std::make_shared<NativeFunction>(NativeFunction("__tan", 1, __tan));
      std::shared_ptr<NativeFunction> floor_func = std::make_shared<NativeFunction>(NativeFunction("__floor", 1, __floor));
      std::shared_ptr<NativeFunction> ceil_func = std::make_shared<NativeFunction>(NativeFunction("__ceil", 1, __ceil));
      std::shared_ptr<NativeFunction> sleep_func = std::make_shared<NativeFunction>(NativeFunction("__sleep", 1, __sleep_ms));
      std::shared_ptr<NativeFunction> clear_func = std::make_shared<NativeFunction>(NativeFunction("__clear", 0, __clear));
      std::shared_ptr<NativeFunction> cursor_up_func = std::make_shared<NativeFunction>(NativeFunction("__cursor_up", 1, __cursor_up));
      std::shared_ptr<NativeFunction> hide_cursor_func = std::make_shared<NativeFunction>(NativeFunction("__hide_cursor", 0, __hide_cursor));
      std::shared_ptr<NativeFunction> show_cursor_func = std::make_shared<NativeFunction>(NativeFunction("__show_cursor", 0, __show_cursor));
      std::shared_ptr<NativeFunction> flush_func = std::make_shared<NativeFunction>(NativeFunction("__flush", 0, __flush));


      globals->define("__emit", Value(native_emit));
      globals->define("__len", Value(len_func));
      globals->define("__push", Value(push_func));
      globals->define("__pop", Value(pop_func));
      globals->define("__input", Value(in_func));
      globals->define("__sin", Value(sin_func));
      globals->define("__cos", Value(cos_func));
      globals->define("__tan", Value(tan_func));
      globals->define("__floor", Value(floor_func));
      globals->define("__ceil", Value(ceil_func));
      globals->define("__sleep", Value(sleep_func));
      globals->define("__clear", Value(clear_func));
      globals->define("__cursor_up", Value(cursor_up_func));
      globals->define("__hide_cursor", Value(hide_cursor_func));
      globals->define("__show_cursor", Value(show_cursor_func));
      globals->define("__flush", Value(flush_func));
    }
}
