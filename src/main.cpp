#include <cstddef>
#include <iostream>

#include "./library/binary.hpp"
#include "./library/character.hpp"
#include "./library/def.hpp"
#include "./library/math.hpp"
#include "./library/serial.hpp"
#include "./library/time.hpp"

#ifndef __custom__string__
#define __custom__string__
#include "./library/string.hpp"
#endif

Serial serial = Serial(64);

int main(int argc, char *argv[]) {
    std::cout << millis() << std::endl;
    delay(1000);
    std::cout << millis() << std::endl;
    std::cout << micros() << std::endl;
    delayMicroseconds(1000000);
    std::cout << micros() << std::endl;
    std::cout << millis() << std::endl;

    // TODO Replace with testing framework probably google test
    String k = String(255, HEX);
    auto value = k.length();
    std::cout << value << std::endl;
    k.concat(30);
    value = k.length();
    std::cout << value << std::endl;
    std::cout << k.toDouble() << std::endl;

    std::cout << constrain(10, 5, 20) << std::endl;

    std::cout << isGraph('c') << std::endl;

    uint8_t test_number = 47;
    std::cout << test_number << std::endl;
    bitWrite(test_number, 0, 0);
    std::cout << test_number << std::endl;

    serial.begin(1000);
    serial.begin(1000, 0x10);
    serial.print("Hello");
    serial.print("World");
    serial.print("\n");
    serial.println("New Line");
    serial.println("New Line 2");
    auto sdf = serial.peek();
    serial.println(sdf);

    return 0;
}