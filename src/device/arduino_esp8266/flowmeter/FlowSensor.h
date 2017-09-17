#ifndef ARDUINO_FLOWSENSOR_H
#define ARDUINO_FLOWSENSOR_H

#include <Arduino.h>

#define DEFAULT_MLITER_VALUE 500

void FLOWSetup();
void FLOWStart(int literVal);
void FLOWInfinitive();
void FLOWStop();
void FLOWLoop();  
#endif /* ARDUINO_FLOWSENSOR_H */
