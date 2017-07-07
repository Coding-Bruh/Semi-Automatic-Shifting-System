#include "LED_DISPLAY.h"
#include <Arduino.h>
LED_DISPLAY::LED_DISPLAY()
{
  pinMode(RPM_PIN,INPUT);

  for(int i: segArr)
    pinMode(i,OUTPUT);

  for(int i: comAnodeArr)
    pinMode(i,OUTPUT);

  for (int i = 0; i < 3; i++)
  {
    pinMode(color[0][i],OUTPUT);
    pinMode(color[1][i],OUTPUT);
    pinMode(color[2][i],OUTPUT);
  }
}

/* 'segOff' method sets all the 7 segment pins to value of 1, which turns off
   all the LEDs on the 7 seven segment display.*/
void LED_DISPLAY::segOff()
{
  displayGear(12);
}

void LED_DISPLAY::displayGear(int num)
{
  for (int i = 0; i < 8; i++)
    digitalWrite(segArr[i],segCode[num][i]);
}

void LED_DISPLAY::displayNeutral()
{
  displayGear(10);
}

void LED_DISPLAY::displayDecimalPoint()
{
  displayGear(11);
}
