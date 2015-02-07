#include "mbed.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
DigitalOut row1(p9);
DigitalOut row2(p10);
DigitalOut row3(p11);
DigitalOut row4(p12);

DigitalIn col4(p5);
DigitalIn col3(p6);
DigitalIn col2(p7);
DigitalIn col1(p8);

int main() {

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

    row1 = 0;
    row2 = 0;
    row3 = 0;
    row4 = 0;

    while(1) {

        // switch on row 1 and check all columns sequentially
        row2 = 1;
        row1 = 0;
        row3 = 0;
        row4 = 0;
        
        if(col2 == 1)
        {
        myled1 = 1;
        wait(0.2);
        myled1 = 0;
        wait(0.2);    
        }

        // switch on row 1 and check all columns sequentially
        row1 = 0;
        row2 = 0;
        row3 = 1;
        row4 = 0;

        if(col3 == 1)
        {
        myled2 = 1;
        wait(0.2);
        myled2 = 0;
        wait(0.2);    
        }


    }
}
