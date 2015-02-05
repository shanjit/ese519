#include "mbed.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
DigitalIn col4(p5);
DigitalIn col3(p6);
DigitalIn col2(p7);
DigitalIn col1(p8);

int main() {
    while(1) {
    if(col1 == 1)
    {
        myled1 = 1;
        wait(0.2);
        myled1 = 0;
        wait(0.2);    
    }
    if(col2 == 1)
    {
        myled2 = 1;
        wait(0.2);
        myled2 = 0;
        wait(0.2);    
    }
    if(col3 == 1)
    {
        myled3 = 1;
        wait(0.2);
        myled3 = 0;
        wait(0.2);    
    }
    if(col4 == 1)
    {
        myled4 = 1;
        wait(0.2);
        myled4 = 0;
        wait(0.2);    
    }
    
    }
}
