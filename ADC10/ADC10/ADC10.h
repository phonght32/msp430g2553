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





uint16_t ADC_Result;

extern void ADC10_Init(void);
extern void ADC10_Start(void);


#endif /* ADC10_ADC10_H_ */
