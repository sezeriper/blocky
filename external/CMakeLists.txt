add_subdirectory(glfw)

add_subdirectory(entt)

add_subdirectory(spdlog)

add_subdirectory(glm)

set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE)
add_subdirectory(FastNoise2)

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

add_library(imgui imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp)