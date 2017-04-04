#include "CoinSelector.h"
#include "FlowSensor.h"
#include "Hardware.h"
#include "Timer.h"
#include "Global.h"

unsigned int totalCoin = 0;
bool selectorInitialized = false;

int anlg = -1;

/* Coin inserted, take action. */
void performInserted()
{
  Printf("Perform inserted!");
  TIMERStart();
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
   
    if(analogRead(A0) > 0)
    {
      performInserted();
      Printf("Coin inserted. Total : %d\n", totalCoin);
      /* Decrease delay. */
      delay(250);
    }
  }
}


