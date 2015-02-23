/*
ese519-lab2-part0
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Connecting the buffer circuit and driving a speaker

*/

#include "mbed.h"
#include "PwmOut.h"

// The buffer circuit was connected to this pin and a frequency of 440 Hz was output on the speaker.
PwmOut pin23(p23);

int main() {
    // Set period 2.2ms ~ 440Hz
    pin23.period_us(2272); 
    pin23 = 0.5;
    
    // Infinite while loop   
    while(1) {

    }
}