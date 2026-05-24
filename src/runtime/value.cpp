#include <memory>
#include <string>
#include <utility>
#include <variant>
#include "lum/runtime/value.hpp"

namespace lum{

        Value::Value() : data(std::monostate{}){}

        Value::Value(double value): data(value){}
        Value::Value(bool value): data(value){}
        Value::Value(std::string value): data(std::move(value)){}
        Value::Value(std::shared_ptr<LumFunction> value): data(std::move(value)){}
        Value::Value(std::shared_ptr<NativeFunction> value): data(std::move(value)){}


        std::string Value::toString() const{
            std::string value = "";
            if(std::holds_alternative<std::monostate>(data)) value="nil";
            else if(std::holds_alternative<double>(data)) value = std::to_string(std::get<double>(data));
            else if(std::holds_alternative<bool>(data)) value = std::get<bool>(data) ? "true" : "false";
            else if(std::holds_alternative<std::string>(data)) value = std::get<std::string>(data);
            else if(std::holds_alternative<std::shared_ptr<LumFunction>>(data)) value = "<fn>";
            else if(std::holds_alternative<std::shared_ptr<NativeFunction>>(data)) value = "<native fn>";

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
            return false;
        }
}
