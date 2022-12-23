add_subdirectory(./test)
add_subdirectory(./lcdDebug)
# used only for debugging purposes
# adds the arduino code builder to the build system
if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/arduinoCode")
    add_subdirectory(./arduinoCode)
endif()