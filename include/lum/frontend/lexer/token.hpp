#pragma once

#include <string>
#include "lum/frontend/lexer/token_type.hpp"

namespace lum {
    struct Token {
        TokenType type;
        std::string lexeme;
        int line;
        int column;
    };
}
