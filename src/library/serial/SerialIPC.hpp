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

class SerialIPC {
   private:
    SerialIPC();
    ~SerialIPC();
    SerialIPC &operator=(SerialIPC &serial) = delete;

   public:
    SerialIPC(SerialIPC &Serial) = delete;
    SerialIPC(const SerialIPC &Serial) = delete;

   public:
    // for use by ArduinoWrapper

    /**
     * @brief get next character available in the receive buffer
     *
     * @return int
     */
    int peek();

    /**
     * @brief number of characters available for write on the transmit buffer
     *
     * @return int
     */
    int availableForWrite();

    /**
     * @brief the number of characters available for reading from the receive buffer
     *
     * @return int
     */
    int available();

    /**
     * @brief write a character to the transmit buffer
     *
     * @param c
     * @return size_t the number of characters written
     */
    size_t write(uint8_t c);

    /**
     * @brief read character from receive buffer
     *
     * @return int
     */
    int read();

    /**
     * @brief wait for space in the transmit buffer
     *
     */
    void flush();

    // for user by SerialDebug or ArduinoTest

    /**
     * @brief the number of characters available for write on the receive buffer
     *
     * @return int
     */
    int c_availableForWrite();

    /**
     * @brief the number of characters available for read on the transmit buffer
     *
     * @return int
     */
    int c_available();

    /**
     * @brief write a character to the receive buffer
     *
     * @param c
     * @return size_t
     */
    size_t c_write(uint8_t c);

    /**
     * @brief read a character from the transmit buffer
     *
     * @return int
     */
    int c_read();

    /**
     * @brief wait for space in the receive buffer
     *
     */
    void c_flush();

    /**
     * @brief get next available character in the transmit buffer
     *
     * @return int
     */
    int c_peek();

   private:
    struct boost_struct;
    boost_struct *boost_objs;
    struct Data;
    Data *data;

   public:
    /**
     * @brief get an instance of the SerialIPC class
     * @return SerialIPC*
     */
    static SerialIPC &getInstance() {
        static SerialIPC instance;
        return instance;
    }
};
