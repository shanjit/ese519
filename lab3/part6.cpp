#include "mbed.h"
/*
*   Lab 3.1 Part 6
*   Team :  Shanjit Singh Jajmann - sjajmann
*           Vaibhav N Bhat - vaibhavn
*   Description : 
*   The voltage across the LDR is proportional to intensity of light
*   The voltage is sampled and the pattern High - Low - High causes the 
*   servo motor to turn on. After the initial high a 2 second time out exists
*   to switch off the light after which the light must be turned on within 10 seconds
*   of the light going high initially
*/

Serial pc(USBTX, USBRX);
PwmOut servo(p21);
AnalogIn ldr(p20);
Timeout flipper;
int flag1 = 0;  
int flag2 = 0;
Timeout flipper2;


Ticker tic;
 int val = 0;
 
// Function to turn on the servo if flag 1 and 2 are high 
// and the ldr has light shining on it
void makeHigh()
{
    if(flag1 && flag2 && val>55000)
    {
       wait(0.1);
       val = ldr.read_u16();
        if(flag1 && flag2 && val>55000)   
       servo = 0.9;    
       }
}

// Function triggered by timeout which resets the flags
void tim_out_flags()
{
    flag1=0;
    flag2=0;
    pc.printf("\n\nreset\n\n");
    
}

// Function to handle events after 2 seconds of 
// light shining for the first time
void tim_out() {
    pc.printf("attaching timeout");
    flipper2.attach(&tim_out_flags, 8.0);  
    
    if(val<23000){    
        flag2 = 1;    
        tic.attach(&makeHigh,0.25); // Check every 0.25s if light is shining the 2nd time
    }
}

int main()
{
    while(1) {
        val = ldr.read_u16();
        pc.printf(" %d%d %d",flag1, flag2, val);
        
        
        if(val > 55000)
        {
            wait(0.1);
            if( (ldr.read_u16()) > 55000)
            {
            flag1 = 1;            
            flipper.attach(&tim_out, 2.0);  // If light is shining for the 1st time,
                                            // wait for 2s before checking for light's
                                            // absence
            }
        }
                
    }
}
