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

#ifndef __lcd_ipc__
#include "../lcd/lcdipc.hpp"
#endif

#ifndef __time_func__
#include "time.hpp"
#endif

#include "Adafruit_RGBLCDShield.hpp"

void Adafruit_RGBLCDShield::init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    void(0);
}

Adafruit_RGBLCDShield::Adafruit_RGBLCDShield() {
    void(0);
}

Adafruit_RGBLCDShield::~Adafruit_RGBLCDShield() {
    void(0);
}

void Adafruit_RGBLCDShield::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
    void(0);
}

void Adafruit_RGBLCDShield::clear() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.clearDisp();
    delayMicroseconds(2000);
}

void Adafruit_RGBLCDShield::home() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.home();
    delayMicroseconds(2000);
}

void Adafruit_RGBLCDShield::noDisplay() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setDisp(false);
}

void Adafruit_RGBLCDShield::display() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setDisp(true);
}

void Adafruit_RGBLCDShield::noBlink() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursBlink(false);
}

void Adafruit_RGBLCDShield::blink() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursBlink(true);
}

void Adafruit_RGBLCDShield::noCursor() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursEnabled(false);
}

void Adafruit_RGBLCDShield::cursor() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursEnabled(true);
}

void Adafruit_RGBLCDShield::scrollDisplayLeft() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.shiftLeft();
}

void Adafruit_RGBLCDShield::scrollDisplayRight() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.shiftRight();
}

void Adafruit_RGBLCDShield::leftToRight() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setDir(true);
}

void Adafruit_RGBLCDShield::rightToLeft() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setDir(false);
}

void Adafruit_RGBLCDShield::autoscroll() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setAutoScroll(true);
}

void Adafruit_RGBLCDShield::noAutoscroll() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setAutoScroll(false);
}

void Adafruit_RGBLCDShield::setBacklight(uint8_t status) {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setBackLight(status);
}

void Adafruit_RGBLCDShield::createChar(uint8_t loc, uint8_t value[]) {
    LcdIPC& temp = LcdIPC::getInstance();
    charBitMap bitMap;
    for (int i = 0; i < 7; i++) {
        bitMap[i] = value[i];
    }
    temp.setCustChars(loc, bitMap);
}

void Adafruit_RGBLCDShield::setCursor(uint8_t col, uint8_t row) {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursorPos((col + (row * 40)));
}

size_t Adafruit_RGBLCDShield::write(uint8_t value) {
    LcdIPC& temp = LcdIPC::getInstance();
    return temp.write(value);
}

uint8_t Adafruit_RGBLCDShield::readButtons() {
    LcdIPC& temp = LcdIPC::getInstance();
    return temp.getButton();
}
