#include <curses.h>
#include <stdint.h>

#include "../../library/lcd/lcdipc.hpp"

class Window {
   private:
    int x;
    int y;
    WINDOW *win_main;
    LcdIPC &lcdipc;

    Window();
    ~Window();

   public:
    void resize_window();

    void print();

    void bt_uptade();

   public:
    static Window &getWindow() {
        static Window instance;
        return instance;
    }
};