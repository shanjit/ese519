#include "mbed.h"
#include "PwmOut.h"

PwmOut pin23(p23);
Serial pc(USBTX, USBRX);
DigitalOut led2(LED2);

Ticker tick;
bool flag = 0;

char arr[12];
int count = 0;

void play()
{
    flag = 1;

   // Output PWM 
    
}

void stop()
{
    if(flag)    // Music was playing - Reset PWM
    {
        // Stop the sound
        flag = 0;
    }
    
    //
    
}

void callback() {
    
    char c = pc.getc();
    if(c != 13 ){
        printf("Got %c\n", c);
        arr[count] = c;
        count++;
    }
    else
    {
        // process the array
        int cnt = 0;
        int freq = 0;
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
        printf("Recd frq %d\n",freq);
        
        cnt = n+1;
        int period = 0;
        while(cnt <count)
        {
            period = period + ((arr[cnt]-48)*pow(10.0,count-cnt-1));
            cnt++;
        }
        printf("Recd period %d\n",period);
        
        play(); // Start Playing the music
        ticker.attach(&stop,300); // Stop after 300
        
    }
}

int main() {
    pin23.period_us(2272); // Set period 2.2ms ~ 440Hz
    pin23 = 0.5;
    pc.attach(&callback);
       
    while(1) {
/*     for(float d = 0.0f; d<=1.0 ; d+=0.1)
     {
         myled = d;
         wait(0.1);
     } */ 
    }
}
