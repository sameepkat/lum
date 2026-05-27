#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "token.hpp"

namespace lum{

    class Lexer {
        public:
        explicit Lexer(std::string source);

        std::vector<Token> scanTokens();

        private:
        std::string source;
        std::vector<Token> tokens;

        int start = 0;
        int current = 0;
        int line = 1;
        int column = 1;
        int tokenColumn = 1;

        static const std::unordered_map<std::string, TokenType> KEYWORDS;

        bool isAtEnd() const;
        char advance();
        char peek() const;
        char peekNext() const;

        bool match(char expected);

        void scanToken();
        void addToken(TokenType type);
        void addStrToken();

        void identifier();
        void number();
        void string();
    };
}
