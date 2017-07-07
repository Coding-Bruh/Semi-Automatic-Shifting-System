#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H


class LED_DISPLAY
{
public:
  LED_DISPLAY();

  // methods for 7 segment display
  void displayGear(int num);
  void displayNeutral();
  void displayDecimalPoint();
  void segOff();
private:
  int RPM_PIN = 0;

  int segArr[8] = {40, 42, 32, 34, 36, 38, 44, 30};
  //                A,  B,  C,  D,  E,  F,  G, DP

  //                      0,1,2,3,4,5,6,7    <= indeces of 'segCode'
  int segCode[13][8] = { {0,1,0,0,0,0,0,1},    /* Displays zero          */
                         {1,1,0,1,1,1,0,1},    /* Displays one           */
                         {1,0,1,0,0,0,0,1},    /* Displays two           */
                         {1,0,0,0,1,0,0,1},    /* Displays three         */
                         {0,0,0,1,1,1,0,1},    /* Displays four          */
                         {0,0,0,0,1,0,1,1},    /* Displays five          */
                         {0,0,0,0,0,0,1,1},    /* Displays six           */
                         {0,1,0,1,1,0,0,1},    /* Displays seven         */
                         {0,0,0,0,0,0,0,1},    /* Displays eight         */
                         {0,0,0,1,1,0,0,1},    /* Displays nine          */
                         {1,0,0,1,0,1,1,1},    /* Displays neutral       */
                         {1,1,1,1,1,1,1,0},     /* Displays decimal point */
                         {1,1,1,1,1,1,1,1}  }; /* Turns display off      */

  // Declaration of common anodes on LED Bar
  int comAnodeArr[16] = {46,48,49,47,45,43,41,39,37, 33, 35, 31, 28, 26, 24, 22};
  //                     C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16

  // Declaration of selection array
  int color[3][3] = { { 2,3,4},      /* Red1, Red2, Red3       */
                      {10,9,8},      /* Green1, Green2, Green3 */
                      { 7,6,5} };    /* Blue1, Blue2, Blue3    */ 
};

#endif
