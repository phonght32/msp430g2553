#include <msp430.h> 
#include <stdint.h>
#include "SPI/SPI.h"


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	BCSCTL2 = SELM_0;
	SPI_A_Init();
	
	while(1)
	{

	}
}
