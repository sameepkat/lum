#pragma once

#include "lum/frontend/ast/expr.hpp"
namespace lum{
    class LiteralExpr;
    class VariableExpr;
    class BinaryExpr;
    class UnaryExpr;
    class CallExpr;
    class AssignExpr;

    class ExprVisitor{
        public:
        virtual ~ExprVisitor() = default;

        virtual void visitLiteralExpr(LiteralExpr& expr) = 0;
        virtual void visitVariableExpr(VariableExpr& expr) = 0;
        virtual void visitBinaryExpr(BinaryExpr& expr) = 0;
        virtual void visitUnaryExpr(UnaryExpr& expr) = 0;
        virtual void visitCallExpr(CallExpr& expr) = 0;
        virtual void visitAssignExpr(AssignExpr& expr) = 0;
        virtual void visitLogicalExpr(LogicalExpr& expr) = 0;
    };

}
