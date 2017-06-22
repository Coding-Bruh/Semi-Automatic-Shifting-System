#include "mbed.h"
#include <string>
CAN can(p30, p29);

using namespace std;

DigitalOut led1(LED1);
DigitalOut led2(LED2);

/* Receiving Message ----------------*/
Serial pc(USBTX, USBRX); // tx, rx
CANMessage msg;
/*-----------------------------------*/

/* Transmitting Message -------------*/
const int  CONTROL_LED2 = 218099784;
int             ledStatus;
/*-----------------------------------*/

//int count = 0;
 
int main()
{
    pc.printf("new code running program\n");
    
    can.frequency(500000);
    
    while(1) 
    {
        
        if(can.read(msg)) 
        {
						int m = can.read(msg);
						pc.printf("%d\n", m);
            if(msg.id == CONTROL_LED2)
            {
                pc.printf("Message received ID: %d\n", (msg.id));
                pc.printf("Message received ID: %x\n",  (msg.id));
                //int len = (msg.len) - '0';
                pc.printf("Message received length: %x\n", (msg.len));
                pc.printf("Message received data: %d\n", (msg.data[0]));
                pc.printf("Message received data: %x\n", (msg.data[0]));
                led2 = !led2;
            }
        }
    }

    /*while(1)
    {
        ledStatus = led2;
        can.write(CANMessage(CONTROL_LED2, "Abhinav", sizeof(21)));
        wait_ms(3000);
        led2 = !led2;
    } */       
}
