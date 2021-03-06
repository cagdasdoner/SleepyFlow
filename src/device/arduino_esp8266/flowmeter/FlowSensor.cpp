#include "FlowSensor.h"
#include "Hardware.h"
#include "Display.h"
#include "Timer.h"
#include "Global.h"

#define DECILITER_THRESHOLD   44

volatile int pulseCount = 0;
int deciliterToMeasure = 0;                     
int pulseInputPin = D5;
int valveControlPin = D6;
int deciliterCount = 0;
bool flowActivation = false;
bool flowInfinitive = false;

void pulseCb()
{ 
  if(flowActivation)
  {
    Printf("%d\n", pulseCount);
    pulseCount++;
  }
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

void readyForFlow()
{
  FLOWStop();
  delay(HW_DELAY);
  DISPWriteLiter(deciliterToMeasure);
  TIMERStart();
  flowActivation = true;
  enableValve();
}

void FLOWStart(int milliliterVal)
{
  deciliterToMeasure = milliliterVal / 100;
  Printf("deciliters : %d.\n", deciliterToMeasure);
  FLOWStop();
  readyForFlow();
}

void FLOWInfinitive()
{
  flowInfinitive = true;
  readyForFlow();
}

void FLOWStop()
{
  flowActivation = false;
  flowInfinitive = false;
  disableValve();
  pulseCount = 0;
  deciliterCount = 0;
  TIMERStop();
  DISPInitialState();
}

void FLOWLoop()    
{
  if(pulseCount > DECILITER_THRESHOLD)
  {
    pulseCount = 0;
    deciliterCount++;
    if(flowInfinitive)
    {
      DISPWriteLiter(deciliterCount);
    }
    else
    {
      DISPWriteLiter(deciliterToMeasure - deciliterCount);
    }
  }
  if(deciliterCount == deciliterToMeasure && deciliterToMeasure != 0 && !flowInfinitive)
  {
    FLOWStop();
  }
}



