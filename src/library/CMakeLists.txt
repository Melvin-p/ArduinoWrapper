add_library(
    ArduinoWrapper
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
)

target_compile_options(ArduinoWrapper PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/wd4996>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-declarations>
)
