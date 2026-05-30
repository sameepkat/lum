#include "lum/frontend/parser/parser.hpp"
#include "lum/frontend/ast/expr.hpp"
#include "lum/frontend/ast/stmt.hpp"
#include "lum/frontend/lexer/token.hpp"
#include "lum/error/error.hpp"
#include <memory>
#include <utility>

namespace lum{
   Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)){}

   const Token& Parser::peekToken() const{
        if(static_cast<unsigned long>(currentTokenIndex) < tokens.size())
            return tokens[currentTokenIndex];
        else
            return tokens.back();
   }

   TokenType Parser::currentTokenType() const {
       return peekToken().type;
   }

   const Token& Parser::advanceToken() {
       if(peekToken().type == TokenType::EndOfFile){
           return tokens.back();
       }
       return tokens[currentTokenIndex++];
   }

   bool Parser::isTokEOF() const {
       return peekToken().type == TokenType::EndOfFile;
    }

    const Token& Parser::previousToken() const{
        return tokens[currentTokenIndex-1];
    }

    bool Parser::check(TokenType type) const{
       return currentTokenType() == type;
    }

    bool Parser::match(TokenType type){
        if(check(type)){
            advanceToken();
            return true;
        }

        return false;
    }

    const Token& Parser::consume(TokenType type, std::string message){
        if(check(type)) return  advanceToken();
        lum::Error::throw_parse(message, peekToken().line, peekToken().column);
    }

    void Parser::skipNewLines(){
        while(match(TokenType::NewLine));
    }

    std::unique_ptr<Stmt> Parser::parseDeclaration(){
        if(match(TokenType::Fn)){
            return parseFunctionDeclaration();
        }
        return parseStatement();
    }

    void Parser::finishStatement(std::string err_msg){
        if(!match(TokenType::NewLine) && !(check(TokenType::RightBrace) || isTokEOF())){
            lum::Error::throw_parse(err_msg, previousToken().line, previousToken().column);
        }else{
            skipNewLines();
        }
    }

    std::unique_ptr<FunctionStmt> Parser::parseFunctionDeclaration(){
        this->functionDepth++;
        auto func = std::make_unique<FunctionStmt>();

        func->func_name = consume(TokenType::Identifier, "expect function name");
        consume(TokenType::LeftParen, "expect '(' after function name");

        if(!check(TokenType::RightParen)){
            do{
                func->params.push_back(consume(TokenType::Identifier, "expect parameter name"));
            }while(match(TokenType::Comma));
        }
        consume(TokenType::RightParen, "expect ')' after parameters.");
        consume(TokenType::LeftBrace, "expect '{' after function declaration");
        func->function_block = parseBlock();
        this->functionDepth--;

        return func;
    }

    std::unique_ptr<BlockStmt> Parser::parseBlock(){
        auto block = std::make_unique<BlockStmt>();

        while(!check(TokenType::RightBrace) && !isTokEOF()){
            skipNewLines();
            if(isTokEOF()) break;
            auto decl = parseDeclaration();
            if(decl) block->statements.push_back(std::move(decl));
            // else advanceToken();
        }

        consume(TokenType::RightBrace, "expect '}' after block");
        return block;
    }

    std::unique_ptr<Stmt> Parser::parseStatement(){
        if(match(TokenType::Return)) return parseReturn();
        if(match(TokenType::If)) return parseIf();
        if(match(TokenType::While)) return parseWhile();
        if(match(TokenType::LeftBrace)){
            auto block = parseBlock();
            return block ? std::unique_ptr<Stmt>(block.release()) : nullptr;
        }

        return parseExpressionStmt();
    }

    std::unique_ptr<ExpressionStmt> Parser::parseExpressionStmt(){
        auto expr = parseExpression();

        auto s = std::make_unique<ExpressionStmt>();
        s->expression = std::move(expr);

        finishStatement("expected newline after statement");
        return s;
    }

    std::unique_ptr<Expr> Parser::parseExpression(){
        return parseAssignment();
        // if(match(TokenType::LogicalOR)) parseLogicalOR();
        // if(match(TokenType::LogicalAND)) parseLogicalAND();
        // if(match(TokenType::EqualEqual)) parseBinaryComparison();
        // if(match(TokenType::EqualEqual)) parseTerm();
        // if(match(TokenType::EqualEqual)) parseFactor();
        // if(match(TokenType::EqualEqual)) parseUnary();
        // if(match(TokenType::EqualEqual)) parseCall();
        // if(match(TokenType::EqualEqual)) parsePrimary();
    }

    std::unique_ptr<Expr> Parser::parseAssignment(){
       auto expr = parseLogicalOR();

       if(match(TokenType::Equal)){
           Token equals = previousToken();
           auto value = parseAssignment();

           if(auto* var = dynamic_cast<VariableExpr*>(expr.get())){
               auto assign = std::make_unique<AssignExpr>();
               assign->name = var->name;
               assign->expression = std::move(value);
               return assign;
           } else if (auto *arr = dynamic_cast<IndexExpr *>(expr.get())) {
             auto assign = std::make_unique<SetIndexExpr>();
             assign->target = std::move(arr->target);
             assign->index = std::move(arr->index);
             assign->value = std::move(value);
             assign->right_bracket = std::move(arr->right_bracket);

             return assign;
           }

           lum::Error::throw_parse("invalid assignment target", equals.line, equals.column);
       }

       return expr;
    }

    std::unique_ptr<Expr> Parser::parseLogicalOR(){
        auto expr = parseLogicalAND();

        while(match(TokenType::LogicalOR)){
            Token or_symbol = previousToken();
            auto right = parseLogicalAND();

            auto logical = std::make_unique<LogicalExpr>();
            logical->logic_token = or_symbol;
            logical->left_expression = std::move(expr);
            logical->right_expression = std::move(right);
            expr = std::move(logical);
        }

        return expr;
    }

    std::unique_ptr<Expr> Parser::parseLogicalAND(){
		auto expr = parseEquality();

		while(match(TokenType::LogicalAND)){
			Token and_symbol = previousToken();
            auto right = parseEquality();

            auto logical = std::make_unique<LogicalExpr>();
            logical->logic_token = and_symbol;
            logical->left_expression = std::move(expr);
            logical->right_expression = std::move(right);
            expr = std::move(logical);
		}

		return expr;
	}
	std::unique_ptr<Expr> Parser::parseEquality(){
        auto expr = parseComparison();

        while(match(TokenType::EqualEqual) ||
            match(TokenType::BangEqual)
        ){
           Token symbol = previousToken();
           auto right = parseComparison();

           auto val = std::make_unique<BinaryExpr>();
           val->left_expression = std::move(expr);
           val->bin_operator = symbol;
           val->right_expression = std::move(right);
           expr = std::move(val);
        }

        return expr;
    }

    std::unique_ptr<Expr> Parser::parseComparison(){
        auto expr = parseTerm();

        while(match(TokenType::GreaterEqual) ||
            match(TokenType::Greater) ||
            match(TokenType::Less) ||
            match(TokenType::LessEqual)
        ){
           Token symbol = previousToken();
           auto right = parseTerm();

           auto val = std::make_unique<BinaryExpr>();
           val->left_expression = std::move(expr);
           val->bin_operator = symbol;
           val->right_expression = std::move(right);
           expr = std::move(val);
        }

        return expr;
    }

    std::unique_ptr<Expr> Parser::parseTerm(){ // +, -
        auto expr = parseFactor();

        while(match(TokenType::Plus) ||
            match(TokenType::Minus)
        ){
            Token symbol = previousToken();
            auto right = parseFactor();

            auto val = std::make_unique<BinaryExpr>();
            val->left_expression = std::move(expr);
            val->bin_operator = symbol;
            val->right_expression = std::move(right);
            expr = std::move(val);
        }

        return expr;
    }

    std::unique_ptr<Expr> Parser::parseFactor(){ // +, -
        auto expr = parseUnary();

        while(match(TokenType::Star) ||
            match(TokenType::Slash) ||
            match(TokenType::Percent)
        ){
            Token symbol = previousToken();
            auto right = parseUnary();

            auto val = std::make_unique<BinaryExpr>();
            val->left_expression = std::move(expr);
            val->bin_operator = symbol;
            val->right_expression = std::move(right);
            expr = std::move(val);
        }

        return expr;
    }

    std::unique_ptr<Expr> Parser::parseUnary(){
        if(match(TokenType::Bang) || match(TokenType::Minus)){
            Token symbol = previousToken();
            auto right = parseUnary();

            auto expr = std::make_unique<UnaryExpr>();
            expr->unary_operator = symbol;
            expr->right_expression = std::move(right);
            return expr;
        }
        return parseCall();
    }

    std::unique_ptr<Expr> Parser::parseCall(){
        auto expr = parsePrimary();

        while(true){
            if(match(TokenType::LeftParen)){
            auto call = std::make_unique<CallExpr>();
            call->callee = std::move(expr);

            while(!check(TokenType::RightParen) && !isTokEOF()){
                call->arguments.push_back(parseExpression());
                skipNewLines();
                if(!match(TokenType::Comma)) break;
            }
            call->paren = consume(TokenType::RightParen, "expect ')' after arguments.");
            expr = std::move(call);
            }else if (match(TokenType::LeftBracket)) {
              auto arr = parseIndex(std::move(expr));

              expr = std::move(arr);

            } else {
                break;
            }
        }
        return expr;
    }


  std::unique_ptr<Expr> Parser::parseIndex(std::unique_ptr<Expr> target) {
      auto index_expr = std::make_unique<IndexExpr>();
      index_expr->target = std::move(target);
      index_expr->index = parseExpression();
      index_expr->right_bracket = consume(TokenType::RightBracket, "expected ']' after array index ");

      return index_expr;
    }

    std::unique_ptr<ReturnStmt> Parser::parseReturn(){
        auto stmt = std::make_unique<ReturnStmt>();
        stmt->return_token = previousToken();

          if (functionDepth>0) {
            if(!(check(TokenType::NewLine) || check(TokenType::RightBrace) || isTokEOF())){
            stmt->return_expr = parseExpression();
            }
          }else {
            lum::Error::throw_parse("top-level return not allowed", stmt->return_token.line, stmt->return_token.column);
          }
        finishStatement("expected newline after return");
        return stmt;
    }

    std::unique_ptr<IfStmt> Parser::parseIf(){
        auto stmt = std::make_unique<IfStmt>();
        stmt->if_token = previousToken();
        stmt->condition = parseExpression();
        consume(TokenType::LeftBrace, "expect { after if condition");
        stmt->then_branch = parseBlock(); // if branch
        skipNewLines();
        if(match(TokenType::Else)){
            consume(TokenType::LeftBrace, "expect '{' after else");
            stmt->else_branch = parseBlock();
        }

        return stmt;
    }

    std::unique_ptr<WhileStmt> Parser::parseWhile(){
        auto stmt = std::make_unique<WhileStmt>();
        stmt->while_token = previousToken();
        stmt->condition = parseExpression();
        consume(TokenType::LeftBrace, "expect '{' after while condition");
        stmt->while_block = parseBlock();


        return stmt;
    }

    std::unique_ptr<Expr> Parser::parsePrimary(){
        if(match(TokenType::Number) || match(TokenType::String) || match(TokenType::True) || match(TokenType::False) || match(TokenType::Nil)){
            Token value = previousToken();
            auto lit = std::make_unique<LiteralExpr>();
            lit->value = value;
            return lit;
        }

        if(match(TokenType::Identifier)){
            Token name = previousToken();
            auto var = std::make_unique<VariableExpr>();
            var->name = name;
            return var;
        }

        if(match(TokenType::LeftParen)){
            auto expr = parseExpression();
            consume(TokenType::RightParen, "expect ')' after expression.");
            return expr;
        }

        if(match(TokenType::LeftBracket)){
            auto expr = parseArray();
            return expr;
        }

        lum::Error::throw_parse("expected expression", peekToken().line, peekToken().column);
    }


  std::unique_ptr<Expr> Parser::parseArray() {
          auto array = std::make_unique<ArrayExpr>();

        while(!check(TokenType::RightBracket) && !isTokEOF()){
          array->array_elements.push_back(parseExpression());
          if(!match(TokenType::Comma)) break;
        }
        array->bracket =
            consume(TokenType::RightBracket, "expect ']' after array elements.");

      return array;
    }

   std::unique_ptr<Program>  Parser::parse(){
       std::unique_ptr<Program> program = std::make_unique<Program>();

       while(!isTokEOF()){
           skipNewLines();
           if(isTokEOF()) break;

           auto decl = parseDeclaration();
            if(decl) program->statements.push_back(std::move(decl));
       }
       return program;
   }

}
