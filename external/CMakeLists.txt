add_subdirectory(entt)
add_subdirectory(spdlog)
add_subdirectory(glm)

if (NOT EMSCRIPTEN)
	set(SDL_STATIC ON CACHE BOOL "" FORCE)
	set(SDL_SHARED OFF CACHE BOOL "" FORCE)
	add_subdirectory(SDL)
endif()

add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

add_library(imgui imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_sdl.cpp)
target_include_directories(imgui PUBLIC imgui)
if (EMSCRIPTEN)
	target_compile_options(imgui PRIVATE "-sUSE_SDL=2")
else()
	target_include_directories(imgui PUBLIC SDL/include)
endif()

add_library(FastNoiseLite INTERFACE)
target_include_directories(FastNoiseLite INTERFACE FastNoiseLite/Cpp)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE stb)
