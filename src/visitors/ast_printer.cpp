// Lexer lexer(source);
// tokens = lexer.scanTokens()

// Parser parser(tokens)
// program = parser.parse();

// ASTPrinter printer
// printer.print(program);


#include "lum/visitors/ast_printer.hpp"
#include "lum/frontend/ast/expr.hpp"

namespace lum{
    void print(Program& program){

    }
    void ASTPrinter::visitLiteralExpr(LiteralExpr& expr){}

    void ASTPrinter::visitVariableExpr(VariableExpr& expr){}

    void ASTPrinter::visitBinaryExpr(BinaryExpr& expr){}

    void ASTPrinter::visitUnaryExpr(UnaryExpr& expr){}

    void ASTPrinter::visitCallExpr(CallExpr& expr){}

    void ASTPrinter::visitAssignExpr(AssignExpr& expr){}
}
