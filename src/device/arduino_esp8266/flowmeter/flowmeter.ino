#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Hardware.h"
#include "Timer.h"
#include "Display.h"
#include "FlowSensor.h"
#include "CoinSelector.h"
#include "Global.h"

void setup()
{
  HWSetup();
  TIMERSetup(TIMER_INTERVAL);
  DISPSetup();
  FLOWSetup();
  COINSetup();
}

void loop()    
{
  TIMERLoop();
  DISPLoop();
  FLOWLoop();
  COINLoop();
}



