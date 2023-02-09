# internals

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
│   │   └── compile.sh       # used to compile a ino file into a executable
│   └── testCompiler       
│       └── compile.sh     # used to compile tests which will run on an arduino executable not implemented yet
└── .vscode                # vscode config
```

![output](https://user-images.githubusercontent.com/70172420/217626751-9b5ac11f-ffb7-47fa-86b4-09aff84c2ace.svg)

TODO explain the structure of the project