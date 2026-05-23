#pragma once

#include "lum/frontend/ast/stmt.hpp"
#include <memory>
#include <vector>

namespace lum{
    class Program{
    public:
        std::vector<std::unique_ptr<Stmt>> statements;
    };
}
