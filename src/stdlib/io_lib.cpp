#include "lum/stdlib/core_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"
#include <iostream>


namespace lum {
lum::Value __input(lum::Interpreter &interpreter, const std::vector<lum::Value> &args) {

  if(!(args.size() == 0))
    lum::Error::throw_internal("expected 0 arguments. found " + std::to_string(args.size()));

  std::string line;
  if (std::getline(std::cin, line)) 
    return Value(line);
  else
    return Value();
  }
}
