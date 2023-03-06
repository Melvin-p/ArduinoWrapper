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

#include "Adafruit_RGBLCDShield.hpp"

#include <LcdIPC.hpp>

#include "time.hpp"

LcdIPC& lcdipc = LcdIPC::getInstance();

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
    lcdipc.clearDisp();
    delayMicroseconds(2000);
}

void Adafruit_RGBLCDShield::home() {
    lcdipc.home();
    delayMicroseconds(2000);
}

void Adafruit_RGBLCDShield::noDisplay() {
    lcdipc.setDisp(false);
}

void Adafruit_RGBLCDShield::display() {
    lcdipc.setDisp(true);
}

void Adafruit_RGBLCDShield::noBlink() {
    lcdipc.setCursBlink(false);
}

void Adafruit_RGBLCDShield::blink() {
    lcdipc.setCursBlink(true);
}

void Adafruit_RGBLCDShield::noCursor() {
    lcdipc.setCursEnabled(false);
}

void Adafruit_RGBLCDShield::cursor() {
    lcdipc.setCursEnabled(true);
}

void Adafruit_RGBLCDShield::scrollDisplayLeft() {
    lcdipc.shiftLeft();
}

void Adafruit_RGBLCDShield::scrollDisplayRight() {
    lcdipc.shiftRight();
}

void Adafruit_RGBLCDShield::leftToRight() {
    lcdipc.setDir(true);
}

void Adafruit_RGBLCDShield::rightToLeft() {
    lcdipc.setDir(false);
}

void Adafruit_RGBLCDShield::autoscroll() {
    lcdipc.setAutoScroll(true);
}

void Adafruit_RGBLCDShield::noAutoscroll() {
    lcdipc.setAutoScroll(false);
}

void Adafruit_RGBLCDShield::setBacklight(uint8_t status) {
    lcdipc.setBackLight(status);
}

void Adafruit_RGBLCDShield::createChar(uint8_t loc, uint8_t value[]) {
    charBitMap bitMap;
    for (int i = 0; i < 7; i++) {
        bitMap[i] = value[i];
    }
    lcdipc.setCustChars(loc, bitMap);
}

void Adafruit_RGBLCDShield::setCursor(uint8_t col, uint8_t row) {
    lcdipc.setCursorPos((col + (row * 40)));
}

size_t Adafruit_RGBLCDShield::write(uint8_t value) {
    return lcdipc.write(value);
}

uint8_t Adafruit_RGBLCDShield::readButtons() {
    return lcdipc.getButton();
}
