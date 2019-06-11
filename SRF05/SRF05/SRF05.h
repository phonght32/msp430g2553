/*
 * SRF05.h
 *
 *  Created on: Aug 15, 2018
 *      Author: Phong
 */
#include <msp430.h>
#include <stdint.h>
#include "../define.h"

#ifndef SRF05_SRF05_H_
#define SRF05_SRF05_H_


uint8_t Falling_Rising_Edge;
float Time_Echo;
uint8_t Data_Ready;
float Range;


#define PORT_SRF05_DIR      P1DIR
#define PORT_SRF05_IN       P1IN
#define PORT_SRF05_OUT      P1OUT
#define PORT_SRF05_SEL      P1SEL
#define PORT_SRF05_SEL2     P1SEL2

#define PIN_SRF05_TRIG      BIT0
#define PIN_SRF05_ECHO      BIT2

extern void SRF05_Init(void);
extern float SRF05_Get_Range(void);
extern void SRF05_Process(void);



#endif /* SRF05_SRF05_H_ */
