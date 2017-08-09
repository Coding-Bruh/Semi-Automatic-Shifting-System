#include"GEAR_SHIFTER.h"

GEAR_SHIFTER::GEAR_SHIFTER(){}

GEAR_SHIFTER::GEAR_SHIFTER(long SPI_Frequency)
{
  clutchPos = 22;   //Positive clutch
  clutchNeg = 24;   //Negative clutch
  gearPos   = 28;   //Positive gear
  gearNeg   = 26;   //Negative gear

  pinMode(clutchPos, OUTPUT);
  pinMode(clutchNeg, OUTPUT);
  pinMode(gearPos, OUTPUT);
  pinMode(gearNeg, OUTPUT);

  initialGearRead = true;
  gearCount = 1;
  
  SPI.beginTransaction(SPISettings(SPI_Frequency, MSBFIRST, SPI_MODE0));
  SPCR |= bit (SPE);
  SPCR |= bit (SPIE);
  SPCR |= _BV(SPE);
  pinMode(MISO,OUTPUT);
}

void GEAR_SHIFTER::readToSPIBuffer()
{
    isrFlag = 0;
    if (bufferPosition < sizeof(spiDataPacket))
        spiDataPacket [bufferPosition++] = SPDR;
}

int GEAR_SHIFTER::processSPIBuffer()
{
  if (isrFlag == 0)
  {
    isrFlag = 1;
    engineRPM_Data = (spiDataPacket[0]<< 8) | spiDataPacket[1];
    int temp = spiDataPacket[2];
    //[For Diagnositics purposes only]--------------------------

         //Serial.print("Converted Data from raw SPI on gear module: ");
         //Serial.println(engineRPM_Data);
         Serial.print("Gear number: ");
         Serial.println(temp);
         //printSPI_DATA();

    //---------------------------------------------------------
    bufferPosition = 0;
    return engineRPM_Data;
  }
  else return engineRPM_Data;
}

int GEAR_SHIFTER:: getEngineRPM_Data()
{ return processSPIBuffer(); }

void GEAR_SHIFTER::readClutchPosition()
{
  //clutchPosition = analogRead();
}

int GEAR_SHIFTER::getGearCount()
{
  return gearCount;
}

void GEAR_SHIFTER::upShift(int gearCount)
{
  switch (gearCount)
  {
    case 1:
      moveGearLev(500);
      retractGearLev(120);
      gearLevStop();
      break;
    case 2:
      moveGearLev(500);
      retractGearLev(120);
      gearLevStop();
      break;
    case 3:
      moveGearLev(500);
      retractGearLev(120);
      gearLevStop();
      break;
    case 4:
      moveGearLev(500);
      retractGearLev(120);
      gearLevStop();
      break;
    case 5:
      moveGearLev(500);
      retractGearLev(120);
      gearLevStop();
      break;
    case 6:
      moveGearLev(500);
      retractGearLev(120);
      gearLevStop();
      break;
    default:
      gearLevStop();
      break;
  }
  /*
                  if (gearCount >= 6) {} // at sixth gear, do nothing. No higher gears
                  else if (gearCount == 0)       // at neutral, shifting to first gear
                  {
                    retractGearLev(500);
                    moveGearLev(100);
                  }
                  else                      // move up a gear
                  {
                    moveGearLev(500);
                    retractGearLev(120);
                  }
  */
}

void GEAR_SHIFTER::downShift(int gearCount)
{
  disengageClutch(500);
  clutchLevStop();
  switch (gearCount)
  {
    case 1:
      retractGearLev(500);
      moveGearLev(120);
      gearLevStop();
      break;
    case 2:
      retractGearLev(500);
      moveGearLev(120);
      gearLevStop();
      break;
    case 3:
      retractGearLev(500);
      moveGearLev(120);
      gearLevStop();
      break;
    case 4:
      retractGearLev(500);
      moveGearLev(120);
      gearLevStop();
      break;
    case 5:
      retractGearLev(500);
      moveGearLev(120);
      gearLevStop();
      break;
    case 6:
      retractGearLev(500);
      moveGearLev(120);
      gearLevStop();
      break;
    default:
      gearLevStop();
      break;
  }
  /*
                  if (gearCount == 1) {}  // at neutral, downshifting will take you to first gear. NO GOOD!!
                  else if(gearCount == 1) // at first gear, shifting to neutral
                  {
                    moveGearLev(80);
                    retractGearLev(50);
                  }
                  else                    // move down a gear
                  {
                    retractGearLev(500);
                    moveGearLev(120);
                    gearLevStop();
                  }
  */
  engageClutch(350);
  clutchLevStop();
}
 
void GEAR_SHIFTER::moveGearLev(int sec)
{
  digitalWrite(gearPos, ON);
  digitalWrite(gearNeg, OFF);
  delay(sec);
}

void GEAR_SHIFTER::retractGearLev(int sec)
{
  digitalWrite(gearPos, OFF);
  digitalWrite(gearNeg, ON);
  delay(sec);
}

void GEAR_SHIFTER::gearLevStop()
{
  digitalWrite(gearPos, OFF);
  digitalWrite(gearNeg, OFF);
}
void GEAR_SHIFTER::clutchLevStop()
{
  digitalWrite(clutchPos, OFF);
  digitalWrite(clutchNeg, OFF);
}

void GEAR_SHIFTER::engageClutch(int sec)
{
  digitalWrite(clutchPos, ON);
  digitalWrite(clutchNeg, OFF);
  delay(sec);
}

void GEAR_SHIFTER::disengageClutch(int sec)
{
  digitalWrite(clutchPos, OFF);
  digitalWrite(clutchNeg, ON);
  delay(sec);
}

void GEAR_SHIFTER::incrementGearCount()
{
  if (gearCount < 6 /*&& initiateGearChange*/)
    gearCount = gearCount + 1; 
}

void GEAR_SHIFTER::decrementGearCount()
{
  if (gearCount > 1 /*&& initiateGearChange*/)
    gearCount = gearCount - 1;
}

void GEAR_SHIFTER::saveGearState(int gear)
{
  Serial.println(gear);
  EEPROM.write(0, gear);
}

void GEAR_SHIFTER::stopActuators()
{
  digitalWrite(gearPos, OFF);
  digitalWrite(gearNeg, OFF);
  digitalWrite(clutchPos, OFF);
  digitalWrite(clutchNeg, OFF); 
}

void GEAR_SHIFTER::runStartUpSequence()
{
  disengageClutch(500);
  clutchLevStop();
  for(int i = 0; i < 6; i++)
  {
    retractGearLev(500);
    moveGearLev(120);
    gearLevStop();
    delay(500);
  }
  engageClutch(500);
  clutchLevStop();
}

