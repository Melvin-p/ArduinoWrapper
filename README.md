# ArduinoWrapper

## What is ArduinoWrapper

It is a wrapper/compatablity layer for Arduino code so that it can run on Windows, Linux and Mac OS (Probably other POSIX compliant systems)

## Idea
Change x.ino to x.cpp then add the include headers to the file, finally compile and link to this library

## Limitations
- The functions are internally different to Arduino’s standard functions so if you rely on this internal behaviour this library may not work.
- Due to how this wrapper works the memory constraints of the Arduino cannot be replicated.  
- There will differences in how serial communication is handled.
- GPIO Pins are not supported

## Plans
- Support Adafruit RGB LCD Shield Library
- automate the x.ino to x.exe process
- support EEPROM
- Maybe create CMake Package

## Build Instructions
### Dependecies
- CMake
- A modern C++ compiler (Supports C++ 17)
- A build system i.e UNIX make, Ninja Build
- A modern OS

Change directory into the project root

```
cmake --no-warn-unused-cli -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS:BOOL=TRUE -DBUILD_SHARED_LIBS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -G Ninja -B ./build
```
```
cmake --build build
```
### Build Notes
Ninja can be replaced with your preferred build system

## Development Enviroment
This project has VScode setup and is using clang format and clangd  
Please do note that clangd will only work once .cache folder is generated which is created during the build process

## Acknowledgements
A lot of code was taken from the Arduino Library
