#ifndef GEAR_SHIFTER_H
#define GEAR_SHIFTER_H

#define ON LOW
#define OFF HIGH

#include <SPI.h>
#include <EEPROM.h>

#define gearStateRegister 0

class GEAR_SHIFTER
{
public:
  GEAR_SHIFTER();
  GEAR_SHIFTER(long SPI_Frequency);

  // methods used inside interrupts
  void  readToSPIBuffer();
  void  readClutchPosition();
  
  int   processSPIBuffer();
  int   getEngineRPM_Data();
  int   getGearCount();

  // methods for shifting
  void  upShift(int gear);
  void  downShift(int gear);

  // increment gearCount
  void  incrementGearCount();
  void  decrementGearCount();
  
  //methods for actuation
  void  moveGearLev(int sec);
  void  retractGearLev(int sec);
  void  gearLevStop(int sec);
  void  saveGearState(int gear);
  void  disengageClutch(int sec);
  void  engageClutch(/*bool fastActuation*/ int sec);
  void  stopActuators();
  
  bool  initialGearRead = false;
  int   pressCount = 0;
private:
  unsigned int engineRPM_Data;  // current RPM value
  volatile int bufferPosition;  // used as index for the 'spiDataPakcet' array
  uint8_t spiDataPacket[3];     // SPI data packet
  bool  isrFlag;                // bool used to detect new interrupts
  int  gearCount = 1; //EEPROM.read(gearStateRegister);
  int gearPos, gearNeg, clutchPos, clutchNeg, clutchPosition;
};

#endif
