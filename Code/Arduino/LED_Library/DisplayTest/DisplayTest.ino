#include "LED_DISPLAY.h"
#include <Wire.h>
#include "I2C.h"
#define SPI_Frequency 800000

LED_DISPLAY hud;
uint8_t gear;
int RPM;
void setup() {
  // put your setup code here, to run once:
  hud = LED_DISPLAY(SPI_Frequency);
  Serial.begin(19200);
  
}

ISR (SPI_STC_vect) {hud.readToSPIBuffer();}

void loop() {
  Wire.begin();
  Wire.setClock(400000L);
  Wire.requestFrom(7, 1);
  if (Wire.available())   // slave may send less than requested
  { 
    gear = Wire.read();    // receive a byte as character         /
  }
  RPM = hud.getRPMData();
  hud.setGaugeMode(1);
  hud.displayGear(gear);
  hud.displayRPMs(hud.mapToLEDGauge(RPM));
  Wire.endTransmission();
  Wire.end();
//  if(hang)
  //  unfreeze();   
}
