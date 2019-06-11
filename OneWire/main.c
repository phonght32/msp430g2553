#include <msp430.h> 
#include "OneWire/OneWire.h"


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
}
