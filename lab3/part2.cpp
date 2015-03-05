
/*
*   Lab 3.1 Part 2
*   Team :  Shanjit Singh Jajmann - sjajmann
*           Vaibhav N Bhat - vaibhavn
*   Description : 
*       The joystick is read and depending on the position the following occurs:
*       Up : 1 random LED glows
*       Down : 2 random LEDs glows
*       Left : 3 random LEDs glows
*       Right : All 4 LEDs glow
*       The random numbers generate for Down and Left are made sure that they 
*       are not equal. The random numbers generated are used for glowing the 
*       corresponding LED
*/


#include "mbed.h"

BusIn joy(p15,p12,p13,p16);
DigitalIn fire(p14);
AnalogIn ain(p17);
Serial pc(USBTX, USBRX);

BusOut leds(LED1,LED2,LED3,LED4);

int main()
{

    while(1) {
//        pc.printf("%d ",rand());                
        if (fire) {
            leds=15;
        } else {
        if(joy == 0){
//        pc.printf("zero");    
        leds = 0;
        }
        if(joy == 1){       // Up is pressed
            int val1 = rand() % 4 ; // Generate a random number bw 0 to 4            
            pc.printf("%d ",val1);
            leds = (1 << (val1));   // One led is lighted up
        }
        else if(joy == 2){          // Down is pressed
            int val1 = rand() % 4 ; // Generate 2 random numbers bw 0 to 4
            int val2 = rand() % 4;
            while(val1 == val2)     // Making sure the same leds don't get selected
            {
                val2 = rand() % 4;
            }
            
            pc.printf("%d %d ",val1, val2);
            leds = (1 << (val1));   
            leds = leds | (1 << val2);  // Write to the leds - 2 are made high
            
        }
        else if(joy == 4){

            int val1 = rand() % 4 ;
            int val2 = rand() % 4;
            while(val1 == val2)
            {
                val2 = rand() % 4;
            }
            int val3 = rand() % 4;
            while(val3 == val2 || val3 == val1)
            {
                val3 = rand() % 4;
            }
            
            pc.printf("%d %d %d",val1, val2, val3);     
            leds = (1 << (val1));       // 3 random unequal nos are generated
            leds = leds | (1 << val2);  // The nos correspond to the led index
            leds = leds | (1 << val3);            
        }
        else if(joy == 8){
//            pc.printf("rt");
            leds = 15;          // Right is pressed ; All leds glow
        }
        
        }
        wait(0.1);
    }
}
