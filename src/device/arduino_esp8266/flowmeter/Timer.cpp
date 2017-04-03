#include "Timer.h"
#include "Display.h"
#include "Global.h"

extern "C" {
#include "user_interface.h"
}

os_timer_t tickTimer;
boolean ticked = false;
unsigned int interval = 1000;
unsigned int totalTicks = 0;

void tickedCallback(void *pArg)
{
  /* Keep our ISR light! */
  ticked = true;
}

void TIMERSetup(unsigned int _interval)
{
  interval = _interval;
}

void TIMERStart()
{
  os_timer_setfn(&tickTimer, tickedCallback, NULL);
  os_timer_arm(&tickTimer, interval, true);
  ticked = false;
}

void TIMERStop()
{
  os_timer_disarm(&tickTimer);
}

unsigned int TIMERGetTicks()
{
  return totalTicks;
}

void TIMERLoop()
{
  if(ticked)
  {
    totalTicks++;
    DISPWriteTime(totalTicks);
    ticked = false;
  }
}
