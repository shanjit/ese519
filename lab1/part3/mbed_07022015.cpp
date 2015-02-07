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


void key_rise_int()
{

    wait(0.01);
    //read the value of the key after 10ms and set the flag
    if(key)
    {
        timer_400.stop();
        flag = true;    
        //start a timer
        timer_key.start();
        pc.printf("key pressed");
    }
    
    else
    {
        flag = false;    
    }
        
}

void key_fall_int()
{
    wait(0.01);
    
    if(!key)
    {
        pc.printf("key released");
        //timer_400.reset();
        // stop the timer
        timer_key.stop();
        
        // read the timer value and decide if dot, dash 
        int timer_key_val = timer_key.read_ms();
        
        if((timer_key_val>40)&&(timer_key_val<220)&&(flag==true) )
        {
            myled1 = 1;
            wait(0.05);
            myled1 = 0;
        }
        
        else if (timer_key_val>220){
            myled2 = 1;
            wait(0.05);
            myled2 = 0;
        }
        
        // reset the timer
        timer_key.stop();
        timer_key.reset();
        flag=0;
        timer_400.reset();
        timer_400.start();
    
    }
}


int main() {
    
    myled1 = 0;
    myled2 = 1;
    myled3 = 1;
    myled4 = 1;

    wait(0.5);
    myled1 = 0;
    myled2 = 0;
    myled3 = 0;
    myled4 = 0;
    
    pc.baud(9600); 
    row = 1;
    

    // start the timer for 400ms 
    timer_400.start();
    
    key.rise(&key_rise_int);
    key.fall(&key_fall_int);
    
    
    while(1) {
        // if timer value hits 400 ms, then reset the timer and read as space. 
        if(timer_400.read_ms()>=400)
        {
        timer_400.reset();
        if(!flag)
        {
        //pc.printf("Got a space\n");    
        myled3 = 1;
        wait(0.05);
        myled3 = 0;
        }
        }
    }
}
