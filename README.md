# ArduinoWrapper

## What is ArduinoWrapper
It is a wrapper/compatibility layer for Arduino code so that it can run on Linux.  
It creates mock hardware devices such as serial so it is best described as a quasi-simulation.

## Core Idea
Arduino's are programmed in a language very similar to C++. It is possible to compile a ino file with very few tweaks on a  
linux machine. The compiler needs definitions for functions such as `millis()` and `serial.println()`. Typically these are
found in the Arduino Core provided by the Arduino IDE. This project provides a library to which arduino code can be linked with
after the arduino code is compiled.  

## Limitations
- Due to how this wrapper works the memory constraints of the Arduino cannot be replicated.  
- There maybe differences in how serial communication is handled  
- GPIO Pins are not supported  
- LCD is assumed to be 16 by 2 and each character to be 5 pixels across and 7 pixels down  
- On an arduino ints are 2 bytes but on x64 systems it is 4 bytes. So there are difference in the size of the fundamental types
- Behaviour of functions may subtle vary from on a real Arduino

## Bugs and limitations to be rectified
- floats in the String class are broken
- the lcd debug utility is very jank
- only one arduinoCode executable can be run on a machine at one time this due to the same shared memory being used

## Plans
- automate the x.ino to x.exe process
- support EEPROM

## Build Instructions
in BUILD.md

## Instructions for use
in DOC.md

## Project Structure
```
project root
│
├── arduino_tests          # test ino files
├── miscellaneous          # random files and folders
│   ├── arduinoCode        # sample ino file for compiling
│   └── custom-triplets    # custom triplet for VCPKG
├── src                    # source code in this folder
│   ├── core               # executables
│   │   ├── lcdDebug       # lcd debugging utility
│   │   ├── serialDebug    # serial debugging utility
│   │   └── test           # test executables
│   └── library            # static and shared libraries
│       ├── ArduinoWrapper # arduinoWrapper library what the code from an ino file is linked to
│       ├── lcd            # lcd library
│       └── serial         # serial library
├── tools                  # tools for compiling ino files
│   ├── arduinoCodeCompiler 
│   │   ├ compile.sh       # used to compile a ino file into a executable
│   └── testCompiler       
│       └── compile.sh     # used to compile tests which will run on an arduino executable not implemented yet
└── .vscode                # vscode config
```

![output](https://user-images.githubusercontent.com/70172420/217626751-9b5ac11f-ffb7-47fa-86b4-09aff84c2ace.svg)

The the lcd library and serial library (used only if serial is built in IPC mode) are built in two different modes producer and consumer  
ArduinoWrapper linked to the producer version of these libraries  
The consumer version of those libraries are used by the lcd debugging and serial debugging utility. In the future they will be used by the arduino code tester.  
The code from the ino file is only linked to the ArduinoWrapper library.

## Development Environment
This project has VScode setup and is using clang format and clangd  
Please do note that clangd will only work once .cache folder is generated which is created during the build process. Also, the vcpkg directory is taken from ```vcpkg``` env variable

## Acknowledgements
A lot of code was taken from the Arduino Library. [Arduino GitHub Cores](https://github.com/arduino)

## License
All code is licensed under GPLv3. Files not under this license will have their license stated in the license header for that particular file.

