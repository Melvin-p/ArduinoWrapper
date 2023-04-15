set(PROJECT_SOURCES
    HardwareSerial.cpp
)

if(lcd_enabled)
    list(APPEND PROJECT_SOURCES LcdTest.cpp)
endif()

add_library(
    ArduinoTest
    ${PROJECT_SOURCES}
)

# link publicly so access to low level libraries are also possible
target_link_libraries(ArduinoTest PUBLIC adwr_reuse SerialCon LcdCon)
target_include_directories(ArduinoTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
