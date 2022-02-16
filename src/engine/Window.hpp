#pragma once

#include <engine/Utils.hpp>
#include <engine/gles2/Context.hpp>

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

#include <memory>

namespace blocky {
struct Window {
  Window(int width, int height, const char *title) : width(width), height(height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_OPENGL);

    if (!window) {
      Utils::printSDLError();
    }
  }

  ~Window() { SDL_Quit(); }

  SDL_Window *getPtr() { return window; }

  float getCursorPosX() const { return cursorX; }
  float getCursorPosY() const { return cursorY; }

  int getWidth() const {
    return width;
  }

  int getHeight() const {
    return height;
  }

  float getAspect() const {
    return static_cast<float>(width) / static_cast<float>(height);
  }

  bool isRunning() const { return !quit; }

  void pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

private:
  SDL_Window *window{};

  bool quit{false};
  bool firstMouseMotion{true};

  float cursorX{};
  float cursorY{};

  int width{};
  int height{};
};
} // namespace blocky