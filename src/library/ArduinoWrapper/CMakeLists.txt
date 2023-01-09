set(PROJECT_SOURCES
    time.cpp
    time.hpp
    string.cpp
    string.hpp
    math.cpp
    math.hpp
    character.cpp
    character.hpp
    binary.cpp
    binary.hpp
    print.cpp
    print.hpp
    printable.hpp
    serial.cpp
    serial.hpp
    stream.cpp
    stream.hpp
    adwr.hpp
)

if(lcd_enabled)
    list(APPEND Adafruit_RGBLCDShield.hpp Adafruit_RGBLCDShield.cpp)
endif()

add_library(
    ArduinoWrapper
    ${PROJECT_SOURCES}
)

if(lcd_enabled)
    target_link_libraries(ArduinoWrapper PRIVATE LcdComProd)
    target_compile_definitions(ArduinoWrapper PUBLIC lcd_enabled)
endif()

target_compile_options(ArduinoWrapper PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/wd4996>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-declarations>
)


