#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>

namespace blocky
{
  struct Context
  {
    Context(GLFWwindow *window, const glm::vec4 &clear_color) : window(window)
    {
      glfwMakeContextCurrent(window);

      if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
        spdlog::error("opengl context creation failed");

      spdlog::info("vendor: {}", glGetString(GL_VENDOR));
      spdlog::info("renderer: {}", glGetString(GL_RENDERER));
      spdlog::info("version: {}", glGetString(GL_VERSION));

      glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    }

    void swapClearBuffers()
    {
      glfwSwapBuffers(window);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    static void frameBufferSizeCallback(GLFWwindow *, int width, int height)
    {
      glViewport(0, 0, width, height);
    }

  private:
    GLFWwindow *window;
  };
}