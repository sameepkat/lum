#include "lum/frontend/ast/stmt.hpp"
#include "lum/frontend/ast/stmt_visitor.hpp"
namespace lum{

    void ExpressionStmt::accept(StmtVisitor& visitor) {
       visitor.visitExpressionStmt(*this);
    }

    void BlockStmt::accept(StmtVisitor& visitor) {
       visitor.visitBlockStmt(*this);
    }

    void FunctionStmt::accept(StmtVisitor& visitor) {
       visitor.visitFunctionStmt(*this);
    }

    void ReturnStmt::accept(StmtVisitor& visitor) {
       visitor.visitReturnStmt(*this);
    }

    void IfStmt::accept(StmtVisitor& visitor) {
       visitor.visitIfStmt(*this);
    }

    void WhileStmt::accept(StmtVisitor& visitor) {
       visitor.visitWhileStmt(*this);
    }

}
