set(PROJECT_SOURCES
        main.cpp
)

add_library(
        inner
        OBJECT
        sample.cpp
)

cmake_path(SET include_file "${CMAKE_CURRENT_LIST_DIR}/sample_private.hpp")

target_link_libraries(inner PUBLIC ArduinoWrapper)
target_compile_options(inner PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-include ${include_file}>
        $<$<CXX_COMPILER_ID:Clang>:-include ${include_file}>
        $<$<CXX_COMPILER_ID:MSVC>:/FI ${include_file}>
)

add_executable(arduinoCode ${PROJECT_SOURCES})
target_link_libraries(arduinoCode PRIVATE SerialProd) 
target_link_libraries(arduinoCode PRIVATE inner)
