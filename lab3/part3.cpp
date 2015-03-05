/*
*   Lab 3.1 Part 3
*   Team :  Shanjit Singh Jajmann - sjajmann
*           Vaibhav N Bhat - vaibhavn
*   Description : 
*       The acclerometer is read and depending on the inclination the following occurs:
*       Up : LED1 glows
*       Down : LEDs 3 and 4 glow
*       Left : LEDs 1,3 and 4 glow
*       Right : LED 4 glows
*       The orientation is read continuously using the getOrientation api
*/

#include "mbed.h"
#include "MMA7660.h"

MMA7660 MMA(p28, p27);  // IMU object is constructed
Serial pc(USBTX, USBRX);

//Initialize LEDs
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);


int main() {  
    if (MMA.testConnection()){  // Blink LEDs if IMU is initialized
        led1 = 1;
        led2 = 1;
        led3 = 1;
        led4 = 1;  
        wait(0.2);
        led1 = 0;
        led2 = 0;
        led3 = 0;
        led4 = 0;  

    }
    while(1) {
        int o = MMA.getOrientation();        
        pc.printf("%d ",o);
        switch(o)       // Determine based on the orientaion
        {
            case 0:
                pc.printf("Up");
                led1 = 1;
                led2 = 0;
                led3 = 0;
                led4 = 0;  
                break;    
            case 1:
                pc.printf("Down");
                led1 = 0;
                led2 = 0;
                led3 = 1;
                led4 = 1;  
                break;    
            case 2:
                pc.printf("Right");
                led1 = 1;
                led2 = 1;
                led3 = 1;
                led4 = 0;  
                break;    
            case 3:
                pc.printf("Left");
                led1 = 0;
                led2 = 0;
                led3 = 0;
                led4 = 1;  
                break;    
            default:
                pc.printf("flat");
                led1 = 0;
                led2 = 0;
                led3 = 0;
                led4 = 0;                                
                break;    
        }
    }

}
