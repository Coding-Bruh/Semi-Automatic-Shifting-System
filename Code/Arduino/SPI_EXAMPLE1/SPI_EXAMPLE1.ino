
#include <SPI.h>

char tmp[2];
uint8_t buf [4];
volatile byte pos;
volatile boolean process_it;
  int voltage;

void setup (void)
{
  Serial.begin (115200);   // debugging
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  
  // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPCR |= bit(SPIE);

}  // end of setup

void printHex(int num, int precision) {
     char tmp[16];
     char format[128];

    sprintf(format, "0x%%.%dX", precision);

    sprintf(tmp, format, num);
     Serial.println(tmp);
}


 //SPI interrupt routine
ISR (SPI_STC_vect)
{
  if (pos < (sizeof (buf)/* - 1*/))
    {
        buf [pos++] = SPDR;
    }
  // example: newline means time to process buffer
 
//  if (SPDR == 0x07)
//  {
//      tmp[0] = SPDR;
//  }
//  else if (SPDR == 0x1C)
//  {
//    tmp[1] = SPDR;
//    if (tmp[0] == 0x07)
//    {
//      process_it = true;
//    }
//  }

}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{

//
//  if (1)
//    {
    
    voltage = ((short)buf[1]*256)+buf[3];
    if(voltage > 32767)
       voltage = voltage - 65536;
       Serial.print("Voltage: ");  
       Serial.println(voltage);

    pos = 0;
//    process_it = false;
//    }
    
}  // end of loop
