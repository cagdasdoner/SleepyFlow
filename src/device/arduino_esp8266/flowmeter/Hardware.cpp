#include "Hardware.h"
#include "Global.h"

void SerialInit()
{
  Serial.begin(BAUD_RATE);
  Serial.setDebugOutput(true);
  delay(HW_DELAY);
}

void GPIOInit()
{

}

void HWSetup()
{
  SerialInit();
  GPIOInit();
  Printf("HW Setup OK.");
}

void HWRestart()
{
  ESP.restart();
}

void HWLoop()
{

}
