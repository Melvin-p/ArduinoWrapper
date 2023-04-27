/**
    code taken and modified from
    Adafruit_RGBLCDShield.h at https://github.com/adafruit/Adafruit-RGB-LCD-Shield-Library

Software License Agreement (BSD License)

Copyright (c) 2012, Adafruit Industries
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holders nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Modified 20th October 2022 by Melvin Pynadath
*/

#ifndef LCD_H
#define LCD_H

#define BUTTON_UP 0x08      //!< Up button
#define BUTTON_DOWN 0x04    //!< Down button
#define BUTTON_LEFT 0x10    //!< Left button
#define BUTTON_RIGHT 0x02   //!< Right button
#define BUTTON_SELECT 0x01  //!< Select button
#define LCD_5x8DOTS 0x00    //!< 8 pixel high font mode0

#include "Print.hpp"

class Adafruit_RGBLCDShield : public Print {
   public:
    void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5,
              uint8_t d6, uint8_t d7);

    Adafruit_RGBLCDShield();

    ~Adafruit_RGBLCDShield();

    void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

    /*!
     * @brief High-level command to clear the display
     */
    void clear();
    /*!
     * @brief High-level command to set the cursor position to zero
     */
    void home();

    /*!
     * @brief High-level command to turn the display off
     */
    void noDisplay();
    /*!
     * @brief High-level command to turn the display on
     */
    void display();
    /*!
     * @brief High-level command to turn off the blinking cursor off
     */
    void noBlink();
    /*!
     * @brief High-level command to turn on the blinking cursor
     */
    void blink();
    /*!
     * @brief High-level command to turn the underline cursor off
     */
    void noCursor();
    /*!
     * @brief High-level command to turn the underline cursor on
     */
    void cursor();
    /*!
     * @brief High-level command to scroll display left without changing the RAM
     */
    void scrollDisplayLeft();
    /*!
     * @brief High-level command to scroll display right without changing the RAM
     */
    void scrollDisplayRight();
    /*!
     * @brief High-level command to make text flow right to left
     */
    void leftToRight();
    /*!
     * @brief High-level command to make text flow left to right
     */
    void rightToLeft();
    /*!
     * @brief High-level command to 'right justify' text from cursor
     */
    void autoscroll();
    /*!
     * @brief High-level command to 'left justify' text from cursor
     */
    void noAutoscroll();

    /*!
     * @brief High-level command to set the backlight, only if the LCD backpack is
     * used
     * @param status Status to set the backlight
     */
    void setBacklight(uint8_t status);

    /*!
     * @brief High-level command that creates custom characters in CGRAM
     * @param location Location in cgram to fill
     * @param charmap[] Character map to use
     */
    void createChar(uint8_t, uint8_t[]);

    /*!
     * @brief High-level command that sets the location of the cursor
     * @param col Column to put the cursor in
     * @param row Row to put the cursor in
     */
    void setCursor(uint8_t, uint8_t);

    /*!
     * @brief Mid-level command that sends data to the display
     * @param value Data to send to the display
     */
    virtual size_t write(uint8_t);

    /*!
     * @brief reads the buttons from the shield
     * @return Returns what buttons have been pressed
     */
    uint8_t readButtons();
};

#endif