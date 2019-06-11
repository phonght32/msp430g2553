#include <msp430.h> 
#include "PWM/PWM.h"


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PWM_Init();
	
	while(1)
	{

	}
}
