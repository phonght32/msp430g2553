/*
 * Capture.h
 *
 *  Created on: Sep 5, 2018
 *      Author: Phong
 */
#include <msp430.h>
#include <stdint.h>

#ifndef CAPTURE_CAPTURE_H_
#define CAPTURE_CAPTURE_H_

#define PORT_CAPTURE_SEL    P1SEL
#define PORT_CAPTURE_SEL2   P1SEL2
#define PORT_CAPTURE_DIR    P1DIR
#define PORT_CAPTURE_OUT    P1OUT
#define PORT_CAPTURE_IN     P1IN
#define PORT_CAPTURE_REN    P1REN

#define PIN_CAPTURE         BIT2

uint8_t loop;

extern void Capture_Init(void);



#endif /* CAPTURE_CAPTURE_H_ */
