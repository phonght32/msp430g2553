/*
 * DS1307.h
 *
 *  Created on: 9 thg 7, 2018
 *      Author: Phong
 */

#include "../I2C/I2C.h"
#include "../UART/UART.h"
//#include "../LCD/LCD.h"

#ifndef DS1307_DS1307_H_
#define DS1307_DS1307_H_

#define DS1307 0x68
#define Time_Add 0x00

extern int sec, min, hour, day , date , month, year;
extern unsigned char Write_Buffer[];
extern unsigned char Read_Buffer[10];



extern void DS1307_Get_Time(void);
extern void DS1307_UART_Put_Time(void);



#endif /* DS1307_DS1307_H_ */
