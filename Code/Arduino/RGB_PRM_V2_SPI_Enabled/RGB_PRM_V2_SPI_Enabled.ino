#include <SPI.h>


/*
For RGB pins LOW = ON, HIGH = OFF
each segment represents 210 RPM incriments

LED PIN - NAME - MCU PIN                1   -   2   -  3
      1 -  C1  - 46            RPM - ..210 - ..420 - ..630
     25 -  C2  - 48            RPM - ..840 - .1050 - .1260
      3 -  C3  - 49            RPM - .1470 - .1680 - .1890
      4 -  C4  - 47            RPM - .2100 - .2310 - .2520
     23 -  C5  - 45            RPM - .2730 - .2940 - .3150
      5 -  C6  - 43            RPM - .3360 - .3570 - .3780
     22 -  C7  - 41            RPM - .3990 - .4200 - .4410
     21 -  C8  - 39            RPM - .4620 - .4830 - .5040
     20 -  C9  - 37            RPM - .5250 - .5460 - .5670
      8 -  C10 - 33            RPM - .5880 - .6090 - .6300
     19 -  C11 - 35            RPM - .6510 - .6720 - .6930
     18 -  C12 - 31            RPM - .7140 - .7350 - .7560
     10 -  C13 - 28            RPM - .7770 - .7980 - .8190
     11 -  C14 - 26            RPM - .8400 - .8610 - .8820
     15 -  C15 - 24            RPM - .9030 - .9240 - .9450
     12 -  C16 - 22            RPM - .9660 - .9870 - 10080

*/


 //*********************** START of Global vars and pins and functions **********************************//
                          
              //7SEG pin setup  LED PIN - NAME - MCU PIN
#define sA 40                     //  7 -  A   - 40                                  __ 5
#define sB 42                     //  6 -  B   - 42                             dsca   0|__| 6
#define sC 32                     //  4 -  C   - 32                                4| 1|2
#define sD 34                     //  2 -  D   - 34                                  --3   .7
#define sE 36                     //  1 -  E   - 36
#define sF 38                     //  9 -  F   - 38
#define sG 44                     // 10 -  G   - 44
#define sDP 30                    //  5 -  DP  - 30
                                  //3,8 -  VCC - 5V out
                                  
              //Anodes          LED PIN - NAME - MCU PIN
#define aG1 A0                    // 24 -  G1  - A0 
#define aG2 A1                    //  6 -  G2  - A1
#define aG3 A2                    // 14 -  G3  - A2
#define aB1 A3                    //  7 -  B1  - A3
#define aB2 A5                    // 16 -  B2  - A5
#define aB3 A4                    //  2 -  B3  - A4
#define aR1 A6                    //  9 -  R1  - A6
#define aR2 A7                    // 17 -  R2  - A7
#define aR3 A8                    // 13 -  R3  - A8

              //Cathode         LED PIN - NAME - MCU PIN       
#define C1 46                     //  1 -  C1  - 46            
#define C2 48                     // 25 -  C2  - 48            
#define C3 49                     //  3 -  C3  - 49            
#define C4 47                     //  4 -  C4  - 47            
#define C5 45                     // 23 -  C5  - 45            
#define C6 43                     //  5 -  C6  - 43            
#define C7 41                     // 22 -  C7  - 41            
#define C8 39                     // 21 -  C8  - 39            
#define C9 37                     // 20 -  C9  - 37            
#define C10 33                    //  8 -  C10 - 33            
#define C11 35                    // 19 -  C11 - 35            
#define C12 31                    // 18 -  C12 - 31            
#define C13 28                    // 10 -  C13 - 28            
#define C14 26                    // 11 -  C14 - 26            
#define C15 24                    // 15 -  C15 - 24            
#define C16 22                    // 12 -  C16 - 22            

                          //Arrays for clean Setup intilization code
int cathode[] = {C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16};
int seg[]={sA,sB,sC,sD,sE,sF,sG,sDP};
int red[] = {aR1,aR2,aR3};
int blue[] = {aB1,aB2,aB3};
int green[] = {aG1,aG2,aG3};
int cLen = 16;
int sLen = 8;
int aLen = 3;
                                                                    
//int RPM_PIN = 7;                                                  //RPM Simulation variable PINOUT not used when running SPI
int RPM = 0;
int RPM_IDLE = 0;                                                   //actual car values will be 600
int RPM_REDLINE=4800;                                               //actual car values will be 10000    for testing with volatge input we will use 1400
#define BLINK_HALF_PERIOD 100 
#define CONVERGE_LED                                                // comment this line out to be boring
/////////////////////////////////////////////////////               START of SPI Define start

