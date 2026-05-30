#pragma once

#include "lum/frontend/ast/expr.hpp"
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
            bool check(TokenType type) const;
            bool match(TokenType type);
            const Token& consume(TokenType type, std::string);
            void skipNewLines();
            void finishStatement(std::string err_msg);


            // Grammar-level methods
            std::unique_ptr<Stmt> parseDeclaration();
            std::unique_ptr<BlockStmt> parseBlock();
            std::unique_ptr<FunctionStmt> parseFunctionDeclaration();
            // parseUseDeclaration();
            // parseObjectDeclaration();

            std::unique_ptr<Stmt> parseStatement();
            std::unique_ptr<ReturnStmt> parseReturn();
            std::unique_ptr<IfStmt> parseIf();
            std::unique_ptr<WhileStmt> parseWhile();
            std::unique_ptr<ExpressionStmt> parseExpressionStmt();

            std::unique_ptr<Expr> parseExpression();
            std::unique_ptr<Expr> parseAssignment();
            std::unique_ptr<Expr> parseLogicalOR();
            std::unique_ptr<Expr> parseLogicalAND();
            std::unique_ptr<Expr> parseEquality();
            std::unique_ptr<Expr> parseComparison();
            std::unique_ptr<Expr> parseTerm();
            std::unique_ptr<Expr> parseFactor();
            std::unique_ptr<Expr> parseUnary();
            std::unique_ptr<Expr> parseCall();
            std::unique_ptr<Expr> parseIndex(std::unique_ptr<Expr>);
            std::unique_ptr<Expr> parsePrimary();
            std::unique_ptr<Expr> parseArray();


      int functionDepth = 0;

    };
}
