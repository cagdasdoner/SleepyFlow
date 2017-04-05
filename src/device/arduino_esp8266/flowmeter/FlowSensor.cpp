#include "FlowSensor.h"
#include "Hardware.h"
#include "Display.h"
#include "Global.h"

#define LITER_THRESHOLD   440
#define LITER_TO_MEASURE  10
#define TOTAL_LITER_PULSE LITER_THRESHOLD * LITER_TO_MEASURE

volatile int pulseCount = 0;                      
int pulseInputPin = D5;
int valveControlPin = D6;
int literCount = 0;
bool flowActivation = false;

void pulseCb()
{
  Printf("%d\n", pulseCount);
  pulseCount++;
}

void enableValve()
{
#ifdef USE_LOW_LEVEL_TRIGGER
  digitalWrite(valveControlPin, LOW);
#else
  digitalWrite(valveControlPin, HIGH);
#endif
}

void disableValve()
{
#ifdef USE_LOW_LEVEL_TRIGGER
  digitalWrite(valveControlPin, HIGH);
#else
  digitalWrite(valveControlPin, LOW);
#endif
}

void FLOWSetup()
{
  pinMode(pulseInputPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pulseInputPin), pulseCb, RISING);
  pinMode(valveControlPin, OUTPUT);
  disableValve();
}

void FLOWStart()
{
  FLOWStop();
  delay(HW_DELAY);
  literCount = 0;
  DISPWriteLiter(LITER_TO_MEASURE);
  flowActivation = true;
  enableValve();
}

void FLOWStop()
{
  disableValve();
  pulseCount = 0;
  flowActivation = false;
  DISPInitialState();
}

void FLOWLoop()    
{
  if(pulseCount > LITER_THRESHOLD)
  {
    Printf("One liter measured.\n");
    literCount++;
    DISPWriteLiter(LITER_TO_MEASURE - literCount);
    pulseCount = 0;
  }
  if(literCount == LITER_TO_MEASURE)
  {
    FLOWStop();
  }
}



