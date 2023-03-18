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

#include "LcdTest.hpp"

#include <LcdIPC.hpp>

static LcdIPC &lcdipc = LcdIPC::getInstance();

lcd getLCD() {
    return lcdipc.getLcd();
}

lcd_str getLCDStr() {
    lcd temp = lcdipc.getLcd();
    lcd_str out;
    for (int i = 0; i < 32; i++) {
        out[i] = temp[i][7];
    }
    return out;
}
