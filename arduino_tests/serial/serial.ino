/*
    Copyright (C) 2023 Melvin Pynadath

    This file is part of ArduinoWrapper.

    ArduinoWrapper is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ArduinoWrapper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ArduinoWrapper.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Testing Time Functions
    delay(1000);
    unsigned long result_milllis = millis();
    Serial.print("Result Millis: ");
    Serial.println(result_milllis);
    delayMicroseconds(1000000);
    unsigned long result_micros = micros();
    Serial.print("Result Micros: ");
    Serial.println(result_micros);

    Serial.print("I received: ");
    while (Serial.available() > 0) {
        char incomingByte = '0';
        incomingByte = Serial.read();
        Serial.print(incomingByte);
    }
    Serial.println();

    delay(4000);

    String teststr = Serial.readString();
    Serial.println(teststr);

    Serial.flush();
}