#pragma once

#include <engine/Utils.hpp>

#include <SDL.h>
#include <spdlog/spdlog.h>
#include <entt/entt.hpp>
#include <backends/imgui_impl_sdl.h>

#include <functional>

namespace blocky {
struct Window {
  using MouseMotionListener = void(int32_t, int32_t);

  void setWindow(SDL_Window* newWindow) { window = newWindow; }

  SDL_Window* getSrc() const { return window; }

  float getAspect() const {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return static_cast<float>(w) / static_cast<float>(h);
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
  SDL_Window* window{};

  bool quit{false};
  bool handleMouse{true};

  entt::sigh<MouseMotionListener> mouseMotionSignal;
};
} // namespace blocky
