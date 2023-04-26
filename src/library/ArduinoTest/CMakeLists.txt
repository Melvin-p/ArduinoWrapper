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

if(lcd_enabled)
    target_compile_definitions(ArduinoTest PUBLIC lcd_enabled)
endif()

if(eeprom_enabled)
    target_compile_definitions(ArduinoTest PUBLIC eeprom_enabled)
endif()

# link publicly so access to low level libraries are also possible
target_link_libraries(ArduinoTest PUBLIC adwr_reuse SerialCon LcdCon eepromCon)
target_include_directories(ArduinoTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
