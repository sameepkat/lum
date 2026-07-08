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

  lum::Value __to_ord(lum::Interpreter &interpreter,
                      const std::vector<lum::Value> &args) {
    std::string s = args[0].asString();
    if (s.size() != 1)
      lum::Error::throw_msg("string length must be equal to 1 for ord function");
    double num = static_cast<unsigned char>(s[0]);

    return Value(num);
  }

  lum::Value __to_chr(lum::Interpreter &interpreter,
                      const std::vector<lum::Value> &args) {
    double num = args[0].asNumber();
    int number = static_cast<int>(num);
    
    char ascii = static_cast<char>(number);
    return Value(std::string(1, ascii));
  }

}
