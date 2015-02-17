#include "mbed.h"
#include "PwmOut.h"

PwmOut pin23(p23);

int main() {
    pin23.period_us(2272); // Set period 2.2ms ~ 440Hz
    pin23 = 0.5;
       
    while(1) {
/*     for(float d = 0.0f; d<=1.0 ; d+=0.1)
     {
         myled = d;
         wait(0.1);
     } */ 
    }
}
