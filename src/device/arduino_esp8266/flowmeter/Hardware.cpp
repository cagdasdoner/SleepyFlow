#include "Hardware.h"
#include "Global.h"

uint16_t serialDelay = 10;

void SerialInit()
{
  Serial.begin(BAUD_RATE);
  Serial.setDebugOutput(true);
  delay(serialDelay);
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
