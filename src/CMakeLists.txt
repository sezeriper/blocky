add_subdirectory(engine)
add_executable(blocky main.cpp)

target_link_libraries(blocky PUBLIC engine)

add_custom_command(TARGET blocky PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:blocky>/resources)
