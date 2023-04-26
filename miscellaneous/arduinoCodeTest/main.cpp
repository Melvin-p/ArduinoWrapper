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

/*
these are needed for low level access
#include <LcdIPC.hpp>
#include <SerialIPC.hpp>
#include <eepromIPC.hpp>
*/

bool run = true;

void sigint_handler(int sig) {
    run = false;
}

int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGABRT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    HardwareSerial Serial = HardwareSerial(12);
    /**
     * for low level access to the serial
     *  SerialIPC& serialipc = SerialIPC::getInstance();
     *  LcdIPC& lcdipc = LcdIPC::getInstance();
     */

    while (run) {
        // arduino code executable will block if the serial transmit buffer is full
        while (Serial.available() > 0) {
            char incomingByte = '0';
            incomingByte = Serial.read();
            auto val = Serial.readString();
            std::cout << incomingByte;
        }

        // send data to arduino code executable
        // Serial.println("Hello World");
    }
    auto val = getLCDStr();
    for (auto temp : val) {
        std::cout << temp;
    }
    std::cout << "\n";
    return 0;
}