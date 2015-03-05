
/*
*   Lab 3.1 Part 1
*   Team :  Shanjit Singh Jajmann - sjajmann
*           Vaibhav N Bhat - vaibhavn
*   Description : 
*        LCD Library is used to print "President Obama"
*        Initially a scrolling text appears followed by static text
*/

#include "mbed.h"
#include "C12832_lcd.h"
#include "Arial_9.h"
#include "Small_7.h"
#include "graphics.h"
 
C12832_LCD lcd;
 
int main()
{
    int i,s;
    lcd.cls();
    lcd.set_font((unsigned char*) Arial_9);
    s = 3;
    lcd.setmode(XOR);             // XOR - a second print will erase  
   lcd.set_auto_up(0);

   for(i=-20; i<5; i++){             // scrolling text
     lcd.locate(5,i);               // Print at x=5 and y=i
     lcd.printf("President");
     lcd.locate(5,i+12);            
     lcd.printf("Obama");           // Printing 'President \n Obama'
     lcd.copy_to_lcd();
     lcd.locate(5,i);
     wait(0.2);
     lcd.printf("President");
     lcd.locate(5,i+12);
     lcd.printf("Obama");
     lcd.copy_to_lcd();
     i=i+1;
   }  
   lcd.locate(5,i);
   lcd.printf("President");
   lcd.locate(5,i+12);
   lcd.printf("Obama");
   lcd.copy_to_lcd();
   
}