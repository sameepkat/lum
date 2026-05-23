#include "lum/error/error.hpp"
#include <iostream>

namespace lum{
    Error::Error(std::string msg) : msg(std::move(msg)){}

    void Error::throw_err(std::string msg, int line, int pos){
        std::cerr
        << msg
        << " at line: "
        << line
        << " and pos: "
        << pos - 1
        << std::endl;
    }
}
