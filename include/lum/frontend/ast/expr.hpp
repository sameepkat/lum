#pragma once

#include "lum/frontend/lexer/token.hpp"
#include <memory>
#include <vector>

namespace lum{
    class ExprVisitor; // Forward Declaration
    class Expr{
        public:
        virtual ~Expr() = default;
        virtual void accept(ExprVisitor& visitor) = 0;
    };

    class LiteralExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;

        Token value;
    };

    class VariableExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;

        Token name;
    };

    class UnaryExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;

        Token unary_operator;
        std::unique_ptr<Expr> right_expression;
    };
    class CallExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;

        Token paren;
        std::unique_ptr<Expr> callee;
        std::vector<std::unique_ptr<Expr>> arguments;
    };
    class AssignExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;

        Token name;
        std::unique_ptr<Expr> expression;
    };

    class BinaryExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;

        std::unique_ptr<Expr> left_expression;
        Token bin_operator;
        std::unique_ptr<Expr> right_expression;
    };

    class LogicalExpr: public Expr {
        public:
        void accept(ExprVisitor& visitor) override;

        std::unique_ptr<Expr> left_expression;
        Token logic_token;
        std::unique_ptr<Expr> right_expression;
    };


    // class ArrayExpr: public Expr{};
    // class ObjectExpr: public Expr{};
    // class IndexExpr: public Expr{};
    // class PipelineExpr: public Expr{};
    // class PropertyExpr: public Expr{};
}
