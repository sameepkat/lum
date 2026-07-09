#include "lum/stdlib/fs_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"
#include <fstream>
#include <sstream>
#include <string>

namespace lum {

std::string expand_tilde(const std::string &p){
  if (p.size() >= 1 && p[0] == '~') {
    const char* home = std::getenv("HOME");
    if (home) {
      if(p.size() == 1) return std::string(home);
      if (p[1] == '/' || p[1] == '\\') return std::string(home) + p.substr(1);
    }
  }
  return p;
}
Value __read_file(Interpreter &interpreter, const std::vector<Value> &args) {
  std::string path = args[0].asString();
  std::string userPath = expand_tilde(path);

  std::ifstream in(userPath, std::ios::in);
  if(!in) lum::Error::throw_msg("failed to open file: " + userPath);

  std::ostringstream ss;
  ss << in.rdbuf();
  return Value(ss.str());
}
Value __write_file(Interpreter &interpreter, const std::vector<Value> &args) {
  std::string path = args[0].asString();
  std::string val = args[1].asString();
  std::string userPath = expand_tilde(path);

  std::ofstream out(userPath, std::ios::out);
  if (!out)
    lum::Error::throw_msg("failed to open file: " + userPath);

  out << val;
  
  return Value();
}

Value __append_file(Interpreter &interpreter, const std::vector<Value> &args) {

  std::string path = args[0].asString();
  std::string val = args[1].asString();
  std::string userPath = expand_tilde(path);

  std::ofstream out(userPath, std::ios::app);
  if (!out)
    lum::Error::throw_msg("failed to open file: " + userPath);

  out << val;

  return Value();
}
}
