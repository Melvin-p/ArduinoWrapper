#include <array>
#include <vector>

#define __lcd_ipc__

typedef std::array<uint8_t, 7> char_map;

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
    char_map getLcdDisp(uint8_t loc);
    void setLcdDisp(uint8_t loc, char_map character);

    char_map getCustChars(uint8_t loc);
    void setCustChars(uint8_t loc, char_map character);

    uint8_t getCursorPos();
    void setCursorPos(bool value);

    bool getDisp();
    void setDisp(bool value);

    bool getCursEnabled();
    void setCursEnabled(bool value);

    bool getCursBlink();
    void setCursBlink(bool value);

    /**
    * true is right
    * false is left
    */
    bool getDir();
    void setDir(bool value);

    uint8_t getBackLight();
    void setBackLight(uint8_t value);

    uint8_t getDispPos();
    void setDispPos(uint8_t value);

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


