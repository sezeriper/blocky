add_library(engine INTERFACE)
target_link_libraries(engine INTERFACE EnTT glad glfw imgui spdlog)
target_include_directories(engine INTERFACE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/external ${PROJECT_SOURCE_DIR}/external/glm)