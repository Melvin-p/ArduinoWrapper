/**
 * puts all necessary include files into a single header for ease of use
 */

#include "./HardwareSerial.hpp"
#include "./Print.hpp"
#include "./Printable.hpp"
#include "./Stream.hpp"
#include "./binary.hpp"
#include "./character.hpp"
#include "./def.hpp"
#include "./math.hpp"
#include "./string.hpp"
#include "./time.hpp"

#ifdef lcd_enabled
#include "Adafruit_RGBLCDShield.hpp"
#endif

#ifdef eeprom_enabled
#include "EEPROM.hpp"
#endif