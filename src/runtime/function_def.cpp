#include "lum/frontend/ast/stmt.hpp"
#include "lum/runtime/function_def.hpp"
#include <vector>

namespace lum {
  FunctionDef::FunctionDef(std::string name, std::vector<Token> params, std::unique_ptr<BlockStmt> body): name(std::move(name)), params(std::move(params)), body(std::move(body)){}
}
