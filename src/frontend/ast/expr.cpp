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

    void ArrayExpr::accept(ExprVisitor& visitor) {
            visitor.visitArrayExpr(*this);
        }

    void IndexExpr::accept(ExprVisitor& visitor) {
            visitor.visitIndexExpr(*this);
        }

    void SetIndexExpr::accept(ExprVisitor& visitor) {
            visitor.visitSetIndexExpr(*this);
        }

    std::unique_ptr<Expr> LiteralExpr::clone() const{
      std::unique_ptr<LiteralExpr> expr = std::make_unique<LiteralExpr>();
      expr->value = value;
      return expr;
    }

    std::unique_ptr<Expr> VariableExpr::clone()const{
      auto expr = std::make_unique<VariableExpr>();
      expr->name = name;
      return expr;
    }

    std::unique_ptr<Expr> UnaryExpr::clone() const{
      auto expr = std::make_unique<UnaryExpr>();
      expr->unary_operator = unary_operator;
      if (right_expression)
        expr->right_expression = right_expression->clone();
      return expr;
    }

    std::unique_ptr<Expr> CallExpr::clone() const{
      auto expr = std::make_unique<CallExpr>();
      expr->paren = paren;
      if (callee)
        expr->callee = callee->clone();
      for (const auto &arg : arguments) {
        if(arg)
          expr->arguments.push_back(arg->clone());
        else
          expr->arguments.push_back(nullptr);
      }

      return expr;
    }

    std::unique_ptr<Expr> AssignExpr::clone() const{
      auto expr = std::make_unique<AssignExpr>();
      expr->name = name;
      if (expression)
        expr->expression = expression->clone();

      return expr;
    }

    std::unique_ptr<Expr> BinaryExpr::clone() const{
      auto expr = std::make_unique<BinaryExpr>();
      expr->bin_operator = bin_operator;
      if (left_expression)
        expr->left_expression = left_expression->clone();
      if (right_expression)
        expr->right_expression = right_expression->clone();

      return expr;
    }

    std::unique_ptr<Expr> LogicalExpr::clone()const{
      auto expr = std::make_unique<LogicalExpr>();
      expr->logic_token = logic_token;
      if (left_expression)
        expr->left_expression = left_expression->clone();
      if (right_expression)
        expr->right_expression = right_expression->clone();

      return expr;
    }

    std::unique_ptr<Expr> ArrayExpr::clone( ) const {
      auto expr = std::make_unique<ArrayExpr>();
      expr->bracket = bracket;
      for (const auto &elem : array_elements) {
        if (elem) 
          expr->array_elements.push_back(elem->clone());
        else 
          expr->array_elements.push_back(nullptr);
      }

      return expr;
    }

    std::unique_ptr<Expr> IndexExpr::clone() const {
      auto expr = std::make_unique<IndexExpr>();
      expr->right_bracket = right_bracket;

      if (target)
        expr->target = target->clone();
      if (index)
        expr->index = index->clone();

      return expr;
    }

    std::unique_ptr<Expr> SetIndexExpr::clone() const {
      auto expr = std::make_unique<SetIndexExpr>();
      expr->right_bracket = right_bracket;

      if (target)
        expr->target = target->clone();
      if (index)
        expr->index = index->clone();
      if (value)
        expr->value = value->clone();

      return expr;
    }
}
