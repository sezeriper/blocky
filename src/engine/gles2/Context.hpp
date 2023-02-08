#pragma once

#include <engine/Utils.hpp>
#include <engine/Window.hpp>

#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

namespace blocky {
struct Context {
  void setContext(SDL_GLContext newContext) { context = newContext; }

  SDL_GLContext getSrc() const {
    return context;
  }

  void vsyncOn() {
    SDL_GL_SetSwapInterval(1);
  }

  void vsyncOff() {
    SDL_GL_SetSwapInterval(0);
  }

  void prepBuffers(const Window& window) {
    SDL_GL_SwapWindow(window.getSrc());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

private:
  SDL_GLContext context;
};
} // namespace blocky
