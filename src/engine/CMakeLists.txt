add_library(engine INTERFACE)
target_link_libraries(engine INTERFACE EnTT imgui spdlog FastNoiseLite glm stb)

target_link_libraries(engine INTERFACE SDL2main SDL2-static)
target_link_libraries(engine INTERFACE glad)

target_include_directories(engine INTERFACE ${PROJECT_SOURCE_DIR}/src)
