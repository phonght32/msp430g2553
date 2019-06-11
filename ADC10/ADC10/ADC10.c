/*
 * ADC10.c
 *
 *  Created on: Sep 5, 2018
 *      Author: Phong
 */
#include "ADC10.h"

extern void ADC10_Init(void)
{
    ADC10CTL0 = SREF_0 + ADC10SHT_1 + ADC10ON +ADC10IE;
    ADC10CTL1 = INCH_4 + ADC10DIV_1 + ADC10SSEL_3;
    ADC10AE0 |= BIT0;
}

extern void ADC10_Start(void)
{
    ADC10CTL0 |= ENC + ADC10SC;
    _bis_SR_register(LPM0_bits + GIE);
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_Interrupt(void)
{
    ADC_Result = ADC10MEM;
    _bic_SR_register_on_exit(LPM0_bits);
}

