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
  RPM_PIN = 0;                    // RPM pin number
  pinMode(RPM_PIN,INPUT);   `     // setting RPM_Pin as input

  for(int i: segArr)              // setting every element of 'segArr' to an output
    pinMode(i,OUTPUT);

  for(int i: comAnodeArr)         // setting every element of 'comAnodeArr' to output
    pinMode(i,OUTPUT);

  for (int i = 0; i < 3; i++)     // setting every element of 'color' to output
  {
    pinMode(color[0][i],OUTPUT);  
    pinMode(color[1][i],OUTPUT);
    pinMode(color[2][i],OUTPUT);
  }

  segOff();

  SPI.beginTransaction(SPISettings(SPI_Frequency, MSBFIRST, SPI_MODE0));
  SPCR |= bit (SPE);
  SPCR |= bit (SPIE);
  pinMode(MISO,OUTPUT);
}

/* 'segOff' method sets all the 7 segment pins to value of 1, which turns off
   all the LEDs on the 7 seven segment display.*/
void LED_DISPLAY::segOff()
{
  displayGear(0);
}

/* 'segOff' method sets all the 7 segment pins to value of 1, which turns off
   all the LEDs on the 7 seven segment display.*/
void LED_DISPLAY::displayGear(int num)
{
  for (int i = 0; i < 8; i++)
    digitalWrite(segArr[i],segCode[num][i]);
}

void LED_DISPLAY::displayNeutral()
{
  displayGear(7);
}

void LED_DISPLAY::displayDecimalPoint()
{
  displayGear(8);
}

void LED_DISPLAY::readToSPIBuffer()
{
    isrFlag = 0;
    if (bufferPosition < sizeof(spiDataPacket))       
        spiDataPacket [bufferPosition++] = SPDR;       
}

int LED_DISPLAY::getRPMData()
{
  return processSPIBuffer();
}

int LED_DISPLAY::getCurrentGearState()
{
  return gear;
}

int LED_DISPLAY::processSPIBuffer()
{
  if (isrFlag == 0)
  {
    isrFlag = 1;
    rpmData = (spiDataPacket[0]<< 8) | spiDataPacket[1];
    gear = spiDataPacket[2];
    //[For Diagnositics purposes only]--------------------------
        /*
         *Serial.print("Converted Data from raw SPI: ");
         *Serial.println(spiData);
         *Serial.print("Gear number");
         *Serial.println(gear);
         *printSPI_DATA();
         */
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
{
  RPM_PIN = num;
  pinMode(RPM_PIN,INPUT);
}

void LED_DISPLAY::setDisplayTypePin(int num)
{
  RPM_PIN = num;
  pinMode(RPM_PIN,INPUT);
}

