#include <SerialIPC.hpp>
#include <csignal>

#include "sample.hpp"

bool run = true;

SerialIPC &serialipc = SerialIPC::getInstance();

void sigint_handler(int sig) {
    run = false;
    serialipc.setBlocked(false);
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