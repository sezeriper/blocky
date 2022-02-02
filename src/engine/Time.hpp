#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace blocky
{
  using Duration = float;

  namespace Time
  {
    Duration second() { return glfwGetTime(); }
    Duration millis() { return glfwGetTime() * 1000.0; }
  }
};