cmake_minimum_required(VERSION 3.20)
project(ArduinoWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# project options
option(BUILD_SHARED_LIBS "SHARED_LIBRARY" ON)
option(lcdDebug "Build lcd viewer" ON)
option(tests "Build tests" ON)
option(lcd_enabled "Build with support for lcd" ON)
option(serialDebug "Build serial monitor" ON)
option(ipc_serial "Build with support for serial over IPC" ON)
option(pedantic "build with all warning" OFF)
option(lto "build with link time optimisation" ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(WIN)
    message(WARNING "Windows detected UNTESTED UNSUPPORTED")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(LINUX)
    message(VERBOSE "Compiling For Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(LINUX)
    message(WARNING "Mac OS detected UNTESTED UNSUPPORTED")
else()
    message(WARNING "Unknown OS dectected")
endif()

if (NOT ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")))
    message(WARNING "Unsupported compiler")
else()
    message(VERBOSE "compiler okay")
    # if compiler okay then warning flags can be added if they are turned on
    if(pedantic)
        add_compile_options(-Wpedantic -Wall -Wextra)
    endif()
endif()

# enable link time optimisation if enabled and supported
if(lto)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_support OUTPUT output)
    if(ipo_support)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_subdirectory(./src/)

set(CMAKE_SKIP_INSTALL_RULES True)