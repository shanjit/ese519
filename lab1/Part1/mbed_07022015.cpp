/*
ese519-lab1-part1
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Idea : Using the keypad, poll the hash key / 2 for active high 

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

// define the leds - visual feedback
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

// define rows for the keypad
DigitalOut row1(p9);
DigitalOut row2(p10);
DigitalOut row3(p11);
DigitalOut row4(p12);

// define the column for the keypad
DigitalIn col4(p5);
DigitalIn col3(p6);
DigitalIn col2(p7);
DigitalIn col1(p8);

int main() {

    // startup pattern to verify that code did load onto the board
    myled1 = 1;
    myled2 = 1;
    myled3 = 1;
    myled4 = 1;
    
    wait(1);
    //switch everything off
    myled1 = 0;
    myled2 = 0;
    myled3 = 0;
    myled4 = 0;

    // initialize rows of the keypad
    row1 = 0;
    row2 = 0;
    row3 = 0;
    row4 = 0;

    while(1) {

// Connections on the mbed
// Mbed - Keypad 
// p5 - 7
// p6 - 6 
// p7 - 5
// p8 - 3
// p10 - 8
// p11 - 4
        // switch on row 1 and check column 
        row2 = 1;
        row1 = 0;
        row3 = 0;
        row4 = 0;
        
        if(col2 == 1) // col3 = p6
        {
        myled1 = 1;
        wait(0.2);
        myled1 = 0;
        wait(0.2);    
        }

        // switch on row 3 and check column 
        row1 = 0;
        row2 = 0;
        row3 = 1;
        row4 = 0;

        if(col3 == 1) // col2 - p7
        {
        myled2 = 1;
        wait(0.2);
        myled2 = 0;
        wait(0.2);    
        }


    }
}
