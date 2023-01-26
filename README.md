# ArduinoWrapper

## What is ArduinoWrapper

It is a wrapper/compatibility layer for Arduino code so that it can run on Linux (may work on other operating systems). 
It creates mock hardware devices such as serial.

## Idea
Change x.ino to x.cpp then add the include headers to the file, finally compile and link to this library

## Limitations
- The functions are internally different to Arduino’s standard functions so if you rely on this internal behaviour this library may not work.
- Due to how this wrapper works the memory constraints of the Arduino cannot be replicated.  
- There will difference in how serial communication is handled.
- GPIO Pins are not supported
- LCD is assumed to be 16 by 2 and each character to be 5 pixels across and 7 pixels down

## Plans
- Support Adafruit RGB LCD Shield Library
- automate the x.ino to x.exe process
- may have to parse the c++ file and modify it before linking to library
- support EEPROM

## Project Structure
```
project root
│
├── .vscode                     # vscode config
├── arduino_tests               # test ino files
├── external                    # external libraries currently only doc test
├── miscellaneous               # random files
├── src                         # source code in this folder
│   ├── core                    # exectuables
│   │   ├── lcdDebug            # lcd debugging utility
│   │   └── test                # test exectuable uses doc test
│   └── library                 # static and shared libraries
│       ├── ArduinoWrapper      # arduinoWrapper library
│       └── lcd                 # lcd library built as static only can be compiled as producer or consumer
└── tools                       # tools for compiling ino files
    ├── arduinoCodeChecker.sh   # checks that ino file compiles if so creates processed cpp files
    ├── arduinoCodeCompiler     
    │   ├── compile.sh          # compiles processed cpp file into executable
    └── testCompiler
        └── compile.sh          # compiles test.cpp containing arduino test code. Not inplemented yet
```


![out](https://user-images.githubusercontent.com/70172420/211109720-8fd536ac-2374-43c2-b76a-2d90e38d567c.svg)



## Build Instructions
Assumes you are familiar with these tools and using ubuntu
### Requirements
- CMake
- A recent version of **gcc or clang** (must support C++ 17)
- Ninja (UNIX Make can be used)
- VCPKG to manage dependencies. Find install instructions [here](https://github.com/microsoft/vcpkg)

###  Dependencies
 - `boost-interprocess`
 - `boost-system`  
 - And if building lcd debug utility. Only some components (the bit in square brackets) are built to reduce compile time
  `qtbase[concurrent,core,dbus,doubleconversion,fontconfig,freetype,gui,harfbuzz,icu,pcre2,png,testlib,thread,widgets,xcb,xcb-xlib,xkb,xkbcommon-x11,xlib,xrender,zstd]`   
  The packages required for VCPKG to compile qtbase can be installed using the command below however your system may require 
  additional dependencies to be installed in this case you need to read the error message from VCPKG to figure out which dependency is missing  
 `sudo apt-get install libfontconfig1-dev libfreetype6-dev libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libxcb-glx0-dev libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev libxcb-util-dev libxcb-xinerama0-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev pkg-config bison python3-disutils autoconf autoconf-archive libtool `

These dependencies can be installed using the typical method however it is recommended that qt is built dynamically and everything else statically, static is default on linux. 
This requires a custom triplet. A folder called custom-triplets is required it is in the miscellaneous folder. 
Note: For some reason VCPKG installs the default x64-linux alongside x64-linux-custom even-though x64-linux is not specified
This should result in a VCPKG install command similar to the one below

```
./vcpkg install boost-interprocess:x64-linux-custom boost-system:x64-linux-custom qtbase[concurrent,core,dbus,doubleconversion,fontconfig,freetype,gui,harfbuzz,icu,pcre2,png,testlib,thread,widgets,xcb,xcb-xlib,xkb,xkbcommon-x11,xlib,xrender,zstd]:x64-linux-custom qtbase[concurrent,core,dbus,doubleconversion,fontconfig,freetype,gui,harfbuzz,icu,pcre2,png,testlib,thread,widgets,xcb,xcb-xlib,xkb,xkbcommon-x11,xlib,xrender,zstd]:x64-linux --overlay-triplets=[PATH TO custom-triplets folder]
```

To build all binaries excluding lcd debug utility in release mode. cd into the project root folder.  
Then run the command below  to create folders
```
mkdir ./build/Release/ -p
```
Then run the command below to create the build system
```
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DVCPKG_TARGET_TRIPLET:STRING=x64-linux-custom -DCMAKE_TOOLCHAIN_FILE=[Path To Your vcpkg.cmake] -DBUILD_SHARED_LIBS:BOOL=TRUE -DlcdDebug:BOOL=OFF  -G Ninja -B ./build/Release/
```  
Then run the command below to build binaries
```
cmake --build build/Release/
```

### Build Notes & Options
Make shared library. On by default
```
-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS:BOOL=TRUE -DBUILD_SHARED_LIBS:BOOL=TRUE
```
Builds the executable that runs the unit tests for the library. On by default
```
-Dtests:BOOL=TRUE
```
Builds the lcd debug utility. on by default
```
-DlcdDebug:BOOL=TRUE
```

## Development Environment
This project has VScode setup and is using clang format and clangd  
Please do note that clangd will only work once .cache folder is generated which is created during the build process. Also, the vcpkg directory is taken from ```vcpkg``` env variable

## Acknowledgements
A lot of code was taken from the Arduino Library. [Arduino GitHub Cores](https://github.com/arduino)

## License
All code is licensed under GPLv3. Files not under this license will have their license stated in the license header for that particular file.

