add_subdirectory(./library/adwr)

if(BUILD_TESTS)
    set(PROJECT_SOURCES
        main.cpp
    )

    add_executable(ArduinoWrapper-test ${PROJECT_SOURCES})
    target_link_libraries(ArduinoWrapper-test PUBLIC ArduinoWrapper)
endif()