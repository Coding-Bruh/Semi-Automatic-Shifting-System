#include "LED_DISPLAY.h"
#include <Wire.h>
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
//  Wire.begin();
//  Wire.requestFrom(7, 1);
//  while (Wire.available())   // slave may send less than requested
//  { 
//    gear = Wire.read();    // receive a byte as character
//    //Serial.println(c);         // print the character
//  }
  RPM = hud.getRPMData();
  hud.setGaugeMode(1);
  hud.displayGear(gear);
  hud.displayRPMs(hud.mapToLEDGauge(RPM));
  //Wire.end();   
}
