/*
ese519-lab2-part1
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Generating a 440 Hz signal : Shown to the TA already. 

*/

#include "mbed.h"
#include "PwmOut.h"

// The oscilloscope was connected to this pin
PwmOut pin23(p23);

int main() {
    // Set period 2.2ms ~ 440Hz
    pin23.period_us(2272); 
    pin23 = 0.5;
       
    while(1) {

    }
}