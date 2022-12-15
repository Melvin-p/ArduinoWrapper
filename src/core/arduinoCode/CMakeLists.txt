set(PROJECT_SOURCES
        main.cpp
        sample.hpp
        sample.cpp
)

 add_executable(arduinoCode ${PROJECT_SOURCES})
 target_link_libraries(arduinoCode PUBLIC libArduinoWrapper)