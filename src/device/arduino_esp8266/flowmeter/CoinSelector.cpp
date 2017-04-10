#include "CoinSelector.h"
#include "Hardware.h"
#include "FlowSensor.h"
#include "Global.h"

#define ANALOG_LOW_LEVEL 2

unsigned int totalCoin = 0;
bool selectorInitialized = false;

/* Coin inserted, take action. */
void performInserted()
{
  Printf("Perform inserted!");
  FLOWStart();
  totalCoin++;
}

unsigned int COINGetTotal()
{
  return totalCoin;
}

void COINSetup()
{
  totalCoin = 0;
  if(analogRead(A0) > 0)
  {
    Printf("Coin selector is not connected?\n");
  }
  else
  {
    selectorInitialized = true;
  }
}

/* Analog reading is not the solution. */
void COINLoop()
{
  if(selectorInitialized)
  {
    if(analogRead(A0) > ANALOG_LOW_LEVEL)
    {
      performInserted();
      Printf("Coin inserted. Total : %d\n", totalCoin);
      /* Decrease delay. */
      delay(250);
    }
  }
}


