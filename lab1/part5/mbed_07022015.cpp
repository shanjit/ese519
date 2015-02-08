#include "mbed.h"

#define DOT 1
#define DASH 2
/*
ese519-lab1-part5
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Idea : Using the keypad and timers, implement dot and dash functionality
Timer 1 is used to measure the duration of the key press
Timer 2 is used independently to generate spaces

7 segment display is interfaced to display dot, space and dash
The ASCII characters are interpreted and printed on the serial terminal

*/

// Connections on the mbed
// Mbed - Keypad 
// p5 - 7
// p6 - 6 
// p7 - 5
// p8 - 3
// p10 - 8
// p11 - 4

// array for saving the received dot / dash pattern
int ch[5];
int count_ch = 0;   // stores count of the number of dots/dashes received

// Flag for detecting key
bool flag = false;

// Set up the row and column for the keypad
// p6 senses active high and p11 activates the row
InterruptIn key(p6);
DigitalOut row(p11);

// leds
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
Serial pc(USBTX, USBRX); // tx, rx

// Timers used for detecting dot/dash and space
Timer timer_400;    // Timer for space
Timer timer_key;

// seven segment display
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

// Function for determing the character after storing the dot/dash pattern received
inline void find_char()
{
    
    if(count_ch==0) 
    {
        return;
    }
    
    else if(count_ch==1)    // If the no of characters received is 1
    {                       // the letter can be either E or T
        if(ch[0]==DOT)
        {
        pc.printf("E");    // Print the interpreted character on the terminal
        }
        
        else if (ch[0]==DASH)
        {
        pc.printf("T");    
        }
    }
    
    else if(count_ch==2)
    {
        if((ch[0]==DOT)&&(ch[1]==DASH))
        {
            pc.printf("A");
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT))       
        {
            pc.printf("I");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DOT))       
        {
            pc.printf("N");
        }

        else if((ch[0]==DASH)&&(ch[1]==DASH))       
        {
            pc.printf("M");
        }        
    }
    
    else if(count_ch==3)
    {
        if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT))
        {
            pc.printf("S");    
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DOT))
        {
            pc.printf("R");
        }

        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DASH))
        {
            pc.printf("W");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DOT))
        {
            pc.printf("D");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DOT))
        {
            pc.printf("G");
        }

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DASH))
        {
            pc.printf("K");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DASH))
        {
            pc.printf("O");
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DASH))
        {
            pc.printf("U");
        }
        
        
    }

    else if(count_ch==4)
    {
        if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT))
        {
            pc.printf("H");   
        }

        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DOT)&&(ch[3]==DOT))
        {
            pc.printf("L");   
        }        
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DASH)&&(ch[3]==DOT))
        {
            pc.printf("F");   
        }        

        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DASH))
        {
            pc.printf("V");   
        }        

        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DOT)&&(ch[3]==DOT))
        {
            pc.printf("Z");   
        }        

        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DOT))
        {
            pc.printf("P");   
        }        

        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DASH))
        {
            pc.printf("J");   
        }        

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DASH)&&(ch[3]==DASH))
        {
            pc.printf("Y");   
        }        

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DASH))
        {
            pc.printf("X");   
        }        

        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DOT)&&(ch[3]==DASH))
        {
            pc.printf("Q");   
        }        

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DASH)&&(ch[3]==DOT))
        {
            pc.printf("C");   
        }        

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT))
        {
            pc.printf("B");   
        }
    }

    else if(count_ch==5)
    {
        if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT)&&(ch[4]==DOT))
        {
            pc.printf("5");
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT)&&(ch[4]==DASH))
        {
            pc.printf("4");
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DASH)&&(ch[4]==DASH))
        {
            pc.printf("3");
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DASH)&&(ch[3]==DASH)&&(ch[4]==DASH))
        {
            pc.printf("2");
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DASH)&&(ch[4]==DASH))
        {
            pc.printf("1");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT)&&(ch[4]==DOT))
        {
            pc.printf("6");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DOT)&&(ch[3]==DOT)&&(ch[4]==DOT))
        {
            pc.printf("7");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DOT)&&(ch[4]==DOT))
        {
            pc.printf("8");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DASH)&&(ch[4]==DOT))
        {
            pc.printf("9");
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DASH)&&(ch[4]==DASH))
        {
            pc.printf("0");
        }
        
    }


}

// Function for space behavior
inline void space()
{
    ss_a = 0;
    wait(0.05);
    ss_a = 1;
    
    // depending on count, determine the character
    find_char();
   
    count_ch = 0;   // Reset the number of characters count
    ch[0] = 0;      // Clear the array
    ch[1] = 0;
    ch[2] = 0;
    ch[3] = 0;
    ch[4] = 0;
    
}

inline void dot()
{
    ss_d = 0;
    wait(0.05);
    ss_d = 1;
    if(count_ch>=5)
    {
    space();   // When count >= 5 the array must be checked for the ascii character
    }
    else
    {
        ch[count_ch] = DOT;  
        count_ch++;  
    }
}

inline void dash()
{
    ss_g = 0;
    wait(0.05);
    ss_g = 1;  
    
    if(count_ch>=5) // When count >= 5 the array must be checked for the ascii character
    {
    space();   
    }
    else
    {
        ch[count_ch] = DASH;  
        count_ch++;  
    }}

// function to turn off the 7 segment
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
// function to turn on the 7 segment
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

// debugging function
void key_rise_int1()
{
    wait(0.01);
    if(key)
    {
        pc.printf("pressed");    
    }
    
}

// debugging function
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
        timer_400.stop();
        flag = true;    
        //start a timer
        timer_key.start();
       // pc.printf("key pressed");
    }
    
    else
    {
        flag = false;    
    }
        
}
// Interrupt handler for key press
void key_fall_int()
{
    wait(0.01);
    
    if(!key)
    {
        //pc.printf("key released");
        //timer_400.reset();
        // stop the timer
        timer_key.stop();
        
        // read the timer value and decide if dot, dash 
        int timer_key_val = timer_key.read_ms();
        
        if((timer_key_val>40)&&(timer_key_val<220)&&(flag==true) )
        {
            /*myled1 = 1;
            wait(0.05);
            myled1 = 0;*/
            dot();
        }
        
        else if (timer_key_val>220){
            /*myled2 = 1;
            wait(0.05);
            myled2 = 0;*/
            dash();
        }
        
        // reset the timer
        timer_key.stop();   // Stop and reset the dot/dash timer
        timer_key.reset();
        flag=0;
        timer_400.reset(); // Reset the space timer
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
    
    key.rise(&key_rise_int);    // Setup the interrupt handlers
    key.fall(&key_fall_int);
    
    
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
        space();
        }
        }
    }
}
