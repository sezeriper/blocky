#pragma once

#include <engine/Time.hpp>
#include <engine/Window.hpp>

namespace blocky {
struct Engine {
  Engine() {
    context.initSDL();
    window.createWindow(920, 720, "blocky", SDL_WINDOW_OPENGL);
    context.createGLContext(window.getPtr(), {0.1f, 0.1f, 0.1f, 1.0f});
    DebugGUI::init(context.getContext(), window.getPtr());
  }

  ~Engine() {
    DebugGUI::destroy();
  }

  void run() {
    create();
    while (window.isRunning()) {
      auto start = Time::seconds();

      context.prepBuffers();
      window.pollEvents();
      DebugGUI::beginDraw();
      update(deltaTime);
      DebugGUI::endDraw();

      deltaTime = Time::seconds() - start;
    }
  }

protected:
  Context context;
  Window window;

  virtual void create() = 0;
  virtual void update(float deltaTime) = 0;

private:
  float deltaTime{Time::seconds()};
};
} // namespace blocky