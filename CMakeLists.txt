cmake_minimum_required(VERSION 3.20)
project(ArduinoWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

option(BUILD_SHARED_LIBS "SHARED_LIBRARY" ON)
option(INTERACTIVE "Build in interactive mode" OFF)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(WIN)
    message(WARNING "Windows detected UNTESTED UNSUPPORTED")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(LINUX)
    message(STATUS "Compling For Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(LINUX)
    message(WARNING "Mac OS detected UNTESTED UNSUPPORTED")
endif()

if (NOT ((CMAKE_CXX_COMPILER_ID STREQUAL "Clnag") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")))
    message(FATAL_ERROR "Unsupported compiler")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_subdirectory(./src/)

set(CMAKE_SKIP_INSTALL_RULES True)