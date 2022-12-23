
#include <signal.h>

#include "sample.hpp"

bool run = true;

void sigint_handler(int sig) {
    run = false;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigint_handler);
    signal(SIGABRT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    setup();
    while (run) {
        loop();
    }
}