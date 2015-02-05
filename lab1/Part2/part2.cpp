#include "mbed.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
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
    col3.rise(&light0);
    col2.rise(&light1);
    while(1) {
    }
}
