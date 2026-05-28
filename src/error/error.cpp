#include "lum/error/error.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

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

    [[noreturn]] void Error::throw_and_return(std::string msg, int line, int pos){
        throw std::runtime_error(
        msg
        + " at line: "
        + std::to_string(line)
        + " and pos: "
        + std::to_string(pos)
        );
    }

  void Error::throw_msg(std::string msg) {
      std::cerr << RED << msg << RESET << std::endl;
    }

  [[noreturn]] void Error::throw_parse(std::string msg, int line, int pos) {
        throw std::runtime_error(
        msg
        + " at line: "
        + std::to_string(line)
        + " and pos: "
        + std::to_string(pos)
        );
     }
     void Error::throw_internal(std::string msg) {
       
        throw std::runtime_error(msg);
     }
}
