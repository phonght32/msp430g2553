/*
 * Capture.c
 *
 *  Created on: Sep 5, 2018
 *      Author: Phong
 */

#include "Capture.h"
extern void Capture_Init(void)
{
        PORT_CAPTURE_SEL |= PIN_CAPTURE;
        PORT_CAPTURE_SEL2 &=~ PIN_CAPTURE;
        PORT_CAPTURE_DIR &=~ PIN_CAPTURE;

//        P1IE |=BIT2;
//        P1IFG &=~ BIT2;

        TA0CTL = TASSEL_2 + MC_2 + TAIE;
        TA0CCTL1 |= CM_1 +CCIS_0+CAP+CCIE;
        TA0R =0;
        _BIS_SR(GIE);
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TA0IV_Interrupt (void)
{
    switch(TA0IV)
    {
        case 10 :          //tran timer
        {
            Timer_Over_Flow++;
            break;
        }
        case 2 :
        {
            double Capture_Value;

                 Capture_Value = TACCR1+Timer_Over_Flow*65536;
                 TA0R = 0;
                 Timer_Over_Flow=0;
                 Heart_Beat= 60/(Capture_Value/1000000);
        }
    }
}


