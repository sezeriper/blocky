#pragma once

#include "sdl/include/SDL_timer.h"
#include <SDL2/SDL.h>

namespace blocky {
namespace Time {
float second() {
  return static_cast<float>(SDL_GetPerformanceCounter()) /
         static_cast<float>(SDL_GetPerformanceFrequency());
}

float millis() { return second() * 1000.0f; }
} // namespace Time
} // namespace blocky