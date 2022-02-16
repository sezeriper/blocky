#pragma once

#include <engine/Utils.hpp>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#ifdef __EMSCRIPTEN__
#include <GLES2/gl2.h>
#else
#include <glad/glad.h>
#endif

namespace blocky {
struct Context {
  Context() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      Utils::printSDLError();
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  }

  void create(SDL_Window *windowPtr, const glm::vec4 &clear_color) {
    window = windowPtr;

    auto context = SDL_GL_CreateContext(window);
    if (!context) {
      Utils::printSDLError();
    }

#ifndef __EMSCRIPTEN__
    if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress))
      spdlog::error("opengl context creation failed");
#endif

    spdlog::info("vendor: {}", glGetString(GL_VENDOR));
    spdlog::info("renderer: {}", glGetString(GL_RENDERER));
    spdlog::info("version: {}", glGetString(GL_VERSION));

    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
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
  SDL_Window *window;
};
} // namespace blocky