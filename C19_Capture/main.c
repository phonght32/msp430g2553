/*
 * main.c
 *
 */
#include <msp430.h>

int cap_value;
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;               //Tat watchdogtimer
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    TA0CTL = TASSEL_2 + MC_2;               //Chon clocktimer = 1Mhz, Cont.up mode
    TA0CCTL1 |= CM_1+CCIS_0+CAP+CCIE;       // Config CCR1 la capture : kich canh len
                                            //Channel A, capture mode, enable ngat
    TA0R =0;

    P1SEL |= BIT2;                          //Config pin thanh chan capture theo ccr1
    P1SEL2 &=~BIT2;                         //Xem datasheet de biet pin nao co kha nang
    P1DIR &=~BIT2;                          //capture

    _BIS_SR(LPM0_bits + GIE);               //Low-power mode + enable ngat toan cuc
}
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TA0IV_Interrupt (void)
{
    switch(TA0IV)
    {
        case TA0IV_TACCR1:
        {
            cap_value = TA0CCR1;                //Lay gia tri capture vo bien cap_value
            TA0R =0;                            //Reset bo dem timer
            break;
        }
    }
}

