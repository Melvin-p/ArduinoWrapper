#include <signal.h>
#include <stdint.h>
#include <stdio.h>

#include "Window.hpp"

Window &window = Window::getWindow();

void resize_handle(int sig) {
    window.resize_window();
}

int main(int argc, char **argv) {
    signal(SIGWINCH, resize_handle);
    while (1 == 1) {
        window.print();
        window.bt_uptade();
    }

    return 0;
}