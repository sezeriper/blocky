#pragma once

#include <engine/Utils.hpp>
#include <engine/Window.hpp>
#include <engine/gles2/Context.hpp>

#include <SDL.h>
#include <glad/glad.h>

#include <cstdint>

namespace blocky {
  void createSDLOpenGL(int width, int height, const char *title, Window& windowContainer, Context& contextContainer) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
      Utils::printSDLError();
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_WindowFlags flags = (SDL_WindowFlags)(
      SDL_WINDOW_OPENGL |
      SDL_WINDOW_RESIZABLE |
      SDL_WINDOW_ALLOW_HIGHDPI
    );

    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              flags);

    if (!window) {
      Utils::printSDLError();
    }

  SDL_GLContext context = SDL_GL_CreateContext(window);

    if (context == NULL) {
      Utils::printSDLError();
    }

    SDL_GL_MakeCurrent(window, context);
    
    if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
      spdlog::error("opengl context creation failed");
    }

    spdlog::info("vendor: {}", glGetString(GL_VENDOR));
    spdlog::info("renderer: {}", glGetString(GL_RENDERER));
    spdlog::info("version: {}", glGetString(GL_VERSION));

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    windowContainer.setWindow(window);
    contextContainer.setContext(context);
  }

  void destroySDLOpenGL(const Window& window, const Context& context) {
    SDL_GL_DeleteContext(context.getSrc());
    SDL_DestroyWindow(window.getSrc());
    SDL_Quit();
  }
}
