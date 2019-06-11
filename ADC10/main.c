#include <msp430.h> 
#include "ADC10/ADC10.h"


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	BCSCTL2 = SELM_0;

	ADC10_Init();
	while(1)
	{
	    ADC10_Start();

	}
}
