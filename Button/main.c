#include <msp430.h> 
#include "Button/Button.h"

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    DCOCTL =CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 = SELM_0;

    Button_Init();

    P1SEL &=~ (BIT0+BIT6);
    P1SEL2 &=~ (BIT0+BIT6);
    P1DIR |= (BIT0+BIT6);
    P1OUT &=~ (BIT0+BIT6);

    while(1)
    {

    }
	

}
