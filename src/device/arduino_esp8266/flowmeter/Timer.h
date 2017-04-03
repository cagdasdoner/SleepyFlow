#ifndef ARDUINO_TIMER_H
#define ARDUINO_TIMER_H

#include <Arduino.h>

void TIMERSetup(unsigned int interval);
void TIMERStart();
void TIMERStop();
unsigned int TIMERGetTicks();
void TIMERLoop();

#endif /* ARDUINO_TIMER_H */
