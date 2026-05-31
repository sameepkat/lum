#include <cmath>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <variant>
#include "lum/runtime/value.hpp"
#include "lum/runtime/function.hpp"
#include "lum/runtime/native_function.hpp"

namespace lum{

        Value::Value() : data(std::monostate{}){}

        Value::Value(double value): data(value){}
        Value::Value(bool value): data(value){}
        Value::Value(std::string value): data(std::move(value)){}
        Value::Value(std::shared_ptr<LumFunction> value): data(std::move(value)){}
        Value::Value(std::shared_ptr<NativeFunction> value): data(std::move(value)){}
        Value::Value(std::shared_ptr<std::vector<Value>> value): data(std::move(value)){}


        std::string Value::toString() const{
            std::string value = "";
            if(std::holds_alternative<std::monostate>(data)) value="nil";
            else if (std::holds_alternative<double>(data)) {
              double number = std::get<double>(data);
              if(isInt(number)) value =  std::to_string(static_cast<long long>(number));
              else {
                std::ostringstream out;
                out << number;
                value = out.str();
              }
            }
            else if(std::holds_alternative<bool>(data)) value = std::get<bool>(data) ? "true" : "false";
            else if(std::holds_alternative<std::string>(data)) value = std::get<std::string>(data);
            else if(std::holds_alternative<std::shared_ptr<LumFunction>>(data)) value = "<fn>";
            else if(std::holds_alternative<std::shared_ptr<NativeFunction>>(data)) value = "<native fn>";
            else if (std::holds_alternative<std::shared_ptr<std::vector<Value>>>(data)) {
              value = "[";
                auto array = asArray();
                for (int i=0;  i < array->size() ; ++i) {
                  if(i>0)value += ", ";
                  value += (*array)[i].toString();
                }
              value += "]";
            }

            return value;
        }

        bool Value::isTruthy() const{
            if(std::holds_alternative<std::monostate>(data)) return false;
            else if(std::holds_alternative<bool>(data)){
                return std::get<bool>(data);
            }
            return true;
        }

        bool Value::equals(const Value& other) const{
            if(data.index() != other.data.index()) return false;
            else if(std::holds_alternative<std::monostate>(data)) return true;
            else if(std::holds_alternative<double>(data)) return std::get<double>(data) == std::get<double>(other.data);
            else if(std::holds_alternative<bool>(data)) return std::get<bool>(data) == std::get<bool>(other.data);
            else if(std::holds_alternative<std::string>(data)) return std::get<std::string>(data) == std::get<std::string>(other.data);
            else if(std::holds_alternative<std::shared_ptr<LumFunction>>(data)) return std::get<std::shared_ptr<LumFunction>>(data) == std::get<std::shared_ptr<LumFunction>>(other.data);
            else if(std::holds_alternative<std::shared_ptr<NativeFunction>>(data)) return std::get<std::shared_ptr<NativeFunction>>(data) == std::get<std::shared_ptr<NativeFunction>>(other.data);
            else if (std::holds_alternative<std::shared_ptr<std::vector<Value>>>(data)){
              auto array = std::get<std::shared_ptr<std::vector<Value>>>(data);
              if(!other.isArray()) return false;
              if(array->size() != other.asArray()->size()) return false;
              for (int i = 0; i < array->size(); ++i) {
                if (!((*array)[i].equals((*other.asArray())[i]))) {
                  return false;
                }
              }
              return true;
            }
            return false;
        }

        bool Value::isNumber() const{
            return std::holds_alternative<double>(data);
        }
        double Value::asNumber() const{
            return std::get<double>(data);
        }
        bool Value::isString() const{
            return std::holds_alternative<std::string>(data);
        }
        std::string Value::asString() const{
            return std::get<std::string>(data);
        }
        bool Value::isLumFunction() const{
                return std::holds_alternative<std::shared_ptr<LumFunction>>(data);
        }
          
        bool Value::isNativeFunction() const{
                return std::holds_alternative<std::shared_ptr<NativeFunction>>(data);
            }
        std::shared_ptr<LumFunction> Value::asLumFunction() const {
            return std::get<std::shared_ptr<LumFunction>>(data);
        }
        std::shared_ptr<NativeFunction> Value::asNativeFunction() const {
            return std::get<std::shared_ptr<NativeFunction>>(data);
        }

        bool Value::isInt(double d) const {
          return std::isfinite(d) && std::trunc(d) == d;
        }

        bool Value::isBool() const {
            return std::holds_alternative<bool>(data);
        }
        bool Value::asBool() const {
            return std::get<bool>(data);
        }

        bool Value::isCallable() const {
          return isLumFunction() || isNativeFunction();
        }
        bool Value::isArray() const {
          
          return std::holds_alternative<std::shared_ptr<std::vector<Value>>>(data);
        }
        std::shared_ptr<std::vector<Value>> Value::asArray() const {
            return std::get<std::shared_ptr<std::vector<Value>>>(data);
        }
}
