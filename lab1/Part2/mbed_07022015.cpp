/*
ese519-lab1-part2
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Idea : Using the keypad, interrupt when the key is pressed. 

*/

#include "mbed.h"


// Connections on the mbed
// Mbed - Keypad 
// p5 - 7
// p6 - 6 
// p7 - 5
// p8 - 3
// p10 - 8
// p11 - 4


//define the leds 
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

//define the pins for # and 2 
DigitalOut pin1(p10);
DigitalOut pin2(p11);


// keypad association
DigitalIn col4(p5);
InterruptIn col3(p6);
InterruptIn col2(p7);
DigitalIn col1(p8);

// ISR when button pressed - lights up led1
void light0(){
        myled1 = 1;
        wait(0.2);
        myled1 = 0;
        wait(0.2);    
    }

// ISR when button pressed - lights up led2    
void light1(){
        myled2 = 1;
        wait(0.2);
        myled2 = 0;
        wait(0.2);    
}

int main() {
    
    pin1 = 1 ;
    pin2 = 1 ;
    
    // associate interrupts with functions light1 and light0
    col3.rise(&light1);
    col2.rise(&light0);
    while(1) {
    }
}
