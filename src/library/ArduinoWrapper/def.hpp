
#include <stdint.h>

#ifndef DEF_H
#define DEF_H

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define F(string_literal) string_literal
#define PROGMEM

typedef bool boolean;
typedef uint8_t byte;
#define word uint16_t

#endif