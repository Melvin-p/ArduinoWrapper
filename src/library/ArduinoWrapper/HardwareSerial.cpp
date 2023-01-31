/*
    Copyright (C) 2022 Melvin Pynadath

    This file is part of ArduinoWrapper.

    ArduinoWrapper is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ArduinoWrapper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ArduinoWrapper.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "HardwareSerial.hpp"

#include <stdint.h>

#include <cstdio>

#include "def.hpp"

#ifdef ipc_serial
#include "./../serial/serial.hpp"
#endif

/*
NOTES:
size of stdin and stdout buffer on windows is limited to the max allowed to the program by the os
however there limits in the terminal buffer and some other buffers.
there are differences for file redirection, command line text redirection and parent program
handles for stdin and stdout

Will wait for input from console
*/

// this function compiles to NOP as it is not required on OS
void HardwareSerial::begin(unsigned long baud, byte config) {
    void(0);
}

// this function compiles to NOP as it is not required on OS
void HardwareSerial::end() {
    void(0);
}

// get number of avaliable bytes for reading from the stdin pipe
int HardwareSerial::available(void) {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->available();
#else
    /*
    NOTES:
    Gets character from the stdin pipe
    if there is a character return 1 and putback the character into the sdtdin pipe
    this may cause a lot of IO operations
    */
    auto c = getchar();
    if (c < 0) {
        return 0;
    } else {
        ungetc(c, stdin);
        return 1;
    }
#endif
}

// peek at the next character in the stdin pipe
int HardwareSerial::peek(void) {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->peek();
#else
    auto c = getchar();
    if (c < 0) {
        return -1;
    } else {
        ungetc(c, stdin);
        return c;
    }
#endif
}

// reads character from stdin pipe
int HardwareSerial::read(void) {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->read();
#else
    auto c = getchar();
    if (c < 0) {
        return -1;
    } else {
        return c;
    }
#endif
}

// get number of avaliable bytes for writing to stdout pipe without blocking
int HardwareSerial::availableForWrite(void) {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->availableForWrite();
#else
    /*
    this function is not used internally used so we will return 60 bytes
    60 because it is less than 64 byte buffer on the Arduino
    */
    return 60;
#endif
}

// waits for something to read all charactes in stdout pipe
// this function compiles to NOP
void HardwareSerial::flush() {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    serial->flush();
#else
    /*
    NOTES:
    Not required as stdout pipe is practically unlimted
     */
    void(0);
#endif
}

// write character to stdout pipe
size_t HardwareSerial::write(uint8_t c) {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->write(c);
#else
    putchar(c);
    return 1;
#endif
}

// on ardunio sets up serial not required on OS
HardwareSerial::HardwareSerial(uint8_t out) {
    void(0);
}