/*
 * Button.h
 *
 *  Created on: Mar 19, 2019
 *      Author: Phong
 */

#include <msp430.h>
#include "../define.h"
#include "../LED/LED.h"

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#define PORT_BUTTON_SEL   P1SEL
#define PORT_BUTTON_SEL2  P1SEL2
#define PORT_BUTTON_DIR   P1DIR
#define PORT_BUTTON_IN    P1IN
#define PORT_BUTTON_OUT   P1OUT
#define PORT_BUTTON_REN   P1REN
#define PORT_BUTTON_IE    P1IE
#define PORT_BUTTON_IES   P1IES
#define PORT_BUTTON_IFG   P1IFG

#define PIN_BUTTON        BIT6

extern void Button_Init(void);





#endif /* BUTTON_BUTTON_H_ */
