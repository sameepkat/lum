#include "lum/visitors/ast_printer.hpp"
#include "lum/frontend/ast/expr.hpp"
#include "lum/frontend/ast/stmt.hpp"
#include <iostream>

namespace lum{

		void ASTPrinter::printIndent(){
						for(int i = 0; i < indent; ++i) std::cout << "  ";
		}

		void ASTPrinter::print(Program& program){
						std::cout << "Program\n";
						indent++;
						for(auto& stmt: program.statements){
										stmt->accept(*this);
						}
						indent--;
		}

		void ASTPrinter::visitLiteralExpr(LiteralExpr& expr){
						printIndent();
						std::cout << "Literal: " << expr.value.lexeme << "\n";
		}

		void ASTPrinter::visitVariableExpr(VariableExpr& expr){
						printIndent();
						std::cout << "Variable: " << expr.name.lexeme << "\n";
		}

		void ASTPrinter::visitBinaryExpr(BinaryExpr& expr){
						printIndent();
						std::cout << "BinaryExpr (" << expr.bin_operator.lexeme << ")\n";
						indent++;
						if(expr.left_expression) expr.left_expression->accept(*this);
						if(expr.right_expression) expr.right_expression->accept(*this);
						indent--;
		}

		void ASTPrinter::visitLogicalExpr(LogicalExpr& expr){
						printIndent();
						std::cout << "LogicalExpr: (" << expr.logic_token.lexeme << ")\n";
						indent++;
						if(expr.left_expression) expr.left_expression->accept(*this);
						if(expr.right_expression) expr.right_expression->accept(*this);
						indent--;
		}

		void ASTPrinter::visitUnaryExpr(UnaryExpr& expr){
						printIndent();
						std::cout << "UnaryExpr (" << expr.unary_operator.lexeme << ")\n";
						indent++;
						if(expr.right_expression) expr.right_expression->accept(*this);
						indent--;
		}

		void ASTPrinter::visitCallExpr(CallExpr& expr){
						printIndent();
						std::cout << "CallExpr\n";
						indent++;
						printIndent();
						std::cout << "Callee:\n";
						indent++;
						if(expr.callee) expr.callee->accept(*this);
						indent--;
						if(!expr.arguments.empty()){
										printIndent();
										std::cout << "Arguments:\n";
										indent++;
										for(auto& arg : expr.arguments){
														if(arg) arg->accept(*this);
										}
										indent--;
						}
						indent--;
		}

		void ASTPrinter::visitAssignExpr(AssignExpr& expr){
						printIndent();
						std::cout << "Assign: " << expr.name.lexeme << "\n";
						indent++;
						if(expr.expression) expr.expression->accept(*this);
						indent--;
		}

		void ASTPrinter::visitExpressionStmt(ExpressionStmt& stmt) {
						printIndent();
						std::cout << "ExpressionStmt\n";
						indent++;
						if(stmt.expression) stmt.expression->accept(*this);
						indent--;
		}

		void ASTPrinter::visitBlockStmt(BlockStmt& stmt) {
						printIndent();
						std::cout << "Block\n";
						indent++;
						for(auto& s : stmt.statements){
										if(s) s->accept(*this);
						}
						indent--;
		}

		void ASTPrinter::visitFunctionStmt(FunctionStmt& stmt) {
						printIndent();
						std::cout << "Function: " << stmt.func_name.lexeme << "\n";
						indent++;
						if(stmt.function_block) stmt.function_block->accept(*this);
						indent--;
		}

		void ASTPrinter::visitReturnStmt(ReturnStmt& stmt) {
						printIndent();
						std::cout << "Return\n";
						indent++;
						if(stmt.return_expr) stmt.return_expr->accept(*this);
						indent--;
		}

