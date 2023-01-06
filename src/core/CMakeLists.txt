# only build tests if tests enabled
if(tests)
    add_subdirectory(./test)
endif()

# only build lcd debugging utility if enabled
if(lcdDebug)
    add_subdirectory(./lcdDebug)
endif()

# used only for debugging purposes
# adds the arduino code builder to the build system
if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/arduinoCode")
    add_subdirectory(./arduinoCode)
endif()