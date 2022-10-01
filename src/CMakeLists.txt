add_subdirectory(engine)
add_executable(blocky main.cpp)

if (EMSCRIPTEN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sUSE_SDL=2 --preload-file resources -sALLOW_MEMORY_GROWTH -O3")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    add_custom_command(TARGET blocky PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)
else()
    add_custom_command(TARGET blocky PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:blocky>/resources)
endif()

target_link_libraries(blocky PUBLIC engine)

