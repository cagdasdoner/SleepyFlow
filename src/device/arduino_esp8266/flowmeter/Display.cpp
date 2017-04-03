#include "Display.h"
#include "Global.h"

#define NDIGITS         8
#define NDIGITS_MASK    7

const int latchpin = D2 ; // RCK
const int clockpin = D1 ; // SCK
const int datapin = D0 ;  // DIO

int valToWrite = 0;
int clockWrite = 0;

byte col[NDIGITS] = {
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000
} ;

byte seg[] = {
  0b11000000,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000,  // 9  
  0b10010000,  // 9  
} ;     

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

void DISPStart()
{
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
  Serial.println("8x7 DISPLAY OK.");
}

void DISPLoop()
{
  /* 40 msec is optimal. */
  LED_irq();
}
