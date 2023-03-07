set(PROJECT_SOURCES
    time.cpp
    string.cpp
    math.cpp
    character.cpp
    binary.cpp
    Print.cpp
    HardwareSerial.cpp
    Stream.cpp
)

#[===[
we can reuse these files in ArduinoTest. This provides the user of the ArduinoTest
abstraction over the barebones data streams
]===]
set(adwr_reuse_sources
    Stream.cpp
    Print.cpp
    time.cpp
)

add_library(
    adwr_reuse
    STATIC
    ${adwr_reuse_sources}
)

set_target_properties(adwr_reuse PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    EXCLUDE_FROM_ALL ON
)

target_compile_definitions(adwr_reuse PUBLIC use_std_str)
target_include_directories(adwr_reuse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(lcd_enabled)
    list(APPEND PROJECT_SOURCES Adafruit_RGBLCDShield.hpp Adafruit_RGBLCDShield.cpp)
endif()

add_library(
    ArduinoWrapper
    ${PROJECT_SOURCES}
)

if(lcd_enabled)
    target_link_libraries(ArduinoWrapper PRIVATE LcdProd)
    target_compile_definitions(ArduinoWrapper PUBLIC lcd_enabled)
endif()

if(ipc_serial)
    target_link_libraries(ArduinoWrapper PRIVATE SerialProd)
    target_compile_definitions(ArduinoWrapper PUBLIC ipc_serial)
endif()

target_include_directories(ArduinoWrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#[===[
If we are not compiling with pedantic enable the warning supperssion flags
some deceprecated functions used in ArduinoWrapper will raise warning on some compilers
when compiling in pedantic the pedantic switches are set globally from the root cmake file
]===]
target_compile_options(ArduinoWrapper PRIVATE
    $<$<NOT:$<BOOL:${pedantic}>>:
        $<$<CXX_COMPILER_ID:MSVC>:/wd4996>
        $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-declarations>
    >
)


