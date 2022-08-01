#pragma once

#include <engine/TextureData.hpp>
#include <engine/gles2/Shader.hpp>
#include <engine/Mipmaps.hpp>

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace blocky {
struct TextureAtlas {
  TextureAtlas (const char* path) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    TextureData textureData(path);
    Mipmaps mipmaps(textureData);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.data);

    for (std::size_t i = 0; i < mipmaps.levelCount(); ++i) {
      glTexImage2D(GL_TEXTURE_2D, i+1, GL_RGB, mipmaps[i].width, mipmaps[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, mipmaps[i].data);
    }
  }

  ~TextureAtlas () {
    glDeleteTextures(1, &texture);
  }

  void use(Shader& shader) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.setUniform("u_texture", 0);
  }

private:
  GLuint texture;
};
}
