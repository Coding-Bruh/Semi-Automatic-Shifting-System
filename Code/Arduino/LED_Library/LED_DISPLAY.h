#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H


class LED_DISPLAY_H
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

  int segSize = 8; // size of 7SEG display
  int segArr[segSize];
  int gearIndeces[12][segSize];

  // Declaration of common anodes on LED Bar
  int comAnodes = 16;
  int comAanodeArr[comAnodes];

  int color[3][3]; //Declaration of selection array
};

#endif
