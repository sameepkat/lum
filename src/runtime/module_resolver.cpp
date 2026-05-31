#include "lum/error/error.hpp"
#include "lum/runtime/module_resolver.hpp"
#include <string>
#include <filesystem>

namespace lum {
std::filesystem::path resolveStdModule(const std::string &name) {
  std::filesystem::path full_path = std::filesystem::path("std")/(name + ".lum");

  if (!std::filesystem::exists(full_path)) {
    lum::Error::throw_internal("can't resolve module name: " + name);
  }

  return full_path;
}
}
