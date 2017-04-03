#include "CoinSelector.h"
#include "FlowSensor.h"
#include "Hardware.h"
#include "Timer.h"
#include "Global.h"

unsigned int totalCoin = 0;

/* Coin inserted, take action. */
void performInserted()
{
  TIMERStart();
  FLOWStart();
}

void COINSetup()
{
  totalCoin = 0;
  if(analogRead(A0) > 0)
  {
    Printf("Coin selector is not connected?\n");
  }
}

/* Analog reading is not the solution. */
void COINLoop()
{
  if(analogRead(A0) > 0)
  {
    Printf("Coin inserted. Total : %d\n",++totalCoin);
    performInserted();
    /* Decrease delay. */
    delay(250);
  }
}

unsigned int COINGetTotal()
{
  return totalCoin;
}


