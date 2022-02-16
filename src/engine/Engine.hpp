#pragma once

#include <engine/Time.hpp>
#include <engine/Window.hpp>
#include <engine/gles2/Context.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace blocky {
struct Engine {
  Engine() { context.create(window.getPtr(), {0.1f, 0.1f, 0.1f, 0.1f}); }

  void run() {
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(loop, reinterpret_cast<void *>(this), 0, 1);
#else
    while (window.isRunning())
      loop(this);
#endif
  }

protected:
  Context context;
  Window window{920, 720, "blocky"};

  virtual void create() = 0;
  virtual void update(float deltaTime) = 0;

private:
  float deltaTime{Time::millis()};
  bool firstRun{true};

  static void loop(void *voidPtr) {
    auto start = Time::millis();
    Engine &engine = *reinterpret_cast<Engine *>(voidPtr);

    if (engine.firstRun) {
      engine.create();
      engine.firstRun = false;
    }

    engine.window.pollEvents();
    engine.update(engine.deltaTime);
    engine.context.prepBuffers();

    engine.deltaTime = Time::millis() - start;
  }
};
} // namespace blocky