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

#include <array>
#include <cstdint>

#ifndef charBitMap_def_H
#define charBitMap_def_H

/**
 * @brief the char bit map that holds a character \n
 * This is used in other data structures such as lcd to represent a individual character \n
 * Each character is 5 pixels across in 7 rows so only the first 5 bits of each value are relevant
 * the the 8th character is a hidden extra piece of data so that the type of character can be easily queried
 */
typedef std::array<uint8_t, 8> charBitMap;

/**
 * @brief a displayed lcd buffer \n
 * contains the displayed portion of the lcd \n
 */
typedef std::array<charBitMap, 32> lcd;

#endif