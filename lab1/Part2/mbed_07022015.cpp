#include "mbed.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

DigitalOut pin1(p10);
DigitalOut pin2(p11);

DigitalIn col4(p5);
InterruptIn col3(p6);
InterruptIn col2(p7);
DigitalIn col1(p8);

void light0(){
        myled1 = 1;
        wait(0.2);
        myled1 = 0;
        wait(0.2);    
    }
    
void light1(){
        myled2 = 1;
        wait(0.2);
        myled2 = 0;
        wait(0.2);    
}

int main() {
    
    pin1 = 1 ;
    pin2 = 0 ;
    col3.rise(&light0);
    
    pin1 = 0 ;
    pin2 = 1 ;
    col2.rise(&light1);
    while(1) {
    }
}
