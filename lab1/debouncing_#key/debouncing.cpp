//debouncing.cpp on key # 

#include "mbed.h"


// Connections on the mbed
// Mbed - Keypad 
// p5 - 7
// p6 - 6 
// p7 - 5
// p8 - 3
// p10 - 8
// p11 - 4

bool flag = false;

InterruptIn key(p6);
DigitalOut row(p11);

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
Serial pc(USBTX, USBRX); // tx, rx

Timer timer_400;
Timer timer_key;

void key_rise_int()
{
    //start a timer
    timer_key.start();
    pc.printf("key pressed");
    wait(0.01);
    //read the value of the key after 10ms and set the flag
    if(key)
    {
        flag = true;    
    }
    
    else
    {
        flag = false;    
    }
        
}

void key_rise_int1()
{
    wait(0.01);
    if(key)
    {
        pc.printf("pressed");    
    }
    
}

void key_fall_int1()
{
    wait(0.01);
    if(!key)
    {
        pc.printf("released");
        
    }
}
void key_fall_int()
{
    pc.printf("key released");
    
    timer_400.reset();
    // stop the timer
    timer_key.stop();
    
    // read the timer value and decide if dot, dash 
    int timer_key_val = timer_key.read_ms();
    
    if((timer_key_val>40)&&(timer_key_val<210)&&(flag==true) )
    {
        pc.printf("Dot\n");
    }
    
    else{
        pc.printf("Dash\n");    
    }
    
    // reset the timer
    timer_key.reset();
    timer_key.start();
    flag=0; 
    timer_400.start();
}


int main() {
    pc.baud(9600); 
    row = 1;

    // start the timer for 400ms 
    //timer_400.start();
    
    key.rise(&key_rise_int1);
    key.fall(&key_fall_int1);
    
    
    while(1) {
/*        // if timer value hits 400 ms, then reset the timer and read as space. 
        if(timer_400.read_ms()>=400)
        {
        timer_400.reset();
        pc.printf("Got a space\n");    
        timer_400.start();
        }*/
    }
}
