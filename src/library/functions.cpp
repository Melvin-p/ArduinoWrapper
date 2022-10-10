#include "functions.hpp"

#include <chrono>
#include <thread>

// GLOBAL
const std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
// END GLOBAL

unsigned long millis() {
    auto stop = std::chrono::high_resolution_clock::now();

    return static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());
}

unsigned long micros() {
    auto stop = std::chrono::high_resolution_clock::now();

    return static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
}

void delay(unsigned long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void delayMicroseconds(unsigned int us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}
