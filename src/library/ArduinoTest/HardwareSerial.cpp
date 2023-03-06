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

SerialIPC &serialipc = SerialIPC::getInstance();

void HardwareSerial::begin(unsigned long baud, byte config) {
    void(0);
}

void HardwareSerial::end() {
    void(0);
}

// get number of available bytes for reading from the stdin pipe
int HardwareSerial::available(void) {
    return serialipc.c_available();
}

// peek at the next character in the stdin pipe
int HardwareSerial::peek(void) {
    return serialipc.c_peek();
}

// reads character from stdin pipe
int HardwareSerial::read(void) {
    return serialipc.c_read();
}

// get number of available bytes for writing to stdout pipe without blocking
int HardwareSerial::availableForWrite(void) {
    return serialipc.c_availableForWrite();
}

// waits for something to read all characters in stdout pipe
void HardwareSerial::flush() {
    serialipc.c_flush();
}

// write character to stdout pipe
size_t HardwareSerial::write(uint8_t c) {
    // need to wait for buffer to have space to write
    serialipc.c_flush();
    return serialipc.c_write(c);
}

HardwareSerial::HardwareSerial(uint8_t out) {
    void(0);
}