#include "LED_DISPLAY.h"

LED_DISPLAY hud;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  hud.displayGear(0);
  delay(2000);
  hud.displayGear(1);
  delay(2000);
  hud.displayGear(2);
  delay(2000);
  hud.displayGear(3);
  delay(2000);
  hud.displayGear(4);
  delay(2000);
  hud.displayGear(5);
  delay(2000);
  hud.displayGear(6);
  delay(2000);
  hud.displayGear(7);
  delay(2000);
  hud.displayGear(8);
  delay(2000);
  hud.displayGear(9);
  delay(2000);
  hud.displayNeutral();
  delay(2000);
  hud.displayDecimalPoint();
  delay(2000);
  hud.segOff();
  delay(2000);
}
