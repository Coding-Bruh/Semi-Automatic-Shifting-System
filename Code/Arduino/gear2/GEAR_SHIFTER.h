#ifndef GEAR_SHIFTER_H
#define GEAR_SHIFTER_H

#include <SPI.h>

class GEAR_SHIFTER
{
public:
  GEAR_SHIFTER();
  GEAR_SHIFTER(long SPI_Frequency);

  void  readToSPIBuffer();
  int   processSPIBuffer();

  int   getRPMData();
private:
  unsigned int   rpmData;        // current RPM value
  volatile int bufferPosition; // used as index for the 'spiDataPakcet' array
  uint8_t spiDataPacket[3];    // SPI data packet
  bool  isrFlag;                // bool used to detect new interrupts
};

#endif
