#pragma once

#include "lum/frontend/ast/program.hpp"
#include "lum/frontend/ast/stmt.hpp"
#include "lum/frontend/lexer/token.hpp"
#include <memory>
#include <vector>

namespace lum{

    class Parser{
        public:
            explicit Parser(std::vector<Token> tokens);

            // void ASTPrinter();
            std::unique_ptr<Program> parse();

        private:
            std::vector<Token> tokens;
            int currentTokenIndex = 0;

            // Helpers
            const Token& peekToken() const;
            TokenType currentTokenType() const;
            const Token& advanceToken();
            bool isTokEOF() const;

            const Token& previousToken() const;
            bool check(TokenType const) const;
            bool match(TokenType type);
            const Token& consume(TokenType type, const char* message);


            // Grammar-level methods
            std::unique_ptr<Stmt> declaration();
            std::unique_ptr<FunctionStmt> functionDeclaration();

            std::unique_ptr<BlockStmt> block();
            std::unique_ptr<Stmt> statement();
            std::unique_ptr<ExpressionStmt> expressionStmt();

            std::unique_ptr<Expr> expression();
            std::unique_ptr<Expr> call();
            std::unique_ptr<Expr> primary();

    };
}
