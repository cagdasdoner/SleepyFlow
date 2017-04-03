#include "FlowSensor.h"
#include "Display.h"
#include "Global.h"

#define LITER_THRESHOLD   440
#define LITER_TO_MEASURE  99
#define TOTAL_LITER_PULSE LITER_THRESHOLD * LITER_TO_MEASURE

volatile int pulseCount = 0;                      
int pulseInputPin = D5;
int literCount = LITER_TO_MEASURE;

void pulseCb()
{
  Serial.println(pulseCount);
  pulseCount++;
}

void FLOWStart()
{
  pinMode(pulseInputPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pulseInputPin), pulseCb, RISING);
  DISPWriteLiter(literCount);
}

void FLOWLoop()    
{
  if(pulseCount > LITER_THRESHOLD)
  {
    Serial.println("One liter measured.");
    literCount--;
    DISPWriteLiter(literCount);
    pulseCount = 0;
  }
}



