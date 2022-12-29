find_package(Curses REQUIRED)

set(lcdDebug_SOURCES
    "lcdDebug.cpp"
    Window.cpp 
    Window.hpp
)

add_executable(lcdDebug ${lcdDebug_SOURCES})
target_include_directories(lcdDebug PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(lcdDebug PRIVATE ${CURSES_LIBRARIES} LcdComCon)
