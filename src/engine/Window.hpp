#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include <engine/gles2/Context.hpp>

namespace blocky
{
  struct Window
  {
    Window(int width, int height, const char *title)
    {
      if (!glfwInit())
      {
        spdlog::error("glfw initialization failed");
      }

      glfwSetErrorCallback(error_callback);

      glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
      glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

      window_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
      if (!window_ptr)
      {
        spdlog::error("window creation failed");
        glfwTerminate();
      }

      glfwSetFramebufferSizeCallback(window_ptr, Context::frameBufferSizeCallback);
    }

    ~Window()
    {
      glfwDestroyWindow(window_ptr);
      glfwTerminate();
    }

    bool is_running() const { return !glfwWindowShouldClose(window_ptr); }

    void poll_events() { glfwPollEvents(); }

    GLFWwindow *get_window_ptr() { return window_ptr; }

  private:
    GLFWwindow *window_ptr;

    static void error_callback(int error, const char *description)
    {
      spdlog::error(description);
    }
  };
}