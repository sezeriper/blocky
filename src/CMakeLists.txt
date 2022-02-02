add_subdirectory(engine)
add_executable(blocky main.cpp)

target_link_libraries(blocky PUBLIC engine)