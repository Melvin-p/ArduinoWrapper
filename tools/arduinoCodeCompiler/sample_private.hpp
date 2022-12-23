#include <limits.h>
#include <signal.h>
#include <stdlib.h>

#include "adwr.hpp"

#pragma GCC push_options
#pragma GCC optimize("O0")

HardwareSerial Serial = HardwareSerial(12);

#pragma GCC pop_options

void setup();
void loop();
