#include <msp430.h>
#include <stdint.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    P1SEL = 0x00;
    P1SEL2 = 0x00;
    P1DIR |= 0xff;
    P1OUT = 0x00;

    P2SEL = 0x00;
    P2SEL2 = 0x00;
    P2DIR |= 0xff;
    P2OUT = 0x00;



    _bis_SR_register(GIE);

    while(1)
    {

    }

}
