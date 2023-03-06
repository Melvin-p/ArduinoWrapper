set(PROJECT_SOURCES
        main.cpp
)

add_executable(arduinoCodeTest
        ${PROJECT_SOURCES}
)

target_link_libraries(arduinoCodeTest PRIVATE ArduinoTest)