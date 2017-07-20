#include "LED_DISPLAY.h"
#include <Arduino.h>

/* 'LED_DISPLAY()' is the default constructor. Nothing has been set. You  will need 
   to use the set methods to set all your pin modes.The rational for this 
   constructor is that it lets the user define all the pin numbers with the 'set' 
   methods.*/
LED_DISPLAY::LED_DISPLAY(){}

/* 'LED_DISPLAY(long)' is a constructor with pins configured to Semi Auto Shifters' 
   display rigg.*/
LED_DISPLAY::LED_DISPLAY(long SPI_Frequency)
{
  rpmIdle = 0;
  rpmRedLine = 5000;
  comAnodeLength = sizeof(comAnodeArr) / 2; //needed to divide by 2 to get proper readings not sure why.

  gaugeMode = false;
  
  RPM_PIN = 0;                    // RPM pin number
  pinMode(RPM_PIN,INPUT);         // setting RPM_Pin as input

  for(int i: segArr)              // setting every element of 'segArr' to an output
    pinMode(i,OUTPUT);

  for(int i: comAnodeArr)
    pinMode(i,OUTPUT);

  for (int i = 0; i < 3; i++)     // setting every element of 'color' to output
  {
    pinMode(color[0][i],OUTPUT);  
    pinMode(color[1][i],OUTPUT);
    pinMode(color[2][i],OUTPUT);
  }

  SPI.beginTransaction(SPISettings(SPI_Frequency, MSBFIRST, SPI_MODE0));
  SPCR |= bit (SPE);
  SPCR |= bit (SPIE);
  SPCR |= _BV(SPE);
  pinMode(MISO,OUTPUT);
}

/* 'segOff' method sets all the 7 segment pins to value of 1, which turns off
   all the LEDs on the 7 seven segment display.*/
void LED_DISPLAY::segOff()
{ displayGear(0); }

/* 'displayGear' method sets all the 7 segment pins to value of 1, which turns off
   all the LEDs on the 7 seven segment display.*/
void LED_DISPLAY::displayGear(int num)
{
  for (int i = 0; i < 8; i++)
    digitalWrite(segArr[i],segCode[num][i]);
}

void LED_DISPLAY::displayNeutral()
{ displayGear(7); }

void LED_DISPLAY::displayDecimalPoint()
{ displayGear(8); }

void LED_DISPLAY::readToSPIBuffer()
{
    isrFlag = 0;
    if (bufferPosition < sizeof(spiDataPacket))       
        spiDataPacket [bufferPosition++] = SPDR;       
}

int LED_DISPLAY::getRPMData()
{ return processSPIBuffer(); }

int LED_DISPLAY::getCurrentGearState()
{ return gear; }

int LED_DISPLAY::processSPIBuffer()
{
  if (isrFlag == 0)
  {
    isrFlag = 1;
    rpmData = (spiDataPacket[0]<< 8) | spiDataPacket[1];
    gear = spiDataPacket[2];
    //[For Diagnositics purposes only]--------------------------
        
         Serial.print("Converted Data from raw SPI: ");
         Serial.println(rpmData);
         //Serial.print("Gear number");
         //Serial.println(gear);
         //printSPI_DATA();
         
    //---------------------------------------------------------
    bufferPosition = 0;
    return rpmData;
  }
  else return rpmData;
}

void LED_DISPLAY::printSPI_DATA()
{
  Serial.println("SPI_ DATA_PACKET:");
  Serial.print("index: ");
  Serial.print(0);
  Serial.print(" -> ");
  Serial.println(spiDataPacket[0]);
  Serial.print("index: ");
  Serial.print(1);
  Serial.print(" -> ");
  Serial.println(spiDataPacket[1]);
  Serial.print("index: ");
  Serial.print(2);
  Serial.print(" -> ");
  Serial.println(spiDataPacket[2]);   
}

void LED_DISPLAY::setRPM_PIN(int num)
{ RPM_PIN = num; pinMode(RPM_PIN,INPUT); }

void LED_DISPLAY::setDisplayTypePin(int num)
{  RPM_PIN = num; pinMode(RPM_PIN,INPUT); }

void LED_DISPLAY::setLEDGaugeParameters(int idle, int redLine, int numComAnodes, int blinky)
{ 
  rpmIdle = idle; rpmRedLine = redLine; 
  comAnodeLength = numComAnodes; blinkPeriod = blinky;
}

int LED_DISPLAY::mapToLEDGauge(int num)
{
  if(!gaugeMode)
    return map(num, rpmIdle, rpmRedLine, 0, comAnodeLength / 2);
  else
    return map(num, rpmIdle, rpmRedLine, 0, comAnodeLength);
}

void LED_DISPLAY::setGaugeMode(int mode)
{ gaugeMode = mode; }

void LED_DISPLAY::displayRPMs(int num)
{ 
  //Serial.println(num);      /*for debugging purposes only.*/
  setColorModes(1,1,1);

  if (!gaugeMode)
  {
    if (num <= 4)
      setColorModes(1, 0);
    else if (num > 4 && num <= 6)
      setColorModes(2, 0);
    else if (num > 6)
      setColorModes(0, 0);
  }
  else
  {
    if (num <= 10)
      setColorModes(1, 0);
    else if (num > 10 && num <= 13)
      setColorModes(2, 0);
    else if (num > 13)
      setColorModes(0, 0);
  }
  
  for(int i = 0; i < comAnodeLength; i++)
  {   
    switch (gaugeMode)
    {
      case false:
        if((i < num || comAnodeLength - i <= num) && (((millis() / 100) % 2) || num < comAnodeLength / 2))
          digitalWrite(comAnodeArr[i],HIGH);
        else
          digitalWrite(comAnodeArr[i], LOW);
        break;
      case true:
        if((i < num) && (((millis() / 100) % 2) || num < comAnodeLength))
          digitalWrite(comAnodeArr[i],HIGH);
        else
          digitalWrite(comAnodeArr[i], LOW);
        break;
      default:
        break;  
    }
  }
}

void LED_DISPLAY::setColorModes(int red, int green, int blue)
{
  for (int i = 0; i < 3; i++)     // setting every row of 'color' to its corresponding value
  {
    digitalWrite(color[0][i],red);  
    digitalWrite(color[1][i],green);
    digitalWrite(color[2][i],blue);
  }
}

void LED_DISPLAY::setColorModes(int row, int state)
{
  for (int i : color[row])     // setting every element of the particular color to a state
    digitalWrite(i, state);  
}

