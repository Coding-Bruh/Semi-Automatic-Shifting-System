#include <SPI.h>


/*
For RGB pins LOW = ON, HIGH = OFF
each segment represents 210 RPM incriments

*/


                          //GLOBAL vars and pins
                                                 //7SEG pin setup
#define sA 40  // 7                                       _ 5
#define sB 42  // 6                                     0|__| 6
#define sC 32  // 4                                     4| 1|2
#define sD 34  // 2                                       --3   .7
#define sE 36  // 1
#define sF 38  // 9
#define sG 44  // 10
#define sDP 30  // 5
                          //Anodes  

#define aG1 A0
#define aG2 A1
#define aG3 A2
#define aB1 A3
#define aB2 A5
#define aB3 A4
#define aR1 A6
#define aR2 A7
#define aR3 A8
                        //Cathode Pin setup                                         1   -   2   -  3
int C1 = 46;                                          //C1 - 46            RPM - ..210 - ..420 - ..630
int C2 = 48;                                          //C2 - 48            RPM - ..840 - .1050 - .1260
int C3 = 49;                                          //C3 - 49            RPM - .1470 - .1680 - .1890
int C4 = 47;                                          //C4 - 47            RPM - .2100 - .2310 - .2520
int C5 = 45;                                          //C5 - 45            RPM - .2730 - .2940 - .3150
int C6 = 43;                                          //C6 - 43            RPM - .3360 - .3570 - .3780
int C7 = 41;                                          //C7 - 41            RPM - .3990 - .4200 - .4410
int C8 = 39;                                          //C8 - 39            RPM - .4620 - .4830 - .5040
int C9 = 37;                                          //C9 - 23            RPM - .5250 - .5460 - .5670
int C10 = 33;                                         //C10- 25            RPM - .5880 - .6090 - .6300
int C11 = 35;                                         //C11- 27            RPM - .6510 - .6720 - .6930
int C12 = 31;                                         //C12- 29            RPM - .7140 - .7350 - .7560
int C13 = 28;                                         //C13- 31            RPM - .7770 - .7980 - .8190
int C14 = 26;                                         //C14- 33            RPM - .8400 - .8610 - .8820
int C15 = 24;                                         //C15- 35            RPM - .9030 - .9240 - .9450
int C16 = 22;                                         //C16- 37            RPM - .9660 - .9870 - 10080

                          //Arrays for clean Setup intilization code
int cathode[] = {C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16};
int seg[]={sA,sB,sC,sD,sE,sF,sG,sDP};
int red[] = {aR1,aR2,aR3};
int blue[] = {aB1,aB2,aB3};
int green[] = {aG1,aG2,aG3};
int cLen = 16;
int sLen = 8;
int aLen = 3;
                                        //RPM Simulation variable PIN
int RPM_PIN = 7;
int RPM = 0;
int RPM_IDLE = 0;                     //actual car values will be 600
int RPM_REDLINE=4700;                  //actual car values will be 10000    for testing with volatge input we will use 1400

/////////////////////////////////////////SPI Define start
volatile byte pos;                      //used for SPI buffer position, its set to global so it can be reset after populated to RPM array
uint8_t buf[4];

                                       //**********************SPI interrupt routine************************************
ISR (SPI_STC_vect)
{
  if (pos < (sizeof (buf)))            //Gets SPI data value (RPM) and places in array (buf)
    {
        buf [pos++] = SPDR;
    }
}                                      // end of interrupt routine SPI_STC_vect

int raw2int()
{
  int data_packet = ((short)buf[1]<<8)+buf[3];
  if(data_packet > 32767)
    data_packet = data_packet - 65536;
    pos = 0;                                                                    //Global var to reset buffer count in interupt
    Serial.print("Converted Data from raw SPI: ");                              //Debugging serial output for raw data conversion
    Serial.println(data_packet);
    return(data_packet);
}
//////////////////////////////////////SPI define end



                                       //************************SETUP LOOP************************************
