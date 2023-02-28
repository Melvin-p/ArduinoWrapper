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
#include <serial.hpp>
#endif

/*
NOTES:
size of stdin and stdout buffer is limited to the max allowed to the program by the os
however there limits in the terminal buffer and some other buffers.
there are differences for file redirection, command line text redirection and parent program handles for stdin and stdout
Will wait for input from console
cannot send data while data is being received on the terminal
These problems can be alleviated by compiling with serialIPC support
*/

void HardwareSerial::begin(unsigned long baud, byte config) {
    void(0);
}

void HardwareSerial::end() {
    void(0);
}

// get number of available bytes for reading from the stdin pipe
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
    this due to a limitation of the language
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

// get number of available bytes for writing to stdout pipe without blocking
int HardwareSerial::availableForWrite(void) {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->availableForWrite();
#else
    /*
    stdout pipe is unlimited
    this function is not used internally used so we will return 60 bytes
    60 because it is less than 64 byte buffer on the Arduino
    */
    return 60;
#endif
}

// waits for something to read all characters in stdout pipe
void HardwareSerial::flush() {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    serial->flush();
#else
    /*
    NOTES:
    Not required as stdout pipe is practically unlimited
     */
    void(0);
#endif
}

// write character to stdout pipe
size_t HardwareSerial::write(uint8_t c) {
#ifdef ipc_serial
    SerialIPC *serial = SerialIPC::getInstance();
    // need to wait for buffer to have space to write
    serial->flush();
    return serial->write(c);
#else
    putchar(c);
    return 1;
#endif
}

HardwareSerial::HardwareSerial(uint8_t out) {
    void(0);
}