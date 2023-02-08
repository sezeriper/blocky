add_subdirectory(engine)
add_executable(blocky main.cpp)

if (EMSCRIPTEN)
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sUSE_SDL=2 --preload-file resources -sALLOW_MEMORY_GROWTH -g -sASSERTIONS=2 -sSTACK_SIZE=536870912 -sINITIAL_MEMORY=1073741824 -sSAFE_HEAP=1 -sDEMANGLE_SUPPORT=1")
    # set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_compile_options(blocky PRIVATE --preload-file resources -sALLOW_MEMORY_GROWTH -g -sASSERTIONS=2 -sSTACK_SIZE=536870912 -sINITIAL_MEMORY=1073741824 -sSAFE_HEAP=1 -sDEMANGLE_SUPPORT=1)
    target_link_options(blocky PRIVATE -sUSE_SDL=2)
    add_custom_command(TARGET blocky PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)
else()
    add_custom_command(TARGET blocky PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:blocky>/resources)
endif()

target_link_libraries(blocky PUBLIC engine)

