#include "LED_DISPLAY.h"

LED_DISPLAY::LED_DISPLAY()
{
  // 7SEG pin assignment
  segArr[] = {40, 42, 32, 34, 36, 38, 44, 30};
  //           A,  B,  C,  D,  E,  F,  G, DP

  //               0,1,2,3,4,5,6,7    <= indeces of 'segCode'
  segCode[][] = { {0,1,0,0,0,0,0,1},    /* Displays zero          */
                  {1,1,0,1,1,1,0,1},    /* Displays one           */
                  {1,0,1,0,0,0,0,1},    /* Displays two           */
                  {1,0,0,0,1,0,0,1},    /* Displays three         */
                  {0,0,0,1,1,1,0,1},    /* Displays four          */
                  {0,0,0,0,1,0,1,1},    /* Displays five          */
                  {0,0,0,0,0,0,1,1},    /* Displays six           */
                  {0,1,0,1,1,0,0,1},    /* Displays seven         */
                  {0,0,0,0,0,0,0,1},    /* Displays eight         */
                  {0,0,0,1,1,0,0,1},    /* Displays nine          */
                  {1,0,0,1,0,1,1,1},    /* Displays neutral       */
                  {1,1,1,1,1,1,1,0}  }; /* Displays decimal point */

  // Common anode assignment
  comAnodeArr[] = {46,48,49,47,45,43,41,39,37, 33, 35, 31, 28, 26, 24, 22}
  //               C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16

  // LED color assignment
  color[][] = { {2,3,4},    /* Red1, Red2, Red3       */
                {10,9,8},   /* Green1, Green2, Green3 */
                {7,6,5}};   /* Blue1, Blue2, Blue3    */
}

/* 'setup' method the pin modes for all the variables with the class*/
void LED_DISPLAY::setup()
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
  for(int i: segArr)
    digitalWrite(i,HIGH);
}

void LED_DISPLAY::displayGear(int num)
{
  for (int i = 0; i < segSize; i++)
    digitalWrite(seg[i],segCode[num][i]);
}

void LED_DISPLAY::displayNeutral()
{
  displayGear(10);
}

void LED_DISPLAY::displayDecimalPoint()
{
  displayGear(11);
}
