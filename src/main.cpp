#include <assert.h>

#include <iostream>

#include "./library/def.hpp"
#include "./library/functions.hpp"
#include "./library/string.hpp"

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

    return 0;
}