#pragma once

#include <SDL.h>

namespace blocky {
namespace Time {

static const auto epoch{SDL_GetPerformanceCounter()};

float seconds() {
  return static_cast<float>(SDL_GetPerformanceCounter() - epoch) /
         static_cast<float>(SDL_GetPerformanceFrequency());
}

float millis() { return seconds() * 1000.0f; }

}
}
