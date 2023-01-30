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

#include <Adafruit_RGBLCDShield.h>

#define OFF 0x0
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

uint8_t numb = 0;

void func0() {
    lcd.clear();
    lcd.setBacklight(VIOLET);
    for (uint8_t i = 0; i < 80; ++i) {
        lcd.print((char)i);
        Serial.print((char)i);
        Serial.print(" ");
        Serial.print(i);
        Serial.print("\n");
    }
}

void func1() {
    lcd.clear();
    lcd.setBacklight(GREEN);
    for (uint8_t i = 80; i < 160; ++i) {
        lcd.print((char)i);
        Serial.print((char)i);
        Serial.print(" ");
        Serial.print(i);
        Serial.print("\n");
    }
}

void func2() {
    lcd.clear();
    lcd.setBacklight(RED);
    for (uint8_t i = 160; i < 240; ++i) {
        lcd.print((char)i);
        Serial.print((char)i);
        Serial.print(" ");
        Serial.print(i);
        Serial.print("\n");
    }
}

void func3() {
    lcd.clear();
    lcd.setBacklight(WHITE);
    for (uint8_t i = 240; i < 256; ++i) {
        lcd.print((char)i);
        Serial.print((char)i);
        Serial.print(" ");
        Serial.print(i);
        Serial.print("\n");
        if (i == 255) {
            break;
        }
    }
}

void update() {
    switch (numb) {
        case 0:
            func0();
            break;
        case 1:
            func1();
            break;
        case 2:
            func2();
            break;
        case 3:
            func3();
            break;
    }
}

void setup() {
    // debuging
    Serial.begin(9600);

    // lcd columns and rows
    lcd.begin(16, 2);

    lcd.blink();
    lcd.cursor();

    func0();
}

void buttons() {
    uint8_t buttons = lcd.readButtons();

    if (buttons & BUTTON_RIGHT) {
        lcd.scrollDisplayRight();
        Serial.println("RIGHT");
        return;
    }

    if (buttons & BUTTON_LEFT) {
        lcd.scrollDisplayLeft();
        Serial.println("LEFT");
        return;
    }

    if ((buttons & BUTTON_DOWN) && (buttons & BUTTON_UP)) {
        lcd.home();
        Serial.println("HOME COMBO");
        return;
    }

    if ((buttons & BUTTON_UP) && !(buttons & BUTTON_DOWN)) {
        numb = ((numb + 1) % 4);
        update();
        Serial.println("UP");
        return;
    }

    if ((buttons & BUTTON_DOWN) && !(buttons & BUTTON_UP)) {
        numb = ((numb - 1) % 4);
        update();
        Serial.println("DOWN");
        return;
    }

    if (buttons & BUTTON_SELECT) {
        lcd.home();
        Serial.println("HOME SELECT");
        return;
    }
}

void loop() {
    if ((millis() % 100) == 0) {
        buttons();
    }
}