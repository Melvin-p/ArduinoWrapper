/*
    Copyright (C) 2022 Melvin Pynadath

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

#include "time.hpp"

#include <chrono>
#include <thread>

// GLOBAL
const auto start = std::chrono::high_resolution_clock::now();
// END GLOBAL

unsigned long millis() {
    auto stop = std::chrono::high_resolution_clock::now();

    return static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());
}

unsigned long micros() {
    auto stop = std::chrono::high_resolution_clock::now();

    return static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
}

void delay(unsigned long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void delayMicroseconds(unsigned int us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}
