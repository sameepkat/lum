#pragma once

#include "lum/frontend/ast/stmt.hpp"
#include "lum/runtime/environment.hpp"
#include <memory>
#include <string>
#include <vector>

namespace lum {
    class Interpreter;
    class LumFunction{
    public:
      LumFunction(FunctionStmt &declaration,
                  std::shared_ptr<Environment> closure);

      int arity() const;
      Value call(Interpreter &interpreter, const std::vector<Value> &arguments);
      std::string toString() const;

    private:
      FunctionStmt *declaration;
      std::shared_ptr<Environment> closure;
    };
}
