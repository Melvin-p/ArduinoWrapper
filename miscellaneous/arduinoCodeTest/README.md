Copy this folder to `src/core/` and it will be automatically added to the build system.  
This file contains an example use of the automated testing framework for the arduino code.  
The folder is git ignored under `/src/core/`


The arduinoCodeTest (the testing executable) is linked to the shared library ArduinoTest which provides 
abstractions over the low level libraries. However instead you can link directly to the low level 
libraries and use them. To do this replace `target_link_libraries(arduinoCodeTest PRIVATE ArduinoTest)` 
in `CMakeLists.txt` with `target_link_libraries(arduinoCodeTest PRIVATE SerialCon LcdCon eepromCon)` 

There are a number of things that need to be taken into account when writing the test, these are

- the lcd, serial and buttons are asynchronous 
- the serial will block if transmit buffer is full which will cause the arduinoCode executable to hang
- it is recommend the results are written to a file. The script automated-testing.py will change the 
directory to appropriate folder when running
- if using the low level libraries the testing executable should not overwrite any data in the transmit buffer. 
So if the buffer is full the testing executable should stop sending data.
- if the arduinoCode executable is not responding the testing executable should time out and exit
- currently polling needs to used to check serial and lcd