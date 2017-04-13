#include "CoinSelector.h"
#include "Hardware.h"
#include "FlowSensor.h"
#include "Global.h"

#define ANALOG_LOW_LEVEL     1
#define COIN_INSERTION_DELAY 100

int prevVal = 0;
int analogVal = 0;

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

/* Analog reading is not the final solution. */
void COINLoop()
{
  if(selectorInitialized)
  {
    analogVal = analogRead(A0);
    if(analogVal > ANALOG_LOW_LEVEL)
    {
      delay(COIN_INSERTION_DELAY);
      performInserted();
      Printf("Coin inserted. Total : %d\n", totalCoin);
    }
    if(analogVal != prevVal)
    {
      Printf("Received new val : %d\n", analogVal);
      prevVal = analogVal;
    }
  }
}


