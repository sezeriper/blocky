#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>


namespace blocky {
constexpr int channelCount{3};
using Pixel = glm::u8vec3;

struct TextureData {
  Pixel* data{nullptr};
  int width{0};
  int height{0};

  TextureData(const char* path) {
    data = reinterpret_cast<Pixel*>(stbi_load(path, &width, &height, nullptr, channelCount));
    if (!data) {
      spdlog::error("Failed to load texture {}", path);
    }
  }

  TextureData(int width, int height) :
    data(reinterpret_cast<Pixel*>(STBI_MALLOC(width * height * sizeof(Pixel)))), width(width), height(height) {}

  TextureData(const TextureData& other) : TextureData(other.width, other.height) {
    std::memcpy(data, other.data, width * height * sizeof(Pixel));
  }

  TextureData& operator=(const TextureData& other) {
    if (this == &other) {
      return *this;
    }

    width = other.width;
    height = other.height;
    data = reinterpret_cast<Pixel*>(STBI_MALLOC(width * height * sizeof(Pixel)));

    std::memcpy(data, other.data, width * height * sizeof(Pixel));

    return *this;
  }

  ~TextureData() {
    STBI_FREE(data);
  }

  Pixel getPixel(std::size_t x, std::size_t y) const {
    return data[y * width + x];
  }

  void setPixel(std::size_t x, std::size_t y, const Pixel& pixel) {
    data[y * width + x] = pixel;
  }
};
}
