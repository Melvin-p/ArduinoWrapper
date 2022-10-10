#include <iostream>

#include "./library/functions.hpp"

int main(int argc, char *argv[]) {
    std::cout << millis() << std::endl;
    delay(1000);
    std::cout << millis() << std::endl;
    std::cout << micros() << std::endl;
    delayMicroseconds(1000000);
    std::cout << micros() << std::endl;
    std::cout << millis() << std::endl;

    /* String k = String(54, HEX);
    auto value = k.length();
    std::cout << value << std::endl;
    k.concat(30);
    value = k.length();
    std::cout << value << std::endl;
    std::cout << k.toDouble() << std::endl; */

    return 0;
}