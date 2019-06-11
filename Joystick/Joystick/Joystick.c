/*
 * Joystick.c
 *
 *  Created on: Sep 11, 2018
 *      Author: ThanhPhong
 */

#include "Joystick.h"

extern void Joystick_Init(void)
{
    ADC10_Init();
    Button_Init();
}
extern void Joystick_Start(void)
{
    ADC10_Start();
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_Interrupt(void)
{
    if(Channel_ADC10==Joystick_VRx)
    {
        ADC10_Result_VRx = ADC10MEM;

        ADC10CTL0 &=~ ENC;
        ADC10CTL1 &=~ Channel_ADC10_Joystick_VRx;
        ADC10CTL1 |= Channel_ADC10_Joystick_VRy;
        Channel_ADC10 = Joystick_VRy;

        LCD_Goto(2, 2);
        LCD_Put_Un_Decimal(ADC10_Result_VRx, 4);

        ADC10_Start();
    }
    else
    {
        ADC10_Result_VRy = ADC10MEM;

        ADC10CTL0 &=~ ENC;
        ADC10CTL1 &=~ Channel_ADC10_Joystick_VRy;
        ADC10CTL1 |= Channel_ADC10_Joystick_VRx;
        Channel_ADC10 = Joystick_VRx;

        LCD_Goto(2, 10);
        LCD_Put_Un_Decimal(ADC10_Result_VRy, 4);

        ADC10_Start();

    }
}
