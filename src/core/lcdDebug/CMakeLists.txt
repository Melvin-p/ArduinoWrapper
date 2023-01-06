set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if (Qt6_FOUND)

    message(STATUS "Qt6 found building lcdDebug")

    add_executable(lcdDebug
        ${PROJECT_SOURCES}
    )

    target_link_libraries(lcdDebug PRIVATE Qt6::Widgets LcdComCon)

    set_target_properties(lcdDebug PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
