#ifndef ARDUINO_DISPLAY_H
#define ARDUINO_DISPLAY_H

#include <Arduino.h>

#define NDIGITS         8
#define NDIGITS_MASK    7

static const byte col[NDIGITS] = {
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000
} ;

static const byte seg[] = {
  0b11000000,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000,  // 9  
  0b10010000,  // 9  
} ;  

void DISPInitialState();
void DISPWriteLiter(int param);
void DISPWriteTime(int tick);
void DISPSetup();
void DISPLoop();

#endif /* ARDUINO_DISPLAY_H */ 
