
#include <SPI.h>


byte dataIN;
byte HByte;
byte LByte;
int RPM;
byte ff=0xFF;


void setup (void)
{
  Serial.begin (9600);   // debugging
  Serial.println("Debugging Start");
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
 
  SPCR |= bit (SPE);

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
} 
void loop (void)
{


dataIN = SPDR;
HByte = 0x000B;//dataIN>>4; 
LByte = 0x000A;//dataIN<<4;
//LByte = LByte>>4;
RPM = (int)HByte*256+(int)LByte;
if (RPM>32767)
  RPM=RPM-65536;
  
//Serial.println(LByte);
//Serial.println(HByte);
Serial.println(RPM);
//Serial.println((HByte<<4)+LByte);
}
