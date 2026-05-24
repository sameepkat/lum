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
        private:
            valueData data;
    };
}
