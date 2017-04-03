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
  
}

void FLOWSetup()
{
  pinMode(pulseInputPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pulseInputPin), pulseCb, RISING);
  pinMode(valveControlPin, OUTPUT);
}

void FLOWStart()
{
  literCount = LITER_TO_MEASURE;
  pulseCount = 0;
  DISPWriteLiter(literCount);
  flowActivation = true;
  digitalWrite(valveControlPin, HIGH);
}

void FLOWStop()
{
  flowActivation = false;
  digitalWrite(valveControlPin, LOW);
}

void FLOWLoop()    
{
  if(pulseCount > LITER_THRESHOLD)
  {
    Printf("One liter measured.\n");
    literCount--;
    DISPWriteLiter(literCount);
    pulseCount = 0;
  }
}



