#include <fstream>
#include <iostream>
#include <sstream>
#include "lum/frontend/lexer/lexer.hpp"
#include "lum/frontend/lexer/token.hpp"
#include "lum/frontend/parser/parser.hpp"
#include "lum/visitors/ast_printer.hpp"
#include "lum/visitors/interpreter.hpp"
int main(int argc, char** argv){
    if (argc != 2){
        std::cerr << "Usage: lum <file.lum>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if(!file){
        std::cerr << "Could not open file: " << argv[1] << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    lum::Lexer lexer(buffer.str());
    std::vector<lum::Token> tokens = lexer.scanTokens();

    // std::cout << "Tokens found: " << tokens.size() << "\n";

    for(const auto& token: tokens){
      // std::cout << static_cast<int>(token.type) << " -> " << token.lexeme << " " << ": (" << token.line << ":" << token.column << ")" << "\n";
    }

    // Printing AST from here on
    lum::Parser parser(tokens);
    std::unique_ptr<lum::Program> program = parser.parse();

    lum::ASTPrinter printer;

    // printer.print(*program);

    lum::Interpreter interpreter;
    interpreter.interpret(*program);
    return 0;
}
