#include "lum/visitors/interpreter.hpp"
#include "lum/frontend/lexer/token.hpp"
#include "lum/runtime/environment.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/return_signal.hpp"
#include "lum/runtime/value.hpp"
#include "lum/runtime/function.hpp"
#include "lum/runtime/native_function.hpp"
#include "lum/stdlib/core_lib.hpp"
#include <cmath>
#include <memory>
#include <string>
#include <iostream>

namespace lum {
    Interpreter::Interpreter() {
      globals = std::make_shared<Environment>();
      environment = globals;
      installCoreLib(globals);
    }
  
    void Interpreter::interpret(Program& program){
        for(auto& stmt: program.statements){
            execute(*stmt);
        }
      
        
    }
  void Interpreter::setInteractiveMode(bool value) {
    this->interactive_mode = value;
    }

    // produce values
    void Interpreter::visitLiteralExpr(LiteralExpr& expr) {
        switch(expr.value.type){
            case TokenType::Number:
                this->evaluated_value = std::stod(expr.value.lexeme);
                break;
            case TokenType::String:
                this->evaluated_value = expr.value.lexeme;
                break;
            case TokenType::True:
                this->evaluated_value = true;
                break;
            case TokenType::False:
                this->evaluated_value = false;
                break;
            case TokenType::Nil:
                this->evaluated_value = Value();
                break;

            default:
                lum::Error::throw_and_return("unrecognized literal: " + expr.value.lexeme, expr.value.line, expr.value.column);
                break;
        }
    }
    void Interpreter::visitVariableExpr(VariableExpr& expr) {
        this->evaluated_value =this->environment->get(expr.name);
    }
    void Interpreter::visitBinaryExpr(BinaryExpr& expr) {
        Value left = evaluate(*expr.left_expression);
        Value right = evaluate(*expr.right_expression);


        switch(expr.bin_operator.type){
            case lum::TokenType::Plus:
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for +", expr.bin_operator.line, expr.bin_operator.column);
                this->evaluated_value = Value(left.asNumber() + right.asNumber());
                break;
            case lum::TokenType::Minus:
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for -", expr.bin_operator.line, expr.bin_operator.column);
                this->evaluated_value = Value(left.asNumber() - right.asNumber());
                break;
            case lum::TokenType::Star:
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for *", expr.bin_operator.line, expr.bin_operator.column);
                this->evaluated_value = Value(left.asNumber() * right.asNumber());
                break;
            case lum::TokenType::Slash:
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for /", expr.bin_operator.line, expr.bin_operator.column);
                if(right.asNumber() == 0) lum::Error::throw_and_return("can't divide by 0", expr.bin_operator.line, expr.bin_operator.column);
                this->evaluated_value = Value(left.asNumber() / right.asNumber());
                break;
            case lum::TokenType::Percent:{
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for %", expr.bin_operator.line, expr.bin_operator.column);

                double left_num = left.asNumber();
                double right_num = right.asNumber();

                if(right_num == 0) lum::Error::throw_and_return("can't divide by 0", expr.bin_operator.line, expr.bin_operator.column);
                if(std::floor(left_num) != left_num || std::floor(right_num) != right_num) lum::Error::throw_and_return("% expects whole numbers", expr.bin_operator.line, expr.bin_operator.column);

                long long lhs = static_cast<long long>(left_num);
                long long rhs = static_cast<long long>(right_num);

                this->evaluated_value = Value(static_cast<double>(lhs % rhs));
                break;}
            case lum::TokenType::Greater:
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for >", expr.bin_operator.line, expr.bin_operator.column);
                if(left.asNumber() > right.asNumber()) this->evaluated_value = Value(true);
                else this->evaluated_value = Value(false);
                break;
            case lum::TokenType::GreaterEqual:
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for >=", expr.bin_operator.line, expr.bin_operator.column);
                if(left.asNumber() >= right.asNumber()) this->evaluated_value = Value(true);
                else this->evaluated_value = Value(false);
                break;
            case lum::TokenType::Less:
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for <", expr.bin_operator.line, expr.bin_operator.column);
                if(left.asNumber() < right.asNumber()) this->evaluated_value = Value(true);
                else this->evaluated_value = Value(false);
                break;
            case lum::TokenType::LessEqual:
                if(!left.isNumber() || !right.isNumber()) lum::Error::throw_and_return("invalid operands for <=", expr.bin_operator.line, expr.bin_operator.column);
                if(left.asNumber() <= right.asNumber()) this->evaluated_value = Value(true);
                else this->evaluated_value = Value(false);
                break;
            case lum::TokenType::EqualEqual:
                if(left.equals(right)) this->evaluated_value = Value(true);
                else this->evaluated_value = Value(false);
                break;
            case lum::TokenType::BangEqual:
                if(left.equals(right)) this->evaluated_value = Value(false);
                else this->evaluated_value = Value(true);
                break;
            default:
                lum::Error::throw_and_return("unrecognized binary operation: " + expr.bin_operator.lexeme, expr.bin_operator.line, expr.bin_operator.column);
                break;
        }
    }
    void Interpreter::visitUnaryExpr(UnaryExpr& expr) {
        Value right = evaluate(*expr.right_expression);
        switch(expr.unary_operator.type){
            case lum::TokenType::Bang:
                if(right.isTruthy()) this->evaluated_value = Value(false);
                else this->evaluated_value = Value(true);
                break;
            case lum::TokenType::Minus:
                if(right.isNumber()) this->evaluated_value = Value(-right.asNumber());
                else lum::Error::throw_and_return("invalid operand for unary: ", expr.unary_operator.line, expr.unary_operator.column);
                break;
            default:
                lum::Error::throw_and_return("unrecognized unary operation: " + expr.unary_operator.lexeme, expr.unary_operator.line, expr.unary_operator.column);
                break;
        }
    }

