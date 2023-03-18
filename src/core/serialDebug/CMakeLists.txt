set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

if (Qt6_FOUND)

    message(STATUS "Qt6 found building serialDebug")

    add_executable(serialDebug
        ${PROJECT_SOURCES}
    )

    target_link_libraries(serialDebug PRIVATE Qt6::Widgets)
    target_link_libraries(serialDebug PRIVATE SerialCon)
    set_target_properties(serialDebug PROPERTIES
        WIN32_EXECUTABLE TRUE
    )

endif()
