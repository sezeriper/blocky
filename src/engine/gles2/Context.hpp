#pragma once

#include <engine/Utils.hpp>

#include <glad/glad.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

namespace blocky {
struct Context {
  void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      Utils::printSDLError();
    }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  }

  void createGLContext(SDL_Window *windowPtr, const glm::vec4 &clearColor) {
    window = windowPtr;

    context = SDL_GL_CreateContext(window);
    if (!context) {
      Utils::printSDLError();
    }

    if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
      spdlog::error("opengl context creation failed");
    }

    spdlog::info("vendor: {}", glGetString(GL_VENDOR));
    spdlog::info("renderer: {}", glGetString(GL_RENDERER));
    spdlog::info("version: {}", glGetString(GL_VERSION));

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
  }

  SDL_GLContext getContext() const {
    return context;
  }

  void vsyncOn() {
    SDL_GL_SetSwapInterval(1);
  }

  void vsyncOff() {
    SDL_GL_SetSwapInterval(0);
  }

  void prepBuffers() {
    SDL_GL_SwapWindow(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

private:
  SDL_Window *window{};
  SDL_GLContext context;
};
} // namespace blocky
