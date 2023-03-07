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

#include <doctest/doctest.h>

#include <adwr.hpp>

/**
 * another test file can be include by
 * #include "example.hpp"
 * example.hpp should only contain a TEST_SUITE and include only
 * include adwr.hpp
 */

TEST_SUITE("String class") {
    /**
    Notes:
    Testing has revealed the arduino has different max_int value
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

    // Test Float

    TEST_CASE("Testing float postive 0 decimal change") {
        float test_float = 101.02;
        String test_string = String(test_float, 2);
        CHECK(test_string == "101.02");
    }

    TEST_CASE("Testing float postive +1 decimal change") {
        float test_float = 101.02;
        String test_string = String(test_float, 3);
        CHECK(test_string == "101.020");
    }

    TEST_CASE("Testing float postive -1 decimal change") {
        float test_float = 101.08;
        String test_string = String(test_float, 1);
        CHECK(test_string == "101.1");
    }

    TEST_CASE("Testing float negative 0 decimal change") {
        float test_float = -101.02;
        String test_string = String(test_float, 2);
        CHECK(test_string == "-101.02");
    }

    TEST_CASE("Testing float negative +1 decimal change") {
        float test_float = -101.02;
        String test_string = String(test_float, 3);
        CHECK(test_string == "-101.020");
    }

    TEST_CASE("Testing float negative -1 decimal change") {
        float test_float = -101.08;
        String test_string = String(test_float, 1);
        CHECK(test_string == "-101.1");
    }

    // Test Double

    TEST_CASE("Testing float postive 0 decimal change") {
        double test_float = 101.02;
        String test_string = String(test_float, 2);
        CHECK(test_string == "101.02");
    }

    TEST_CASE("Testing float postive +1 decimal change") {
        double test_float = 101.02;
        String test_string = String(test_float, 3);
        CHECK(test_string == "101.020");
    }

    TEST_CASE("Testing float postive -1 decimal change") {
        double test_float = 101.08;
        String test_string = String(test_float, 1);
        CHECK(test_string == "101.1");
    }

    TEST_CASE("Testing float negative 0 decimal change") {
        double test_float = -101.02;
        String test_string = String(test_float, 2);
        CHECK(test_string == "-101.02");
    }

    TEST_CASE("Testing float negative +1 decimal change") {
        double test_float = -101.02;
        String test_string = String(test_float, 3);
        CHECK(test_string == "-101.020");
    }

    TEST_CASE("Testing float negative -1 decimal change") {
        double test_float = -101.08;
        String test_string = String(test_float, 1);
        CHECK(test_string == "-101.1");
    }

    // Test other string functions

    TEST_CASE("Concat String and float") {
        float test_float = 0.001;
        String test_string("Hello World ");
        test_string.concat(test_float);
        CHECK(test_string == "Hello World 0.001");
        CHECK(test_string.length() == 17);
    }

    TEST_CASE("Concat String and double") {
        double test_double = 0.001;
        String test_string("Hello World ");
        test_string.concat(test_double);
        CHECK(test_string == "Hello World 0.001");
        CHECK(test_string.length() == 17);
    }

    TEST_CASE("Concat String and int") {
        int test_int = 12;
        String test_string("Hello World ");
        test_string.concat(test_int);
        CHECK(test_string == "Hello World 12");
        CHECK(test_string.length() == 14);
    }

    TEST_CASE("Concat String and unsigned int") {
        unsigned int test_uint = 12;
        String test_string("Hello World ");
        test_string.concat(test_uint);
        CHECK(test_string == "Hello World 12");
        CHECK(test_string.length() == 14);
    }

    TEST_CASE("Concat String and long") {
        long test_long = 12;
        String test_string("Hello World ");
        test_string.concat(test_long);
        CHECK(test_string == "Hello World 12");
        CHECK(test_string.length() == 14);
    }

    TEST_CASE("Concat String and unsigned long") {
        unsigned long test_ulong = 12;
        String test_string("Hello World ");
        test_string.concat(test_ulong);
        CHECK(test_string == "Hello World 12");
        CHECK(test_string.length() == 14);
    }

    TEST_CASE("Concat String and unsigned char") {
        unsigned char test_uchar = 104;
        String test_string("Hello World ");
        test_string.concat(test_uchar);
        CHECK(test_string == "Hello World 104");
        CHECK(test_string.length() == 15);
    }

    TEST_CASE("Concat String and char") {
        char test_char = 'f';
        String test_string("Hello World ");
        test_string.concat(test_char);
        CHECK(test_string == "Hello World f");
        CHECK(test_string.length() == 13);
    }

    TEST_CASE("Concat String and String") {
        String test_string_2 = "\nHello World";
        String test_string("Hello World");
        test_string.concat(test_string_2);
        CHECK(test_string == "Hello World\nHello World");
        CHECK(test_string.length() == 23);
    }

    TEST_CASE("Concat String and cstr") {
        char test_char[] = {'H', 'E', 'L', 'L', 'O', '\0'};
        String test_string("Hello World ");
        test_string.concat(test_char);
        CHECK(test_string == "Hello World HELLO");
        CHECK(test_string.length() == 17);
        CHECK(*test_string.begin() == 'H');
        CHECK(*(test_string.end() - 1) == 'O');
    }

    TEST_CASE("Concat String and cstr from String") {
        String test_string_2 = "How are you";
        String test_string("Hello World ");
        test_string.concat(test_string_2.c_str());
        CHECK(test_string == "Hello World How are you");
        test_string_2.replace('o', 'u');
        CHECK(test_string_2 == "Huw are yuu");
        test_string.concat(test_string_2.c_str());
        CHECK(test_string == "Hello World How are youHuw are yuu");
    }

    TEST_CASE("String case change and replace") {
        String test_string("ALL UPPERCASE");
        String test_string_2("all lowercase");
        test_string.toLowerCase();
        CHECK(test_string == "all uppercase");
        test_string_2.toUpperCase();
        CHECK(test_string_2 == "ALL LOWERCASE");
        String test_string_3 = "base";
        String test_string_4 = "case";
        test_string.replace(test_string_4, test_string_3);
        CHECK(test_string == "all upperbase");
    }

    TEST_CASE("String trim") {
        String test_string("   Trim   ");
        CHECK(test_string == "   Trim   ");
        test_string.trim();
        CHECK(test_string == "Trim");
    }

    TEST_CASE("String remove") {
        String test_string = "hello";
        test_string.remove(2, 2);
        CHECK(test_string == "heo");
    }

    TEST_CASE("String equality") {
        String test_string = "ALL UPPERCASE";
        String test_string_2 = "all uppercase";
        CHECK(test_string.equalsIgnoreCase(test_string_2) == true);
        test_string.toLowerCase();
        CHECK(test_string.startsWith("all") == true);
        CHECK(test_string.endsWith("case") == true);
        // compare 2 ??
    }

    TEST_CASE("String to numerics") {
        String s_int = "123";
        String s_double = "90.003";
        auto i_int = s_int.toInt();
        auto d_double = s_double.toDouble();
        CHECK(i_int == 123);
        CHECK(d_double == 90.003);
        // float returns very long decimals
    }
}
