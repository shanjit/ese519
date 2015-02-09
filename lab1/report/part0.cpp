/*
ese519-lab1-part0
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Idea : Vary the frequency of the led blink by reading randomness from the universe using onboard ADC

*/

#include "mbed.h"

// define leds 
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

// analog pins to read randomness from the universe
AnalogIn ain(p19);
int a[4];

// serial interface - for debug
Serial pc(USBTX, USBRX);

// ticker timer for 18 second window
Ticker ticker_period_18;

// read the adc and assign digits to array 'a'
void get_adc()
{
    // This gets called every 18 seconds and updates the 'a' array
    int temp;
    temp = ain.read_u16();
    a[0] = temp%10;
    temp = temp/10;
    a[1] = temp%10;
    temp = temp/10;
    a[2] = temp%10;
    temp = temp/10;
    a[3] = temp%10;
    
    // for debug - to see randomness on terminal
    pc.printf("Bits are %d %d %d %d\n",a[0],a[1],a[2],a[3]);   
    
}
    
int main() {
  
  // serial speed
  pc.baud(9600); 
  
  
  // 18 second timer period
  ticker_period_18.attach(&get_adc,18.0); 
  get_adc();
  while(1) {
    
    // led1
    myled1 = 1;
    wait(0.1*a[0]);
    myled1 = 0;
    
    //led2
    myled2 = 1;
    wait(0.1*a[1]);
    myled2 = 0;
    
    //led3
    myled3 = 1;
    wait(0.1*a[2]);
    myled3 = 0;
    
    //led4
    myled4 = 1;
    wait(0.1*a[3]);
    myled4 = 0;

  }
 
}
