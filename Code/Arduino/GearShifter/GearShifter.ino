#include <EEPROM.h>

#define IN1 8   //Positive clutch
#define IN2 9   //negative clutch
#define IN3 10  //negative gear
#define IN4 11  //positive gear

#define clutchPos IN1
#define clutchNeg IN2
#define gearPos   IN4
#define gearNeg   IN3

#define gearStateRegister 1

#define RED_BUTTON   A0  //up shift
#define BLACK_BUTTON A2  //down shift

#define ON LOW
#define OFF HIGH

uint8_t gearCount = EEPROM.read(gearStateRegister);

void setup() {

  Serial.begin(19200);

  pinMode(RED_BUTTON, INPUT);
  pinMode(BLACK_BUTTON, INPUT);
  
  pinMode(clutchPos,OUTPUT);
  pinMode(clutchNeg,OUTPUT);
  pinMode(gearPos,OUTPUT);
  pinMode(gearNeg,OUTPUT);

  int gearpos = 80;
 
  //runStartUpRoutine();
  //retractGearLev(200);
  moveGearLev(500);
  //gearStop(10);
  retractGearLev(100); 
  //moveGearLev(500);

  
  //moveGearLev(gearpos);
  //gearStop(100);
  //retractGearLev(gearpos);

  
}

void loop() 
{
//  int up = analogRead(RED_BUTTON);
//  int down = analogRead(BLACK_BUTTON); 
//  Serial.print("up: ");
//  Serial.print(up);
//  Serial.print(" down: ");
//  Serial.println(down);
//  if(up > 900)
//  {
//    upShift(gearCount);
//    incrementGear();
//  }
//  if(down > 900)
//  {
//    downShift(gearCount);
//    decrementGear();
//  }
//
//  Serial.println(gearCount);
//  EEPROM.write(gearStateRegister, gearCount);
  digitalWrite(clutchPos,OFF);
  digitalWrite(clutchNeg,OFF);
  digitalWrite(gearPos,OFF);
  digitalWrite(gearNeg,OFF);

}

void retractGearLev(int sec)
{
  digitalWrite(gearPos,OFF);
  digitalWrite(gearNeg,ON);
  delay(sec);
}

void moveGearToCenter()
{
  digitalWrite(gearPos,ON);
  digitalWrite(gearNeg,OFF);
  delay(100);
}

void moveGearLev(int sec)
{
  digitalWrite(gearPos,ON);
  digitalWrite(gearNeg,OFF);
  delay(sec);
}

void gearStop(int sec)
{
  digitalWrite(gearPos,OFF);
  digitalWrite(gearNeg,OFF);
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
  if(gearCount == 6){} // at sixth gear, do nothing. No higher gears
  else if (gearCount == 0)       // at neutral, shifting to first gear
  {
    retractGearLev(500);
    moveGearLev(100);
  }
  else                      // move up a gear
  {  
    moveGearLev(500);
    retractGearLev(100);
  }
}

void downShift(int gearCount)
{
  if(gearCount == 0){}    // at neutral, downshifting will take you to first gear. NO GOOD!!
  else if(gearCount == 1) // at first gear, shifting to neutral
  {
    moveGearLev(80); 
    retractGearLev(50);
  }
  else                    // move down a gear
  {
    retractGearLev(500);
    moveGearLev(100);
  }
}

void incrementGear()
{
  if (gearCount < 6)
    gearCount++;
}

void decrementGear()
{
  if (gearCount > 0)
    gearCount--;
}

