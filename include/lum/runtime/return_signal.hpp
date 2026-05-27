#pragma once
#include "lum/runtime/value.hpp"

namespace lum {
class ReturnSignal {
public:
  explicit ReturnSignal(Value value);
  Value value;
};
}
