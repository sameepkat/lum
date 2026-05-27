#include "lum/runtime/function.hpp"
#include "lum/runtime/environment.hpp"
#include "lum/runtime/return_signal.hpp"
#include "lum/visitors/interpreter.hpp"
#include "lum/runtime/value.hpp"


namespace lum {
    LumFunction::LumFunction(FunctionStmt &declaration,
                            std::shared_ptr<Environment> closure) {
    this->declaration = &declaration;

    this->closure = closure;
    }

    int LumFunction::arity() const {
    return declaration->params.size();
    }

    std::string LumFunction::toString() const{
    return "<fn " + declaration->func_name.lexeme + ">";
    }

    Value LumFunction::call(Interpreter &interpreter,
                            const std::vector<Value> &arguments) {
    auto func_env = std::make_shared<Environment>(closure);
    for (size_t i=0; i<arguments.size(); ++i) {
        func_env->define(declaration->params[i].lexeme, arguments[i]);
    }
    try {
      interpreter.executeBlock(declaration->function_block->statements, func_env);
        return Value();
    } catch (ReturnSignal& rs) {
      return rs.value;
    }
    }
}
  

