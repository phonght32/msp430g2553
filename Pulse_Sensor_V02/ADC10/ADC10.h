/*
 * ADC10.h
 *
 *  Created on: Sep 5, 2018
 *      Author: Phong
 */

#include <msp430.h>
#include <stdint.h>

#ifndef ADC10_ADC10_H_
#define ADC10_ADC10_H_

#define PORT_CREATE_PULSE_SEL   P1SEL
#define PORT_CREATE_PULSE_SEL2  P1SEL2
#define PORT_CREATE_PULSE_DIR   P1DIR
#define PORT_CREATE_PULSE_OUT   P1OUT

#define PIN_CREATE_PULSE        BIT5

uint16_t ADC_Result;

extern void ADC10_Init(void);
extern void ADC10_Get_Value(void);


#endif /* ADC10_ADC10_H_ */
