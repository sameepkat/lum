#include <string>
#include "lum/stdlib/string_lib.hpp"
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"
#include "lum/error/error.hpp"

namespace lum {
lum::Value __to_string(lum::Interpreter &interpreter, const std::vector<lum::Value> &args){
    Value val = args[0].toString();

    return val;
}
  lum::Value __to_number(lum::Interpreter &interpreter, const std::vector<lum::Value> &args){
    Value val;
    try{
      val = std::stod(args[0].asString());
    }catch(const std::invalid_argument&){
      lum::Error::throw_msg("invalid argument. cannot convert given string to number");
    }catch(const std::out_of_range&){
      lum::Error::throw_msg("given string is out of range");
    }

    return val;
  }

}
