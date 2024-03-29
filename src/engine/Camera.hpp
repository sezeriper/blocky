#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace blocky {
struct Camera {
  float fov{75.0f};
  float aspect{1.0f};
  float near{0.01f};
  float far{1000.0f};

  float yaw{glm::radians(-90.0f)};
  float pitch{0.0f};

  glm::vec3 pos{0.0f};
  glm::vec3 front{0.0f};
  glm::vec3 right{0.0f};
  glm::vec3 up{0.0f};
  glm::vec3 ahead{0.0f};

  glm::mat4 proj{1.0f};
  glm::mat4 view{1.0f};


  static constexpr glm::vec3 worldUp{0.0f, 1.0f, 0.0f};

  void calcProjMat() {
    proj = glm::perspective(glm::radians(fov), aspect, near, far);
  }

  void calcViewMat() {
    front = glm::vec3(
      glm::cos(yaw) * glm::cos(pitch),
      glm::sin(pitch),
      glm::sin(yaw) * glm::cos(pitch)
    );

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));

    view = glm::lookAt(pos, pos + front, up);

    ahead = glm::cross(worldUp, right);
  }

  glm::mat4 getViewProjMat() const { return proj * view; }
};
} // namespace blocky