#include "mbed.h"
 
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
AnalogIn ain(p19);
Serial pc(USBTX, USBRX);
Ticker ticker_period_18;

int a[4];

void get_adc()
{
    // This gets called every 2 second and updates the 'a' array
    int temp;
    temp = ain.read_u16();
    a[0] = temp%10;
    temp = temp/10;
    a[1] = temp%10;
    temp = temp/10;
    a[2] = temp%10;
    temp = temp/10;
    a[3] = temp%10;
    
    pc.printf("Bits are %d %d %d %d\n",a[0],a[1],a[2],a[3]);   
    
}
    
int main() {
  pc.baud(9600); 
  
  
  // 1 second timer period
  ticker_period_18.attach(&get_adc,18.0); 
  get_adc();
  while(1) {
    myled1 = 1;
    wait(0.1*a[0]);
    myled1 = 0;
    
    myled2 = 1;
    wait(0.1*a[1]);
    myled2 = 0;
    
    myled3 = 1;
    wait(0.1*a[2]);
    myled3 = 0;
    
    myled4 = 1;
    wait(0.1*a[3]);
    myled4 = 0;

  }
 
}