volatile byte pos;                                                  //used for SPI buffer position, its set to global so it can be reset after populated to RPM array
uint8_t buf[2];
uint8_t isr_flag = 0;
int data_packet;
                                                                    //Start of Interrupt routine (ISR)
ISR (SPI_STC_vect)
{
  isr_flag = 0;
  if (pos < (sizeof (buf)))                                         //Gets SPI data value (RPM) and places in array (buf)
    {
        buf [pos++] = SPDR;                                         //Populates buffer array with bytes at pos less then buff size
    }
    
}                                                                   // end of interrupt routine SPI_STC_vect

int raw2int()
{
  if(isr_flag == 0) {
  isr_flag = 1;
  data_packet = buf[0];
  data_packet <<= 8;
  data_packet |= buf[1];
  //data_packet = ((short)buf[0]<<8)+buf[1];
//  if(data_packet > 32767)
//    data_packet = data_packet - 65536;
                                                            //Global pos variable set to 0 to reset buffer count for next interrupt buf population
    Serial.print("Converted Data from raw SPI: ");                  //Debugging serial output for raw data conversion
    Serial.println(data_packet);
    Serial.print("buf[0]: ");
    printHex(buf[0],2);
    Serial.print("buf[1]: ");
    printHex(buf[1],2);

    pos = 0;
    return(data_packet);                                            //Returns signed integer value after conversion via PE3's datasheet for CAN messages
  }
  else
  return data_packet;
}
/*
 * Fix for error posibility: create pesudo ACK fedback through a GPIO pin OR shorten up the BYTES sent and be strict about BYTE matching
 * maybe use a loop check to verify bytes being sent are never whitespace HEX value (reminder set serial to output all HEX values ONLY including those for 
 * white space and NEWLINE commands) 
 */

////////////////////////////////////////////////////////            END of SPI define


///////////////////////////////////////////////////////             START of LED functions
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

void flashLED()                          // Currently does not funtion as of 7/4
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

void initialize()                        // No longer needed but kept in for asthetics
{
    int cath;
    int segSection;
    int segMAP = map(cath,0,sLen,0,cLen);
     
    for(cath = 0; cath < cLen; cath++)
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
          //digitalWrite(seg[segMAP],HIGH);
          delay(100);
       }


    for(segSection = 0; segSection < sLen; segSection++)
      {
          digitalWrite(seg[segSection],HIGH);
           delay(100);
      }
    resetLED();
}


void resetLED()                   //Turns off all anodes on LED Bar which clears the display
{                                 //regardless of what section on the cathodes are turned on
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
if(num > 12)                               //sets any number given to function outside 
  num = 12;                                //of its scope to turn off the 7seg display
    
  for(int led =0; led < 8; led++)
  {
    digitalWrite(seg[led],segment[num][led]);
  }
}
///////////////////////////////////////////////////////             END of LED functions

void printHex(int num, int precision) {
     char tmp[16];
     char format[128];

     sprintf(format, "0x%%.%dX", precision);

     sprintf(tmp, format, num);
     Serial.println(tmp);
}

//*********************** END of Global vars and pins and functions **********************************//



//************************ Start of Setup ************************************//
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
                    
                    
                    
/////////////////////////////////////////////////////////////////               START of SPI Setup
SPI.beginTransaction(SPISettings(800000, MSBFIRST, SPI_MODE0));
SPCR |= bit (SPE);                                                            // turn on SPI in slave mode
pinMode(MISO, OUTPUT);                                                        // have to send on master in, *slave out*
pos = 0;                                                                      // buffer empty to get ready for interrupts
SPCR |= bit(SPIE);                                                            // now turn on interrupts
/////////////////////////////////////////////////////////////////               END of SPI Setup  
  
}

//************************ END of Setup ************************************//


//************************ Main loop **************************************//
void loop() 
    {

          //RPM = analogRead(RPM_PIN);      //Use only for POT Demo mode SPI disabled
          //RPM = RPM*10;

          RPM = raw2int();           //Use when SPI enabled
          #ifdef CONVERGE_LED
            int ledLevel = map(RPM,RPM_IDLE,RPM_REDLINE, 0, cLen / 2);
          #else
            int ledLevel = map(RPM,RPM_IDLE,RPM_REDLINE, 0, cLen);
          #endif
          
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
    #ifdef CONVERGE_LED
      if ((thisLed < ledLevel || cLen - thisLed <= ledLevel) && (((millis() / BLINK_HALF_PERIOD) % 2) || ledLevel < cLen / 2))
    #else
      if (thisLed < ledLevel && (((millis() / 100) % 2) || ledLevel < cLen))
    #endif
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
//**************************END of Main Loop*************************************//


