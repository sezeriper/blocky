#pragma once

#include <engine/Time.hpp>
#include <engine/Window.hpp>
#include <engine/gles2/DebugGUI.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

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
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(advance, this, 0, true);
#else
    while (window.isRunning()) {
      advance(this);
    }
#endif
  }

protected:
  Context context;
  Window window;

  virtual void create() = 0;
  virtual void update(float deltaTime) = 0;

private:
  float deltaTime{Time::seconds()};

  static void advance(void* enginePtr) {
    Engine* engine = reinterpret_cast<Engine*>(enginePtr);
    auto start = Time::seconds();

    engine->context.prepBuffers();
    engine->window.pollEvents();
    DebugGUI::beginDraw();
    engine->update(engine->deltaTime);
    DebugGUI::endDraw();

    engine->deltaTime = Time::seconds() - start;
  }
};
} // namespace blocky