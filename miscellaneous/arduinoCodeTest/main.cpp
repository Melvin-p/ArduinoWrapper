/**
 * This file is a example usage of the testing framework ArduinoTest.
 * This testing framework is to assist in writing automated tests for
 * arduino code executables.
 * the stream and print classes from the arduino have been reused
 * to provide abstraction over the bare datastreams. You can read the
 * serial output of an arduino code executable and send serial data
 * to it as well. This testing framework only works if ArduinoWrapper
 * has been compiled with serial over IPC support.
 * lcd support in this testing framework will only be enabled if it is
 * enabled in ArduinoWrapper
 */

#include <csignal>
#include <iostream>
#include <test.hpp>  //contains all the necessary includes for the testing framework

// TODO write lcd example

bool run = true;

void sigint_handler(int sig) {
    run = false;
}

int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGABRT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    HardwareSerial Serial = HardwareSerial(12);
    while (run) {
        while (Serial.available() > 0) {
            char incomingByte = '0';
            incomingByte = Serial.read();
            auto val = Serial.readString();
            std::cout << incomingByte;
        }

        // send data to arduino
        // Serial.println("Hello World");
    }
    return 0;
}