/*
 * Button.c
 *
 *  Created on: Mar 19, 2019
 *      Author: Phong
 */


#include "Button.h"

extern void Button_Init(void)
{
    PORT_BUTTON_SEL  &=~ PIN_BUTTON;
    PORT_BUTTON_SEL2 &=~ PIN_BUTTON;
    PORT_BUTTON_DIR  &=~ PIN_BUTTON;
    PORT_BUTTON_REN  |=  PIN_BUTTON;    //Pull up register enable
    PORT_BUTTON_OUT  |=  PIN_BUTTON;
    PORT_BUTTON_IE   |=  PIN_BUTTON;
    PORT_BUTTON_IES  |=  PIN_BUTTON;    //Detect falling edge
    PORT_BUTTON_IFG  &=~ PIN_BUTTON;

    _bis_SR_register(GIE);
}

//#pragma vector = PORT1_VECTOR
//__interrupt void Button_Interrupt(void)
//{
//    if(PORT_BUTTON_IFG&PIN_BUTTON)
//    {
//        _delay_cycles(30000*Freq_MHz);
//        if(!(PORT_BUTTON_IN&PIN_BUTTON))
//        {
//            Led1_Red_On();
//        }
//    }
//    PORT_BUTTON_IFG &=~ PIN_BUTTON;
//}


