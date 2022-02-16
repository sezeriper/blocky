add_library(engine INTERFACE)
target_link_libraries(engine INTERFACE EnTT imgui spdlog)

if(NOT EMSCRIPTEN)
	target_link_libraries(engine INTERFACE SDL2main SDL2-static)
	target_link_libraries(engine INTERFACE glad)
endif()

target_include_directories(engine INTERFACE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/external ${PROJECT_SOURCE_DIR}/external/glm)