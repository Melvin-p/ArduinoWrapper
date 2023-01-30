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

void setup() {
    Serial.begin(9600);

    byte test_number = 0b10000000;     // the 0b prefix indicates a binary constant
    Serial.println(test_number, BIN);  // 10000000
    bitWrite(test_number, 0, 1);       // write 1 to the least significant bit of x
    Serial.println(test_number, BIN);  // 10000001
    auto test_word = makeWord(70000);

    Serial.println(test_word, BIN);

    auto hightByte_Result = highByte(test_word);
    Serial.println(hightByte_Result);

    auto lowByte_Result = lowByte(test_word);
    Serial.println(lowByte_Result);

    auto bitRead_Result = bitRead(test_word, 10);
    Serial.println(bitRead_Result);

    bitSet(test_word, 10);
    Serial.println(test_word, BIN);

    bitRead_Result = bitRead(test_word, 10);
    Serial.println(bitRead_Result);

    hightByte_Result = highByte(test_word);
    Serial.println(hightByte_Result);

    int x = 6;
    Serial.println(bitClear(x, 2));

    Serial.println(bit('c'));
    Serial.println();
}

void loop() {
}