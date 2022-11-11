set(PROJECT_SOURCES
        main.cpp
        sample.hpp
        sample.cpp
)

 add_executable(ardCode ${PROJECT_SOURCES})
 target_link_libraries(ardCode PUBLIC ArduinoWrapper)