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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../external/doctest.h"
#include "../../library/ArduinoWrapper/adwr.hpp"

TEST_SUITE("String class") {
    /**
    Notes:
    Testing has revealed the arduino has differnt max_int value
    int are 16bit
    longs are 32bit
    Using #define int short will compile however
    the c++ standard library forbids macroizing the keyword "int" also
    the c++ standard states "The type of an integer literal is the first of the corresponding list in Table 7 in which its value can be represented"
    Looking table 7 shows int is default
    */

    TEST_CASE("String from char array") {
        String test_string = "Hello";
        CHECK(test_string.equals("Hello"));
        CHECK_FALSE(test_string.equals("World"));
        CHECK(test_string.length() == 5);
    }

    TEST_CASE("String from string and flash storage") {
        String test_string = F("Hello");
        String test_string_2 = String(test_string);
        CHECK(test_string_2.equals("Hello"));
    }

    TEST_CASE("String from number") {
        String test_string = String(23.6534, 3);
        CHECK(test_string == "23.653");
    }

    // MAX BIN

    TEST_CASE("Testing 65535 UINT_MAX to BIN") {
        String test_string = String(65535, BIN);
        CHECK(test_string == "1111111111111111");
    }

    TEST_CASE("Testing 2147483647 LONG_MAX to BIN") {
        String test_string = String(2147483647, BIN);
        CHECK(test_string == "1111111111111111111111111111111");
    }

    TEST_CASE("Testing 32767 INT_MAX to BIN") {
        String test_string = String(32767, BIN);
        CHECK(test_string == "111111111111111");
    }

    TEST_CASE("Testing 4294967295 ULONG_MAX to BIN") {
        unsigned long temp = 4294967295;
        String test_string = String(temp, BIN);
        CHECK(test_string == "11111111111111111111111111111111");
    }

    TEST_CASE("Testing 255 UCHAR_MAX to BIN") {
        String test_string = String(255, BIN);
        CHECK(test_string == "11111111");
    }

    TEST_CASE("Testing 127 CHAR_MAX TO BIN") {
        String test_string = String(127, BIN);
        CHECK(test_string == "1111111");
    }

    // MAX OCT

    TEST_CASE("Testing 65535 UINT_MAX to OCT") {
        String test_string = String(65535, OCT);
        CHECK(test_string == "177777");
    }

    TEST_CASE("Testing 2147483647 LONG_MAX to OCT") {
        String test_string = String(2147483647, OCT);
        CHECK(test_string == "17777777777");
    }

    TEST_CASE("Testing 32767 INT_MAX to OCT") {
        String test_string = String(32767, OCT);
        CHECK(test_string == "77777");
    }

    TEST_CASE("Testing 4294967295 ULONG_MAX to OCT") {
        unsigned long temp = 4294967295;
        String test_string = String(temp, OCT);
        CHECK(test_string == "37777777777");
    }

    TEST_CASE("Testing 255 UCHAR_MAX to OCT") {
        String test_string = String(255, OCT);
        CHECK(test_string == "377");
    }

    TEST_CASE("Testing 127 CHAR_MAX to OCT") {
        String test_string = String(127, OCT);
        CHECK(test_string == "177");
    }

    // MAX HEX

    TEST_CASE("Testing 65535 UINT_MAX to HEX") {
        String test_string = String(65535, HEX);
        CHECK(test_string == "ffff");
    }

    TEST_CASE("Testing 2147483647 LONG_MAX to HEX") {
        String test_string = String(2147483647, HEX);
        CHECK(test_string == "7fffffff");
    }

    TEST_CASE("Testing 32767 INT_MAX to HEX") {
        String test_string = String(32767, HEX);
        CHECK(test_string == "7fff");
    }

    TEST_CASE("Testing 4294967295 ULONG_MAX to HEX") {
        unsigned long temp = 4294967295;
        String test_string = String(temp, HEX);
        CHECK(test_string == "ffffffff");
    }

    TEST_CASE("Testing 255 UCHAR_MAX to HEX") {
        String test_string = String(255, HEX);
        CHECK(test_string == "ff");
    }

    TEST_CASE("Testing 127 CHAR_MAX to HEX") {
        String test_string = String(127, HEX);
        CHECK(test_string == "7f");
    }

    // MIN BIN

    TEST_CASE("Testing -2147483648 LONG_MIN to BIN") {
        String test_string_2 = String(static_cast<long>(0b10000000000000000000000000000000), BIN);
        CHECK(test_string_2 == "10000000000000000000000000000000");
    }

    TEST_CASE("Testing -128 CHAR_MIN to BIN") {
        String test_string_3 = String(static_cast<char>(0b1111111110000000), BIN);
        CHECK(test_string_3 == "1111111110000000");
    }

    TEST_CASE("Testing -32768 INT_MIN to BIN") {
        String test_string_4 = String(static_cast<int>(static_cast<short>(0b1000000000000000)), BIN);
        CHECK(test_string_4 == "1000000000000000");
    }

    // ZERO BIN

    TEST_CASE("Testing long 0 to BIN") {
        long zero_long = 0;
        String test_string = String(zero_long, BIN);
        CHECK(test_string == "0");
    }

    TEST_CASE("Testing int 0 to BIN") {
        int zero_int = 0;
        String test_string = String(zero_int, BIN);
        CHECK(test_string == "0");
    }

    TEST_CASE("Testing unisgned int 0 to BIN") {
        unsigned int zero_uint = 0;
        String test_string = String(zero_uint, BIN);
        CHECK(test_string == "0");
    }

    TEST_CASE("Testing unisgned long 0 to BIN") {
        unsigned long zero_ulong = 0;
        String test_string = String(zero_ulong, BIN);
        CHECK(test_string == "0");
    }

    TEST_CASE("Testing unsinged char 0 to BIN") {
        unsigned char zero_uchar = 0;
        String test_string = String(zero_uchar, BIN);
        CHECK(test_string == "0");
    }

    // ZERO OCT

    TEST_CASE("Testing long 0 to OCT") {
        long zero_long = 0;
        String test_string = String(zero_long, OCT);
        CHECK(test_string == "0");
    }

    TEST_CASE("Testing int 0 to OCT") {
        int zero_int = 0;
        String test_string = String(zero_int, OCT);
        CHECK(test_string == "0");
    }

    TEST_CASE("Testing unisgned int 0 to OCT") {
        unsigned int zero_uint = 0;
        String test_string = String(zero_uint, OCT);
        CHECK(test_string == "0");
    }

    TEST_CASE("Testing unisgned long 0 to OCT") {
        unsigned long zero_ulong = 0;
        String test_string = String(zero_ulong, OCT);
        CHECK(test_string == "0");
    }

    TEST_CASE("Testing unsinged char 0 to OCT") {
        unsigned char zero_uchar = 0;
        String test_string = String(zero_uchar, OCT);
        CHECK(test_string == "0");
    }

    // Test Random

    TEST_CASE("Testing long to BIN") {
        long test_long = 834;
        String test_string = String(test_long, BIN);
        CHECK(test_string == "1101000010");
    }

    TEST_CASE("Testing int to BIN") {
        int test_int = 738;
        String test_string = String(test_int, BIN);
        CHECK(test_string == "1011100010");
    }

    TEST_CASE("Testing unisgned int to BIN") {
        unsigned int test_unit = 937;
        String test_string = String(test_unit, BIN);
        CHECK(test_string == "1110101001");
    }

    TEST_CASE("Testing unisgned long to BIN") {
        unsigned long test_ulong = 384;
        String test_string = String(test_ulong, BIN);
        CHECK(test_string == "110000000");
    }

    TEST_CASE("Testing unsinged char to BIN") {
        unsigned char test_uchar = 101;
        String test_string = String(test_uchar, BIN);
        CHECK(test_string == "1100101");
    }
}
