#include <EEPROM.h>
#include <SPI.h>

#define IN1 22   //Positive clutch    // -> done
#define IN2 24   //negative clutch    // -> done
#define IN3 26   //negative gear      // -> done
#define IN4 28   //positive gear      // -> done

#define clutchPos IN1   // -> done
#define clutchNeg IN2   // -> done
#define gearPos   IN4   // -> done
#define gearNeg   IN3   // -> done

#define gearStateRegister 1   // -> done

#define RED_BUTTON   A0  //up shift
#define BLACK_BUTTON A1  //down shift

#define ON LOW        // -> done
#define OFF HIGH      // -> done

uint8_t gearCount = EEPROM.read(gearStateRegister); // -> done
int up, down;
uint8_t spiDataPacket[2];
uint8_t isrFlag = 0;
int rpmData;
int bufferPosition = 0;
bool start, pass1;

void setup() {

  Serial.begin(19200);
  //Serial1.begin(19200);

  pinMode(RED_BUTTON, INPUT);
  pinMode(BLACK_BUTTON, INPUT);

  pinMode(clutchPos, OUTPUT);
  pinMode(clutchNeg, OUTPUT);
  pinMode(gearPos, OUTPUT);
  pinMode(gearNeg, OUTPUT);

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPCR |= bit (SPE);
  SPCR |= bit (SPIE);
  //SPCR |= _BV(SPE);
  pinMode(MISO, OUTPUT);
  pinMode(SS, OUTPUT);
  //sendGearCount();

  //start = runStartUpRoutine();
  pass1 = false;
}

ISR (SPI_STC_vect)
{readToSPIBuffer();}                      // end of interrupt routine SPI_STC_vect


void loop()
{
    up = analogRead(RED_BUTTON);
    down = analogRead(BLACK_BUTTON);
    
    Serial.print("up: ");
    Serial.print(up);
    Serial.print(" down: ");
    Serial.println(down);
    if (up > 900)
    {
      upShift(gearCount);
      incrementGear();
      //sendGearCount();
    }
    if (down > 900)
    {
      downShift(gearCount);
      decrementGear();
      //sendGearCount();
    }
   int incomingByte; 

    int rpm = getRPMData();
    Serial.println(rpm);
    //Serial.println(gearCount);
    EEPROM.write(gearStateRegister, gearCount);
    digitalWrite(clutchPos, OFF);
    digitalWrite(clutchNeg, OFF);
    digitalWrite(gearPos, OFF);
    digitalWrite(gearNeg, OFF);
}

void retractGearLev(int sec)
{
  digitalWrite(gearPos, OFF);
  digitalWrite(gearNeg, ON);
  delay(sec);
}

void moveGearToCenter()
{
  digitalWrite(gearPos, ON);
  digitalWrite(gearNeg, OFF);
  delay(100);
}

void moveGearLev(int sec)
{
  digitalWrite(gearPos, ON);
  digitalWrite(gearNeg, OFF);
  delay(sec);
}

void gearStop(int sec)
{
  digitalWrite(gearPos, OFF);
  digitalWrite(gearNeg, OFF);
  delay(sec);
}

void saveGearPosition(uint8_t gear)
{
  EEPROM.write(gearStateRegister, gear);
}

int readGearPosition()
{
  return EEPROM.read(gearStateRegister);
}


void upShift(int gearCount)
{
  if (gearCount == 6) {} // at sixth gear, do nothing. No higher gears
  else if (gearCount == 0)       // at neutral, shifting to first gear
  {
    retractGearLev(500);
    moveGearLev(100);
  }
  else                      // move up a gear
  {
    moveGearLev(500);
    retractGearLev(130);
  }
}

void downShift(int gearCount)
{
  if (gearCount == 1) {}  // at neutral, downshifting will take you to first gear. NO GOOD!!
  //  else if(gearCount == 1) // at first gear, shifting to neutral
  //  {
  //    moveGearLev(80);
  //    retractGearLev(50);
  //  }
  else                    // move down a gear
  {
    retractGearLev(500);
    moveGearLev(130);
  }
}

void incrementGear()
{
  if (gearCount < 6)
    gearCount++;
}

void decrementGear()
{
  if (gearCount > 1)
    gearCount--;
}

void readToSPIBuffer()
{
  isrFlag = 0;
  if (bufferPosition < sizeof(spiDataPacket))
    spiDataPacket [bufferPosition++] = SPDR;
}

int getRPMData()
{
  return processSPIBuffer();
}

int processSPIBuffer()
{
  if (isrFlag == 0)
  {
    isrFlag = 1;
    rpmData = (spiDataPacket[0] << 8) | spiDataPacket[1];
    //[For Diagnositics purposes only]--------------------------

    Serial.print("Converted Data from raw SPI: ");
    Serial.println(rpmData);
    //printSPI_DATA();

    //---------------------------------------------------------
    bufferPosition = 0;
    return rpmData;
  }
  else return rpmData;
}

bool runStartUpRoutine()
{
  Serial.println("this happened");
  //digitalWrite(SS, LOW);
  //SPI.transfer(gearCount);
  //digitalWrite(SS, HIGH);
  return true;
}







void neutral(int i)
{
  //    while(i > 0)
  //    {
  //      retractGearLev(500);
  //      moveGearLev(100);
  //      gearStop(50);
  //      i--;
  //    }
  //gearStop(10);
  moveGearLev(20);
  retractGearLev(20);
}

