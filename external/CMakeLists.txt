add_subdirectory(entt)

add_subdirectory(spdlog)

add_subdirectory(glm)

if(NOT EMSCRIPTEN)
	set(SDL_STATIC ON CACHE BOOL "" FORCE)
	set(SDL_SHARED OFF CACHE BOOL "" FORCE)
	add_subdirectory(sdl)

	add_library(glad glad/src/glad.c)
	target_include_directories(glad PUBLIC glad/include)
endif()

add_library(imgui imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp)