
#include "def.hpp"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
// abs is global
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
// round is global
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x) * (x))

/*
in math.h the following can be found so math.h can be included for these functions
abs
pow
sqrt
sin
cos
tan
round
*/

long map(long x, long in_min, long in_max, long out_min, long out_max);

long random(long howbig);
long random(long howsmall, long howbig);
void randomSeed(unsigned long seed);
