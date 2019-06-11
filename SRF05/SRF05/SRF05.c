/*
 * SRF05.c
 *
 *  Created on: Aug 15, 2018
 *      Author: Phong
 */

#include "SRF05.h"


extern float SRF05_Get_Range(void)
{
    Data_Ready=0;
    Falling_Rising_Edge =1;

    PORT_SRF05_OUT |= PIN_SRF05_TRIG;
    _delay_cycles(20*Freq_MHz);
    PORT_SRF05_OUT &=~ PIN_SRF05_TRIG;

    while(!Data_Ready)
    {

    }
    Data_Ready=0;
    Range = Time_Echo/58;
    return Range;
}

extern void SRF05_Init(void)
{
    PORT_SRF05_SEL &=~ PIN_SRF05_TRIG;
    PORT_SRF05_SEL2 &=~ PIN_SRF05_TRIG;
    PORT_SRF05_DIR |= PIN_SRF05_TRIG;
    PORT_SRF05_OUT &=~ PIN_SRF05_TRIG;

    PORT_SRF05_SEL |= PIN_SRF05_ECHO;
    PORT_SRF05_SEL2 &=~ PIN_SRF05_ECHO;
    PORT_SRF05_DIR &=~ PIN_SRF05_ECHO;

    TA0CTL = TASSEL_2 + MC_2 + TAIE;
    TA0CCTL1 |= CM_3 +CCIS_0+CAP+CCIE;
    _BIS_SR(GIE);
}

extern void SRF05_Process(void)
{
    if(Falling_Rising_Edge) //rising edge
    {
        TA0R = 0;
        Falling_Rising_Edge = 0;
    }
    else
    {
        Time_Echo = TA0CCR1 ;
        Falling_Rising_Edge = 1;
        Data_Ready=1;
    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void SRF05_Echo_Int(void)
{
    switch(TA0IV)
    {
        case TA0IV_TACCR1 :
        {
            SRF05_Process();
            break;
        }
    }
}

