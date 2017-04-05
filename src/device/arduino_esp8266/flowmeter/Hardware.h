#ifndef ARDUINO_HARDWARE_H
#define ARDUINO_HARDWARE_H

#include <Arduino.h>

#define USE_LOW_LEVEL_TRIGGER
#define USE_NODEMCU_BOARD

/*
 * A0 - Analog   0 - Coin Selector IN (temporary)
 * D0 - Digital 16 - Display DIO
 * D1 - Digital  5 - Display SCK
 * D2 - Digital  4 - Display RCK
 * D3 - Digital  0 - 
 * D4 - Digital  2 - 
 * D5 - Digital 14 - Flow Sensor IN
 * D6 - Digital 12 - Valve Relay OUT
 * D7 - Digital 13 - 
 * D8 - Digital 15 - 
 */

void HWSetup();
void HWRestart();
void HWLoop();

#endif /* ARDUINO_HARDWARE_H */


