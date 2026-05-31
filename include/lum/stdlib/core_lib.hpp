#pragma once

#include "lum/runtime/environment.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {
    Value print_func(Interpreter &interpreter, const std::vector<Value> &args);
    Value __emit(Interpreter &interpreter, const std::vector<Value> &args);

    void installCoreLib(std::shared_ptr<Environment> globals);
}
