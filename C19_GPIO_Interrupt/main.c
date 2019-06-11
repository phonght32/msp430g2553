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
    // cho phep ngat canh xuong
    P1IE |= BIT3;
    P1IES |= BIT3;
    P1IFG &=~ BIT3;
    _bis_SR_register(GIE);

    while(1)
    {

    }
}

//chuong trinh phuc vu ngat
#pragma vector = PORT1_VECTOR
__interrupt void Button_Int(void)
{
    if(P1IFG&BIT3)      //kiem tra co ngat
    {
        _delay_cycles(3000);
        if(!(P1IN&BIT3))
        {
            P1OUT ^= BIT0;
        }
    }
    P1IFG &=~ BIT3;     //xoa co ngat
}
