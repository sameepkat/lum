#include "lum/runtime/return_signal.hpp"

namespace lum {
  ReturnSignal::ReturnSignal(Value value) {
    this->value = value;
  }
}
