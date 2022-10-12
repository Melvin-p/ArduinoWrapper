#include <assert.h>

#include <cstddef>
#include <iostream>

#include "./library/binary.hpp"
#include "./library/character.hpp"
#include "./library/def.hpp"
#include "./library/math.hpp"
#include "./library/string.hpp"
#include "./library/time.hpp"

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

    return 0;
}