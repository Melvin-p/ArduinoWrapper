
#include "serial.hpp"

#include <corecrt_wstdio.h>
#include <stdio.h>

#include <cstdio>

#include "def.hpp"

/*
NOTES:
size of stdin and stdout buffer on windows is limited to the max allowed to the program by the os
however there limits in the terminal buffer and some other buffers.
there are differences for file redirection, command line text redirection and parent program
handles for stdin and stdout
*/

// this function compiles to NOP as it is not required on OS
void Serial::begin(unsigned long baud, byte config) {
    void(0);
}

// this function compiles to NOP as it is not required on OS
void Serial::end() {
    void(0);
}

// get number of avaliable bytes for reading from the stdin pipe
int Serial::available(void) {
    /* TODO
    NOTES:
    Not used internally however commonly used for reading from serial buffer on arduino
    most likely OS specific
    */
    void(0);
}

// peek at the next character in the stdin pipe
int Serial::peek(void) {
    auto c = getchar();
    if (c < 0) {
        return -1;
    } else {
        ungetc(c, stdin);
        return c;
    }
}

// reads character from stdin pipe
int Serial::read(void) {
    auto c = getchar();
    if (c < 0) {
        return -1;
    } else {
        return c;
    }
}

// get number of avaliable bytes for writing to stdout pipe without blocking
int Serial::availableForWrite(void) {
    /*
    this function is not used internally used so we will return 60 bytes
    60 because it is less than 64 byte buffer on the Arduino
    */
    return 60;
}

// waits for something to read all charactes in stdout pipe
void Serial::flush() {
    /* TODO
    NOTES:
    most likely need to know how many characters are left in stdout pipe
    most likely OS specific
     */
    void(0);
}

// write character to stdout pipe
size_t Serial::write(uint8_t c) {
    putchar(c);
    return 1;
}