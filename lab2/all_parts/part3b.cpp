/*
ese519-lab2-part3b
	Vaibhav N. Bhat (vaibhavn@seas)
	Shanjit S. Jajmann (sjajmann@seas)

Making the keypad work via scanning.
Part 3(a) has been shown via a fritzing diagram. 
Both Part 3(a) and 3(b) have been used to complete Part 4 of the lab

*/

#include "mbed.h"
#include "PwmOut.h"
#define ARR_SIZE 12

// Set the pin configuration
PwmOut pin23(p23);
PwmOut pin24(p24);
PwmOut pin25(p25);
Serial pc(USBTX, USBRX);

// Define a timeout
Timeout flipper;

// Make a ticker
Ticker int_stop;

int flag=0;

/*

Hardware Keypad connections
pin 1 - p11 => row 2
pin 2 - p12 => row 3
pin 3 - p13 => column 1
pin 4 - p14 => row 4
pin 5 - p15 => column 2
pin 6 - p16 => column 3
pin 7 - p17 => column 4
pin 8 - p18 => row 1

*/

// Define LEDs
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// Define the rows of the keypad
DigitalOut row1(p18);
DigitalOut row2(p11);
DigitalOut row3(p12);
DigitalOut row4(p14);

// Define the columns of the keypad
InterruptIn col1(p13);
InterruptIn col2(p15);
InterruptIn col3(p16);
InterruptIn col4(p17);

// Debug code to see interrupts on cols
void col1_rise_int()
{

 wait(0.01);
	
	if(col1==1)
	{
	led1 = 1;
	wait(0.1);
	led1 = 0; 


	}
	
	
}

// Debug code to see interrupts on cols
void col2_rise_int()
{
wait(0.01);
	
	if(col2==1)
	{
	led2 = 1;
	wait(0.1);
	led2 = 0;    
	
	}
	
	
}

// Debug code to see interrupts on cols
void col3_rise_int()
{
wait(0.01);
	
	if(col3==1)
	{
	led3 = 1;
	wait(0.1);
	led3 = 0;    
	
	}
	
	
}

// Debug code to see interrupts on cols
void col4_rise_int()
{
wait(0.01);
	
	if(col4==1)
	{
	 led4 = 1;
	wait(0.1);
	led4 = 0;   
	
	}
	
	
}

// Debug code to see interrupts on cols
void fall_int()
{
	led1=0;
	
	//printf("off");    
}


// Flip attached to ticker
void flip()
{
	if((col1==0)&&(col2==0)&&(col3==0)&&(col4==0)&&(flag==1))
	{
		flag = 0;    
		pin24 =0;
		pin25=0;
		
	}
}

int main() {
	
	// Ticker int_stop attached to flip for 10 uS
	// Sets the flag 0 periodically if columns are all zero 
	// and the flag was set initially
	int_stop.attach(&flip, 0.000010);
	

	// Make all Rows Low
	row1 = 0;
	row2 = 0;
	row3 = 0;
	row4 = 0;
	
	// switch off LEDs
	led1 = led2 = led3 = led4 = 0;

	// Infinite while(1) for implementing row scanning
	while(1) {
	
	// if flag is zero
	// check if any of the columns light up when row1 is kept HIGH
	if(flag==0)
	{
		row1 = 1;
		row2 = 0;
		row3 = 0;
		row4 = 0;
	
		if(col1==1)
		{ 
			wait(0.01); 
			if(col1==1)
				{
					pc.printf("1");  
					flag=1;
				}
		}
		else if (col2==1)
		{
		 	wait(0.01); 
	 	if(col2==1) 
	 		{
	 			pc.printf("2");   
	 			flag=1;
	 		}
		}
		else if (col3==1)
		{
			wait(0.01); 
	 		if(col3==1) 
	 			{
	 				pc.printf("3");   
	 				flag=1;
	 			}
		}
		else if (col4==1)
		{
			wait(0.01); 
	 		if(col4==1) 
	 			{
	 				pc.printf("A");   
	 				flag=1;
	 			}
		}
		
	}

	// if flag is zero
	// check if any of the columns light up when row2 is kept HIGH
	if(flag==0)
	{
		row1 = 0;
		row2 = 1;
		row3 = 0;
		row4 = 0;
	if(col1==1)
	{ 
	  	wait(0.01); 
 		if(col1==1) 
 			{	
 				pc.printf("4");  
 				flag=1;
 			}
	}
	else if (col2==1)
	{
	 	wait(0.01); 
 		if(col2==1) 
 			{
 				pc.printf("5");   
 				flag=1;
 			}
	}
	else if (col3==1)
	{
	 	wait(0.01); 
 		if(col3==1)
 			{ 
 				pc.printf("6");  
 				flag=1;
 			}
	}    
	else if (col4==1)
	{
	 	wait(0.01); 
 		if(col4==1) 
 			{
 				pc.printf("B");   
 				flag=1;
 			}

	}
	}

	// if flag is zero
	// check if any of the columns light up when row3 is kept HIGH
	if(flag==0)
	{
		row1 = 0;
		row2 = 0;
		row3 = 1;
		row4 = 0;

		if(col1==1)
		{ 
	 		wait(0.01); 
 			if(col1==1) 
 				{	
 					pc.printf("7"); 
 					flag=1;
 				}
		}
		else if (col2==1)
		{
	 		wait(0.01); 
 			if(col2==1) 
 				{
 					pc.printf("8");   
 					flag=1;
 				}
		}
		else if (col3==1)
		{
	 		wait(0.01); 
 			if(col3==1) 
 				{	
 					pc.printf("9"); 
 					flag=1;
 				}
		}    
		else if (col4==1)
		{
	 		wait(0.01); 
 			if(col4==1) 
 				{	
 					pc.printf("C"); 
 					flag=1;
 				}
		}
	}
	// if flag is zero
	// check if any of the columns light up when row4 is kept HIGH
	if(flag==0)
	{
		row1 = 0;
		row2 = 0;
		row3 = 0;
		row4 = 1;
		if(col1==1)
		{ 
		  	wait(0.01); 
	 		if(col1==1) 
	 			{
	 				pc.printf("*");  
	 				flag=1;
	 			}
		}
		else if (col2==1)
		{
			wait(0.01); 
	 		if(col2==1)
	 			{ 
	 				pc.printf("0"); 
	 				flag=1;
	 			}
		}
		else if (col3==1)
		{
		 	wait(0.01); 
	 		if(col3==1) 
	 		{
	 			pc.printf("#");  
	 			flag=1;
	 		}
		}    
		else if (col4==1)
		{
		 	wait(0.01); 
	 		if(col4==1) 
	 			{
	 				pc.printf("D");   
	 				flag=1;
	 			}

		}

		}
	
	}
}   