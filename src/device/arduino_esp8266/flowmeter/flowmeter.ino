#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Hardware.h"
#include "Timer.h"
#include "Display.h"
#include "FlowSensor.h"
#include "CoinSelector.h"
#include "MQTTConnector.h"
#include "Credentials.h"
#include "Global.h"


void WiFiBegin(const char* ssid, const char* pass)
{
  WiFi.begin(ssid, pass);
  Printf("Waiting for AP connection ...\n");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Printf(".");
  }
  MQTTBegin();
}

void setup()
{
  HWSetup();
  TIMERSetup(TIMER_INTERVAL);
  DISPSetup();
  FLOWSetup();
#ifdef USE_COIN_SELECTOR
  COINSetup();
#endif
  WiFiBegin(STA_SSID, STA_PASS);
}

void loop()    
{
  TIMERLoop();
  DISPLoop();
  FLOWLoop();
#ifdef USE_COIN_SELECTOR
  COINLoop();
#endif
  MQTTLoop();
}



