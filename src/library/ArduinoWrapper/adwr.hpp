/**
 * puts all necessary include files into a single header for ease of use
 */

#include "./binary.hpp"
#include "./character.hpp"
#include "./math.hpp"
#include "./serial.hpp"
#include "./time.hpp"

#ifndef __def_main__
#include "def.hpp"
#endif

#ifndef __custom__string__
#include "./library/string.hpp"
#endif

#ifdef lcd_enabled
#include "Adafruit_RGBLCDShield.hpp"
#endif