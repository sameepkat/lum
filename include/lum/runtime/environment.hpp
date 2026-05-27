#pragma once

#include "lum/frontend/lexer/token.hpp"
#include "lum/runtime/value.hpp"
#include <memory>
#include <string>
#include <unordered_map>
namespace lum{
    class Environment{
        public:
            Environment();
            explicit Environment(std::shared_ptr<Environment> enclosing);

            void define(const std::string& name, Value value);
            Value get(const Token& token) const;
            void assign(const Token& token, Value value);

        private:
            std::unordered_map<std::string, Value> values;
            std::shared_ptr<Environment> enclosing;
            bool assignExisting(const Token&, Value);
    };
}
