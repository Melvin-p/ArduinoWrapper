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
- LCD is assumed to be 16 by 2 and each character to be 5 pixels across and 7 pixels down

## Plans
- Support Adafruit RGB LCD Shield Library
- automate the x.ino to x.exe process
- may have to parse the c++ file and modify it before linking to library
- support EEPROM
- Maybe create CMake Package

## Build Instructions
### Dependecies
- CMake
- A recent version of **gcc or clang** (must support C++ 17)
- A build system i.e UNIX make, Ninja Build
- **A Linux based operating system** (Ubuntu recommended **Mac OS untested assume not supported** )
- VCPKG Used for handling the boost library dependencies Find install instructions [here](https://github.com/microsoft/vcpkg)

Some boost libraries are required, use the following VCPKG command to install them
```
vcpkg install boost-interprocess:x64-linux boost-serialization:x64-linux
```

Open a terminal navigate to repository root then the two CMake commands below can be run. Add the appropriate path to to your vcpkg.cmake. If you don't have Ninja installed run ```cmake.exe -g --help``` and select a suitable generator. Built binaries are in the output folder.

This command generates the build files in the build directory

```
cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Release -DVCPKG_TARGET_TRIPLET:STRING=x64-linux -DCMAKE_TOOLCHAIN_FILE=[Path To Your vcpkg.cmake] -DBUILD_SHARED_LIBS:BOOL=TRUE -G Ninja -B ./build
```  
This command actually builds the library or exectutable
```
cmake --build build
```

### Build Notes & Options
Make shared library. On by default
```
-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS:BOOL=TRUE -DBUILD_SHARED_LIBS:BOOL=TRUE
```  
Builds the library in interactive mode. This allows graphical serial IO, LCD and buttons
```
-DINTERACTIVE:BOOL=TRUE
```  
Builds the executable that runs the unit tests for the library
```
-DBUILD_TESTS:BOOL=TRUE
```
If there is a compile error try deleting the build directory and re-running the commands

## Development Enviroment
This project has VScode setup and is using clang format and clangd  
Please do note that clangd will only work once .cache folder is generated which is created during the build process. Also the vckpg directory is taken from ```vcpkg``` env variable

## Acknowledgements
A lot of code was taken from the Arduino Library.

## License
All code is licensed under GPLv3. Files not under this license will have their license stated in the license header for that particular file.

