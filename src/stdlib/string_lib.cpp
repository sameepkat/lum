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

  lum::Value __substr(lum::Interpreter &interpreter,
                      const std::vector<lum::Value> &args) {
    std::string str = args[0].asString();
    long long start = args[1].asInt();
    long long len = args[2].asInt();

    return Value(str.substr(start, len));
  }

  lum::Value __split(lum::Interpreter &interpreter,
                     const std::vector<lum::Value> &args) {
    std::string str = args[0].asString();
    std::string delimiter = args[1].asString();

    // if (delimiter.size() != 1) {
    //     lum::Error::throw_internal("delimiter must be of length 1");
    // }

    //std::shared_ptr<std::vector<Value>> parts;
    auto parts = std::make_shared<std::vector<Value>>();
    size_t start = 0;
    while(true) {
      size_t pos = str.find(delimiter, start);
      if (pos == std::string::npos) {
        parts->push_back(str.substr(start));
        break;
      }
      parts->push_back(str.substr(start, pos - start));
      start = pos + 1;
    }

    return Value(parts);
  }

  lum::Value __join(lum::Interpreter &interpreter,
                    const std::vector<lum::Value> &args) {
    std::shared_ptr<std::vector<Value>> array = args[0].asArray();
    std::string delimiter = args[1].asString();

    std::string out;
    for (size_t i = 0; i < array->size(); ++i) {
      if (i) out += delimiter;
      out += array->at(i).asString();
    }

    return Value(out);
  }

  lum::Value __index_of(lum::Interpreter &interpreter,
                        const std::vector<lum::Value> &args) {
    std::string str = args[0].asString();
    std::string substr = args[1].asString();

    Value val;

    size_t pos = str.find(substr);
    if(pos == std::string::npos) val = static_cast<double>(-1);
    else val = static_cast<double>(pos);

    return val;
  }
}
