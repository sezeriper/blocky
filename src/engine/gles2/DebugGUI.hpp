#pragma once

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

namespace blocky {
namespace DebugGUI {

  void init(SDL_GLContext context, SDL_Window* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 100");
  }

  void destroy() {
  	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  }

  void beginDraw() {
  	ImGui_ImplOpenGL3_NewFrame();
  	ImGui_ImplSDL2_NewFrame();
  	ImGui::NewFrame();
  }

  void endDraw() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
};
} // namespace blocky
