#pragma once

#include "lum/frontend/ast/expr.hpp"
#include "lum/frontend/ast/expr_visitor.hpp"
#include "lum/frontend/ast/program.hpp"
#include "lum/frontend/ast/stmt_visitor.hpp"

namespace lum{
    class ASTPrinter: public ExprVisitor, StmtVisitor{
        public:
            void print(Program& program);

            void visitLiteralExpr(LiteralExpr& expr) override;

            void visitVariableExpr(VariableExpr& expr) override;

            void visitBinaryExpr(BinaryExpr& expr) override;

            void visitUnaryExpr(UnaryExpr& expr) override;

            void visitCallExpr(CallExpr& expr) override;

            void visitAssignExpr(AssignExpr& expr) override;

            void visitExpressionStmt(ExpressionStmt& stmt) override;

            void visitBlockStmt(BlockStmt& stmt) override;

            void visitFunctionStmt(FunctionStmt& stmt) override;

            void visitReturnStmt(ReturnStmt& stmt) override;

            void visitIfStmt(IfStmt& stmt) override;

            void visitWhileStmt(WhileStmt& stmt) override;
    };
}
