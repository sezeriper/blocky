#pragma once

#include <engine/Utils.hpp>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <glad/glad.h>

namespace blocky {
struct Shader {
  Shader() = default;

  Shader(std::filesystem::path vertSrcPath, std::filesystem::path fragSrcPath) {
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

    auto vertSrc = Utils::readFile(vertSrcPath);
    auto vertSrcPtr = vertSrc.c_str();

    auto fragSrc = Utils::readFile(fragSrcPath);
    auto fragSrcPtr = fragSrc.c_str();

    glShaderSource(vert, 1, &vertSrcPtr, nullptr);
    glShaderSource(frag, 1, &fragSrcPtr, nullptr);

    glCompileShader(vert);
    glCompileShader(frag);

    checkError(vert);
    checkError(frag);

    program = glCreateProgram();

    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    glDeleteShader(vert);
    glDeleteShader(frag);
  }

  ~Shader() { glDeleteProgram(program); }

  void use() { glUseProgram(program); }

  template <typename Type>
  void setUniform(const char *name, const Type &value) {
    const auto location = glGetUniformLocation(program, name);

    if constexpr (std::is_same_v<Type, glm::mat4x4>) {
      glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    }

    if constexpr (std::is_same_v<Type, GLint>) {
      glUniform1i(location, value);
    }
  }

private:
  GLuint program{0};

  void checkError(GLuint ID) {
    GLint result{GL_FALSE};
    GLint infoSize{0};

    glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &infoSize);

    if (infoSize > 0) {
      std::string error(infoSize, '\0');
      glGetShaderInfoLog(ID, infoSize, nullptr, error.data());
      spdlog::error(error.data());
    }
  }
};
}
