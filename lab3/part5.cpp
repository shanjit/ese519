/*
*   Lab 3.1 Part 5
*   Team :  Shanjit Singh Jajmann - sjajmann
*           Vaibhav N Bhat - vaibhavn
*   Description : 
*   The display value of the temperature sensor is stored in a variable
*   The current temperature is continuously read and compared with the stored
*   value. If the difference exceeds 2 degrees, the display is updated and the 
*   new value is the saved as the display value.
*/

#include "mbed.h"
#include "LM75B.h"
#include "C12832.h"

C12832 lcd(p5, p7, p6, p8, p11);

LM75B sensor(p28,p27);  // Temp sensor
Serial pc(USBTX,USBRX);

float temp = 0; //Display value variable
char* sayings[] = {"Hello", "How areyou"};  // Array for saving sayings

int idx = 0;    // current index into the sayings array
int main ()
{

    //Try to open the LM75B
    if (sensor.open()) {
        printf("Device detected!\n");

    lcd.cls();
    lcd.locate(0,15);
    lcd.printf(sayings[idx]);   // Print 1st saying on startup 
    
    temp = (float) sensor;  // Save the temperature for comparison later
    float currTemp = temp;
    lcd.locate(0,3);
    lcd.printf("Temp = %.3f\n",currTemp); // Display the temperature
    
        while (1) {
        currTemp =  (float) sensor;           
    
    //If the temp difference changes by 2 degrees update the saying and
    // temperature on the lcd    
        if( ((currTemp-temp) > 0.25) || ( (currTemp-temp) < -0.25) ){
            lcd.cls();
            lcd.locate(0,3);
            temp = currTemp;    //Update temp with changed temperature
            lcd.printf("Temp = %.3f\n", currTemp);
            lcd.locate(0,15);
            idx = 1- idx;   //Toggle the indx
            lcd.printf(sayings[idx]);                           
            }
            wait(1.0);
        }

    } else {
        error("Device not detected!\n");
    }

}
