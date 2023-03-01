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

#include <SerialIPC.hpp>
#include <cstdio>

#include "def.hpp"

void HardwareSerial::begin(unsigned long baud, byte config) {
    void(0);
}

void HardwareSerial::end() {
    void(0);
}

// get number of available bytes for reading from the stdin pipe
int HardwareSerial::available(void) {
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->c_available();
}

// peek at the next character in the stdin pipe
int HardwareSerial::peek(void) {
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->c_peek();
}

// reads character from stdin pipe
int HardwareSerial::read(void) {
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->c_read();
}

// get number of available bytes for writing to stdout pipe without blocking
int HardwareSerial::availableForWrite(void) {
    SerialIPC *serial = SerialIPC::getInstance();
    return serial->c_availableForWrite();
}

// waits for something to read all characters in stdout pipe
void HardwareSerial::flush() {
    SerialIPC *serial = SerialIPC::getInstance();
    serial->c_flush();
}

// write character to stdout pipe
size_t HardwareSerial::write(uint8_t c) {
    SerialIPC *serial = SerialIPC::getInstance();
    // need to wait for buffer to have space to write
    serial->c_flush();
    return serial->c_write(c);
}

HardwareSerial::HardwareSerial(uint8_t out) {
    void(0);
}