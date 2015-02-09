#include "mbed.h"
/*
ese519-lab1-part4
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Idea : Using the keypad and timers, implement dot and dash functionality
Timer 1 is used to measure the duration of the key press
Timer 2 is used independently to generate spaces

7 segment display is interfaced to display dot, space and dash

Dot - Segment D
Dash - Segment G
Space - Segment A
*/

// Connections on the mbed
// Mbed - Keypad 
// p5 - 7
// p6 - 6 
// p7 - 5
// p8 - 3
// p10 - 8
// p11 - 4


bool flag = false;

// Define the row and column for keypad
InterruptIn key(p6);
DigitalOut row(p11);

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
Serial pc(USBTX, USBRX); // tx, rx

// 2 timers used for space and dot/dash measurement
Timer timer_400;
Timer timer_key;

// seven segment display interface
// Mbed - Seven Segment (common anode)
// p21 - 1  
// p22 - 2 
// gnd - 3
// p24 - 4
// p25 - 5 
// p26 - 6 
// p27 - 7 
// gnd - 8
// p29 - 9
// p30 - 10

DigitalOut ss_a(p27);
DigitalOut ss_b(p26);
DigitalOut ss_c(p24);
DigitalOut ss_d(p22);
DigitalOut ss_e(p21);
DigitalOut ss_f(p29);
DigitalOut ss_g(p30);
DigitalOut ss_dot(p25);

// Function for handling dot behavior
inline void dot()
{
ss_d = 0;
wait(0.05);
ss_d = 1;    
    
}

// Function for handling dash behavior
inline void dash()
{
    ss_g = 0;
    wait(0.05);
    ss_g = 1;  
        
}

// Function for handling space behavior
inline void space()
{
    ss_a = 0;
    wait(0.05);
    ss_a = 1;   

}
// Function for turning of the 7 segment display

void segment_off()
{
    ss_a = 1;
    ss_b = 1;
    ss_c = 1;
    ss_d = 1;
    ss_e = 1;
    ss_f = 1;
    ss_g = 1;
    ss_dot = 1;
    
}

// Function for turning on all leds in the 7 segment display
// Used for debugging
void segment_on()
{
    ss_a = 0;
    ss_b = 0;
    ss_c = 0;
    ss_d = 0;
    ss_e = 0;
    ss_f = 0;
    ss_g = 0;
    ss_dot = 0;   
}

// Interrupt handler for key press - Debugging purpose
void key_rise_int1()
{
    wait(0.01); // Debounce period
    if(key)
    {
        pc.printf("pressed");    
    }
    
}

// Interrupt handler for key release - Debugging purpose
void key_fall_int1()
{
    wait(0.01);
    if(!key)
    {
        pc.printf("released");
        
    }
}

// Interrupt handler for key press
void key_rise_int()
{

    wait(0.01);
    //read the value of the key after 10ms and set the flag
    if(key)
    {
        timer_400.stop();   // Stop the space timer
        flag = true;    
        //start a timer for measuring the duration of the key press
        timer_key.start();  
        pc.printf("key pressed");
    }
    
    else
    {
        flag = false;    // Debouncing failed- key wasn't pressed
    }
        
}

// Interrupt handler for key release
void key_fall_int()
{
    wait(0.01);
    
    if(!key)
    {
        pc.printf("key released");
        //timer_400.reset();
        // stop the timer used for measuring key press
        timer_key.stop();
        
        // read the timer value and decide if dot, dash 
        int timer_key_val = timer_key.read_ms();
        
        if((timer_key_val>40)&&(timer_key_val<220)&&(flag==true) )
        {
            /*myled1 = 1;
            wait(0.05);
            myled1 = 0;*/
            dot();  // Dot pressed
        }
        
        else if (timer_key_val>220){
            /*myled2 = 1;
            wait(0.05);
            myled2 = 0;*/
            dash(); //Dash pressed
        }
        
        // reset the measurement timer
        timer_key.stop();   
        timer_key.reset();
        flag=0;
        timer_400.reset();  // Restart the space timer after reset
        timer_400.start();
    
    }
}


int main() {
    
    
    // Check the leds
    myled1 = 0;
    myled2 = 1;
    myled3 = 1;
    myled4 = 1;

    wait(0.5);
    myled1 = 0;
    myled2 = 0;
    myled3 = 0;
    myled4 = 0;
    
    // Check the seven segment
    segment_off();
    wait(0.5);
    segment_on();
    wait(0.5);
    segment_off();
    
    pc.baud(9600); 
    row = 1;
    

    // start the timer for 400ms 
    timer_400.start();
    
    key.rise(&key_rise_int);
    key.fall(&key_fall_int);    // Set up the interrupt handlers
    
    
    while(1) {
        // if timer value hits 400 ms, then reset the timer and read as space. 
        if(timer_400.read_ms()>=400)
        {
        timer_400.reset();
        
        if(!flag)
        {
        //pc.printf("Got a space\n");    
        /*myled3 = 1;
        wait(0.05);
        myled3 = 0;*/
        space();    // Space occured
        }
        }
    }
}
