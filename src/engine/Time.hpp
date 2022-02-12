#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace blocky
{
  namespace Time
  {
    float second() { return glfwGetTime(); }
    float millis() { return glfwGetTime() * 1000.0; }
  }
};