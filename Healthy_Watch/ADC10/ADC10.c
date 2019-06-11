/*
 * ADC10.c
 *
 *  Created on: Sep 5, 2018
 *      Author: Phong
 */
#include "ADC10.h"

extern void ADC10_Init(void)
{
    ADC10CTL0 = SREF_0 + ADC10SHT_1 + ADC10ON;
    ADC10CTL1 = INCH_4 + ADC10DIV_1 + ADC10SSEL_3;
    ADC10AE0 |= BIT0;

    PORT_CREATE_PULSE_SEL &=~ PIN_CREATE_PULSE;
    PORT_CREATE_PULSE_SEL2 &=~ PIN_CREATE_PULSE;
    PORT_CREATE_PULSE_DIR |= PIN_CREATE_PULSE;
}
extern void ADC10_Get_Value(void)
{
    ADC10CTL0 |= ADC10SC +ENC;
    while(ADC10BUSY&ADC10CTL1);
    ADC_Result = ADC10MEM;
    if(ADC_Result>700)
           {
                PORT_CREATE_PULSE_OUT |= PIN_CREATE_PULSE;
                _delay_cycles(3000);
           }
    else
                PORT_CREATE_PULSE_OUT &=~ PIN_CREATE_PULSE;
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_Interrupt(void)
{
    ADC_Result = ADC10MEM;
    if(ADC_Result>800)
           {
                PORT_CREATE_PULSE_OUT |= PIN_CREATE_PULSE;
                _delay_cycles(3000);
           }
    else
                PORT_CREATE_PULSE_OUT &=~ PIN_CREATE_PULSE;
    _bic_SR_register_on_exit(LPM0_bits);
}

