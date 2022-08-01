#pragma once

#include <engine/TextureData.hpp>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

#include <vector>


namespace blocky {
TextureData downsample(const TextureData& texture) {
  auto width = texture.width / 2;
  auto height = texture.height / 2;

  TextureData out{width, height};

  for (std::size_t y = 0; y < height; ++y) {
    for (std::size_t x = 0; x < width; ++x) {
      const auto x2 = x*2;
      const auto y2 = y*2;

      glm::vec3 average = texture.getPixel(x2, y2);
      average += texture.getPixel(x2+1, y2);
      average += texture.getPixel(x2, y2+1);
      average += texture.getPixel(x2+1, y2+1);
      average /=  4.0f;

      out.setPixel(x, y, average);
    }
  }

  return out;
}

struct Mipmaps {
  Mipmaps(const TextureData& texture) {
    generateMipmaps(texture);
  }

  const TextureData& operator[](std::size_t level) const {
    return levels[level];
  }

  const std::size_t levelCount() const {
    return levels.size();
  }

private:
  std::vector<TextureData> levels;

  void generateMipmaps(const TextureData& texture) {
    const auto newLevel = downsample(texture);
    levels.emplace_back(newLevel);

    if (newLevel.width == 1 || newLevel.height == 1) return;

    generateMipmaps(newLevel);
  }
};
}
