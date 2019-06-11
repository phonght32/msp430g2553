#include <msp430.h> 
#include "UART/UART.h"


/**
 * main.c
 */


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 = SELM_0;

    P1DIR |= BIT0 + BIT6;
    P1OUT &=~(BIT0 + BIT6);

    UART_Init();
    while(1)
    {
        UART_Put_String("Ho Thanh Phong \n");
        _delay_cycles(1000000);
    }
}
