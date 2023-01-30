/**
 * puts all necessary include files into a single header for ease of use
 */

#include "./HardwareSerial.hpp"
#include "./binary.hpp"
#include "./character.hpp"
#include "./def.hpp"
#include "./math.hpp"
#include "./print.hpp"
#include "./printable.hpp"
#include "./stream.hpp"
#include "./string.hpp"
#include "./time.hpp"

#ifdef lcd_enabled
#include "Adafruit_RGBLCDShield.hpp"
#endif