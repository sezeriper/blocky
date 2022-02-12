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
      while (window.isRunning())
      {
        auto start = Time::millis();
        window.pollEvents();
        update(deltaTime);
        context.swapClearBuffers();
        deltaTime = Time::millis() - start;
      }
    }

    virtual void update(float deltaTime) = 0;

  protected:
    Window window{920, 720, "blocky"};
    Context context{window.getWindowPtr(), {0.1f, 0.1f, 0.1f, 0.1f}};
    float deltaTime{Time::millis()};
  };
}