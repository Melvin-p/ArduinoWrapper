
#include <signal.h>

#include "sample.hpp"

bool run = true;

void sigint_handler(int sig) {
    run = false;
}

int main(int argc, char *argv[]) {
    setup();
    signal(SIGINT, sigint_handler);
    while (run) {
        loop();
    }
}