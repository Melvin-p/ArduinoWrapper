# ArduinoWrapper

## What is ArduinoWrapper
It is a wrapper/compatibility layer for Arduino code so that it can run on Linux. (Windows not supported)  
It creates mock hardware devices such as serial so it is best described as a quasi-simulation.

**This was created for a university project**

## Core Idea
Arduino's are programmed in a language very similar to C++. It is possible to compile a ino file with very few tweaks on a  
linux machine. The compiler needs definitions for functions such as `millis()` and `serial.println()`. Typically these are
found in the Arduino Core provided by the Arduino IDE. This project provides a library to which arduino code can be linked with
after the arduino code is compiled.  

## Limitations
- Due to how this wrapper works the memory constraints of the Arduino cannot be replicated.  
- There maybe differences in how serial communication is handled.  
- GPIO Pins are not supported. It should be possible to add this feature similarly to how lcd module was implemented.  
- LCD is assumed to be 16 by 2 and each character to be 5 pixels across and 7 pixels down.  
- On an arduino ints are 2 bytes but on x64 systems it is 4 bytes. So there are difference in the size of some fundamental types  
- Behavior of functions may subtle vary from on a real Arduino  
- floating point behavior may differ from arduino's because floats are emulated on an arduino  
- assembly for the Arduino cannot be run

## Bugs and limitations to be rectified
- the lcd debug utility is very jank  
- poor documentation  

## Plans
- support EEPROM

## Build Instructions
in BUILD.md

## Instructions for use
in DOC.md

## Project Structure
in INTERNALS.md

## Development Environment
This project has VScode setup and is using clang format and clangd  
Please do note that clangd will only work once .cache folder is generated which is after building.   
Also, the vcpkg directory is taken from ```vcpkg``` env variable 
and assumes your vcpkg is configured with the custom triplet as described in `BUILD.md`

## Acknowledgements
A lot of code was ported/taken from the Arduino Library. [Arduino GitHub Cores](https://github.com/arduino)

## License
All code is licensed under GPLv3. Files not under this license will have their license stated in the license header for that particular file.