		void ASTPrinter::visitIfStmt(IfStmt& stmt) {
						printIndent();
						std::cout << "If\n";
						indent++;
						printIndent(); std::cout << "Condition:\n";
						indent++;
						if(stmt.condition) stmt.condition->accept(*this);
						indent--;
						if(stmt.then_branch) {
										printIndent(); std::cout << "Then:\n";
										indent++;
										stmt.then_branch->accept(*this);
										indent--;
						}
						if(stmt.else_branch) {
										printIndent(); std::cout << "Else:\n";
										indent++;
										stmt.else_branch->accept(*this);
										indent--;
						}
						indent--;
		}

		void ASTPrinter::visitWhileStmt(WhileStmt& stmt) {
						printIndent();
						std::cout << "While\n";
						indent++;
						printIndent(); std::cout << "Condition:\n";
						indent++;
						if(stmt.condition) stmt.condition->accept(*this);
						indent--;
						if(stmt.while_block) {
										printIndent(); std::cout << "Body:\n";
										indent++;
										stmt.while_block->accept(*this);
										indent--;
						}
						indent--;
		}

    void ASTPrinter::visitBreakStmt(BreakStmt& stmt) {
            printIndent();
            std::cout << "Break\n";
    }

    void ASTPrinter::visitContinueStmt(ContinueStmt &stmt) {
          printIndent();
          std::cout << "Continue\n";
    }

		void ASTPrinter::visitArrayExpr(ArrayExpr& expr) {
						printIndent();
						std::cout << "Array\n";
						indent++;
						printIndent(); std::cout << "Elements:\n";
						indent++;

						for (int i=0;  i < expr.array_elements.size() ; ++i) {
										expr.array_elements[i]->accept(*this);
						}

						indent--;
						indent--;
		}

		void ASTPrinter::visitIndexExpr(IndexExpr &expr) {
						printIndent();
						std::cout << "Index\n";
						indent++;

						printIndent();
						std::cout << "Target\n";
						indent++;
						expr.target->accept(*this);
						indent--;

						printIndent();
						std::cout << "Element\n";
						indent++;
						expr.index->accept(*this);
						indent--;

						indent--;
		}

		void ASTPrinter::visitSetIndexExpr(SetIndexExpr &expr) {
						printIndent();
						std::cout << "SetIndex\n";
						indent++;

						printIndent();
						std::cout << "Target\n";
						indent++;
						expr.target->accept(*this);
						indent--;

						printIndent();
						std::cout << "Index\n";
						indent++;
						expr.index->accept(*this);
						indent--;

						printIndent();
						std::cout << "Value\n";
						indent++;
						expr.value->accept(*this);
						indent--;

						indent--;
		}

		void ASTPrinter::visitUseStmt(UseStmt& stmt) {
						printIndent();
						std::cout << "Use\n";
						indent++;

						printIndent();
						std::cout << stmt.module_name.lexeme << "\n";
						indent--;

		}


		void ASTPrinter::visitObjectExpr(ObjectExpr &expr) {
						printIndent();
						std::cout << "Object\n";
						indent++;

						printIndent();
						std::cout << "Fields\n";
						indent++;

						for (const auto& field: expr.items) {
										printIndent();
										std::cout << "Field: " << field.key.lexeme << "\n";
										indent++;
										if (field.value) field.value->accept(*this);
										indent--;
						}

						indent--;
						indent--;
		}

		void ASTPrinter::visitPropertyExpr(PropertyExpr &expr) {
						printIndent();
						std::cout << "Property\n";
						indent++;

						printIndent();
						std::cout << "Target\n";
						indent++;
						expr.target->accept(*this);
						indent--;

						printIndent();
						std::cout << "Key\n";
						indent++;
						std::cout << expr.key.lexeme << "\n";
						indent--;

						indent--;
		}

		void ASTPrinter::visitSetPropertyExpr(SetPropertyExpr &expr) {
						printIndent();
						std::cout << "SetProperty\n";
						indent++;

						printIndent();
						std::cout << "Target\n";
						indent++;
						expr.target->accept(*this);
						indent--;

						printIndent();
						std::cout << "Key\n";
						indent++;
						std::cout << expr.key.lexeme <<"\n";
						indent--;

						printIndent();
						std::cout << "Value\n";
						indent++;
						expr.value->accept(*this);
						indent--;

						indent--;

		}
}
