#include "lum/frontend/ast/stmt.hpp"
#include "lum/frontend/ast/stmt_visitor.hpp"
#include <memory>
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

    void UseStmt::accept(StmtVisitor& visitor) {
       visitor.visitUseStmt(*this);
    }

    void BreakStmt::accept(StmtVisitor &visitor) {
				visitor.visitBreakStmt(*this);	
    }

    void ContinueStmt::accept(StmtVisitor &visitor) {
				visitor.visitContinueStmt(*this);
    }

    std::unique_ptr<Stmt> ExpressionStmt::clone() const {
      auto stmt = std::make_unique<ExpressionStmt>();
      if (expression)
        stmt->expression = expression->clone();

      return stmt;
    }

    std::unique_ptr<BlockStmt> BlockStmt::cloneBlock() const {
      auto block = std::make_unique<BlockStmt>();

      for (const auto &statement : statements) {
        if (statement)
          block->statements.push_back(statement->clone());
        else
          block->statements.push_back(nullptr);
      }

      return block;
    }

  std::unique_ptr<Stmt> BlockStmt::clone() const {
    auto stmt = std::make_unique<BlockStmt>();

    for (const auto &statement : statements) {
      if (statement)
        stmt->statements.push_back(statement->clone());
      else 
        stmt->statements.push_back(nullptr);
    }

    return stmt;
    }

  std::unique_ptr<Stmt> FunctionStmt::clone() const {
    auto stmt = std::make_unique<FunctionStmt>();

    stmt->func_name = func_name;
    for (const auto& parameters: params) {
      stmt->params.push_back(parameters);
    }

    if (function_block)
      stmt->function_block = function_block->cloneBlock();

    return stmt;
    }

  std::unique_ptr<Stmt> ReturnStmt::clone() const {
    auto stmt = std::make_unique<ReturnStmt>();
    stmt->return_token = return_token;

    if (return_expr)
      stmt->return_expr = return_expr->clone();

    return stmt;
    }

  std::unique_ptr<Stmt> IfStmt::clone() const {
    auto stmt = std::make_unique<IfStmt>();
    stmt->if_token = if_token;
    if (condition)
      stmt->condition = condition->clone();
    if (then_branch)
      stmt->then_branch = then_branch->cloneBlock();
    if (else_branch)
      stmt->else_branch = else_branch->cloneBlock();

    return stmt;
    }

  std::unique_ptr<Stmt> WhileStmt::clone() const {
    auto stmt = std::make_unique<WhileStmt>();
    stmt->while_token = while_token;

    if (condition)
      stmt->condition = condition->clone();
    if (while_block)
      stmt->while_block = while_block->cloneBlock();
    return stmt;
    }

  std::unique_ptr<Stmt> BreakStmt::clone() const {
		auto stmt = std::make_unique<BreakStmt>();
		stmt->break_token = break_token;

		return stmt;
    }

  std::unique_ptr<Stmt> ContinueStmt::clone() const {
    auto stmt = std::make_unique<ContinueStmt>();
		stmt->continue_token = continue_token;

		return stmt;
    }

  std::unique_ptr<Stmt> UseStmt::clone() const {
    auto stmt = std::make_unique<UseStmt>();
    stmt->use_token = use_token;
    stmt->module_name = module_name;

    return stmt;
    }

}
