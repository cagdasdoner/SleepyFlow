#include "Display.h"
#include "Global.h"

const int latchpin = D2 ; // RCK
const int clockpin = D1 ; // SCK
const int datapin = D0 ;  // DIO

int valToWrite = 0;
int clockWrite = 0;   

byte segbuf[NDIGITS] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff } ;
byte segcnt = 0;

void LED_irq(void)
{
  digitalWrite(latchpin, LOW);
  // select the digit...
  shiftOut(datapin, clockpin, MSBFIRST, col[segcnt]) ;
  // and select the segments
  shiftOut(datapin, clockpin, MSBFIRST, segbuf[segcnt]) ;
  digitalWrite(latchpin, HIGH) ;
  segcnt ++ ;
  segcnt &= NDIGITS_MASK ;
}

void DISPWriteLiter(int param)
{
  segbuf[6] = seg[param / 10];
  segbuf[7] = seg[param % 10];
}

void DISPWriteTime(int tick)
{
  int minuteWrite = tick / 60;
  int secondWrite = tick % 60;
  segbuf[0] = seg[minuteWrite];
  segbuf[2] = seg[secondWrite / 10];
  segbuf[3] = seg[secondWrite % 10];
}

void DISPSetup()
{
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
  Printf("8x7 DISPLAY OK.");
}

void DISPLoop()
{
  /* 40 msec is optimal. */
  LED_irq();
}
