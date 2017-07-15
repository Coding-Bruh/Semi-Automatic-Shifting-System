#include "LED_DISPLAY.h"

#define SPI_Frequency 800000

LED_DISPLAY hud;

void setup() {
  // put your setup code here, to run once:
  hud = LED_DISPLAY(SPI_Frequency);
  Serial.begin(115200);

}

ISR (SPI_STC_vect) {hud.readToSPIBuffer();}

void loop() {
  // put your main code here, to run repeatedly:
  
  int RPM = hud.getRPMData();
  hud.setGaugeMode(1);
  hud.displayGear(hud.getCurrentGearState());
  hud.displayRPMs(hud.mapToLEDGauge(RPM));  
  
}
