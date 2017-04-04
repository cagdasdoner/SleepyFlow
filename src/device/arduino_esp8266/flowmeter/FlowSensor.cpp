#include "FlowSensor.h"
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
  digitalWrite(valveControlPin, HIGH);
}

void disableValve()
{
  digitalWrite(valveControlPin, LOW);
}

void FLOWSetup()
{
  pinMode(pulseInputPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pulseInputPin), pulseCb, RISING);
  pinMode(valveControlPin, OUTPUT);
}

void FLOWStart()
{
  FLOWStop();
  delay(HW_DELAY);
  literCount = 0;
  pulseCount = 0;
  DISPWriteLiter(literCount);
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
    DISPWriteLiter(literCount);
    pulseCount = 0;
  }
  if(literCount == LITER_TO_MEASURE)
  {
    FLOWStop();
  }
}



