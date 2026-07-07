#include "lum/error/error.hpp"
#include "lum/runtime/module_resolver.hpp"
#include <string>
#include <filesystem>

#ifndef LUM_STD_PATH
#define LUM_STD_PATH ""
#endif

namespace lum {
std::filesystem::path resolveStdModule(const std::string &name) {
  std::filesystem::path full_path;
  std::filesystem::path std_path = std::filesystem::path(LUM_STD_PATH) / (name + ".lum");
  std::filesystem::path dev_path = std::filesystem::path("std")/(name + ".lum");

  if(std::filesystem::exists(std_path)) {
    full_path = std::filesystem::path(std::filesystem::path(LUM_STD_PATH) / (name + ".lum"));
  } else if (std::filesystem::exists(dev_path)) {
    full_path = std::filesystem::path("std")/(name + ".lum");
  } else {
    lum::Error::throw_internal("can't resolve module name: " + name);
  }

  return full_path;
}
}
