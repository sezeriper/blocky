add_library(engine INTERFACE)
target_link_libraries(engine INTERFACE imgui EnTT spdlog FastNoiseLite glm stb glad)

if (NOT EMSCRIPTEN)
	target_link_libraries(engine INTERFACE SDL2main SDL2-static)
endif()

target_include_directories(engine INTERFACE ${PROJECT_SOURCE_DIR}/src)
