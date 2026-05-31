#pragma once

#include "lum/frontend/ast/stmt.hpp"
#include <vector>
#include <string>

namespace lum {
class FunctionDef {
public:
  FunctionDef(std::string, std::vector<Token>, std::unique_ptr<BlockStmt>);
  std::string name;
  std::vector<Token> params;
  std::unique_ptr<BlockStmt> body;
};
}
