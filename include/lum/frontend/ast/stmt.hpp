#pragma once

#include "lum/frontend/ast/expr.hpp"
#include <memory>
#include <vector>

namespace lum{
    class StmtVisitor; // Forward Declaration
    class Stmt{
        public:
        virtual ~Stmt() = default;
        virtual void accept(StmtVisitor& visitor) = 0;
        virtual std::unique_ptr<Stmt> clone() const = 0;
    };

    class ExpressionStmt: public Stmt{
        public:
        void accept(StmtVisitor& visitor) override;
        std::unique_ptr<Stmt> clone() const override;

        std::unique_ptr<Expr> expression;
    };
    class BlockStmt: public Stmt{
        public:
        void accept(StmtVisitor& visitor) override;
        std::unique_ptr<Stmt> clone() const override;
        std::unique_ptr<BlockStmt> cloneBlock() const;

        std::vector<std::unique_ptr<Stmt>> statements;
    };
    class FunctionStmt: public Stmt{
        public:
        void accept(StmtVisitor& visitor) override;
        std::unique_ptr<Stmt> clone() const override;

        Token func_name;
        std::vector<Token> params;
        std::unique_ptr<BlockStmt> function_block;
    };

    class ReturnStmt: public Stmt{
        public:
        void accept(StmtVisitor& visitor) override;
        std::unique_ptr<Stmt> clone() const override;

            Token return_token; // Not strictly needed, Useful for error messages/ location
            std::unique_ptr<Expr> return_expr;

    };
    class IfStmt: public Stmt{
        public:
        void accept(StmtVisitor& visitor) override;
        std::unique_ptr<Stmt> clone() const override;

        Token if_token;
        std::unique_ptr<Expr> condition;
        std::unique_ptr<BlockStmt> then_branch;
        std::unique_ptr<BlockStmt> else_branch; // this can be optional
    };

    class WhileStmt: public Stmt{
        public:
        void accept(StmtVisitor& visitor) override;
        std::unique_ptr<Stmt> clone() const override;

        Token while_token;
        std::unique_ptr<Expr> condition;
        std::unique_ptr<BlockStmt> while_block;
    };
  class UseStmt: public Stmt{
    public:
        void accept(StmtVisitor& visitor) override;
        std::unique_ptr<Stmt> clone() const override;

        Token use_token;
        Token module_name;
  };
//     class objectstmt: public stmt{};
}
