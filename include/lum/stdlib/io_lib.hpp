#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {
Value __input(lum::Interpreter &interpreter,
              const std::vector<lum::Value> &args);
}
