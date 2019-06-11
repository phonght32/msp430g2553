/*
 * Led.c
 *
 *  Created on: Nov 4, 2018
 *      Author: Phong
 */

#include "Led.h"


void Led_Init(void)
{
    PORT_LED_SEL &=~ (LED_GREEN+LED_RED);
    PORT_LED_SEL2 &=~ (LED_GREEN+LED_RED);

    PORT_LED_DIR |= (LED_GREEN+LED_RED);
    PORT_LED_OUT &=~ (LED_GREEN+LED_RED);
}



