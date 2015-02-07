#include "mbed.h"

// define the initial pins config
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

int main() {
    while(1) {
        // switch on leds
        myled1 = 1;
        myled2 = 1;
        myled3 = 1;
        myled4 = 1;
        wait(1); // wait for one second
        // switch off leds
        myled1 = 0;
        myled2 = 0;
        myled3 = 0;
        myled4 = 0;
        wait(1); // wait for one second
    }
}
