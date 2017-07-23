#include "mbed.h"
#include <string>
CAN can(p30, p29);

using namespace std;

DigitalOut led1(LED1);
DigitalOut led2(LED2);

/* Receiving Message ----------------*/
#define CAN_Frequency 500000
Serial pc(USBTX, USBRX); // tx, rx
CANMessage msg;
int address = 0x0cfff248;
/*-----------------------------------*/


/*SPI--------------------------------*/
#define MOSI_1 				p5
#define MISO_1 				p6
#define SCLK_1 				p7
#define CS_PIN_1   			p8
#define CS_PIN_2   			p9

#define SPI_Frequency 800000
#define Bit_Rate 			8
#define Mode 					0

SPI spi1(MOSI_1,MISO_1,SCLK_1); //mosi, miso, sclk
I2C i2c(p28, p27);



DigitalOut chipSelect1(CS_PIN_1);
DigitalOut chipSelect2(CS_PIN_2);



/* Transmitting Message -------------*/
//const int  CONTROL_LED2 = 218099784;
//int             ledStatus;
/*-----------------------------------*/

int isrFlag = 0;
int isrFlag2 = 1;
unsigned char gear, prevGear;
char lByte, hByte;
 
int main()
{
	pc.printf("new code running program\n");
	can.frequency(CAN_Frequency);
	
	spi1.frequency(SPI_Frequency);
	spi1.format(Bit_Rate, Mode);
	
	int addr = (0x7<<1 | 0x01); // send address + !write = 1
	char data;
	i2c.frequency(500000);
	
  while(1) 
  {
    if((can.read(msg)) &&(msg.id == address)) 
    {
			i2c.start();
			i2c.write(addr);
			gear = i2c.read(0);
			i2c.stop();
			char lByte = msg.data[0];
			char hByte = msg.data[1];
			short voltage;
			//char data[]= {hByte,lByte};
			voltage = ((short)hByte<<8)|lByte;
			//pc.printf("hbyte: %x, lbyte: %x \n", hByte, lByte);
			pc.printf("voltage: %d \n", voltage);
			chipSelect1 = 0;
			chipSelect2 = 0;
					spi1.write(hByte);
					spi1.write(lByte);
					spi1.write(gear);
			chipSelect1 = 1;
			chipSelect2 = 1;
			pc.printf("gear: %x \n", gear);
			
    }
	}   
}

/*CAN data buffer print statements*/
/*----------------------------------------------------------------------------*/
//pc.printf("Message received ID: %x\n",  (msg.id));
//pc.printf("Message received data: %x\n", (msg.data[0]));
//pc.printf("Message received data: %x\n", (msg.data[1]));
//pc.printf("Message received data: %x\n", (msg.data[2]));
//pc.printf("Message received data: %x\n", (msg.data[3]));
//pc.printf("Message received data: %x\n", (msg.data[4]));
//pc.printf("Message received data: %x\n", (msg.data[5]));
//pc.printf("Message received data: %x\n", (msg.data[6]));
//pc.printf("Message received data: %x\n", (msg.data[7]));




/*Write with SPI [obsolete]*/
/*----------------------------------------------------------------------------*/
//wait_ms(500);
//pc.printf("high: %x, low: %x, combined: %x\n", hByte, lByte, voltage);
//pc.printf("%x\n",voltage);
//int a = msg.data[0];
//char c;
//char voltData[] = {hByte,lByte,0x07,0x1C}; 
/*for(const char *p = voltData; (c = *p); p++)
{
	spi.write(c);
	pc.printf("Sent: %x\n", c);
	
}*/


//wait_ms(100);
//spi.write(0x07);
//spi.write(0x1C);
//spi.write(0x0A);
//spi.write((char)voltage);
//spi.write('\n');
//pc.printf("Sent: %d\n", voltage);

//int whoami = spi.write(0x00);
//pc.printf("WHOAMI register = 0x%X\n", whoami);


//can.monitor(1);


/*CAN writing a CAN Extended message*/
/*----------------------------------------------------------------------------*/
/*while (1)
{
    int count = 0;

    msg.format = CANExtended;
    msg.id = 0x71;
    msg.len = 8;
    msg.data[1] = 0x42;
    while (count <= 6)
    {
        can.write(msg);
        wait_ms(1);
        count++;
    }
    

    msg.format = CANExtended;
    msg.id = 0x81;
    msg.len = 8;
    msg.data[1] = 0x46;

    while(count < 10)
    {
        can.write(msg);
        wait_ms(1);
        count++;
    }
    //can.reset();
} */  