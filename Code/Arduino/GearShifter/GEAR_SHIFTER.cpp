#include"GEAR_SHIFTER.h"

GEAR_SHIFTER::GEAR_SHIFTER(){}

GEAR_SHIFTER::GEAR_SHIFTER(long SPI_Frequency)
{
  SPI.beginTransaction(SPISettings(SPI_Frequency, MSBFIRST, SPI_MODE0));
  SPCR |= bit (SPE);
  SPCR |= bit (SPIE);
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
    rpmData = (spiDataPacket[0]<< 8) | spiDataPacket[1];
    //[For Diagnositics purposes only]--------------------------

         //Serial.print("Converted Data from raw SPI: ");
         //Serial.println(rpmData);
         //Serial.print("Gear number");
         //Serial.println(gear);
         //printSPI_DATA();

    //---------------------------------------------------------
    bufferPosition = 0;
    return rpmData;
  }
  else return rpmData;
}

int GEAR_SHIFTER::getRPMData()
{ return processSPIBuffer(); }
