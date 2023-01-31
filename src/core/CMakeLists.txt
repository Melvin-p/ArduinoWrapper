# only build tests if tests enabled
if(tests)
    add_subdirectory(./test)
endif()

# only build lcd debugging utility if enabled and lcd functionality enabled
if(lcdDebug AND lcd_enabled)
    add_subdirectory(./lcdDebug)
endif()

# only build serial debugging utility if enable and serial IPC functionality enabled
if(serialDebug AND ipc_serial)
    add_subdirectory(serialDebug)
endif()

# used only for debugging purposes
# adds the arduino code builder to the build system
if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/arduinoCode")
    add_subdirectory(./arduinoCode)
endif()
