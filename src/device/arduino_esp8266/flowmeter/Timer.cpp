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

void publishCallback(void *pArg)
{
  /* Keep our ISR light! */
  ticked = true;
}

void TIMERStart()
{
  os_timer_setfn(&tickTimer, publishCallback, NULL);
  os_timer_arm(&tickTimer, interval, true);
  ticked = false;
}

void TIMERStop()
{
  os_timer_disarm(&tickTimer);
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
