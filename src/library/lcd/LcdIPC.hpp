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

#include <stddef.h>
#include <stdint.h>

#include "lcd_data_types.hpp"

#define BUTTON_UP 0x08      //!< Up button
#define BUTTON_DOWN 0x04    //!< Down button
#define BUTTON_LEFT 0x10    //!< Left button
#define BUTTON_RIGHT 0x02   //!< Right button
#define BUTTON_SELECT 0x01  //!< Select button

#ifndef LCD_IPC_H
#define LCD_IPC_H

/**
 * @brief the LCD communication class \n
 *
 * Contains the shared lcd data structure and methods to manipulate it. \n
 * singleton
 */
class LcdIPC {
   private:
    LcdIPC();
    ~LcdIPC();
    LcdIPC &operator=(LcdIPC &lcdipc) = delete;

   public:
    LcdIPC(LcdIPC &lcdipc) = delete;
    LcdIPC(const LcdIPC &lcdipc) = delete;

   public:
    /**
     * @brief Get char on the lcd at specified location
     *
     * @param loc
     * @return charBitMap
     */
    charBitMap getLcdDisp(uint8_t loc);

    /**
     * @brief Set char on the lcd at specified location
     *
     * @param loc
     * @param value
     */
    void setLcdDisp(uint8_t loc, char value);

    /**
     * @brief push a character on to the display
     *
     * @param value
     * @return size_t the number of bytes written
     */
    size_t write(uint8_t value);

    /**
     * @brief get custom characters from the lcd \n
     *
     * only 8 custom characters in the display so will do % 8 on loc
     *
     * @param loc
     * @return charBitMap
     */
    charBitMap getCustChars(uint8_t loc);

    /**
     * @brief create a custom character \n
     *
     * creates a customs character. There are only 8 custom characters so will do % 8 on loc
     *
     * @param loc
     * @param character
     */
    void setCustChars(uint8_t loc, charBitMap character);

    /**
     * @brief get the position of the cursor
     *
     * @return uint8_t
     */
    uint8_t getCursorPos();

    /**
     * @brief set the postion of the cursor
     *
     * @param value
     */
    void setCursorPos(uint8_t value);

    /**
     * @brief is the display on
     *
     * @return true
     * @return false
     */
    bool getDisp();

    /**
     * @brief turn display on and off
     *
     * @param value
     */
    void setDisp(bool value);

    /**
     * @brief is the cursor enabled
     *
     * @return true
     * @return false
     */
    bool getCursEnabled();

    /**
     * @brief enable or disable the cursor
     *
     * @param value
     */
    void setCursEnabled(bool value);

    bool getCursBlink();
    void setCursBlink(bool value);

    /**
     * @brief get the direction the display moves in \n
     *
     * true is left to right \n
     * false is right to left \n
     *
     * @return true
     * @return false
     */
    bool getDir();

    /**
     * @brief set the direction of the display \n
     *
     * true is left to right \n
     * false is right to left \n
     *
     * @param value
     */
    void setDir(bool value);

    /**
     * @brief get the colour of the back light
     *
     * @return uint8_t
     */
    uint8_t getBackLight();

    /**
     * @brief set the colour of teh back light
     *
     * @param value
     */
    void setBackLight(uint8_t value);

    /**
     * @brief get the display postion this is the where the first character shown on the lcd is
     *
     * @return uint8_t
     */
    uint8_t getDispPos();

    /**
     * @brief set the display postion
     *
     * @param value
     */
    void setDispPos(uint8_t value);

    /**
     * @brief clear the lcd
     *
     */
    void clearDisp();

    /**
     * @brief shift the display to the left
     *
     */
    void shiftLeft();

    /**
     * @brief shift the display to the right
     *
     */
    void shiftRight();

    /**
     * @brief set the cursor and display to postion 0
     *
     */
    void home();

    /**
     * @brief turn autoscroll on or off
     *
     * @param value
     */
    void setAutoScroll(bool value);

    /**
     * @brief check if autoscroll is on or off
     *
     * @return true
     * @return false
     */
    bool getAutoScroll();

    /**
     * @brief set the buttons \n
     *
     * see the preprocessor marcos BUTTON_* for the bit flags \n
     *
     * @param value
     */
    void setButton(uint8_t value);

    /**
     * @brief get the buttons
     *
     * @return uint8_t
     */
    uint8_t getButton();

    /**
     * @brief get the displayed portion of the lcd
     *
     * @return lcd
     */
    lcd getLcd();

   private:
    struct lcdData;
    lcdData *data;
    struct boost_struct;
    boost_struct *boost_objs;

   public:
    /**
     * @brief get an instance of the lcdIPC class
     *
     * @return LcdIPC*
     */
    static LcdIPC &getInstance() {
        static LcdIPC instance;
        return instance;
    }
};

#endif