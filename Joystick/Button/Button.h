/*
 * Button.h
 *
 *  Created on: Sep 6, 2018
 *      Author: Phong
 */
#include <msp430.h>
#include <stdint.h>
#include "../define.h"

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_



#define PORT_BUTTON_SEL     P1SEL
#define PORT_BUTTON_SEL2    P1SEL2
#define PORT_BUTTON_DIR     P1DIR
#define PORT_BUTTON_IN      P1IN
#define PORT_BUTTON_OUT     P1OUT
#define PORT_BUTTON_IE      P1IE
#define PORT_BUTTON_IES     P1IES
#define PORT_BUTTON_IFG     P1IFG
#define PORT_BUTTON_REN     P1REN

#define PIN_BUTTON_INC      BIT1
#define PIN_BUTTON_DEC      BIT0
#define PIN_BUTTON_MODE     BIT5

extern uint8_t Mode;


extern void Button_Init(void);



#endif /* BUTTON_BUTTON_H_ */
