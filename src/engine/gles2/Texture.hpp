#pragma once

#include <engine/TextureData.hpp>
#include <engine/gles2/Shader.hpp>

#include <glad/glad.h>

namespace blocky {
struct Texture {
  Texture(const char* path) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    TextureData textureData(path);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  ~Texture() {
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
