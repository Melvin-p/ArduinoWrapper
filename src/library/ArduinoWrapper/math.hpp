/*
    code taken and modified from
    Arduino.h - Main include file for the Arduino SDK
    Copyright (c) 2005-2013 Arduino Team.  All right reserved.

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

#include "def.hpp"

#ifndef MATH_H
#define MATH_H

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
// abs is global
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
// round is global
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x) * (x))

/*
in math.h the following can be found so math.h can be included for these functions
abs
pow
sqrt
sin
cos
tan
round
*/

long map(long x, long in_min, long in_max, long out_min, long out_max);

long random(long howbig);
long random(long howsmall, long howbig);
void randomSeed(unsigned long seed);

#endif