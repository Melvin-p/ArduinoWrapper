/*
    code taken and modified from
    Part of the Wiring project - http://wiring.org.co
    Copyright (c) 2004-06 Hernando Barragan
    Modified 13 August 2006, David A. Mellis for Arduino - http://www.arduino.cc/

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

#include "binary.hpp"

unsigned int makeWord(unsigned int w) {
    return w;
}

unsigned int makeWord(unsigned char h, unsigned char l) {
    return (h << 8) | l;
}