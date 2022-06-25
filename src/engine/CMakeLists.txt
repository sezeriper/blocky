add_library(engine INTERFACE)
target_link_libraries(engine INTERFACE EnTT imgui spdlog FastNoiseLite glm stb)

target_link_libraries(engine INTERFACE SDL2main SDL2-static)
target_link_libraries(engine INTERFACE glad)

target_include_directories(engine INTERFACE ${PROJECT_SOURCE_DIR}/src)

target_compile_options(engine INTERFACE -fsanitize=address)
target_link_options(engine INTERFACE -fsanitize=address)
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0) 
