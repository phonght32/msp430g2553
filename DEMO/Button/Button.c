/*
 * Button.c
 *
 *  Created on: Nov 4, 2018
 *      Author: Phong
 */

#include "Button.h"

void Button_Init(void)
{
    PORT_BUTTON_SEL &=~ PIN_BUTTON;
    PORT_BUTTON_SEL &=~ PIN_BUTTON;

    PORT_BUTTON_DIR &=~ PIN_BUTTON;
    PORT_BUTTON_REN |= PIN_BUTTON;
    PORT_BUTTON_OUT |= PIN_BUTTON;

    PORT_BUTTON_IE |= PIN_BUTTON;
    PORT_BUTTON_IES |= PIN_BUTTON;
}


