#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include <spdlog/spdlog.h>

namespace blocky
{
  namespace Utils
  {
    std::string readFile(std::filesystem::path path)
    {
      std::ifstream stream(path, std::ios::in | std::ios::binary);
      if (!stream.is_open())
      {
        spdlog::error("can't open file {}", path.c_str());
      }

      const auto size = std::filesystem::file_size(path);
      std::string result(size, '\0');

      stream.read(result.data(), size);

      return result;
    }
  }
}