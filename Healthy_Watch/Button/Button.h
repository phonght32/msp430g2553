/*
 * Button.h
 *
 *  Created on: Sep 6, 2018
 *      Author: Phong
 */
#include <msp430.h>
#include <stdint.h>
#include "../define.h"
#include "../LCD/LCD.h"
//#include "../ADC10/ADC10.h"

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#define Time_Debounce               600000

#define Mode_Display_Time           0
#define Mode_Display_Temp           9
#define Mode_Display_Heart_Beat     1
#define Mode_Change_Time            3

#define Mode_Change_Time_Hour       1
#define Mode_Change_Time_Min        2
#define Mode_Change_Time_Sec        3
#define Mode_Change_Time_Day        4
#define Mode_Change_Time_Date       5
#define Mode_Change_Time_Mon        6
#define Mode_Change_Time_Year       7

#define PORT_BUTTON_SEL             P1SEL
#define PORT_BUTTON_SEL2            P1SEL2
#define PORT_BUTTON_DIR             P1DIR
#define PORT_BUTTON_IN              P1IN
#define PORT_BUTTON_OUT             P1OUT
#define PORT_BUTTON_IE              P1IE
#define PORT_BUTTON_IES             P1IES
#define PORT_BUTTON_IFG             P1IFG
#define PORT_BUTTON_REN             P1REN

#define PIN_BUTTON_START_PULSE_SENSOR               BIT3
#define PIN_BUTTON_DEC                              BIT0
#define PIN_BUTTON_CHANGE_TIME                      BIT1
#define PIN_BUTTON_MODE                             BIT1

extern uint8_t Mode;
extern uint8_t Mode_Calib_Time;
extern uint8_t Count_Display;



extern void Button_Init(void);
extern void Button_Detect_Mode(void);
extern void Button_Interrupt_En(void);
extern void Button_Interrupt_Dis(void);
extern void Button_Detect_Start_Pulse_Sensor(void);



#endif /* BUTTON_BUTTON_H_ */
