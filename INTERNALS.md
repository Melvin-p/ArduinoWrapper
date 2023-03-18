# internals

## Project Structure
```
project root
│
├── arduino_tests          # test ino files
├── miscellaneous          # random files and folders
│   ├── arduinoCode        # sample ino file for compiling
│   ├── custom-triplets    # custom triplet for VCPKG
│   └── arduinoCodeTest    # sample test to demonstrate use of testing framework
├── src                    # source code in this folder
│   ├── core               # executables
│   │   ├── lcdDebug       # lcd debugging utility
│   │   ├── serialDebug    # serial debugging utility
│   │   └── test           # test executables
│   └── library            # static and shared libraries
│       ├──ArduinoTest     # automated testing framework    
│       ├── ArduinoWrapper # arduinoWrapper library what the code from an ino file is linked to
│       ├── lcd            # lcd library
│       └── serial         # serial library
├── tools                  # tools for compiling ino files
│   ├── arduinoCodeCompiler 
│   │   └── compile.sh       # used to compile a ino file into a executable
│   └── testCompiler       
│       └── compile.sh     # used to compile tests which will run on an arduino executable not implemented yet
└── .vscode                # vscode config
```

![output](https://user-images.githubusercontent.com/70172420/223544693-05ad80b6-1380-42b9-8668-4e64ad1adbe1.svg)

## details

The project has two main static libraries  
- lcd
- serial  

These two handle the IPC for serial and lcd. They can be compiled in two different modes as a producer 
or a consumer. The producer mode is consumed by the Arduino code executable by consuming ArduinoWrapper. 
In producer mode the shared memory is created when the program starts and is freed when the program 
closes. In consumer mode the program will connect to an existing shared memory. This behavior is so 
that closing and reopening the arduino code executable will reset it additionally shared memory is 
persistent so it will not be cleared on program close which will lead to a resource leak. Closing the 
SerialDebug, LcdDebug or testing framework should not clear the shared memory or try to create the 
shared memory as those programs can be started and stopped in any arbitrary order. This leads to a 
restriction were arduino code executable must be started first, then connecting programs can be run 
and those programs must be closed before the arduino code executable is closed.

The two main shared libraries are  
They were chosen to be static libraries for convenience 
- ArduinoWrapper
- ArduinoTest

Arduino wrapper can be built with lcd support on or off. If built with on it will consume lcd static 
library in producer mode. Support for serial over stdin/stdout or SerialIPC can be chosen at build 
time for ArduinoWrapper. If building with SerialIPC then the serial library is consumed in producer 
mode. Include adwr.hpp to get all the headers necessary.

The ArduinoTest consumes lcd and serial in consumer mode. It reuses the HardwareSerial class from 
ArduinoWrapper with the buffers swapped this provides a layer of abstraction over the raw data 
streams. Also the readString function will return a std::string instead of arduino string 
this is done through pre processor macros. Include test.hpp to get all the headers necessary.

lcdDebug consumes lcd library in consumer mode  
the key bindings are wasd and c for select.

serialDebug consumes the serial library in consumer mode  
this works very much like the serial monitor however the auto scroll lock doesn't work

ArduinoWrapper-Test executable runs tests on the ArduinoWrapper library


## adding a new component  

if you wish to add a new component such a emulating the GPIO. Start by creating a static library 
like lcd. This should be located in src/library. You should make two different versions one which 
will be consumed by ArduinoWrapper and another which will be consumed by a debugging utility or 
the ArduinoTest. In ArduinoWrapper add your new library as a link library make sure to add a 
feature flag. Use lcd and serial as an example.

You can also add tests for your new component in src/core/tests  
create a file called `[A SUITABLE NAME].hpp` in it include `<doctest/doctest.h>` and `<adwr.hpp>` 
then include your `[A SUITABLE NAME].hpp` in main.cpp  
your tests should be in one or modules
