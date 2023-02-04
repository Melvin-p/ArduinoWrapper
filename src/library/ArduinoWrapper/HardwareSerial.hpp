/*
    code taken and modified from
    HardwareSerial.h - Hardware serial library for Wiring
    Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
    Modified 28 September 2010 by Mark Sproul
    Modified 14 August 2012 by Alarus
    Modified 3 December 2013 by Matthijs Kooijman

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
    along with ArduinoWrapper. If not, see <https://www.gnu.org/licenses/>.

    Modified 18 October 2022 by Melvin Pynadath
*/

#include <stdint.h>

#include "Stream.hpp"

#ifndef SERIAL_H
#define SERIAL_H

class HardwareSerial : public Stream {
   public:
    HardwareSerial(uint8_t out);
    void begin(unsigned long baud) {
        begin(baud, 0xff);
    }
    void begin(unsigned long, uint8_t);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    virtual int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) {
        return write((uint8_t)n);
    }
    inline size_t write(long n) {
        return write((uint8_t)n);
    }
    inline size_t write(unsigned int n) {
        return write((uint8_t)n);
    }
    inline size_t write(int n) {
        return write((uint8_t)n);
    }
    using Print::write;  // pull in write(str) and write(buf, size) from Print
    operator bool() {
        return true;
    }
};

#endif