#include <msp430.h> 
#include <stdint.h>
#include "Joystick/Joystick.h"
#include "LCD/LCD.h"


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	DCOCTL = CALBC1_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	BCSCTL2 = SELM_0;

	LCD_Init();
	LCD_Clear();
	LCD_Home();
	
	LCD_Goto(2,0);
	LCD_Put_String("X:");
    LCD_Goto(2,8);
    LCD_Put_String("Y:");

    Joystick_Init();
    Joystick_Start();

    while(1)
    {

    }
}