void setup() 
{   
       // 7 Segment pinout control

  for(int sPin = 0; sPin < sLen; sPin++)
      {
        pinMode(seg[sPin],OUTPUT);
      }
  
           //RGB Anode control 
  
  for (int aPin = 0; aPin < aLen; aPin++) 
      {
        pinMode(red[aPin], OUTPUT);
        pinMode(green[aPin], OUTPUT);
        pinMode(blue[aPin], OUTPUT);
      }

              //Cathode Control
                                      
    for (int cPin = 0; cPin < cLen; cPin++) 
      {
        pinMode(cathode[cPin], OUTPUT);
      }
  
  //DEBUGGING Stuff
  //pinMode(RPM_PIN,INPUT);     //Potentiameter input
  Serial.begin(115200);       //  setup serial 
               
  initialize();               //not needed anymore but looks cool
                    
                    
                    
                    //SPI Setup
  SPI.beginTransaction(SPISettings(800000, MSBFIRST, SPI_MODE0));
  SPCR |= bit (SPE);     // turn on SPI in slave mode
  pinMode(MISO, OUTPUT); // have to send on master in, *slave out*
  pos = 0;   // buffer empty to get ready for interrupts
  SPCR |= bit(SPIE); // now turn on interrupts
  
}





                                       //**********************main loop ***********************************************

void loop() 
    {

          //RPM = analogRead(RPM_PIN);      //Use only for POT Demo mode SPI disabled
          //RPM = RPM*10;

          RPM = raw2int();           //Use when SPI enabled
          int ledLevel = map(RPM,RPM_IDLE,RPM_REDLINE, 0, cLen);
          
          resetLED();
 
          if(RPM <=2500)
            greenLED(LOW);
          if(RPM >= 2501 && RPM <=4000)
            blueLED(LOW);
          if(RPM >= 4001)
            redLED(LOW);
                                                                               

  // loop over the LED array:
  for (int thisLed = 0; thisLed < cLen; thisLed++) 
    {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
      if (thisLed < ledLevel) 
        {
          digitalWrite(cathode[thisLed],HIGH);
          printSeg(ledLevel);
        }
        // turn off all pins higher than the ledLevel:
      else 
        {
          digitalWrite(cathode[thisLed], LOW);
        }
  }
}
////////////////////////////////////////////////////////////////////////////////////


//**************************LED FUNCTIONS****************************************//


void redLED(bool state)
{
    for(int a = 0; a < aLen; a++)
      {
        digitalWrite(red[a],state);
      }
}

void greenLED(bool state)
{
   
    for(int a = 0; a < aLen; a++)
      {
        digitalWrite(green[a],state);
      }
}

void blueLED(bool state)
{
    
    for(int a = 0; a < aLen; a++)
      {
        digitalWrite(blue[a],state);
      }
}

void flashLED()
{
  for(int led = 0; led < cLen; led++)
  {
    digitalWrite(cathode[led],HIGH);
  }
    delay(100);
  for(int led = 0; led < cLen; led++)
  {
    digitalWrite(cathode[led],LOW);
  }
 
}



//////////////////////////////////////////////////////////////INITIALIZE
void initialize()
{
    for(int cath = 0; cath < cLen; cath++)
      {
          digitalWrite(cathode[cath],HIGH);
          printSeg(cath);
          delay(100);
          redLED(LOW);
          blueLED(LOW);
          greenLED(LOW);
      }
    

  
    for(int cath = 0; cath < cLen; cath++)
      {
          digitalWrite(cathode[cath],LOW);
          delay(10);
       }


    for(int segSection = 0; segSection < sLen; segSection++)
      {
          digitalWrite(seg[segSection],HIGH);
           delay(100);
      }
    resetLED();
}


void resetLED()
{
   redLED(HIGH);
   blueLED(HIGH);
   greenLED(HIGH);
}


int segment[13][8]={ {0,1,0,0,0,0,0,1},    /* Displays zero          */
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
                     {1,1,1,1,1,1,1,0},
                     {1,1,1,1,1,1,1,1}}; /* Displays decimal point */

void printSeg(int num)
{
if(num > 12)      //sets any number given to function outside of its scope to turn off the 7seg display
  num = 12;
    
  for(int led =0; led < 8; led++)
{
  digitalWrite(seg[led],segment[num][led]);
}
}

