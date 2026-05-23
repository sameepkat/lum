#include "lum/frontend/parser/parser.hpp"
#include "lum/frontend/ast/expr.hpp"
#include "lum/frontend/ast/stmt.hpp"
#include "lum/frontend/lexer/token.hpp"
#include "lum/error/error.hpp"
#include <memory>
#include <utility>

namespace lum{
   Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)){}

   const Token& Parser::peekToken() const{
        if(currentTokenIndex < tokens.size())
            return tokens[currentTokenIndex];
        else
            return tokens.back();
   }

   TokenType Parser::currentTokenType() const {
       return peekToken().type;
   }

   const Token& Parser::advanceToken() {
       if(peekToken().type == TokenType::EndOfFile){
           return tokens.back();
       }
       return tokens[currentTokenIndex++];
   }

   bool Parser::isTokEOF() const {
       return peekToken().type == TokenType::EndOfFile;
    }

    const Token& Parser::previousToken() const{
        return tokens[currentTokenIndex-1];
    }

    bool Parser::check(TokenType type) const{
       return currentTokenType() == type;
    }

    bool Parser::match(TokenType type){
        if(check(type)){
            advanceToken();
            return true;
        }

        return false;
    }

    const Token& Parser::consume(TokenType type, const char* message){
        if(check(type)) return  advanceToken();
        lum::Error::throw_err(message, peekToken().line, peekToken().column);
        return tokens.back();
    }

    void Parser::skipNewLines(){
        while(match(TokenType::NewLine));
    }

    std::unique_ptr<Stmt> Parser::parseDeclaration(){
        if(match(TokenType::Fn)){
            return parseFunctionDeclaration();
        }
        return parseStatement();
    }

    std::unique_ptr<FunctionStmt> Parser::parseFunctionDeclaration(){
        auto func = std::make_unique<FunctionStmt>();

        func->func_name = consume(TokenType::Identifier, "expect function name");
        consume(TokenType::LeftParen, "expect '(' after function name");

        if(!check(TokenType::RightParen)){
            do{
                func->params.push_back(consume(TokenType::Identifier, "expect parameter name"));
            }while(match(TokenType::Comma));
        }
        consume(TokenType::RightParen, "expect ')' after parameters.");
        consume(TokenType::LeftBrace, "expect '{' after function declaration");
        func->function_block = parseBlock();
        return func;
    }

    std::unique_ptr<BlockStmt> Parser::parseBlock(){
        auto block = std::make_unique<BlockStmt>();

        while(!check(TokenType::RightBrace) && !isTokEOF()){
            skipNewLines();
            auto decl = parseDeclaration();
            if(decl) block->statements.push_back(std::move(decl));
            else advanceToken();
        }

        consume(TokenType::RightBrace, "expect '}' after block");
        return block;
    }

    std::unique_ptr<Stmt> Parser::parseStatement(){
        // if(match(TokenType::Return)) return parseReturn();
        // if(match(TokenType::If)) return parseIf();
        if(match(TokenType::LeftBrace)){
            auto block = parseBlock();
            return block ? std::unique_ptr<Stmt>(block.release()) : nullptr;
        }

        return parseExpressionStmt();
    }

    std::unique_ptr<ExpressionStmt> Parser::parseExpressionStmt(){
        auto expr = parseExpression();

        auto s = std::make_unique<ExpressionStmt>();
        s->expression = std::move(expr);

        if(match(TokenType::NewLine)){
            while(match(TokenType::NewLine)){}
        }else if(!(check(TokenType::RightBrace) || isTokEOF())){
            lum::Error::throw_err("expected newline after statement", previousToken().line, previousToken().column);

            while(!check(TokenType::NewLine) && !check(TokenType::RightBrace) && !isTokEOF()){
                advanceToken();
            }
            if(match(TokenType::NewLine)){
                while(match(TokenType::NewLine)){}
            }
        }

        return s;
    }

    std::unique_ptr<Expr> Parser::parseExpression(){
        return parseCall();
    }

    std::unique_ptr<Expr> Parser::parseCall(){
        auto expr = parsePrimary();

        while(true){
            if(match(TokenType::LeftParen)){
            auto call = std::make_unique<CallExpr>();
            call->callee = std::move(expr);

            while(!check(TokenType::RightParen) && !isTokEOF()){
                call->arguments.push_back(parseExpression());
                skipNewLines();
                if(!match(TokenType::Comma)) break;
            }
            consume(TokenType::RightParen, "Expect ')' after arguments.");
            expr = std::move(call);
            } else {
                break;
            }
        }
        return expr;
    }

    // std::unique_ptr<ReturnStmt> Parser::parseReturn(){

    //     return // ?;
    // }

    std::unique_ptr<Expr> Parser::parsePrimary(){
        if(match(TokenType::Number) || match(TokenType::String) || match(TokenType::True) || match(TokenType::False) || match(TokenType::Nil)){
            Token value = previousToken();
            auto lit = std::make_unique<LiteralExpr>();
            lit->value = value;
            return lit;
        }

        if(match(TokenType::Identifier)){
            Token name = previousToken();
            auto var = std::make_unique<VariableExpr>();
            var->name = name;
            return var;
        }

        if(match(TokenType::LeftParen)){
            auto expr = parseExpression();
            consume(TokenType::RightParen, "Expect ')' after expression.");
            return expr;
        }

        lum::Error::throw_err("Expected expression.", peekToken().line, peekToken().column);
        return nullptr;
    }


   std::unique_ptr<Program>  Parser::parse(){
       std::unique_ptr<Program> program = std::make_unique<Program>();

       while(!isTokEOF()){
           skipNewLines();
           auto decl = parseDeclaration();
            if(decl) program->statements.push_back(std::move(decl));
            else{
                    // TODO: ERROR
                    advanceToken();
                }
       }
       return program;
   }
}
