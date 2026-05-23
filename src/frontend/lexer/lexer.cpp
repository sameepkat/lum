//#include "../../../include/lum/frontend/lexer/lexer.hpp"
#include "lum/frontend/lexer/lexer.hpp"
#include "lum/frontend/lexer/token.hpp"
#include "lum/error/error.hpp"
#include <cctype>
#include <unordered_map>

namespace lum{
    const std::unordered_map<std::string, TokenType> Lexer::KEYWORDS = {
        {"fn", TokenType::Fn},
        {"if", TokenType::If},
        {"else", TokenType::Else},
        {"while", TokenType::While},
        {"for", TokenType::For},
        {"return", TokenType::Return},
        {"true", TokenType::True},
        {"false", TokenType::False},
        {"nil", TokenType::Nil},
        {"use", TokenType::Use},
    };

    Lexer::Lexer(std::string source) : source(std::move(source)){}

    bool Lexer::isAtEnd() const {
        return current >= static_cast<int>(source.length());
    }

    char Lexer::advance() {
        char c = source[current++];

        if(c == '\n'){
            line++;
            column = 1;
        }else{
            column++;
        }

        return c;
    }

    char Lexer::peek() const {
        if(isAtEnd()){
            return '\0';
        }

        return source[current];
    }

    char Lexer::peekNext() const {
        if(current + 1 >= static_cast<int>(source.length())){
            return '\0';
        }

        return source[current + 1];
    }

    bool Lexer::match(char expected){
        if (isAtEnd()){
            return false;
        }

        if(source[current] != expected){
            return false;
        }

        advance();
        return true;
    }

    std::vector<Token> Lexer::scanTokens(){
        while(!isAtEnd()){
            start = current;
            tokenColumn = column;
            scanToken();
        }

        tokens.push_back(Token{
            TokenType::EndOfFile,
            "",
            line,
            column
        });

        return tokens;
    }

    void Lexer::scanToken(){
        char c = advance();

        switch(c){
            case '(':
                addToken(TokenType::LeftParen);
                break;
            case ')':
                addToken(TokenType::RightParen);
                break;
            case '{':
                addToken(TokenType::LeftBrace);
                break;
            case '}':
                addToken(TokenType::RightBrace);
                break;
            case '[':
                addToken(TokenType::LeftBracket);
                break;
            case ']':
                addToken(TokenType::RightBracket);
                break;
            case ',':
                addToken(TokenType::Comma);
                break;
            case '.':
                addToken(TokenType::Dot);
                break;
            case ':':
                addToken(TokenType::Colon);
                break;
            case '+':
                addToken(TokenType::Plus);
                break;
            case '-':
                addToken(TokenType::Minus);
                break;
            case '*':
                addToken(TokenType::Star);
                break;
            case '/':
                if(match('/')){
                    while(peek() != '\n' && !isAtEnd()){
                        advance();
                    }
                }else{
                    addToken(TokenType::Slash);
                }
                break;
            case '%':
                addToken(TokenType::Percent);
                break;
            case '=':
                addToken(match('=') ? TokenType::EqualEqual : TokenType::Equal);
                break;
            case '!':
                addToken(match('=') ? TokenType::BangEqual : TokenType::Bang);
                break;
            case '>':
                addToken(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
                break;
            case '<':
                addToken(match('=') ? TokenType::LessEqual : TokenType::Less);
                break;

            case ' ':
            case '\r':
            case '\t':
            case '\n':
                break;
            case '"':
                string();
                break;

            default:
                if(std::isdigit(static_cast<unsigned char>(c))) {
                    number();
                }else if (
                    std::isalpha(static_cast<unsigned char>(c)) || c == '_'
                ){
                    identifier();
                }else {
                    lum::Error::throw_err("Unexpected character in lexer", line, column);
                }
                break;
        }
    }


    void Lexer::addToken(TokenType type){
        std::string text = source.substr(start, current - start);

        tokens.push_back(Token{
            type,
            text,
            line,
            tokenColumn
        });
    }

    void Lexer::identifier() {
       while(
           std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_'
       ) {
           advance();
       }

       std::string text = source.substr(start, current - start);

       auto keyword = KEYWORDS.find(text);

       if (keyword != KEYWORDS.end()) {
           addToken(keyword->second);
       }else{
           addToken(TokenType::Identifier);
       }
    }

    void Lexer::number() {
        while(std::isdigit(static_cast<unsigned char>(peek()))){
            advance();
        }

        if(peek() == '.' && std::isdigit(static_cast<unsigned char>(peekNext()))){
            advance();

            while(std::isdigit(static_cast<unsigned char>(peekNext()))){
                advance();
            }
        }

        addToken(TokenType::Number);
    }

    void Lexer::string() {
       while(peek() != '"' && !isAtEnd()) {
           advance();
       }

       if(isAtEnd()){
           lum::Error::throw_err("Unterminated String", line, column);
       }

       advance();

       addToken(TokenType::String);
    }
}
