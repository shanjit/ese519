#include "mbed.h"

#define DOT 1
#define DASH 2
/*
ese519-lab1-Extra Credit Seven segment
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Idea : Using the keypad and timers, implement dot and dash functionality
Timer 1 is used to measure the duration of the key press
Timer 2 is used independently to generate spaces

7 segment display is interfaced to display dot, space and dash
The ASCII characters are interpreted and printed on the serial terminal

Buzzer is interfaced to beep when a dot is pressed and a longer beep
when a dash is pressed

ASCII characters are display on the 7 segment display

2 spaces are allowed between letters.
5 or more spaces is considered as one space

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

bool flag = false;

// Set up the row and column for the keypad
// p6 senses active high and p11 activates the row
InterruptIn key(p6);
DigitalOut row(p11);

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
Serial pc(USBTX, USBRX); // tx, rx

// Timers used for detecting dot/dash and space
Timer timer_400;    // Timer for space
Timer timer_key;

DigitalOut buzz(p23);

// seven segment display
// Mbed - Seven Segment (common cathode)
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

// Function which displays ASCII character on the 7 segment display given a character
void seven_seg_disp(char sev_ch)
{
    if(sev_ch == '0'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    

    else if(sev_ch == '1'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 1;
            ss_f = 1;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    

    else if(sev_ch == '2'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 1;
            ss_d = 0;
            ss_e = 0;
            ss_f = 1;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
      
    }    

    else if(sev_ch == '3'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 1;
            ss_f = 1;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    } 
    else if(sev_ch == '4'){
            ss_a = 1;
            ss_b = 1;
            ss_c = 0;
            ss_d = 1;
            ss_e = 1;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }  

    else if(sev_ch == '5'){
            ss_a = 0;
            ss_b = 1;
            ss_c = 0;
            ss_d = 0;
            ss_e = 1;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }      
    
    else if(sev_ch == '6'){
            ss_a = 0;
            ss_b = 1;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
    
    else if(sev_ch == '7'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 1;
            ss_f = 1;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == '8'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == '9'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 1;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    

    else if(sev_ch == 'A'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
    
    else if(sev_ch == 'B'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'C'){
            ss_a = 0;
            ss_b = 1;
            ss_c = 1;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'D'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'E'){
            ss_a = 0;
            ss_b = 1;
            ss_c = 1;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 0;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'F'){
            ss_a = 0;
            ss_b = 1;
            ss_c = 1;
            ss_d = 1;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'G'){
            ss_a = 0;
            ss_b = 1;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'H'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'I'){
            ss_a = 1;
            ss_b = 1;
            ss_c = 1;
            ss_d = 1;
            ss_e = 0;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       

    else if(sev_ch == 'J'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 1;
            ss_f = 1;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'K'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'L'){
            ss_a = 1;
            ss_b = 1;
            ss_c = 1;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       

    else if(sev_ch == 'M'){
            ss_a = 1;
            ss_b = 1;
            ss_c = 1;
            ss_d = 1;
            ss_e = 1;
            ss_f = 1;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'N'){
            ss_a = 1;
            ss_b = 1;
            ss_c = 1;
            ss_d = 1;
            ss_e = 1;
            ss_f = 1;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'O'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e =0 ;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'P'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 1;
            ss_d = 1;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'Q'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 0;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'R'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'S'){
            ss_a = 0;
            ss_b = 1;
            ss_c = 0;
            ss_d = 0;
            ss_e = 1;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'T'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 1;
            ss_f = 1;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'U'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    

    else if(sev_ch == 'V'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    
           else if(sev_ch == 'W'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 0;
            ss_e = 0;
            ss_f = 0;
            ss_g = 1;
            ss_dot = 1;
            wait(0.30);
       
    }    

       
    else if(sev_ch == 'X'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 0;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    
       
    else if(sev_ch == 'Y'){
            ss_a = 1;
            ss_b = 0;
            ss_c = 0;
            ss_d = 1;
            ss_e = 1;
            ss_f = 0;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    

    else if(sev_ch == 'Z'){
            ss_a = 0;
            ss_b = 0;
            ss_c = 1;
            ss_d = 0;
            ss_e = 0;
            ss_f = 1;
            ss_g = 0;
            ss_dot = 1;
            wait(0.30);
       
    }    

            ss_a = 1;
            ss_b = 1;
            ss_c = 1;
            ss_d = 1;
            ss_e = 1;
            ss_f = 1;
            ss_g = 1;
            ss_dot = 1; 
}

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
        pc.printf("E");     // Print the interpreted character on the terminal
        seven_seg_disp('E');  
        }
        
        else if (ch[0]==DASH)
        {
        pc.printf("T");    
        seven_seg_disp('T');          
        }
    }
    
    else if(count_ch==2)
    {
        if((ch[0]==DOT)&&(ch[1]==DASH))
        {
            pc.printf("A");
        seven_seg_disp('A');  
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT))       
        {
            pc.printf("I");
        seven_seg_disp('I');  
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DOT))       
        {
            pc.printf("N");
        seven_seg_disp('N');              
        }

        else if((ch[0]==DASH)&&(ch[1]==DASH))       
        {
            pc.printf("M");
        seven_seg_disp('M');  
        }        
    }
    
    else if(count_ch==3)
    {
        if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT))
        {
            pc.printf("S");    
        seven_seg_disp('S');  
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DOT))
        {
            pc.printf("R");
        seven_seg_disp('R');  
        }

        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DASH))
        {
            pc.printf("W");
        seven_seg_disp('W');              
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DOT))
        {
            pc.printf("D");
        seven_seg_disp('D');              
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DOT))
        {
            pc.printf("G");
        seven_seg_disp('G');              
        }

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DASH))
        {
            pc.printf("K");
        seven_seg_disp('K');  
        }
        
        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DASH))
        {
            pc.printf("O");
        seven_seg_disp('O');              
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DASH))
        {
            pc.printf("U");
        seven_seg_disp('U');  
        }
        
        
    }

    else if(count_ch==4)
    {
        if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT))
        {
            pc.printf("H");   
        seven_seg_disp('H');              
        }

        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DOT)&&(ch[3]==DOT))
        {
            pc.printf("L");
           seven_seg_disp('L');      
        }        
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DASH)&&(ch[3]==DOT))
        {
            pc.printf("F");   
            seven_seg_disp('F');  
        }        

        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DASH))
        {
            pc.printf("V");  
            seven_seg_disp('V');   
        }        

        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DOT)&&(ch[3]==DOT))
        {
            pc.printf("Z");  
            seven_seg_disp('Z');   
        }        

        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DOT))
        {
            pc.printf("P");  
           seven_seg_disp('P');    
        }        

        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DASH))
        {
            pc.printf("J"); 
          seven_seg_disp('J');      
        }        

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DASH)&&(ch[3]==DASH))
        {
            pc.printf("Y");
         seven_seg_disp('Y');           
        }        

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DASH))
        {
            pc.printf("X");
         seven_seg_disp('X');        
        }        

        else if((ch[0]==DASH)&&(ch[1]==DASH)&&(ch[2]==DOT)&&(ch[3]==DASH))
        {
            pc.printf("Q");
         seven_seg_disp('Q');        
        }        

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DASH)&&(ch[3]==DOT))
        {
            pc.printf("C");
         seven_seg_disp('C');        
        }        

        else if((ch[0]==DASH)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT))
        {
            pc.printf("B");
         seven_seg_disp('B');        
        }
    }

    else if(count_ch==5)
    {
        if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT)&&(ch[4]==DOT))
        {
            pc.printf("5");
            seven_seg_disp('5');
            
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DOT)&&(ch[4]==DASH))
        {
            pc.printf("4");
            seven_seg_disp('4');
            
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DOT)&&(ch[3]==DASH)&&(ch[4]==DASH))
        {
            pc.printf("3");
            seven_seg_disp('3');
            
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DOT)&&(ch[2]==DASH)&&(ch[3]==DASH)&&(ch[4]==DASH))
        {
            pc.printf("2");
            seven_seg_disp('2');
            
        }
        
        else if((ch[0]==DOT)&&(ch[1]==DASH)&&(ch[2]==DASH)&&(ch[3]==DASH)&&(ch[4]==DASH))
        {
            pc.printf("1");
            seven_seg_disp('1');
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
            seven_seg_disp('0');
        }
        
    }


}

// Counter for no of spaces
int count_space = 0;
bool bool_space = false;    // Flag for displaying space

// Function for handling space
inline void space()
{
    ss_a = 0;
    wait(0.05);
    ss_a = 1;
    
    count_space++;  // Increment the no of spaces received
    
    if(count_space<3){  // If there are two between letters then interpret the letter
        
    // depending on count, determine the character
    find_char();
   
    count_ch = 0;   // Reset the count and array
    ch[0] = 0;
    ch[1] = 0;
    ch[2] = 0;
    ch[3] = 0;
    ch[4] = 0;
    bool_space = false;
    }
    
    else if ((count_space>=5)&&(bool_space==false)) // Display space
    {
     bool_space = true;

    pc.printf("space");

    
    }

}
        
// Function for handling dot
inline void dot()
{
    count_space = 0;
    ss_d = 0;
    wait(0.05);
    ss_d = 1;
    
    buzz=1;
    wait(0.05);
    buzz = 0;
    if(count_ch>=5)
    {
    space();   
    }
    else
    {
        ch[count_ch] = DOT;  
        count_ch++;  
    }
}

// Function for handling dash
inline void dash()
{
    count_space = 0;
    ss_g = 0;
    wait(0.05);
    ss_g = 1;  

    buzz=1;
    wait(0.15);
    buzz = 0;
        
    if(count_ch>=5)
    {
    space();   
    }
    else
    {
        ch[count_ch] = DASH;  
        count_ch++;  
    }}

// Function for turning off the 7 segment display
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

// Function for turning on the 7 segment display
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

// Debugging function
void key_rise_int1()
{
    wait(0.01);
    if(key)
    {
        pc.printf("pressed");    
    }
    
}

// Debugging function
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
        //start a timer
        timer_key.start();  // Start the button press timer
       // pc.printf("key pressed");
    }
    
    else
    {
        flag = false;    
    }
        
}

// Interrupt handler for key release
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
        {  // dot received
            /*myled1 = 1;
            wait(0.05);
            myled1 = 0;*/
            dot();
        }
        
        // dash received
        else if (timer_key_val>220){
            /*myled2 = 1;
            wait(0.05);
            myled2 = 0;*/
            dash();
        }
        
        // reset the timer
        timer_key.stop();
        timer_key.reset();
        flag=0;
        timer_400.reset();  // Reset and restart the space timer
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
    
    key.rise(&key_rise_int);    // Set up the interrup handler
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
