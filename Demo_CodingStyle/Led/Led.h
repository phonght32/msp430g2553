/*
 * Led.h
 *
 *  Created on: Nov 4, 2018
 *      Author: Phong
 */

#include <msp430.h>

#ifndef LED_LED_H_
#define LED_LED_H_

#define LED_RED         BIT0
#define LED_GREEN       BIT6

#define PORT_LED_SEL    P1SEL
#define PORT_LED_SEL2   P1SEL2
#define PORT_LED_DIR    P1DIR
#define PORT_LED_REN    P1REN
#define PORT_LED_IN     P1IN
#define PORT_LED_OUT    P1OUT

void Led_Init(void);                //ham con khoi tao led



#endif /* LED_LED_H_ */
