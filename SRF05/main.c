#include <msp430.h> 
#include "SRF05/SRF05.h"
#include "LCD/LCD.h"
#include "define.h"

/**
 * main.c
 */
float Distance;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	BCSCTL2 = SELM_0;

	SRF05_Init();

	LCD_Init();
	LCD_Clear();
	LCD_Home();
	LCD_Put_String("Range: ");
	LCD_Goto(1,14);
	LCD_Put_String("cm");
	while(1)
	{
	    LCD_Goto(1,6);
	    Distance= SRF05_Get_Range();
	    LCD_Put_Float(Distance, 6, 2);
	    _delay_cycles(100000*Freq_MHz);
	}
}
