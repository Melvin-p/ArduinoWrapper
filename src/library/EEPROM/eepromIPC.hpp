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

#ifndef EEPROM_IPC_H
#define EEPROM_IPC_H

#define E_BUFFER_SIZE 1024
#include <array>
#include <cstdint>

/**
 * @brief EEPROM communication class
 *
 */
class eepromIPC {
   private:
    eepromIPC();
    ~eepromIPC();
    eepromIPC &operator=(eepromIPC &lcdipc) = delete;

   public:
    eepromIPC(eepromIPC &eepromIPC) = delete;
    eepromIPC(const eepromIPC &eepromIPC) = delete;

   public:
    /**
     * @brief read a byte from the EEPROM
     *
     * @param p position
     * @return uint8_t
     */
    uint8_t eeprom_read_byte(const uint8_t p);

    /**
     * @brief write a byte to the EEPROM
     *
     * @param p position
     * @param value
     */
    void eeprom_write_byte(uint8_t p, uint8_t value);
    std::array<uint8_t, E_BUFFER_SIZE> getEEPROM();

   private:
    struct Data;
    Data *data;
    struct boost_struct;
    boost_struct *boost_objs;

   public:
    static eepromIPC &getInstance() {
        static eepromIPC instance;
        return instance;
    }
};

#endif