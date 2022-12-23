#include <ncurses.h>

#include <iostream>

#include "../../library/lcd/lcdipc.hpp"

int main(int argc, char **argv) {
    LcdIPC &lcdipc = LcdIPC::getInstance();
    lcd value = lcdipc.getLcd();
    std::cout << "Test" << "\n";
    for (uint16_t j = 0; j < 32; j++) {
        for (uint8_t i = 0; i < 7; i++) {
            unsigned char row = value[j][i];
            for (uint8_t mask = 0x80; mask != 0; mask >>= 1) {
                if (row & mask) {
                    std::cout << "O";
                } else {
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    return 0;
}