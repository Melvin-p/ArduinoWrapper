set(PROJECT_SOURCES
    HardwareSerial.cpp
    LcdTest.cpp
)

add_library(
    ArduinoTest
    ${PROJECT_SOURCES}
)

# link publicly so access to low level libraries are also possible
target_link_libraries(ArduinoTest PUBLIC adwr_reuse SerialCon LcdComCon)
target_include_directories(ArduinoTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
