#include "lum/stdlib/core_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/native_function.hpp"
#include "lum/stdlib/array_lib.hpp"
#include "lum/stdlib/io_lib.hpp"
#include "lum/stdlib/math_lib.hpp"
#include "lum/stdlib/time_lib.hpp"
#include "lum/stdlib/terminal_lib.hpp"
#include "lum/stdlib/string_lib.hpp"
#include "lum/stdlib/fs_lib.hpp"
#include "lum/visitors/interpreter.hpp"
#include "lum/visitors/interpreter.hpp"
#include "lum/runtime/value.hpp"
#include <vector>

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

    Value __lum_typeof(Interpreter &interpreter, const std::vector<Value> &args) {
      if (args.size() != 1) lum::Error::throw_internal("expected 1 argument. found " + std::to_string(args.size()));
      std::string type_string = args[0].lum_typeof();
      return Value(type_string);
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
      std::shared_ptr<NativeFunction> string_func = std::make_shared<NativeFunction>(NativeFunction("__to_string", 1, __to_string));
      std::shared_ptr<NativeFunction> number_func = std::make_shared<NativeFunction>(NativeFunction("__to_number", 1, __to_number));
      std::shared_ptr<NativeFunction> ord_func = std::make_shared<NativeFunction>(NativeFunction("__to_ord", 1, __to_ord));
      std::shared_ptr<NativeFunction> chr_func = std::make_shared<NativeFunction>(NativeFunction("__to_chr", 1, __to_chr));
      std::shared_ptr<NativeFunction> substr_func = std::make_shared<NativeFunction>(NativeFunction("__substr", 3, __substr));
      std::shared_ptr<NativeFunction> split_func = std::make_shared<NativeFunction>(NativeFunction("__split", 2, __split));
      std::shared_ptr<NativeFunction> join_func = std::make_shared<NativeFunction>(NativeFunction("__join", 2, __join));
      std::shared_ptr<NativeFunction> index_of_func = std::make_shared<NativeFunction>(NativeFunction("__index_of", 2, __index_of));
      std::shared_ptr<NativeFunction> type_func = std::make_shared<NativeFunction>(NativeFunction("type", 1, __lum_typeof));
      std::shared_ptr<NativeFunction> read_file_func = std::make_shared<NativeFunction>(NativeFunction("__read_file", 1, __read_file));
      std::shared_ptr<NativeFunction> write_file_func = std::make_shared<NativeFunction>(NativeFunction("__write_file", 2, __write_file));
      std::shared_ptr<NativeFunction> append_file_func = std::make_shared<NativeFunction>(NativeFunction("__append_file", 2, __append_file));


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
      globals->define("__to_string", Value(string_func));
      globals->define("__to_number", Value(number_func));
      globals->define("__to_ord", Value(ord_func));
      globals->define("__to_chr", Value(chr_func));
      globals->define("__substr", Value(substr_func));
      globals->define("__split", Value(split_func));
      globals->define("__join", Value(join_func));
      globals->define("__index_of", Value(index_of_func));
      globals->define("type", Value(type_func));
      globals->define("__read_file", Value(read_file_func));
      globals->define("__write_file", Value(write_file_func));
      globals->define("__append_file", Value(append_file_func));
    }
}
