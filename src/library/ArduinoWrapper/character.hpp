/*
    code taken and modified from
    WCharacter.h - Character utility functions for Wiring & Arduino
    Copyright (c) 2010 Hernando Barragan.  All right reserved.

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
    along with ArduinoWrapper. If not, see <https://www.gnu.org/licenses/>.

    Modified 18 October 2022 by Melvin Pynadath
 */

#ifndef CHAR_H
#define CHAR_H

#include <ctype.h>

#include "def.hpp"

inline boolean isAlphaNumeric(int c) {
    return (isalnum(c) == 0 ? false : true);
}

// Checks for an alphabetic character.
// It is equivalent to (isupper(c) || islower(c)).
inline boolean isAlpha(int c) {
    return (isalpha(c) == 0 ? false : true);
}

// Checks whether c is a 7-bit unsigned char value
// that fits into the ASCII character set.
inline boolean isAscii(int c) {
    return (isascii(c) == 0 ? false : true);
}

// Checks for a blank character, that is, a space or a tab.
inline boolean isWhitespace(int c) {
    return (isblank(c) == 0 ? false : true);
}

// Checks for a control character.
inline boolean isControl(int c) {
    return (iscntrl(c) == 0 ? false : true);
}

// Checks for a digit (0 through 9).
inline boolean isDigit(int c) {
    return (isdigit(c) == 0 ? false : true);
}

// Checks for any printable character except space.
inline boolean isGraph(int c) {
    return (isgraph(c) == 0 ? false : true);
}

// Checks for a lower-case character.
inline boolean isLowerCase(int c) {
    return (islower(c) == 0 ? false : true);
}

// Checks for any printable character including space.
inline boolean isPrintable(int c) {
    return (isprint(c) == 0 ? false : true);
}

// Checks for any printable character which is not a space
// or an alphanumeric character.
inline boolean isPunct(int c) {
    return (ispunct(c) == 0 ? false : true);
}

// Checks for white-space characters. For the avr-libc library,
// these are: space, formfeed ('\f'), newline ('\n'), carriage
// return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
inline boolean isSpace(int c) {
    return (isspace(c) == 0 ? false : true);
}

// Checks for an uppercase letter.
inline boolean isUpperCase(int c) {
    return (isupper(c) == 0 ? false : true);
}

// Checks for a hexadecimal digits, i.e. one of 0 1 2 3 4 5 6 7
// 8 9 a b c d e f A B C D E F.
inline boolean isHexadecimalDigit(int c) {
    return (isxdigit(c) == 0 ? false : true);
}

// Converts c to a 7-bit unsigned char value that fits into the
// ASCII character set, by clearing the high-order bits.
inline int toAscii(int c) {
    return toascii(c);
}

// Warning:
// Many people will be unhappy if you use this function.
// This function will convert accented letters into random
// characters.

// Converts the letter c to lower case, if possible.
inline int toLowerCase(int c) {
    return tolower(c);
}

// Converts the letter c to upper case, if possible.
inline int toUpperCase(int c) {
    return toupper(c);
}

#endif