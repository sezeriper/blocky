#pragma once

#include <engine/Utils.hpp>
#include <engine/gles2/Context.hpp>

#include <SDL.h>
#include <spdlog/spdlog.h>
#include <entt/entt.hpp>
#include <backends/imgui_impl_sdl.h>

#include <functional>

namespace blocky {
struct Window {
  using MouseMotionListener = void(int32_t, int32_t);

  void createWindow(int width, int height, const char *title, uint32_t flags) {
    this->width = width;
    this->height = height;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              flags);

    if (!window) {
      Utils::printSDLError();
    }
  }

  ~Window() { SDL_Quit(); }

  SDL_Window *getPtr() { return window; }

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
      ImGui_ImplSDL2_ProcessEvent(&event);
      switch(event.type) {
        case SDL_QUIT:
          quit = true;
        break;
        case SDL_MOUSEMOTION:
          if (handleMouse) {
            mouseMotionSignal.publish(event.motion.xrel, event.motion.yrel);
          }
        break;
      }
    }
  }

  bool isPressed(SDL_Keycode key) const {
    const uint8_t *state = SDL_GetKeyboardState(nullptr);
    return state[SDL_GetScancodeFromKey(key)];
  }

  auto getMouseMotionSink() {
    return entt::sink{mouseMotionSignal};
  }

  void releaseMouse() {
    SDL_SetRelativeMouseMode(SDL_FALSE);
    handleMouse = false;
  }

  void captureMouse() {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    handleMouse = true;
  }

private:
  SDL_Window *window{};

  bool quit{false};
  bool handleMouse{true};

  int width{};
  int height{};

  entt::sigh<MouseMotionListener> mouseMotionSignal;
};
} // namespace blocky
