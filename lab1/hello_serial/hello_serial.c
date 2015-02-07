//hello_serial
#include "mbed.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
AnalogIn randin(p18);

Serial pc(USBTX, USBRX); // tx, rx

Ticker ticker_period_18;
int arr[4];
void blink(){
        int i = 0;
        int curr;
        arr[0] = randin.read_u16() % 4;
        arr[1] = randin.read_u16() % 4;
        
        arr[2] = randin.read_u16() % 4;
    
        arr[3] = randin.read_u16() % 4;
        pc.printf("arr[0] is %d ",arr[0]);   
        pc.printf("arr[1] is %d ",arr[1]);   
        pc.printf("arr[2] is %d ",arr[2]);   
        pc.printf("arr[3] is %d ",arr[3]);                           
//        printf("%d ", randin.read_u16());
        curr = arr[i];
        for(int k=0; k<4 ; k++){    

        switch(curr){
        case 0: 
            myled1 = 1;
            wait(4.5);

            myled1 = 0;
        case 1: 
            myled2 = 1;
            wait(4.5);

            myled2 = 0;
        case 2: 
            myled3 = 1;
            wait(4.5);
            myled3 = 0;
        case 3: 
            myled4 = 1;
            wait(4.5);
            myled4 = 0;
            }
        i = (i+1)%4;
        }
        
}

int main() {
    pc.baud(9600);   
    ticker_period_18.attach(&blink,18.0);
    while(1) {
        //blink(curr);        
        pc.printf("Hello World!\n");
    }
}