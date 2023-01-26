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

#include <limits.h>
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

    char char_1 = 'a';
    auto isAlpha_result = isAlpha(char_1);
    Serial.print("Result isAlpha: ");
    Serial.println(isAlpha_result);

    char char_2 = 'a';
    auto isAlphaNumeric_result = isAlphaNumeric(char_2);
    Serial.print("Result isAlphaNumeric: ");
    Serial.println(isAlphaNumeric_result);

    char char_3 = 'a';
    auto isAscii_result = isAscii(char_3);
    Serial.print("Result isAscii: ");
    Serial.println(isAscii_result);

    char char_4 = 'a';
    auto isControl_result = isControl(char_4);
    Serial.print("Result isControl: ");
    Serial.println(isControl_result);

    char char_5 = 'a';
    auto isDigit_result = isDigit(char_5);
    Serial.print("Result isDigit: ");
    Serial.println(isDigit_result);

    char char_6 = 'a';
    auto isGraph_result = isGraph(char_6);
    Serial.print("Result isGraph: ");
    Serial.println(isGraph_result);

    char char_7 = 'a';
    auto isHexadecimalDigit_result = isHexadecimalDigit(char_7);
    Serial.print("Result isHexadecimalDigit: ");
    Serial.println(isHexadecimalDigit_result);

    char char_8 = 'a';
    auto isLowerCase_result = isLowerCase(char_8);
    Serial.print("Result isLowerCase: ");
    Serial.println(isLowerCase_result);

    char char_9 = 'a';
    auto isPrintable_result = isPrintable(char_9);
    Serial.print("Result isPrintable: ");
    Serial.println(isPrintable_result);

    char char_10 = 'a';
    auto isPunct_result = isPunct(char_10);
    Serial.print("Result isPunct_result: ");
    Serial.println(isPunct_result);

    char char_11 = 'a';
    auto isSpace_result = isSpace(char_11);
    Serial.print("Result isSpace: ");
    Serial.println(isSpace_result);

    char char_12 = 'a';
    auto isUpperCase_result = isUpperCase(char_12);
    Serial.print("Result isUpperCase: ");
    Serial.println(isUpperCase_result);

    char char_13 = 'a';
    auto isWhitespace_result = isWhitespace(char_13);
    Serial.print("Result isWhitespace: ");
    Serial.println(isWhitespace_result);

    String test_str = F("Hello World");
    String test_str_2 = "Hello";
    String test_str_3 = "asdf";
    String test_str_4 = "asdfgzx";
    String test_str_5 = "Hello World!!";

    Serial.print("Result String Comp 1: ");
    Serial.println(test_str.compareTo(test_str_2));

    Serial.print("Result String Comp 2: ");
    Serial.println(test_str.compareTo(test_str_5));

    Serial.print("Result charAt str_0: ");
    Serial.println(test_str.charAt(0));

    Serial.print("Result concat: ");
    Serial.println(test_str_3.concat(test_str_4));

    auto result_c_str = test_str_3.c_str();

    Serial.print("Result endsWith: ");
    Serial.println(test_str_3.endsWith(test_str_4));

    Serial.print("Result equals: ");
    Serial.println(test_str.equals(test_str_5));

    Serial.print("Result equalsIgnoreCase: ");
    Serial.println(test_str.equalsIgnoreCase(test_str_5));

    byte bytes[test_str.length() + 1];
    test_str.getBytes(bytes, test_str.length() + 1);
    Serial.print("Result getBytes: ");
    for (int i = 0; i < test_str.length(); i++) {
        Serial.print((char)bytes[i]);
    }
    Serial.println();

    Serial.print("Result indexOf: ");
    Serial.println(test_str.indexOf("H"));

    Serial.println(String(UINT_MAX, DEC));
    Serial.println(String(UINT_MAX, BIN));
    Serial.println(String(UINT_MAX, OCT));
    Serial.println(String(UINT_MAX, HEX));
    Serial.println();

    Serial.println(String(INT_MAX, DEC));
    Serial.println(String(INT_MAX, BIN));
    Serial.println(String(INT_MAX, OCT));
    Serial.println(String(INT_MAX, HEX));
    Serial.println();

    Serial.println(String(LONG_MAX, DEC));
    Serial.println(String(LONG_MAX, BIN));
    Serial.println(String(LONG_MAX, OCT));
    Serial.println(String(LONG_MAX, HEX));
    Serial.println();

    Serial.println(String(ULONG_MAX, DEC));
    Serial.println(String(ULONG_MAX, BIN));
    Serial.println(String(ULONG_MAX, OCT));
    Serial.println(String(ULONG_MAX, HEX));
    Serial.println();

    Serial.println(String(CHAR_MAX, DEC));
    Serial.println(String(CHAR_MAX, BIN));
    Serial.println(String(CHAR_MAX, OCT));
    Serial.println(String(CHAR_MAX, HEX));
    Serial.println();

    Serial.println(String(UCHAR_MAX, DEC));
    Serial.println(String(UCHAR_MAX, BIN));
    Serial.println(String(UCHAR_MAX, OCT));
    Serial.println(String(UCHAR_MAX, HEX));
    Serial.println();

    Serial.println(String(CHAR_MIN, DEC));
    Serial.println(String(CHAR_MIN, BIN));
    Serial.println(String(CHAR_MIN, OCT));
    Serial.println(String(CHAR_MIN, HEX));
    Serial.println();

    Serial.println(String(LONG_MIN, DEC));
    Serial.println(String(LONG_MIN, BIN));
    Serial.println(String(LONG_MIN, OCT));
    Serial.println(String(LONG_MIN, HEX));
    Serial.println();

    Serial.println(String(INT_MIN, DEC));
    Serial.println(String(INT_MIN, BIN));
    Serial.println(String(INT_MIN, OCT));
    Serial.println(String(INT_MIN, HEX));
    Serial.println();

    long t1 = 834;
    Serial.println(String(t1, BIN));
    Serial.println();

    int t2 = 738;
    Serial.println(String(t2, BIN));
    Serial.println();

    unsigned long t3 = 384;
    Serial.println(String(t3, BIN));
    Serial.println();

    unsigned int t4 = 937;
    Serial.println(String(t4, BIN));
    Serial.println();

    unsigned char t5 = 101;
    Serial.println(String(t5, BIN));
    Serial.println();
}
