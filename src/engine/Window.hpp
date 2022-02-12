#pragma once

#include <memory>
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

      glfwSetErrorCallback(errorCallback);

      glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
      glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

      window = glfwCreateWindow(width, height, title, nullptr, nullptr);
      if (!window)
      {
        spdlog::error("window creation failed");
        glfwTerminate();
      }

      glfwSetWindowUserPointer(window, this);

      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      glfwSetCursorPosCallback(window, cursorPosCallback);

      glfwSetFramebufferSizeCallback(window, Context::frameBufferSizeCallback);
    }

    ~Window()
    {
      glfwDestroyWindow(window);
      glfwTerminate();
    }

    float getCursorPosX() const { return cursorX; }
    float getCursorPosY() const { return cursorY; }

    float getWidth() const {
      int width{ 0 };
      glfwGetWindowSize(window, &width, nullptr);
      return static_cast<float>(width);
    }

    float getHeight() const {
      int height{ 0 };
      glfwGetWindowSize(window, nullptr, &height);
      return static_cast<float>(height);
    }

    bool isRunning() const { return !glfwWindowShouldClose(window); }

    void pollEvents() { glfwPollEvents(); }

    GLFWwindow *getWindowPtr() { return window; }

    void vsyncOn() {
      glfwSwapInterval(1);
    }

    void vsyncOff() {
      glfwSwapInterval(0);
    }

  private:
    GLFWwindow *window{};

    bool firstMouseMotion{ true };

    float cursorX{};
    float cursorY{};

    static void errorCallback(int error, const char *description)
    {
      spdlog::error(description);
    }

    static void cursorPosCallback(GLFWwindow* win, double xpos, double ypos) {
      auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));

      if (window->firstMouseMotion) {
        glfwSetCursorPos(window->getWindowPtr(), 0.0, 0.0);
        window->firstMouseMotion = false;
        return;
      }

      window->cursorX = static_cast<float>(xpos);
      window->cursorY = static_cast<float>(ypos);
    }
  };
}