#pragma once

#include <game/ChunkSystem.hpp>
#include <game/FPSController.hpp>
#include <game/BlockMesh.hpp>

#include <engine/gles2/Texture.hpp>
#include <engine/Engine.hpp>
#include <engine/Camera.hpp>
#include <engine/gles2/Renderer.hpp>
#include <engine/gles2/Shader.hpp>

#include <entt/entt.hpp>
#include <spdlog/spdlog.h>


namespace blocky {
struct Game : Engine {

  void create() override {
    context.vsyncOn();
    window.getMouseMotionSink().connect<&FPSController::handleMouse>(fpsController);
  }

  void update(float deltaTime) override {
    fpsController.handleKeyboard(deltaTime, window);

    if (window.isPressed(SDLK_f)) {
      window.releaseMouse();
    } else {
      window.captureMouse();
    }

    createDebugUI(deltaTime);

    chunkSystem.update(registry, fpsController.camera.pos);

    shader.use();
    texture.use(shader);
    fpsController.use(shader);

    Renderer::render(registry, shader);
  }


private:
  entt::registry registry;
  Shader shader{"resources/shaders/textured.vert", "resources/shaders/textured.frag"};
  FPSController fpsController{window.getAspect()};

  float viewDistance{8.0f};
  ChunkSystem chunkSystem;

  Texture texture{"resources/textures/dirt.png"};

  void createDebugUI(float deltaTime) {
    ImGui::Begin("blocky control panel");

    ImGui::SliderFloat("view distance", &viewDistance, 1.0f, 128.0f);
    chunkSystem.setViewDistance(viewDistance);

    ImGui::Text("%.3f ms/frame (%.1f FPS)", deltaTime * 1000.0f, 1.0f / deltaTime);
    ImGui::End();
  }
};
}
