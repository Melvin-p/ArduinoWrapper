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

#include "def.hpp"

#define BUTTON_UP 0x08      //!< Up button
#define BUTTON_DOWN 0x04    //!< Down button
#define BUTTON_LEFT 0x10    //!< Left button
#define BUTTON_RIGHT 0x02   //!< Right button
#define BUTTON_SELECT 0x01  //!< Select button

#ifndef LCD_IPC_H
#define LCD_IPC_H

class LcdIPC {
   private:
    LcdIPC();
    ~LcdIPC();
    LcdIPC &operator=(LcdIPC &lcdipc) = delete;

   public:
    LcdIPC(LcdIPC &lcdipc) = delete;
    LcdIPC(const LcdIPC &lcdipc) = delete;

   public:
    charBitMap getLcdDisp(uint8_t loc);
    void setLcdDisp(uint8_t loc, char value);
    size_t write(uint8_t value);

    charBitMap getCustChars(uint8_t loc);
    void setCustChars(uint8_t loc, charBitMap character);

    uint8_t getCursorPos();
    void setCursorPos(uint8_t value);

    bool getDisp();
    void setDisp(bool value);

    bool getCursEnabled();
    void setCursEnabled(bool value);

    bool getCursBlink();
    void setCursBlink(bool value);

    /**
    true is left to right
    false is right to left
    */
    bool getDir();
    void setDir(bool value);

    uint8_t getBackLight();
    void setBackLight(uint8_t value);

    uint8_t getDispPos();
    void setDispPos(uint8_t value);

    void clearDisp();

    void shiftLeft();
    void shiftRight();

    void home();

    void setAutoScroll(bool value);
    bool getAutoScroll();

    void setButton(uint8_t value);
    uint8_t getButton();

    lcd getLcd();

   private:
    struct lcdData;
    lcdData *data;
    struct boost_struct;
    boost_struct *boost_objs;

   private:
    static LcdIPC *instance;

   public:
    static LcdIPC *getInstance() {
        if (instance == nullptr) {
            instance = new LcdIPC();
        }
        return instance;
    }
};

#endif