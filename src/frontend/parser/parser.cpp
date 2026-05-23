#include "lum/frontend/parser/parser.hpp"
#include "lum/frontend/lexer/token.hpp"
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

    // void ASTPrinter(){
    //     std::cout << "ASTPrinter: TODO"  << std::endl;
    // }

   std::unique_ptr<Program>  Parser::parse(){
       std::unique_ptr<Program> program = std::make_unique<Program>();
       // TODO: Fill program->statements by parsing tokens

       while(!isTokEOF()){
           auto decl = parseDeclaration();
            if(decl) program->statements.push_back(std::move(decl));
            else{
                    // TODO: ERROR
                    advanceToken();
                }
       return program;
   }
}
