#include "lum/frontend/ast/expr.hpp"
#include "lum/frontend/ast/expr_visitor.hpp"

namespace lum{

    void LiteralExpr::accept(ExprVisitor& visitor) {
        visitor.visitLiteralExpr(*this);
    }

    void VariableExpr::accept(ExprVisitor& visitor){
        visitor.visitVariableExpr(*this);
    }

    void UnaryExpr::accept(ExprVisitor& visitor) {
        visitor.visitUnaryExpr(*this);
    }

    void CallExpr::accept(ExprVisitor& visitor) {
        visitor.visitCallExpr(*this);
    }

    void AssignExpr::accept(ExprVisitor& visitor) {
        visitor.visitAssignExpr(*this);
    }

    void BinaryExpr::accept(ExprVisitor& visitor) {
        visitor.visitBinaryExpr(*this);
    }

    void LogicalExpr::accept(ExprVisitor& visitor){
        visitor.visitLogicalExpr(*this);
    }
}
