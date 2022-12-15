#include "sample.hpp"

#include <limits.h>
#include <stdlib.h>

HardwareSerial Serial = HardwareSerial(12);

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Testing Time Functions
    delay(1000);
    unsigned long result_milllis = millis();
    Serial.print("Result Millis: ");
    Serial.println(result_milllis);
}
