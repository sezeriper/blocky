#pragma once

#include <engine/Camera.hpp>
#include <engine/Time.hpp>
#include <engine/Engine.hpp>
#include <engine/gles2/Shader.hpp>
#include <engine/gles2/Renderer.hpp>
#include <engine/Timer.hpp>

#include <entt/entt.hpp>
#include <spdlog/spdlog.h>

#include <array>
#include <memory>

namespace blocky
{
  struct Game : Engine
  {
    Game()
    {
      std::array<GLfloat, 12> vertices{
          0.5f, 0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          -0.5f, -0.5f, 0.0f,
          -0.5f, 0.5f, 0.0f
      };

      std::array<GLuint, 6> indices{
          0, 1, 3,
          1, 2, 3
      };

      auto entity = registry.create();

      auto &mesh = registry.emplace<Renderer::Mesh>(entity);
      mesh = Renderer::makeMesh(vertices, indices);

      registry.emplace<Renderer::Transform>(entity, 1.0f);

      shader.use();

      camera.aspect = window.getWidth() / window.getHeight();
      camera.pos = glm::vec3{0.0f, 0.0f, 2.0f};
      camera.calcProjMat();

      window.vsyncOn();
    }

    void update(float deltaTime) override
    {
      spdlog::info("FPS: {}", 1000.0f / deltaTime);

      camera.yaw = window.getCursorPosX() * cursorSens;
      camera.pitch = -window.getCursorPosY() * cursorSens;
      camera.calcViewMat();
      shader.setUniform("viewProjMat", camera.getViewProjMat());

      Renderer::render(registry, shader);
    }

  private:
    entt::registry registry;
    Shader shader{"./shaders/flatcolor.vs", "./shaders/flatcolor.fs"};
    Camera camera;

    float cursorSens{0.002f};
  };
}