/*
 * DS1307.c
 *
 *  Created on: 9 thg 7, 2018
 *      Author: Phong
 */

#include "DS1307.h"



extern void DS1307_Get_Time(void)
{
    I2C_Read(0x00,8,Read_Buffer);
    sec    =((Read_Buffer[0]&0xf0)>>4)*10 + (Read_Buffer[0]&0x0f);
    min    =((Read_Buffer[1]&0xf0)>>4)*10 + (Read_Buffer[1]&0x0f);
    hour   =((Read_Buffer[2]&0xf0)>>4)*10 + (Read_Buffer[2]&0x0f);
    day    =((Read_Buffer[3]&0xf0)>>4)*10 + (Read_Buffer[3]&0x0f);
    date   =((Read_Buffer[4]&0xf0)>>4)*10 + (Read_Buffer[4]&0x0f);
    month  =((Read_Buffer[5]&0xf0)>>4)*10 + (Read_Buffer[5]&0x0f);
    year   =((Read_Buffer[6]&0xf0)>>4)*10 + (Read_Buffer[6]&0x0f);
}



extern void DS1307_UART_Put_Time(void)
{
        UART_Put_Int(hour);
        UART_Put_String(" : ");
        UART_Put_Int(min);
        UART_Put_String(" : ");
        UART_Put_Int(sec);
        UART_Put_String(", ");
        UART_Put_String("Thu ");
        UART_Put_Int(day);
        UART_Put_String(", ");
        UART_Put_Int(date);
        UART_Put_String("/");
        UART_Put_Int(month);
        UART_Put_String("/20");
        UART_Put_Int(year);
        UART_Put_Char(10);
}




