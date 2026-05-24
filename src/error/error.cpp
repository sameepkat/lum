#include "lum/error/error.hpp"
#include <iostream>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

namespace lum{
    Error::Error(std::string msg) : msg(std::move(msg)){}

    void Error::throw_err(std::string msg, int line, int pos){
        std::cerr
        << RED
        << msg
        << BOLD
        << " at line: "
        << line
        << " and pos: "
        << pos
        << RESET
        << std::endl;
    }
}
