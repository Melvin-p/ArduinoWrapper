cmake_minimum_required(VERSION 3.20)
project(ArduinoWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

option(BUILD_SHARED_LIBS "SHARED_LIBRARY" ON)
option(INTERACTIVE "Build in interactive mode" OFF)
option(BUILD_TESTS "Build Tests" ON)
option(CONSUMER "turn on if unit test exe\
controls if the application clears shared memory before creating shared memory and clears shared memory on termination\
leave off for ArduinoWrapper library" 
OFF)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(WIN)
    message(STATUS "Compling For Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(LINUX)
    message(STATUS "Compling For Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(LINUX)
    message(WARNING "Mac OS Detected")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

if(INTERACTIVE)
     add_compile_definitions(INTERACTIVE)
endif()

if(CONSUMER)
    add_compile_definitions(CONSUMER)
endif()


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_subdirectory(./src/)

set(CMAKE_SKIP_INSTALL_RULES True)