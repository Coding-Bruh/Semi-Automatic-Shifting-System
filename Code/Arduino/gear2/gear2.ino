#include <EEPROM.h>
#include"GEAR_SHIFTER.h"

#define IN1 22   //Positive clutch
#define IN2 24   //negative clutch
#define IN3 26   //negative gear
#define IN4 28   //positive gear

#define clutchPos IN1
#define clutchNeg IN2
#define gearPos   IN4
#define gearNeg   IN3

#define gearStateRegister 1

#define RED_BUTTON   A0  //up shift
#define BLACK_BUTTON A1  //down shift

#define ON LOW
#define OFF HIGH

#define SPI_Frequency 800000

uint8_t gearCount = EEPROM.read(gearStateRegister);
GEAR_SHIFTER shifter;


void setup() {
  shifter = GEAR_SHIFTER(SPI_Frequency);
  Serial.begin(115200);
}

ISR (SPI_STC_vect)
{ shifter.readToSPIBuffer();
  //if((digitalRead(SS) == LOW))// || (shifet.gear == 0))
  //digitalWrite(MISO,gearCount);
}                      // end of interrupt routine SPI_STC_vect


void loop()
{
  if ((digitalRead(SS) == LOW))
  {
    //digitalWrite(MISO, gearCount);
    //Serial.println(gearCount);
  }
  //Serial.write(gearCount);
  //delay(1000);
  int RPM = shifter.getRPMData();
  //      digitalWrite(SS, HIGH);


  digitalWrite(clutchPos, OFF);
  digitalWrite(clutchNeg, OFF);
  digitalWrite(gearPos, OFF);
  digitalWrite(gearNeg, OFF);
}







//void retractGearLev(int sec)
//{
//  digitalWrite(gearPos, OFF);
//  digitalWrite(gearNeg, ON);
//  delay(sec);
//}
//
//void moveGearToCenter()
//{
//  digitalWrite(gearPos, ON);
//  digitalWrite(gearNeg, OFF);
//  delay(100);
//}
//
//void moveGearLev(int sec)
//{
//  digitalWrite(gearPos, ON);
//  digitalWrite(gearNeg, OFF);
//  delay(sec);
//}
//
//void gearStop(int sec)
//{
//  digitalWrite(gearPos, OFF);
//  digitalWrite(gearNeg, OFF);
//  delay(sec);
//}
//
//void saveGearPosition(uint8_t gear)
//{
//  EEPROM.write(gearStateRegister, gear);
//}
//
//int readGearPosition()
//{
//  return EEPROM.read(gearStateRegister);
//}
//
//
//void upShift(int gearCount)
//{
//  if (gearCount == 6) {} // at sixth gear, do nothing. No higher gears
//  else if (gearCount == 0)       // at neutral, shifting to first gear
//  {
//    retractGearLev(500);
//    moveGearLev(100);
//  }
//  else                      // move up a gear
//  {
//    moveGearLev(500);
//    retractGearLev(100);
//  }
//}
//
//void downShift(int gearCount)
//{
//  if (gearCount == 1) {}  // at neutral, downshifting will take you to first gear. NO GOOD!!
//  //  else if(gearCount == 1) // at first gear, shifting to neutral
//  //  {
//  //    moveGearLev(80);
//  //    retractGearLev(50);
//  //  }
//  else                    // move down a gear
//  {
//    retractGearLev(500);
//    moveGearLev(100);
//  }
//}

//void incrementGear()
//{
//  if (gearCount < 6)
//    gearCount++;
//}
//
//void decrementGear()
//{
//  if (gearCount > 1)
//    gearCount--;
//}
//
//void readToSPIBuffer()
//{
//  isrFlag = 0;
//  if (bufferPosition < sizeof(spiDataPacket))
//    spiDataPacket [bufferPosition++] = SPDR;
//}
//
//int getRPMData()
//{
//  return processSPIBuffer();
//}
//
//int processSPIBuffer()
//{
//  if (isrFlag == 0)
//  {
//    isrFlag = 1;
//    rpmData = (spiDataPacket[0] << 8) | spiDataPacket[1];
//    //[For Diagnositics purposes only]--------------------------
//
//    Serial.print("Converted Data from raw SPI: ");
//    Serial.println(rpmData);
//    //printSPI_DATA();
//
//    //---------------------------------------------------------
//    bufferPosition = 0;
//    return rpmData;
//  }
//  else return rpmData;
//}
//
//void sendGearCount()
//{
//
//  // setting spi into slave mode
//  //SPCR |= 1 >> SPE;
//}
//
//bool runStartUpRoutine()
//{
//  Serial.println("this happened");
//  //digitalWrite(SS, LOW);
//  //SPI.transfer(gearCount);
//  //digitalWrite(SS, HIGH);
//  return true;
//}
//
//
//
//
//
//
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

