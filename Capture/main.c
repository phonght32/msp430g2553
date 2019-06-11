#include <msp430.h> 
#include "Capture/Capture.h"


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Capture_Init();
	while(1)
	{

	}
}
