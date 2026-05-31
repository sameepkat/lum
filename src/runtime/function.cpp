#include "lum/runtime/function.hpp"
#include "lum/runtime/environment.hpp"
#include "lum/runtime/return_signal.hpp"
#include "lum/visitors/interpreter.hpp"
#include "lum/runtime/value.hpp"
#include "lum/runtime/function_def.hpp"


namespace lum {
  LumFunction::LumFunction(const std::shared_ptr<FunctionDef> &declaration,
                            std::shared_ptr<Environment> closure) {
    this->definition = declaration;

    this->closure = closure;
    }

    int LumFunction::arity() const {
    return definition->params.size();
    }

    std::string LumFunction::toString() const{
      //     return "<fn " + definition.func_name.lexeme + ">";
      return "<fn " + definition->name + ">";
    }

    Value LumFunction::call(Interpreter &interpreter,
                            const std::vector<Value> &arguments) {
    auto func_env = std::make_shared<Environment>(closure);
    for (size_t i=0; i<arguments.size(); ++i) {
        func_env->define(definition->params[i].lexeme, arguments[i]);
    }
    try {
      interpreter.executeBlock(definition->body->statements, func_env);
        return Value();
    } catch (ReturnSignal& rs) {
      return rs.value;
    }
    }
}
  

