/*
 * Joystick.h
 *
 *  Created on: Sep 11, 2018
 *      Author: ThanhPhong
 */

#include <msp430.h>
#include <stdint.h>
#include "../ADC10/ADC10.h"
#include "../LCD/LCD.h"
#include "../Button/Button.h"


#ifndef JOYSTICK_JOYSTICK_H_
#define JOYSTICK_JOYSTICK_H_


#define Channel_ADC10_Joystick_VRx    INCH_4
#define Channel_ADC10_Joystick_VRy    INCH_3
#define Joystick_VRx    4
#define Joystick_VRy    3


uint8_t Channel_ADC10;
uint16_t ADC10_Result_VRx;
uint16_t ADC10_Result_VRy;


extern void Joystick_Init(void);
extern void Joystick_Start(void);





#endif /* JOYSTICK_JOYSTICK_H_ */
