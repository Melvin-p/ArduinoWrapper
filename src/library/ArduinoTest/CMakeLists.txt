set(PROJECT_SOURCES
    HardwareSerial.cpp
)

add_library(
    ArduinoTest
    ${PROJECT_SOURCES}
)

target_link_libraries(ArduinoTest PUBLIC adwr_reuse PRIVATE SerialCon)
target_include_directories(ArduinoTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

