# instructions

You first need to setup the dependencies see `BUILD.md`  
The quickest way to compile a ino file is to copy the arduinoCode folder in the miscellaneous to sr/core/  
Then in the newly created sample.cpp copy and paste in the code from the ino file. Then remove any include directives.  
Now run the two CMake build commands again  
This will create a executable in the build/output folder called arduinoCode
Run this executable **first**
Then the executables lcdDebug and serialDebug can be run to see the lcd and serial
The wasd for up down left right and c for select in lcdDebug
