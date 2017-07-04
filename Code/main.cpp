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
/*-----------------------------------*/


/*SPI--------------------------------*/
#define MOSI                    p5
#define MISO                    p6
#define SCLK                    p7
#define CS_PIN                  p8
#define SPI_Frequency           800000
#define Bit_Rate                16
#define Mode                    0
SPI spi(MOSI,MISO,SCLK); //mosi, miso, sclk
DigitalOut chipSelect(CS_PIN);

/* Transmitting Message -------------*/
//const int  CONTROL_LED2 = 218099784;
//int             ledStatus;
/*-----------------------------------*/

//int count = 0;

int main()
{
    pc.printf("new new code running program\n");

    can.frequency(CAN_Frequency);

    spi.frequency(SPI_Frequency);
    spi.format(Bit_Rate, Mode);

    while(1) {
        //can.monitor(1);
        if(can.read(msg)) {
            //pc.printf("%d\n", msg);
            if(msg.id == 0x0cfff248) {
                //pc.printf("Message received ID: %x\n",  (msg.id));
                pc.printf("Message received data: %x\n", (msg.data[0]));
                pc.printf("Message received data: %x\n", (msg.data[1]));
                //pc.printf("Message received data: %x\n", (msg.data[2]));
                //pc.printf("Message received data: %x\n", (msg.data[3]));
                //pc.printf("Message received data: %x\n", (msg.data[4]));
                //pc.printf("Message received data: %x\n", (msg.data[5]));
                //pc.printf("Message received data: %x\n", (msg.data[6]));
                //pc.printf("Message received data: %x\n", (msg.data[7]));

                chipSelect = 0;
                //short voltage;

                char lByte = msg.data[0];
                char hByte = msg.data[1];
                //char data[]= {hByte,lByte};
                //voltage = ((short)hByte<<8)|lByte;


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
                spi
                spi.write(hByte);
                spi.write(lByte);
                //wait_ms(100);
                //spi.write(0x07);
                //spi.write(0x1C);
                //spi.write(0x0A);
                //spi.write((char)voltage);
                //spi.write('\n');
                //pc.printf("Sent: %d\n", voltage);
                chipSelect = 1;
            }
        }


        //int whoami = spi.write(0x00);
        //pc.printf("WHOAMI register = 0x%X\n", whoami);

    }

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
}
