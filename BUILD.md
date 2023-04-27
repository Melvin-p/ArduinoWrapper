# Build Instructions

The following instructions use Ubuntu and clang adapt as required.  
Replace square brackets and their contents in commands as directed.  
MSVC is not supported. Linux running on x64 with clang or gcc is required.  
Dependencies can be installed using your system package manager this is quicker 
however in the longer run it is recommend you use vcpkg as things are less likely to break  
The dependencies you need to install using your package manager should be called something along the line of qt6 devel and boost devel  
[doctest](https://github.com/doctest/doctest) needs to be installed using vcpkg or `doctest_include_dire` CMake variable can be passed with directory of doctest. 

## Requirements
- CMake 3.22.1 or greater
- Clang 14 or greater (GCC 11 or greater can be used as well) 
- VCPKG to manage dependencies. Find install instructions [here](https://github.com/microsoft/vcpkg) OR use your system package manager
- Ubuntu (tested on 22.04)
- ninja (other build systems can be used)

## Build Options
Build options can be set when running the CMake commands
```
-D[ADD FLAG HERE]:BOOL=TRUE
```
- lcdDebug  
    Default: ON  
    Requires: lcd_enabled  
    Dependencies: Qt6, boost  
    builds the lcd debugging executable  
- tests  
    Default: ON  
    Requires:  
    Dependencies: doctest, (boost if building with lcd_enabled and ipc_serial)  
    builds the tests  
- lcd_enabled  
    Default: ON  
    Requires:  
    Dependencies: boost  
    Builds with support for lcd  
- serialDebug  
    Default: ON  
    Requires: ipc_serial  
    Dependencies: Qt6, boost  
    builds the serial debugging executable  
- ipc_serial  
    Default: ON  
    Requires:  
    Dependencies: boost  
    Builds serial over IPC  
- pedantic  
    Default: OFF  
    Requires:  
    Dependencies:  
    builds with -Wpedantic -Wall -Wextra flags  
- eeprom_enabled  
    Default: ON  
    Requires:  
    Dependencies: boost  
    turns on eeprom support  
- lto  
    Default: ON  
    Requires:  
    Dependencies:  
    Builds with  link time optimisation on  

##  Dependencies
**skip if using system package manager**  
major version must match  
 - `boost-interprocess` 1.81
 - `boost-system` 1.81
 - `boost-circular-buffer` 1.81
 - `doctest` 2.4.9
 - `Qt6` 6.4.2 Only some components (the bit in square brackets) need to be built to reduce compile time
  `qtbase[concurrent,core,dbus,doubleconversion,fontconfig,freetype,gui,harfbuzz,icu,pcre2,png,testlib,thread,widgets,xcb,xcb-xlib,xkb,xkbcommon-x11,xlib,xrender,zstd]`   
  Additional packages need to be installed for Qt6 to compile, your system may need different set of packages in this case you need to read the error message from VCPKG to figure out which dependency is missing or check the Qt website. The command below installs the packages need for Qt6 to compile on Ubuntu.

 ```
 sudo apt-get install libfontconfig1-dev libfreetype6-dev libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libxcb-glx0-dev libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev libxcb-util-dev libxcb-xinerama0-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev pkg-config bison python3-distutils autoconf autoconf-archive libtool 
 ```

After VCPKG has been setup.  
It is recommended that Qt is built dynamically and everything else statically. This requires a custom triplet. The custom triplet folder is found in the miscellaneous folder in the project root. Run the following command to install boost and doctest dependencies in VCPKG.

```
./vcpkg install boost-interprocess:x64-linux-custom boost-system:x64-linux-custom boost-circular-buffer:x64-linux-custom doctest:x64-linux-custom --overlay-triplets=[PATH TO custom-triplets folder]
```

Qt6 on VCPKG installs the default triplet alongside the the custom triplet even though the custom triplet has been specified. So it is necessary to install Qt6 twice. Run the following command to install Qt6 in VCPKG.
```
./vcpkg install qtbase[concurrent,core,dbus,doubleconversion,fontconfig,freetype,gui,harfbuzz,icu,pcre2,png,testlib,thread,widgets,xcb,xcb-xlib,xkb,xkbcommon-x11,xlib,xrender,zstd]:x64-linux-custom qtbase[concurrent,core,dbus,doubleconversion,fontconfig,freetype,gui,harfbuzz,icu,pcre2,png,testlib,thread,widgets,xcb,xcb-xlib,xkb,xkbcommon-x11,xlib,xrender,zstd]:x64-linux --overlay-triplets=[PATH TO custom-triplets folder]
```

## Build

in the project root run
```
mkdir build/Release/ --parents
```

Then run the following command (Ninja can be replace with another build system) to create the build system.
Build options go in this command. Remove `DCMAKE_TOOLCHAIN_FILE` if not using vcpkg.  

```
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DVCPKG_TARGET_TRIPLET:STRING=x64-linux-custom -DCMAKE_TOOLCHAIN_FILE=[Path To Your vcpkg.cmake] -DBUILD_SHARED_LIBS:BOOL=TRUE -G Ninja -B ./build/Release/
```
Then run to build
```
cmake --build build/Release
```

Binaries produced will be in the output folder
