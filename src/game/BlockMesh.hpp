#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <array>

namespace blocky {
namespace BlockMesh {

  constexpr std::array<glm::vec3, 8> blockPositions {
      glm::vec3(0.0f, 0.0f, 0.0f), // 0
      glm::vec3(1.0f, 0.0f, 0.0f), // 1
      glm::vec3(1.0f, 1.0f, 0.0f), // 2
      glm::vec3(0.0f, 1.0f, 0.0f), // 3
      glm::vec3(0.0f, 0.0f, 1.0f), // 4
      glm::vec3(1.0f, 0.0f, 1.0f), // 5
      glm::vec3(1.0f, 1.0f, 1.0f), // 6
      glm::vec3(0.0f, 1.0f, 1.0f), // 7
  };

  constexpr std::array<GLuint, 36> blockIndices {
    0, 1, 2, // Fron Face
    0, 2, 3,

    5, 4, 7, // Back Face
    5, 7, 6,

    1, 5, 6, // Right Face
    1, 6, 2,

    4, 0, 3, // Left Face
    4, 3, 7,

    3, 2, 6, // Top Face
    3, 6, 7,

    4, 5, 1, // Bottom Face
    4, 1, 0,
  };
}
}
