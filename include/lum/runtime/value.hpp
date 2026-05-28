#pragma once

#include <memory>
#include <string>
#include <variant>

namespace lum{
    class LumFunction;
    class NativeFunction;

    using valueData = std::variant<
        std::monostate, // nil
        double,
        bool,
        std::string,
        std::shared_ptr<LumFunction>,
        std::shared_ptr<NativeFunction>
    >;

    class Value{
        public:
            Value();
            Value(double value);
            Value(bool value);
            Value(std::string value);
            Value(std::shared_ptr<LumFunction> value);
            Value(std::shared_ptr<NativeFunction> value);


            std::string toString() const;
            bool isTruthy() const;
            bool equals(const Value& other) const;

            bool isNumber() const;
            double asNumber() const;
            bool isString() const;
            std::string asString() const;
            bool isBool() const;
            bool asBool() const;

            bool isCallable() const;

            bool isLumFunction() const;
            bool isNativeFunction() const;
            std::shared_ptr<LumFunction> asLumFunction() const;
            std::shared_ptr<NativeFunction> asNativeFunction() const;

        private:
            valueData data;
            bool isInt(double) const;
    };
}
