#include "LcdTest.hpp"

#include <LcdIPC.hpp>

static LcdIPC &lcdipc = LcdIPC::getInstance();

lcd getLCD() {
    return lcdipc.getLcd();
}

lcd_str getLCDStr() {
    lcd temp = lcdipc.getLcd();
    lcd_str out;
    for (int i = 0; i < 32; i++) {
        out[i] = temp[i][7];
    }
    return out;
}
