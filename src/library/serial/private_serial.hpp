/*
    Copyright (C) 2023 Melvin Pynadath

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

#include <cstdint>
#include <cstdio>

#include "def.hpp"

class SerialIPC {
   private:
    SerialIPC();
    ~SerialIPC();
    SerialIPC &operator=(SerialIPC &serial) = delete;

   public:
    SerialIPC(SerialIPC &Serial) = delete;
    SerialIPC(const SerialIPC &Serial) = delete;

   public:
    //for use by ArduinoWrapper

    int peek();
    int availableForWrite();
    int available();
    size_t write(uint8_t c);
    int read();
    void flush();

    //for user by SerialDebug or ArduinoTest

    int c_availableForWrite();
    int c_available();
    size_t c_write(uint8_t c);
    int c_read();
    void c_flush();

   private:
    struct boost_struct;
    boost_struct *boost_objs;
    Buffers *t_buffer;
    Buffers *r_buffer;

   private:
    static SerialIPC *instance;

   public:
    static SerialIPC *getInstance() {
        if (instance == nullptr) {
            instance = new SerialIPC();
        }
        return instance;
    }
};
