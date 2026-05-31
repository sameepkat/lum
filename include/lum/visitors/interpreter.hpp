#pragma once

#include "lum/frontend/ast/expr_visitor.hpp"
#include "lum/frontend/ast/program.hpp"
#include "lum/frontend/ast/stmt_visitor.hpp"
#include "lum/runtime/environment.hpp"
#include "lum/runtime/value.hpp"
#include <memory>
#include <optional>
#include <vector>

namespace lum{
  class LumFunction;
    class Interpreter: public ExprVisitor,public StmtVisitor{
        public:
      Interpreter();
            void interpret(Program &);
            void setInteractiveMode(bool value);

      // Helper to print
            void emit(const Value& value, bool new_line, bool to_stderr);
            // produce values
            void visitLiteralExpr(LiteralExpr& expr) override;
            void visitVariableExpr(VariableExpr& expr) override;
            void visitBinaryExpr(BinaryExpr& expr) override;
            void visitUnaryExpr(UnaryExpr& expr) override;
            void visitCallExpr(CallExpr& expr) override;
            void visitAssignExpr(AssignExpr& expr) override;
            void visitLogicalExpr(LogicalExpr& expr) override;
            void visitArrayExpr(ArrayExpr& expr) override;
            void visitIndexExpr(IndexExpr& expr) override;
            void visitSetIndexExpr(SetIndexExpr& expr) override;

            // produce side effects
            void visitExpressionStmt(ExpressionStmt& stmt) override;
            void visitBlockStmt(BlockStmt& stmt) override;
            void visitFunctionStmt(FunctionStmt& stmt) override;
            void visitReturnStmt(ReturnStmt& stmt) override;
            void visitIfStmt(IfStmt& stmt) override;
            void visitWhileStmt(WhileStmt& stmt) override;
            void visitUseStmt(UseStmt& stmt) override;

            class EnvironmentGuard { // For RAII
                public:
                    EnvironmentGuard(Interpreter& interpreter, std::shared_ptr<Environment> new_env);
                    ~EnvironmentGuard();
                private:
                    Interpreter* interpreter;
                    std::shared_ptr<Environment> previous_env;
            };
        private:
            bool interactive_mode = false; // for repl and notebooks
            std::optional<Value> last_result; // user-facing session output state

            friend class LumFunction;
      
            std::shared_ptr<Environment> globals, environment;
            Value evaluated_value;

            Value evaluate(Expr&);
            void execute(Stmt&);
            void executeBlock(const std::vector<std::unique_ptr<Stmt>>&, std::shared_ptr<Environment>);

            // TODO: Type-check helpers
            // TODO: truthiness/ equality helpers
    };

}
