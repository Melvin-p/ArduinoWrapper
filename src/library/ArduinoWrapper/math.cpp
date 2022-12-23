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

#include "math.hpp"

#include <cstdlib>

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long random(long howbig) {
    if (howbig == 0) {
        return 0;
    }
    return rand() % howbig;
}

long random(long howsmall, long howbig) {
    if (howsmall >= howbig) {
        return howsmall;
    }
    long diff = howbig - howsmall;
    return random(diff) + howsmall;
}

void randomSeed(unsigned long seed) {
    if (seed != 0) {
        srand(seed);
    }
}