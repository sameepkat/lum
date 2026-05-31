#pragma once
#include <string>
#include <filesystem>

namespace lum {
  std::filesystem::path resolveStdModule(const std::string& name);
}
