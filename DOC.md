# instructions

You first need to setup the dependencies see `BUILD.md`  
The quickest way to compile a sketch is to copy the arduinoCode folder in the miscellaneous folder to sr/core/  
Then in the newly created sample.cpp copy and paste in the code from the ino file. Then remove any include directives.  
Now run the two CMake build commands again  
You may need to delete and recreate your build folder  
This will create a executable in the build/output folder called arduinoCode  
Run this executable **first**  
Then the executables lcdDebug and serialDebug can be run to see the lcd and serial  
The wasd for up down left right and c for select in lcdDebug  


if you wish to run multiple instances of arduino code you need to set the env variable `ard_ipc` to a 
different string for each instance. This will create a separate shared memory segment for each arduino 
code executable. It will also need to be set for each instance of serialDebug or lcdDebug so they 
connect to the correct shared memory segment.  
Note: **only use alpha numeric, _, -,** characters in `ard_ipc`  
To do this in bash as an example `(export ard_ipc="YOUR_STRING"; ./[executable])` 

# running tests

tools/arduinoCodeCompiler/compile.sh can be used to compile a sketch. It assumes you built the binaries in build/Release/output.   
Further details can be found in compile.sh  
tools/automated-testing.py can be used to run tests on a batch of sketches. To do this  

- write an arduinoCodeTest  
copy the arduinoCodeTest folder in the miscellaneous folder to sr/core/  
Then you can write tests for arduinoCode executables.  
Further details in miscellaneous/arduinoCodeTest/README.md
- compile so that built the binaries in build/Release/output  
- then run automated-testing.py with the appropriate command line options