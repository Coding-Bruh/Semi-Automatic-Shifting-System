#include <EEPROM.h>
#include <Wire.h>
#include"GEAR_SHIFTER.h"

#define RED_BUTTON   A0  //up shift
#define BLACK_BUTTON A1  //down shift

#define gearStateRegister 0

#define SPI_Frequency 800000

int up, down, idle;
bool disengaged;

GEAR_SHIFTER shifter;
int engineRPM = 0;

void setup() {
  shifter = GEAR_SHIFTER(SPI_Frequency);
  Serial.begin(19200);

  pinMode(RED_BUTTON, INPUT);
  pinMode(BLACK_BUTTON, INPUT);

  pinMode(A2, INPUT);
  
  Wire.begin(7); // join i2c bus with address #7
  Wire.setClock(400000L);
  Wire.onReceive(handleI2CReceive);
  Wire.onRequest(handleI2CRequest);

  idle = 175;
  disengaged = false;
  //------------------------------------------
  shifter.disengageClutch(1000);  
  shifter.engageClutch(600);
  shifter.clutchLevStop();
  
  shifter.disengageClutch(200);
  shifter.clutchLevStop();
  for(int i = 0; i < 7; i++)
  {
    if(i < 6)
    {
      shifter.retractGearLev(500);
      shifter.moveGearLev(100);
      shifter.gearLevStop();
    }
    else
    {
      shifter.retractGearLev(500);
      shifter.moveGearLev(60);
      shifter.gearLevStop();
    }
    delay(500);
  }
  //----------------------------------------
   disengaged = true;
//shifter.moveGearLev(500);
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
  engineRPM = shifter.getEngineRPM_Data();
  //Serial.print("RPM: ");
  //Serial.println(engineRPM);

  if (engineRPM <= idle && !disengaged)
  {
    shifter.disengageClutch(200);
    shifter.clutchLevStop();
    disengaged = true;
  }
  else if (engineRPM > idle && disengaged)
  {
    shifter.engageClutch(200);
    shifter.clutchLevStop();
    disengaged = false;
  }
  else;

  up = analogRead(RED_BUTTON);
  down = analogRead(BLACK_BUTTON);
  
/* Shifting to higher gear  */
  if (up >= 1000){
    shifter.incrementGearCount();
    shifter.upShift(shifter.getGearCount());
  }
  else if (down >= 1000){
    shifter.disengageClutch(200);
    shifter.clutchLevStop();
    shifter.decrementGearCount();
    shifter.downShift(shifter.getGearCount());
    shifter.engageClutch(200);
    shifter.clutchLevStop();
  }
  else;

  shifter.saveGearState(shifter.getGearCount());
  shifter.stopActuators();
}

///* Testing Clutch */
//  shifter.disengageClutch(100);
//  shifter.engageClutch(200);
//  shifter.saveGearState(100);
//  
//  shifter.retractGearLev(500);
//  shifter.moveGearLev(100);
//  shifter.stopActuators();
//  
//  /*Finding nuetral*/
//   //Stage 1: retract gear lev
//   shifter.retractGearLev(120);
//   delay(1000);
//   //Stage 2: move gear lev
//   shifter.moveGearLev(120);
