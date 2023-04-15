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

#include "EEPROM.hpp"

#include <eepromIPC.hpp>

eepromIPC &eepromipc = eepromIPC::getInstance();

uint8_t eeprom_read_byte(const uint8_t __p) {
    return eepromipc.eeprom_read_byte(__p);
}

void eeprom_write_byte(uint8_t __p, uint8_t __value) {
    eepromipc.eeprom_write_byte(__p, __value);
}