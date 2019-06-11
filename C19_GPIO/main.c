#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    // stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	 // chon cau hinh GPIO cho P1.3
	P1SEL &=~ BIT0+BIT3;
	P1SEL2 &=~ BIT0+BIT3;

	// cau hinh input/output
	P1DIR &=~ BIT3;
	P1DIR |= BIT0;

	// cai dat dien tro keo len
	P1REN |= BIT3;
	P1OUT |= BIT3;
	
	while(1)
	{
	    if(!(P1IN&BIT3))
	    {
	        _delay_cycles(3000);
	        if(!(P1IN&BIT3))
	        {
	            P1OUT |= BIT0;
	        }

	    }
	    else
	    {
	        P1OUT &=~ BIT0;
	    }
	    /*
	     * Nhung cau lenh thuc hien rat lau 10s
	     */
	}
}
