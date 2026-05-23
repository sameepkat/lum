#pragma once

namespace lum{
    class ExpressionStmt;
    class BlockStmt;
    class FunctionStmt;
    class ReturnStmt;
    class IfStmt;
    class WhileStmt;


    class StmtVisitor{
        public:
        virtual ~StmtVisitor() = default;

        virtual void visitExpressionStmt(ExpressionStmt& stmt) = 0;
        virtual void visitBlockStmt(BlockStmt& stmt) = 0;
        virtual void visitFunctionStmt(FunctionStmt& stmt) = 0;
        virtual void visitReturnStmt(ReturnStmt& stmt) = 0;
        virtual void visitIfStmt(IfStmt& stmt) = 0;
        virtual void visitWhileStmt(WhileStmt& stmt) = 0;
    };
}
