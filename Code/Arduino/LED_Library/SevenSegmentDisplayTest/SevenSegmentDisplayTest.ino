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
  hud.displayGear(1);
  delay(1000);
  hud.displayGear(2);
  delay(1000);
  hud.displayGear(3);
  delay(1000);
  hud.displayGear(4);
  delay(1000);
  hud.displayGear(5);
  delay(1000);
  hud.displayGear(6);
  delay(1000);
}
