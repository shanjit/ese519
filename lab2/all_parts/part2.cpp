/*
ese519-lab2-part0
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Generating a signal of a particular frequency for a particular time.
Shown to the TA already. 

*/

#include "mbed.h"
#include "PwmOut.h"

#define ARR_SIZE 12

// Define pin connections
PwmOut pin23(p23);

// Initialize serial connection
Serial pc(USBTX, USBRX);
DigitalOut led2(LED2);


// Timeout resource used: http://developer.mbed.org/handbook/Timeout
Timeout flipper;

Ticker tick;

// Array to store the serial input
char arr[ARR_SIZE];
int count = 0;

// Global variables
int period = 0;
int freq = 0;

// Stop the tone
void stop()
{
    pc.printf("Stopped");
    pin23=0.0;    
}

// Play the tone
void play()
{
   // Output PWM
   int t = (1.0/freq)*1000000;
   pc.printf("T is %d", t);

   // PWM connection on Pin23
   pin23.period_us(t);
   pin23 = 0.5;
   
   // Attach the timeout to stop after certain period.
   flipper.attach(&stop, period/1000.0);

}

bool flag=false;

// Read from Serial and parse for freq. and period
void callback() {
    
    char c = pc.getc();
    if(c != 13 ){
        
        printf("Got %c\n", c);
        arr[count] = c;
        count++;
    }
    else
    {
        // Debug code
        //pc.printf("count is : %d", count);
        
        // process the array to find frequency
        int cnt = 0;
        freq = 0;
        period = 0;
        while(arr[cnt]!=' '){
            cnt++;
        }
        int n = cnt;
        printf("n is %d",n);
        while(cnt)
        {
            freq = freq + ((arr[n-cnt]-48)*pow(10.0,cnt-1));
            cnt--;
        }
        // debug code
        //printf("Recd frq %d\n",freq);
        //cnt = n+1;
        //pc.printf("cnt: %d, period, %d", cnt, period);

        // process the array to find period
        while(cnt <count)
        {
            period = period + ((arr[cnt]-48)*pow(10.0,count-cnt-1));
            pc.printf("period, %d", period);
            cnt++;
        }
        //debug code
        //printf("Recd period %d\n",period);
        
        //clear the array
        memset ( arr, 0, ARR_SIZE );

        // set count of characters read to 0
        count = 0;

        // play tone
        // the maximum the frequency can be is 1Mhz, this is due to software limitation
        if(freq>1000000)
        {
            // if the frequncy is more than 1Mhz then make the freq. as 1000 Hz
            // We could also deal with this condition by showing invalid entry to the user 
            // on the serial monitor, but since it was not specified on how to deal with this
            // we chose to do this.
            freq = 1000;
        }

        if (period>1800)
        {
            // if the period is more than 1800 (30 minutes) then make the period 1 second
            period = 1;
        }
        play(); 
    }
}

int main() {

    // attach a callback to parse frequency and period
    pc.attach(&callback);
       
    // infinite while loop
    while(1) {

    }
}