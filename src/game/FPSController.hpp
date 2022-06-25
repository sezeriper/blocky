#pragma once

#include <engine/Camera.hpp>
#include <engine/Window.hpp>
#include <engine/gles2/Shader.hpp>

#include <SDL.h>

namespace blocky {
struct FPSController {
  Camera camera{};
  float cursorSens{0.002f};
  float speed{32.0f};

  FPSController(float aspect) {
    camera.aspect = aspect;
    camera.pos = glm::vec3{0.0f, 140.0f, 0.0f};
    camera.calcProjMat();
    camera.calcViewMat();
  }

  void handleMouse(int32_t dx, int32_t dy) {
    auto xf = static_cast<float>(dx);
    auto yf = static_cast<float>(dy);

    camera.yaw += xf * cursorSens;
    camera.pitch -= yf * cursorSens;

    camera.pitch = glm::clamp(camera.pitch, glm::radians(-89.9f), glm::radians(89.9f));
  }

  void handleKeyboard(float deltaTime, const Window &window) {
    const auto scalar = speed * deltaTime;

    if (window.isPressed(SDLK_w)) {
      camera.pos += camera.ahead * scalar;
    }
    if (window.isPressed(SDLK_a)) {
      camera.pos -= camera.right * scalar;
    }
    if (window.isPressed(SDLK_s)) {
      camera.pos -= camera.ahead * scalar;
    }
    if (window.isPressed(SDLK_d)) {
      camera.pos += camera.right * scalar;
    }
    if (window.isPressed(SDLK_SPACE)) {
      camera.pos += Camera::worldUp * scalar;
    }
    if (window.isPressed(SDLK_LSHIFT)) {
      camera.pos -= Camera::worldUp * scalar;
    }

    camera.calcViewMat();
  }

  void use(Shader& shader) {
    shader.setUniform("u_view_proj_mat", camera.getViewProjMat());
  }
};
}
