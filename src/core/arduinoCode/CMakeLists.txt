set(PROJECT_SOURCES
        main.cpp
        sample.hpp
)

add_library(
        inner
        STATIC
        sample_private.hpp
        sample.cpp
)

cmake_path(SET include_file "${CMAKE_CURRENT_LIST_DIR}/sample_private.hpp")

target_link_libraries(inner PUBLIC ArduinoWrapper)
target_compile_options(inner PRIVATE
    $<$<NOT:$<BOOL:${WIN32}>>:
            $<$<CXX_COMPILER_ID:GNU>:-include ${include_file}>
            $<$<CXX_COMPILER_ID:Clang>:-include ${include_file}>
    >
)

add_executable(arduinoCode ${PROJECT_SOURCES})
target_link_libraries(arduinoCode PRIVATE inner)


