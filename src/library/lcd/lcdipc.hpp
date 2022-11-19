#ifndef __charBitMap_def__
#include "def.hpp"
#endif

#include <cstdint>

#define BUTTON_UP 0x08      //!< Up button
#define BUTTON_DOWN 0x04    //!< Down button
#define BUTTON_LEFT 0x10    //!< Left button
#define BUTTON_RIGHT 0x02   //!< Right button
#define BUTTON_SELECT 0x01  //!< Select button

#define __lcd_ipc__

/**
inherit this class privately to communciate with LCD
*/
class LcdIPC {
   private:
    LcdIPC();
    ~LcdIPC();
    LcdIPC(LcdIPC &lcdipc) {
    }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"

    LcdIPC &operator=(LcdIPC &lcdipc) {
    }
#pragma GCC diagnostic pop

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

   private:
    struct lcdData;
    lcdData *data;
    struct boost_struct;
    boost_struct *boost_objs;

   public:
    static LcdIPC &getInstance() {
        static LcdIPC instance;
        return instance;
    }
};
