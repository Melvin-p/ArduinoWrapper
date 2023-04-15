add_subdirectory(./lcd)
add_subdirectory(./ArduinoWrapper)
add_subdirectory(./EEPROM)
add_subdirectory(./serial)

# testing framework only supported with serial over IPC
if(ipc_serial)
    add_subdirectory(./ArduinoTest)
endif()