#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace lum{
    class LumFunction;
    class NativeFunction;
    class Value;

    using valueData = std::variant<
        std::monostate, // nil
        double,
        bool,
        std::string,
        std::shared_ptr<LumFunction>,
        std::shared_ptr<NativeFunction>,
        std::shared_ptr<std::vector<Value>>,
        std::shared_ptr<std::unordered_map<std::string, Value>>
    >;

    class Value{
        public:
            Value();
            Value(double value);
            Value(bool value);
            Value(std::string value);
            Value(std::shared_ptr<LumFunction> value);
            Value(std::shared_ptr <NativeFunction> value);
            Value(std::shared_ptr<std::vector<Value>> value);
            Value(std::shared_ptr<std::unordered_map<std::string, Value>> value);


            std::string toString() const;
            bool isTruthy() const;
            bool equals(const Value& other) const;
            std::string lum_typeof() const;

            bool isNumber() const;
            double asNumber() const;
            long long asInt() const;
            bool isString() const;
            std::string asString() const;
            bool isBool() const;
            bool asBool() const;
            bool isArray() const;
            std::shared_ptr<std::vector<Value>> asArray() const;
            bool isObject() const;
            std::shared_ptr<std::unordered_map<std::string, Value>> asObject() const;

            bool isCallable() const;

            bool isLumFunction() const;
            bool isNativeFunction() const;
            std::shared_ptr<LumFunction> asLumFunction() const;
            std::shared_ptr<NativeFunction> asNativeFunction() const;

            bool isInt(double) const;
        private:
            valueData data;
    };
}
