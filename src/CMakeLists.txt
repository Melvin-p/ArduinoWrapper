add_subdirectory(./library/)

set(PROJECT_SOURCES
main.cpp
main.hpp
)

add_executable(ArduinoWrapper-test ${PROJECT_SOURCES})
target_link_libraries(ArduinoWrapper-test PUBLIC ArduinoWrapper)