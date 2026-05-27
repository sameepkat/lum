#include "lum/stdlib/core_lib.hpp"
#include "lum/runtime/environment.hpp"
#include "lum/runtime/native_function.hpp"
#include "lum/visitors/interpreter.hpp"
#include <iostream>
#include <memory>

namespace lum {
  Value print_func(Interpreter &interpreter, const std::vector<Value> &args) {

    std::cout << args[0].toString() << "\n";
    return Value();
}
  
    void installCoreLib(std::shared_ptr<Environment> globals) {
      std::shared_ptr<NativeFunction> native_print =
    std::make_shared<NativeFunction>(NativeFunction("print", 1, print_func));



      globals->define("print", Value(native_print));
    }

}
