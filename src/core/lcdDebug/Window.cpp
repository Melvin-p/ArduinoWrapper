#include "Window.hpp"

Window::Window() : lcdipc(LcdIPC::getInstance()) {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    getmaxyx(stdscr, y, x);

    win_main = newwin(y, x, 0, 0);

    refresh();
}

Window::~Window() {
    endwin();
}

void Window::resize_window() {
    getmaxyx(stdscr, y, x);
    wresize(win_main, y, x);
}

void Window::print() {
    lcd value = lcdipc.getLcd();

    wmove(win_main, 0, 0);
    for (uint16_t j = 0; j < 16; j++) {
        for (uint8_t i = 0; i < 7; i++) {
            unsigned char row = value[j][i];
            int temp_x;
            int temp_y;
            getyx(win_main, temp_y, temp_x);
            for (uint8_t mask = 0x80; mask != 0; mask >>= 1) {
                if (row & mask) {
                    // write character if bit is 1
                    wprintw(win_main, "0");
                } else {
                    wprintw(win_main, " ");
                }
            }
            // move to the next line for the character
            wmove(win_main, temp_y + 1, temp_x);
        }
        // move to next character 9 across
        int temp_x;
        int temp_y;
        getyx(win_main, temp_y, temp_x);
        wmove(win_main, 0, temp_x + 9);
    }

    wmove(win_main, 7, 0);
    for (uint16_t j = 16; j < 32; j++) {
        for (uint8_t i = 0; i < 7; i++) {
            unsigned char row = value[j][i];
            int temp_x;
            int temp_y;
            getyx(win_main, temp_y, temp_x);
            for (uint8_t mask = 0x80; mask != 0; mask >>= 1) {
                if (row & mask) {
                    wprintw(win_main, "0");
                } else {
                    wprintw(win_main, " ");
                }
            }
            wmove(win_main, temp_y + 1, temp_x);
        }
        int temp_x;
        int temp_y;
        getyx(win_main, temp_y, temp_x);
        wmove(win_main, 7, temp_x + 9);
    }

    wrefresh(win_main);
}

void Window::bt_uptade() {
#define BUTTON_UP 0x08      //!< Up button
#define BUTTON_DOWN 0x04    //!< Down button
#define BUTTON_LEFT 0x10    //!< Left button
#define BUTTON_RIGHT 0x02   //!< Right button
#define BUTTON_SELECT 0x01  //!< Select button

    // button char values
    // CHANGE KEY MAPPING HERE
    uint8_t up = 'w';
    uint8_t down = 's';
    uint8_t right = 'd';
    uint8_t left = 'a';
    uint8_t select = 'l';

    uint8_t bt_status = 0;

    if (wgetch(win_main) == up) {
        bt_status = bt_status | BUTTON_UP;
    }

    if (wgetch(win_main) == down) {
        bt_status = bt_status | BUTTON_DOWN;
    }

    if (wgetch(win_main) == right) {
        bt_status = bt_status | BUTTON_RIGHT;
    }

    if (wgetch(win_main) == left) {
        bt_status = bt_status | BUTTON_LEFT;
    }

    if (wgetch(win_main) == select) {
        bt_status = bt_status | BUTTON_SELECT;
    }

    lcdipc.setButton(bt_status);

    flushinp();
}