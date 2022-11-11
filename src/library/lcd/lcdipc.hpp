#ifndef __charBitMap_def__
#include "def.hpp"
#endif

#include <cstdint>

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
    LcdIPC &operator=(LcdIPC &lcdipc) {
    }

    public:
    charBitMap getLcdDisp(uint8_t loc);
    void setLcdDisp(uint8_t loc, char value);
    void write(uint8_t value);

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

   private:
    struct lcdData;
    lcdData *data;
    struct boost_struct;
    boost_struct *boost_objs;

   public:
    static LcdIPC& getInstance() {
        static LcdIPC instance;
        return instance;
    }
};


