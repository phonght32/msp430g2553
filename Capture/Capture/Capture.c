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
//        PORT_CAPTURE_REN |= PIN_CAPTURE;
//        PORT_CAPTURE_OUT &=~ PIN_CAPTURE;


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
            break;
        }
        case 2 :
        {
            loop++;

            break;
        }
        default:
            break;
    }
}


