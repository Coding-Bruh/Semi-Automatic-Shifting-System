#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H


class LED_DISPLAY
{
public:
  LED_DISPLAY();
  void setup();

  // methods for 7 segment display
  void displayGear(int num);
  void displayNeutral();
  void displayDecimalPoint();
  void segOff();
private:
  int RPM_PIN = 0;

  int segArr[8];
  int segCode[12][8];

  // Declaration of common anodes on LED Bar
  int comAanodeArr[16];

  int color[3][3]; //Declaration of selection array
};

#endif
