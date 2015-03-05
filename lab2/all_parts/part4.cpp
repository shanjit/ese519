/*
ese519-lab2-part4
    Vaibhav N. Bhat (vaibhavn@seas)
    Shanjit S. Jajmann (sjajmann@seas)

Output two square waves from mbed and feed a hardware circuit

*/

#include "mbed.h"
#include <stdlib.h>

volatile int pincheck = 1;

//Row pins
InterruptIn row1(p13);
InterruptIn row2(p15);
InterruptIn row3(p16);
InterruptIn row4(p17);

//Coloumn pins
DigitalOut col1(p18);
DigitalOut col2(p11);
DigitalOut col3(p12);
DigitalOut col4(p14);

// The two pins on which frequencies are to be produced
// Pin 24 is using the default PWM out
// Pin 25 is using a timeout with a scantick
PwmOut pin24(p24);
DigitalOut pin25(p25);

//Ticker to scan every 4ms
Ticker scantick;
Ticker pwmtick1, pwmtick2;
Timeout timeout;

Serial pc(USBTX, USBRX);

// default period value
float period = 1.0;

// setting frequency 1 to run via a PWM   
void setFreq1(float f){
    pin24.period(1.0/f);
    pin24 = 0.5;
}

// setting a frequency 2 to run via tickers and timeout
void setFreq2(float f){
    period = 1.0/f;
    pwmtick1.attach(&high, period);
    timeout.attach(&startTick2, 0.5*period);
}

// Column scanner - switching columns on 
void colscanner(){
    pincheck=pincheck+1;
    if(pincheck == 5)
        pincheck = 1;
    switch (pincheck)
    {
        case 1:
            col1 = 1;
            col2 = 0;
            col3 = 0;
            col4 = 0;
            break;
        case 2:
            col1 = 0;
            col2 = 1;
            col3 = 0;
            col4 = 0;
            break;
        case 3:
            col1 = 0;
            col2 = 0;
            col3 = 1;
            col4 = 0;
            break;
        case 4:
            col1 = 0;
            col2 = 0;
            col3 = 0;
            col4 = 1;
            break;               
    }   
}

void high(){
    pin25 = 1;
}
void low(){
    pin25 = 0;
}
void startTick2 (){
    pwmtick2.attach(&low, period);
}

// Column 1 Pressed Interrupt Handler
void col1p (){
    scantick.detach();
    if (pincheck == 1)
        pc.printf("1 pressed");
        setFreq1(1209.0);
        setFreq2(697.0);
    else if (pincheck== 2)
        pc.printf("4 pressed");
        setFreq1(1209.0);
        setFreq2(770.0);
    else if (pincheck ==3)
        pc.printf("7 pressed");
        setFreq1(1209.0);
        setFreq2(852.0);
    else if (pincheck ==4)
        pc.printf("* pressed");
        setFreq1(1209.0);
        setFreq2(941.0);
}

// Column 2 Pressed Interrupt Handler
void col2p (){
    scantick.detach();
    if (pincheck == 1)
        pc.printf("2 pressed");
        setFreq1(1336.0);
        setFreq2(697.0);
    else if (pincheck== 2)
        pc.printf("5 pressed");
        setFreq1(1336.0);
        setFreq2(770.0);
    else if (pincheck ==3)
        pc.printf("8 pressed");
        setFreq1(1336.0);
        setFreq2(852.0);
    else if (pincheck ==4)
        pc.printf("0 pressed");
        setFreq1(1336.0);
        setFreq2(941.0);
}

// Column 3 Pressed Interrupt Handler
void col3p (){
    scantick.detach();
    if (pincheck == 1)
        pc.printf("3 pressed");
        setFreq1(1477.0);
        setFreq2(697.0);
    else if (pincheck== 2)
        pc.printf("6 pressed");
        setFreq1(1477.0);
        setFreq2(770.0);
    else if (pincheck ==3)
        pc.printf("9 pressed");
        setFreq1(1477.0);
        setFreq2(852.0);
    else if (pincheck ==4)
        pc.printf("# pressed");
        setFreq1(1477.0);
        setFreq2(941.0);
}

// Column 4 Pressed Interrupt Handler
void col4p (){
    scantick.detach();
    if (pincheck == 1)
        pc.printf("A pressed");
        setFreq1(1633.0);
        setFreq2(697.0);
    else if (pincheck== 2)
        pc.printf("B pressed");
        setFreq1(1633.0);
        setFreq2(770.0);
    else if (pincheck ==3)
        pc.printf("C pressed");
        setFreq1(1633.0);
        setFreq2(852.0);
    else if (pincheck ==4)
        pc.printf("4 pressed");
        setFreq1(1633.0);
        setFreq2(941.0);
}

// Column Released Interrupt Handler
void colr()
{
    scantick.attach(&colscanner,0.004);

    // Stop all the square wave output on pin24 and pin25.
    pwmtick1.detach();
    pwmtick2.detach();
    pin24 = 0;

}
   
int main()
{
    // Set all columns to be zero initially
    col1 = 0;
    col2 = 0;
    col3 = 0;
    col4 = 0;

    // Set rising edge interrupts on the rows
    row1.rise(&col1p);
    row2.rise(&col2p);
    row3.rise(&col3p);
    row4.rise(&col4p);

    // Set falling edge interrupts on the rows
    row1.fall(&colr);
    row2.fall(&colr);
    row3.fall(&colr);
    row4.fall(&colr);

    // Scan to find what has been pressed
    scantick.attach(&colscanner,0.004);
   
    while(1)
    {

    }

}
