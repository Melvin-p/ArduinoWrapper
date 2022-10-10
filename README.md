# ArduinoWrapper

## What is ArduinoWrapper

It is a wrapper/compatablity layer for Arduino code so that it can run on Windows, Linux and Mac OS (Probably other POSIX compliant systems)

## Idea
Change x.ino to x.cpp then include headers to the file, finally compile and link to this library

## Limitations
- The functions are internally different to Arduino’s standard functions so if you rely on undocumented behaviour this library may not work.
- Due to how this wrapper works the memory constraints of the Arduino cannot be replicated.  
- There will differences in how serial communication is handled.
- GPIO Pins are not supported

## Plans
- Output a shared library that can linked to (Windows DLL Issues)
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
cmake --no-warn-unused-cli --graphviz=./build/Release/target_graph.dot -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -G Ninja -B ./build
```
```
cmake --build build
```
### Further Notes
Ninja can be replaced with your preferred build system
graphviz can be removed if graphviz is not installed

## Development Enviroment
This project has VScode setup and is using clang format and clangd  
Please do note that clangd will only work once .cache file is generated which is created during the build process

## Acknowledgements
A lot of code was taken from the Arduino Library
