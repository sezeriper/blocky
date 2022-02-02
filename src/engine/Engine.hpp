
#pragma once

#include <engine/Window.hpp>
#include <engine/gles2/Context.hpp>
#include <engine/gles2/Renderer.hpp>
#include <engine/Time.hpp>

namespace blocky
{
  struct Engine
  {
    void run()
    {
      create();
      while (window.is_running())
      {
        auto start = Time::millis();
        window.poll_events();
        update(deltaTime);
        context.swapClearBuffers();
        deltaTime = Time::millis() - start;
      }
    }

    virtual void create() = 0;
    virtual void update(Duration deltaTime) = 0;

  private:
    Window window{720, 720, "blocky"};
    Context context{window.get_window_ptr(), {0.1f, 0.1f, 0.1f, 0.1f}};

    Duration deltaTime = Time::millis();
  };
}