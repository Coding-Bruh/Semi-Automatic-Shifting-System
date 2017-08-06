#include <EEPROM.h>
#include <Wire.h>
#include"GEAR_SHIFTER.h"

#define RED_BUTTON   A0  //up shift
#define BLACK_BUTTON A1  //down shift

#define gearStateRegister 0

#define SPI_Frequency 800000

int up, down;

GEAR_SHIFTER shifter;

 int startTime, endTime;

void setup() {
  shifter = GEAR_SHIFTER(SPI_Frequency);
  Serial.begin(19200);

  pinMode(RED_BUTTON, INPUT);
  pinMode(BLACK_BUTTON, INPUT);

  pinMode(A2, INPUT);
  
  Wire.begin(7); // join i2c bus with address #7
  Wire.onReceive(handleI2CReceive);
  Wire.onRequest(handleI2CRequest);

  /* Testing Clutch */
  shifter.engageClutch(1000);
  //shifter.saveGearState(100);
  
//  shifter.retractGearLev(500);
//  shifter.moveGearLev(100);
//  shifter.stopActuators();
  
  /*Finding nuetral*/
  // Stage 1: retract gear lev
    //shifter.retractGearLev(120);
    //delay(1000);
  // Stage 2: move gear lev
   // shifter.moveGearLev(120);
    
}

// interrupt handlers
void handleI2CReceive(int numBytes)
{ char command = Wire.read();} // [pretty much just ignore the command]

void handleI2CRequest()
{ Wire.write(shifter.getGearCount());}

ISR (SPI_STC_vect)
{ shifter.readToSPIBuffer();}

void loop()
{
  int engineRPM = shifter.getEngineRPM_Data();

  //int neutralReading = analogRead(A2);
  //Serial.print("neutral reading: ");
  //Serial.println(neutralReading);
  
  //while (neutralReading != 0)
  //{
    //Serial.println(neutralReading);
    //shifter.moveGearLev(0.5);
  //}
  
  up = analogRead(RED_BUTTON);
  down = analogRead(BLACK_BUTTON);

//  Serial.print("up: ");
//  Serial.print(up);
//  Serial.print(" down: ");
//  Serial.println(down);
  
/* Shifting to higher gear  */

  if (up == 1023){
    shifter.upShift(shifter.getGearCount());
    shifter.incrementGearCount();
  }

/* Shifting to lower gear */

  if (down == 1023){
    shifter.downShift(shifter.getGearCount());
    shifter.decrementGearCount();
  }

  shifter.saveGearState(shifter.getGearCount());
  delay(1000);
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

