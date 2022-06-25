#pragma once

#include <engine/gles2/Shader.hpp>
#include <engine/gles2/Texture.hpp>

#include <entt/entt.hpp>

namespace blocky {
namespace Renderer {

using Transform = glm::mat4;

struct Vertex {
    constexpr Vertex(glm::vec3 position, glm::vec2 uvs) : position(position), uvs(uvs) {}

    glm::vec3 position;
    glm::vec2 uvs;
};

using Index = GLuint;

using Buffer = GLuint;

struct Mesh {
  Buffer vertBuf;
  Buffer idxBuf;
  GLsizei elmCount;
};

Buffer makeVertexBuffer(const auto& vertices) {
  Buffer vertBuf{0};
  glGenBuffers(1, &vertBuf);
  glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

  return vertBuf;
}

Buffer makeIndexBuffer(const auto& indices) {
  Buffer idxBuf{0};
  glGenBuffers(1, &idxBuf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBuf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Index), indices.data(), GL_STATIC_DRAW);

  return idxBuf;
}

Mesh makeMesh(const auto& vertices, const auto& indices) {
  return {
    makeVertexBuffer(vertices),
      makeIndexBuffer(indices),
      static_cast<GLsizei>(indices.size())
  };
}

void destroyBuffer(const Buffer& buffer) {
  glDeleteBuffers(1, &buffer);
}

void destroyMesh(const Mesh& mesh) {
  destroyBuffer(mesh.vertBuf);
  destroyBuffer(mesh.idxBuf);
}

void drawMesh(const Mesh& mesh) {
  glBindBuffer(GL_ARRAY_BUFFER, mesh.vertBuf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.idxBuf);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(glm::vec3));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glDrawElements(GL_TRIANGLES, mesh.elmCount, GL_UNSIGNED_INT, nullptr);
}

void render(const entt::registry& registry, Shader& shader) {
  auto view = registry.view<const Mesh, const Transform>();

  for (const auto &[entity, mesh, transform] : view.each()) {
    shader.setUniform("u_model_mat", transform);
    drawMesh(mesh);
  }
}
}
}
