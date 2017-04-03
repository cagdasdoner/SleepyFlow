#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Timer.h"
#include "Display.h"
#include "FlowSensor.h"
#include "CoinSelector.h"
#include "Global.h"

void setup()
{
  Serial.begin(BAUD_RATE);
  Serial.println("FLOWMETER..");
  TIMERStart();
  DISPStart();
  FLOWStart();
  COINStart();
}

void loop()    
{
  TIMERLoop();
  DISPLoop();
  FLOWLoop();
  COINLoop();
}



