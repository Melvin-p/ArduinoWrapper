/* these are the only useable includes from the ArduinoWrapper directory
 * others will return a link error
 */
// Begin ArduinoWrapper Includes
#include <HardwareSerial.hpp>
#include <Print.hpp>
#include <Printable.hpp>
#include <Stream.hpp>
#include <def.hpp>
#include <time.hpp>
// END ArduinoWrapper Includes

#ifdef lcd_enabled
#include <LcdTest.hpp>
#endif

// these are needed for low level access
#ifdef lcd_enabled
#include <LcdIPC.hpp>
#endif
#include <SerialIPC.hpp>