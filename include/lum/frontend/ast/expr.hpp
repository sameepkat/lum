#pragma once

#include "lum/frontend/lexer/token.hpp"
#include <memory>
#include <vector>

namespace lum{

    class Expr; 
    struct ObjectField{
        Token key;
        std::unique_ptr<Expr> value;
    };
  
    class ExprVisitor; // Forward Declaration
    class Expr{
        public:
        virtual ~Expr() = default;
        virtual void accept(ExprVisitor& visitor) = 0;
        virtual std::unique_ptr<Expr> clone() const = 0;
    };

    class LiteralExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

        Token value;
    };

    class VariableExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

        Token name;
    };

    class UnaryExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

        Token unary_operator;
        std::unique_ptr<Expr> right_expression;
    };
    class CallExpr: public Expr{
        public:
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

        Token paren;
        std::unique_ptr<Expr> callee;
        std::vector<std::unique_ptr<Expr>> arguments;
    };
    class AssignExpr: public Expr{
        public:
        std::unique_ptr<Expr> clone() const override;
        void accept(ExprVisitor& visitor) override;

        Token name;
        std::unique_ptr<Expr> expression;
    };

    class BinaryExpr: public Expr{
        public:
        std::unique_ptr<Expr> clone() const override;
        void accept(ExprVisitor& visitor) override;

        std::unique_ptr<Expr> left_expression;
        Token bin_operator;
        std::unique_ptr<Expr> right_expression;
    };

    class LogicalExpr: public Expr {
        public:
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

        std::unique_ptr<Expr> left_expression;
        Token logic_token;
        std::unique_ptr<Expr> right_expression;
    };


    class ArrayExpr: public Expr {
    public:
      void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

      // std::unique_ptr<Expr> arr_var;
      Token bracket;
      std::vector<std::unique_ptr<Expr>> array_elements;
    };

    class IndexExpr : public Expr {
    public:
      void accept(ExprVisitor& visitor) override;
      std::unique_ptr<Expr> clone() const override;

      std::unique_ptr<Expr> target;
      std::unique_ptr<Expr> index;
      Token right_bracket;
    };

    class SetIndexExpr: public Expr{
    public:
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

        std::unique_ptr<Expr> target;
        std::unique_ptr<Expr> index;
        std::unique_ptr<Expr> value;
        Token right_bracket;
    };

    class ObjectExpr: public Expr{
    public:
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;
      
        Token starting_brace;
        std::vector<ObjectField> items;
    };

    class PropertyExpr: public Expr{
    public: 
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

        Token dot;
        std::unique_ptr<Expr> target;
        Token key;
    };

    class SetPropertyExpr: public Expr{
    public: 
        void accept(ExprVisitor& visitor) override;
        std::unique_ptr<Expr> clone() const override;

        Token dot;
        std::unique_ptr<Expr> target;
        Token key;
        std::unique_ptr<Expr> value;
    };
    // class PipelineExpr: public Expr{};
}
