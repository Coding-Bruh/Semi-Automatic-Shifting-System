#include <EEPROM.h>
#include <Wire.h>
#include"GEAR_SHIFTER.h"

#define gearStateRegister 1

#define RED_BUTTON   A0  //up shift
#define BLACK_BUTTON A1  //down shift

#define SPI_Frequency 800000

int up, down;

GEAR_SHIFTER shifter;


void setup() {
  shifter = GEAR_SHIFTER(SPI_Frequency);
  Serial.begin(250000);

  pinMode(RED_BUTTON, INPUT);
  pinMode(BLACK_BUTTON, INPUT);
  
  Wire.begin(7); // join i2c bus with address #7
  Wire.onReceive(handleI2CReceive);
  Wire.onRequest(handleI2CRequest);

  //shifter.disengageClutch(500);
  
}

// interrupt handlers
void handleI2CReceive(int numBytes)
{ char command = Wire.read();} // [pretty much just ignore the command]

void handleI2CRequest()
{
  byte data;
  data = shifter.getGearCount();
  Wire.write(data);
}

ISR (SPI_STC_vect)
{ shifter.readToSPIBuffer();}


void loop()
{
  int engineRPM = shifter.getEngineRPM_Data();
  
  up = analogRead(RED_BUTTON);
  down = analogRead(BLACK_BUTTON);

//  Serial.print("up: ");
//  Serial.print(up);
//  Serial.print(" down: ");
//  Serial.println(down);
  
// Shifting to higher gear
  if (up > 900){
    shifter.upShift(shifter.getGearCount());
    shifter.incrementGearCount();
  }

// Shifting to lower gear
  if (down > 900){
    shifter.downShift(shifter.getGearCount());
    shifter.decrementGearCount();
  }

  shifter.saveGearState(shifter.getGearCount());
  shifter.stopActuators();
}

//
//void neutral(int i)
//{
//  //    while(i > 0)
//  //    {
//  //      retractGearLev(500);
//  //      moveGearLev(100);
//  //      gearStop(50);
//  //      i--;
//  //    }
//  //gearStop(10);
//  moveGearLev(20);
//  retractGearLev(20);
//}

