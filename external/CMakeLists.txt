if(NOT EMSCRIPTEN)
	add_subdirectory(glfw)
endif()

add_subdirectory(entt)

add_subdirectory(spdlog)

add_subdirectory(glm)

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

add_library(imgui imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp)