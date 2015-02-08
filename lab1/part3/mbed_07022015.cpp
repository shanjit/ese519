/*
ese519-lab1-part1
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Idea : Using the keypad and timers, implement dot and dash functionality

*/

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

// Interrupt whenever pin is pressed (#) - keypad
InterruptIn key(p6);
DigitalOut row(p11);

// led interface - visual feedback
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

/*
*   Dot represented by led1
*   Dash represented by led2
*   Space represented by led3
*/

// serial interface - for debugging
Serial pc(USBTX, USBRX);

// timers to ensure dot and dash 
Timer timer_400;
Timer timer_key;

// ISR when the key is just pressed on the keypad (for debugging)
void key_rise_int1()
{
    // debouncing code - wait and check
    wait(0.01);
    if(key)
    {   
        // serial debug
        pc.printf("pressed");    
    }
    
}

// ISR when the key is just pressed on the keypad (for debugging)
void key_fall_int1()
{   
    // debouncing code - wait and check
    wait(0.01);
    if(!key)
    {
        // serial debug
        pc.printf("released");
        
    }
}


// ISR when the key is just pressed on the keypad
void key_rise_int()
{
    // debouncing code - wait and check
    //read the value of the key after 10ms and set the flag
    wait(0.01);
    
    if(key)
    {
        timer_400.stop();   // Stop the space timer 
        flag = true;    
        //start a timer
        timer_key.start();  // Start counting the duration of the key press
        pc.printf("key pressed");   // For debugging
    }
    
    else
    {
        flag = false;    
    }
        
}

// ISR when the key is just pressed on the keypad
void key_fall_int()
{
    wait(0.01);
    
    if(!key)
    {
        pc.printf("key released");  // For debugging 
        //timer_400.reset();
        // stop the timer
        timer_key.stop();   // Stop the first timer which measures the key press
        
        // read the timer value and decide if dot, dash 
        int timer_key_val = timer_key.read_ms();
        
        if((timer_key_val>40)&&(timer_key_val<220)&&(flag==true) )  // Dot has been pressed
        {
            myled1 = 1;
            wait(0.05);
            myled1 = 0;
        }
        
        else if (timer_key_val>220){    // Dash has been pressed
            myled2 = 1;     
            wait(0.05);
            myled2 = 0;
        }
        
        // Reset and stop the measurement timer
        timer_key.stop();
        timer_key.reset();
        flag=0;
        timer_400.reset();  // Reset and restart the timer for space
        timer_400.start();
    
    }
}


int main() {
    
    myled1 = 0;     // blink the leds once to indicate start of the program
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
    

    // start the timer for 400ms to check the occurence of space
    timer_400.start();
    
    key.rise(&key_rise_int);    // Set up the button interrupt handlers
    key.fall(&key_fall_int);
    
    
    while(1) {
        // if timer value hits 400 ms, then reset the timer and read as space. 
        if(timer_400.read_ms()>=400)
        {
        timer_400.reset();
        if(!flag)
        {
        //pc.printf("Got a space\n");    
        myled3 = 1;     //Indicate the presence of space by blinking led
        wait(0.05);
        myled3 = 0;
        }
        }
    }
}
