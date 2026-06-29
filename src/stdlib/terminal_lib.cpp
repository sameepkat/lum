#include "lum/stdlib/terminal_lib.hpp"
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"
#include <iostream>

namespace lum {
lum::Value __clear(lum::Interpreter &interpreter, const std::vector<lum::Value> &args){
  std::system("clear");
	return lum::Value();
}

lum::Value __cursor_up(lum::Interpreter &interpreter,
                       const std::vector<lum::Value> &args) {
    int n = static_cast<int>(args[0].asNumber());
    
    std::cout << "\x1b[" << n << "A";
    std::cout.flush();
    return Value();
}

lum::Value __hide_cursor(lum::Interpreter &interpreter, const std::vector<lum::Value> &args){
    std::cout << "\x1b[?25l" ;
    std::cout.flush();
    return Value();
}

lum::Value __show_cursor(lum::Interpreter &interpreter, const std::vector<lum::Value> &args){
    std::cout << "\x1b[?25h" ;
    std::cout.flush();
    return Value();
}

lum::Value __flush(lum::Interpreter &interpreter, const std::vector<lum::Value> &args){
    std::cout.flush();
    return Value();
}
}
