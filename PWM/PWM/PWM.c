/*
 * PWM.c
 *
 *  Created on: Aug 14, 2018
 *      Author: Phong
 */

#include "PWM.h"


extern void PWM_Init(void)
{
    P1DIR |= BIT6;
    P1SEL |= BIT6;
    P1SEL2 &=~ BIT6;

    TA0CTL |= TASSEL_2 + MC_1;
    TA0CCTL1 |= OUTMOD_7;
    TACCR0 = 1000;
    TACCR1 = 20;
}
