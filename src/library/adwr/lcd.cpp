#ifndef __lcd_ipc__
#include "../lcd/lcdipc.hpp"
#endif

#ifndef __time_func__
#include "time.hpp"
#endif

#include "lcd.hpp"

void Lcd::init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    void(0);
}

Lcd::Lcd() {
    void(0);
}

Lcd::~Lcd() {
    void(0);
}

void Lcd::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
    void(0);
}

void Lcd::clear() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.clearDisp();
    delayMicroseconds(2000);
}

void Lcd::home() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.home();
    delayMicroseconds(2000);
}

void Lcd::noDisplay() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setDisp(false);
}

void Lcd::display() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setDisp(true);
}

void Lcd::noBlink() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursBlink(false);
}

void Lcd::blink() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursBlink(true);
}

void Lcd::noCursor() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursEnabled(false);
}

void Lcd::cursor() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursEnabled(true);
}

void Lcd::scrollDisplayLeft() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.shiftLeft();
}

void Lcd::scrollDisplayRight() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.shiftRight();
}

void Lcd::leftToRight() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setDir(true);
}

void Lcd::rightToLeft() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setDir(false);
}

void Lcd::autoscroll() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setAutoScroll(true);
}

void Lcd::noAutoscroll() {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setAutoScroll(false);
}

void Lcd::setBacklight(uint8_t status) {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setBackLight(status);
}

void Lcd::createChar(uint8_t loc, uint8_t value[]){
    LcdIPC& temp = LcdIPC::getInstance();
    charBitMap bitMap;
    bitMap.fill(*value);
    temp.setCustChars(loc, bitMap);
}

void Lcd::setCursor(uint8_t col, uint8_t row) {
    LcdIPC& temp = LcdIPC::getInstance();
    temp.setCursorPos((col + (row * 40)));
}

size_t Lcd::write(uint8_t) {
    LcdIPC& temp = LcdIPC::getInstance();
    return size_t();
}

