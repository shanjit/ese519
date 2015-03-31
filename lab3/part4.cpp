/*
*   Lab 3.1 Part 4
*   Team :  Shanjit Singh Jajmann - sjajmann
*           Vaibhav N Bhat - vaibhavn
*   Description : 
*       The acclerometer is read and depending on the inclination
*       wave files are read and played on the speaker and audio out
*       A flag is used to detect joystick press, upon which the music starts
*       The orientation of the IMU switches the song
*/

#include "mbed.h"
#include "USBHostMSD.h"
#include "wave_player.h"
#include "MMA7660.h"

MMA7660 MMA(p28, p27);  // IMU object is constructed 
Serial pc(USBTX, USBRX);
DigitalIn fire(p14);
BusIn joy(p15,p12,p13,p16);

int flag = 0; // flag is set when joystick is clicked or moved

// Modified mbed Application board waveplayer demo
//Plays the wave files from the USB flash drive
//Outputs to onboard speaker (but at very low volume)
//and the Audio Out jack for connection to a set of amplified PC speakers (at higher volume)

//Analog Out Jack
AnalogOut DACout(p18);
//On Board Speaker
PwmOut PWMout(p26);
wave_player waver(&DACout,&PWMout);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// RGB leds
PwmOut r (p23); 
PwmOut g (p24);
PwmOut b (p25);

int main()
{
    USBHostMSD msd("usb");
    FILE *wave_file;
    //setup PWM hardware for a Class D style audio output
    PWMout.period(1.0/400000.0);
    // wait until connected to a USB device
    while(!msd.connect()) {
        Thread::wait(500);
    }
    
    while(1) {
        
        if(fire || joy )    // if the joystick is pressed set the flag
        {
            flag = 1;    
        }
        
        int o = MMA.getOrientation();    //Continously read the IMU
        if(flag){
            switch(o)
            {
                case 0:
                    pc.printf("Up");
                    led1 = 1;   
                    led2 = 0;
                    led3 = 0;
                    led4 = 0;  
                    r = 1.0;    // Light up RGB led
                    g = 0.5;
                    b = 0.5;

                    //open wav file and play file0                
                    wave_file=fopen("/usb/file0.wav","r");
                    pc.printf("%p",wave_file);
                    waver.play(wave_file);
                    fclose(wave_file);                
                    break;    
                case 1:
                    pc.printf("Down");

                    r = 0.5;
                    g = 1.0;
                    b = 0.5;
                   
                    led1 = 0;
                    led2 = 0;
                    led3 = 1;
                    led4 = 1;  

                    //open wav file and play file1                                    
                    wave_file=fopen("/usb/file1.wav","r");
                    waver.play(wave_file);
                    fclose(wave_file);                
                    
                    break;    
                case 2:
                    pc.printf("Right");
                    led1 = 1;
                    led2 = 1;
                    led3 = 1;
                    led4 = 0;
                    //open wav file and play file2
                    wave_file=fopen("/usb/file2.wav","r");
                    waver.play(wave_file);
                    fclose(wave_file);                
                    r = 0.0;
                    g = 0.5;
                    b = 1.0;
  
                    break;    
                case 3:
                    pc.printf("Left");
                    led1 = 0;
                    led2 = 0;
                    led3 = 0;
                    led4 = 1;  
                    //open wav file and play file3
                    wave_file=fopen("/usb/file3.wav","r");
                    waver.play(wave_file);
                    fclose(wave_file);                
                    r = 1.0;
                    g = 0.5;
                    b = 0.25;
                    break;    
                default:    //IMU is flat
                    pc.printf("flat");
                    led1 = 0;
                    led2 = 0;
                    led3 = 0;
                    led4 = 0;                                
                    r = 0.33;
                    g = 0.33;
                    b = 0.33;    
                    break;    
            }
        }
    }
}