/*
 * UART.h
 *
 *  Created on: 9 thg 7, 2018
 *      Author: Phong
 */
#include <msp430.h>

#ifndef UART_UART_H_
#define UART_UART_H_

extern void UART_Init(void);
extern void UART_Put_Int(unsigned long n);
extern void UART_Put_Char(char chr);
extern void UART_Put_String(char *str);
extern char UART_Get_Char();
extern void UART_Get_String(char *str);

#endif /* UART_UART_H_ */
