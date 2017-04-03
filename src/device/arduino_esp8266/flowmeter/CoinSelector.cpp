#include "CoinSelector.h"
#include "Global.h"

unsigned int totalCoin = 0;

void performInserted()
{

}

void COINStart()
{
  totalCoin = 0;
}

/* Analog reading is not healthy. */
void COINLoop()
{
  int a = analogRead(A0);
  if(a > 0)
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


