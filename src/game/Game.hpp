#pragma once

#include <engine/Engine.hpp>
#include <engine/gles2/Shader.hpp>
#include <engine/gles2/Renderer.hpp>
#include <engine/Timer.hpp>

#include <entt/entt.hpp>

#include <array>
#include <memory>

namespace blocky
{
  struct Game : Engine
  {
    void create() override
    {
      std::array<GLfloat, 12> vertices{
          0.5f, 0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          -0.5f, -0.5f, 0.0f,
          -0.5f, 0.5f, 0.0f};

      std::array<GLuint, 6> indices{
          0, 1, 3,
          1, 2, 3};

      for (std::size_t i = 0; i < 10000; ++i)
      {
        auto entity = registry.create();
        auto &mesh = registry.emplace<Renderer::Mesh>(entity);
        mesh = Renderer::makeMesh(vertices, indices);
      }

      shader.use();
    }

    void update(Duration delta_time) override
    {
      Timer timer;
      Renderer::render(registry, shader);
    }

  private:
    entt::registry registry;
    Shader shader{"../../src/game/shaders/flatcolor.vs", "../../src/game/shaders/flatcolor.fs"};
  };
}