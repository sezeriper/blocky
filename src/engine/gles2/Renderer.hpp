#pragma once

#include <engine/gles2/Shader.hpp>

#include <entt/entt.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace blocky
{
  namespace Renderer
  {
    using Buffer = GLuint;

    struct Mesh
    {
      Buffer vertBuf;
      Buffer elmBuf;
      GLsizei elmCount;
    };

    using Transform = glm::mat4;

    constexpr GLsizei getSize(const auto &data)
    {
      return data.size() * sizeof(data[0]);
    }

    Mesh makeMesh(const auto &vertices, const auto &indices)
    {
      Buffer vertBuf{0};
      Buffer elmBuf{0};

      glGenBuffers(1, &vertBuf);
      glGenBuffers(1, &elmBuf);

      glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elmBuf);

      glBufferData(GL_ARRAY_BUFFER, getSize(vertices), vertices.data(), GL_STATIC_DRAW);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, getSize(indices), indices.data(), GL_STATIC_DRAW);

      return {vertBuf, elmBuf, static_cast<GLsizei>(indices.size())};
    }

    void destroyMesh(const Mesh &mesh)
    {
      glDeleteBuffers(1, &mesh.vertBuf);
      glDeleteBuffers(1, &mesh.elmBuf);
    }

    void drawMesh(const Mesh &mesh)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.elmBuf);
      glBindBuffer(GL_ARRAY_BUFFER, mesh.vertBuf);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);
      glEnableVertexAttribArray(0);
      glDrawElements(GL_TRIANGLES, mesh.elmCount, GL_UNSIGNED_INT, 0);
    }

    void render(const entt::registry &registry, Shader &shader)
    {
      auto view = registry.view<const Mesh, const Transform>();

      for (const auto &[entity, mesh, transform] : view.each())
      {
        shader.setUniform("modelMat", transform);
        drawMesh(mesh);
      }
    }
  }
}