    void Interpreter::visitCallExpr(CallExpr& expr) {
        Value callee = evaluate(*expr.callee);
        std::vector<Value> args;

        if (!callee.isCallable()) {
           lum::Error::throw_and_return("value is not callable: " + callee.toString(), expr.paren.line, expr.paren.column);
        }

        for (const auto &arg : expr.arguments) {
          args.push_back(evaluate(*arg));
        }

        if (callee.isLumFunction()) {
          if(!(callee.asLumFunction()->arity() == args.size())) lum::Error::throw_and_return("expected arguments: " + std::to_string(callee.asLumFunction()->arity()) + "  received arguments: " + std::to_string(args.size()), expr.paren.line, expr.paren.column);
          else this->evaluated_value = callee.asLumFunction()->call(*this, args);
        } else if (callee.isNativeFunction()) {
          if(!(callee.asNativeFunction()->arity() == args.size())) lum::Error::throw_and_return("expected arguments: " + std::to_string(callee.asNativeFunction()->arity()) + "  received arguments: " + std::to_string(args.size()), expr.paren.line, expr.paren.column);
          else this->evaluated_value = callee.asNativeFunction()->call(*this, args);
        }
    }
    void Interpreter::visitAssignExpr(AssignExpr& expr) {
        Value right = evaluate(*expr.expression);
        this->environment->assign(expr.name, right);

        this->evaluated_value = right;
    }

    void Interpreter::visitLogicalExpr(LogicalExpr& expr) {
        Value left = evaluate(*expr.left_expression);

        switch (expr.logic_token.type) {
            case lum::TokenType::LogicalAND:
                if(!left.isTruthy()){
                    this->evaluated_value = left;
                }else{
                    Value right = evaluate(*expr.right_expression);
                    this->evaluated_value = right;
                }
                break;
            case lum::TokenType::LogicalOR:
                if(left.isTruthy()) this->evaluated_value = left;
                else{
                    Value right = evaluate(*expr.right_expression);
                    this->evaluated_value = right;
                }
                break;
            default:
                lum::Error::throw_and_return("invalid logical operation: " + expr.logic_token.lexeme, expr.logic_token.line, expr.logic_token.column);
                break;
        }
    }

    // produce side effects
    void Interpreter::visitExpressionStmt(ExpressionStmt &stmt) {
      Value result = evaluate(*stmt.expression);
      if (interactive_mode) {
        last_result = result;
      } else {
        last_result.reset();
      }
    }

    void Interpreter::visitBlockStmt(BlockStmt &stmt) {
      auto block_env = std::make_shared<Environment>(environment);
      executeBlock(stmt.statements, block_env);
    }
    void Interpreter::visitFunctionStmt(FunctionStmt &stmt) {
      auto func = std::make_shared<LumFunction>(stmt, environment);
      this->environment->define(stmt.func_name.lexeme, Value(func));

    }
    void Interpreter::visitReturnStmt(ReturnStmt &stmt) {
      if(stmt.return_expr != nullptr){
        auto return_val = evaluate(*stmt.return_expr);
        throw ReturnSignal(return_val);
    }
      else {
        auto return_val = Value();
        throw ReturnSignal(return_val);
    }
    }

    void Interpreter::visitIfStmt(IfStmt &stmt) {
      auto condition = evaluate(*stmt.condition);
      if (condition.isTruthy()) {
        visitBlockStmt(*stmt.then_branch);
      } else {
        if (stmt.else_branch != nullptr) {
          visitBlockStmt(*stmt.else_branch);
        }
      }
    }

    void Interpreter::visitWhileStmt(WhileStmt &stmt) {
      auto condition = evaluate(*stmt.condition);
      while(condition.isTruthy()) {
        visitBlockStmt(*stmt.while_block);
        condition = evaluate(*stmt.condition);
      }
    }

    Value Interpreter::evaluate(Expr& expr){
       expr.accept(*this);

        return this->evaluated_value;
    }
    void Interpreter::execute(Stmt& stmt){
        stmt.accept(*this);
    }
  void Interpreter::executeBlock(const std::vector<std::unique_ptr<Stmt>>& statements, std::shared_ptr<Environment> environment){
        EnvironmentGuard guard(*this, environment);

        for(auto& stmt: statements){
            stmt->accept(*this);
        }
    }

    Interpreter::EnvironmentGuard::EnvironmentGuard(Interpreter& interpreter, std::shared_ptr<Environment> new_env){
        this->interpreter = &interpreter;
        this->previous_env = interpreter.environment;
        this->interpreter->environment = std::move(new_env);
    }

    Interpreter::EnvironmentGuard::~EnvironmentGuard(){
        this->interpreter->environment = std::move(this->previous_env);
    }

    void Interpreter::emit(const Value &value, bool new_line,
                             bool to_stderr) {
      std::string text = value.toString();
      if (to_stderr) {
        new_line ? std::cerr << text << "\n" : std::cerr << text;
      } else {
        new_line ? std::cout << text << "\n" : std::cout << text;
      }
    }
}
