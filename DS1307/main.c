#include <msp430.h> 
#include "DS1307/DS1307.h"
#include "I2C/I2C.h"
#include "LCD/LCD.h"
#include "UART/UART.h"
#include "define.h"


/**
 * main.c
 */


int sec, min, hour, day , date , month, year;
unsigned char Write_Buffer[]={0x00,0x00,0x20,0x05,0x09,0x08,0x18};
//                             sec,min ,hour ,day,date,mon ,year
unsigned char Read_Buffer[10];


void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 = SELM_0;

    LCD_Init();
//    UART_Init();
    I2C_Init(DS1307);


    I2C_Write(Time_Add,7,Write_Buffer);
    while(1)
    {
        DS1307_Get_Time();
//        DS1307_UART_Put_Time();

//        LCD_Clear();
        LCD_Home();
        DS1307_LCD_Put_Time();
        _delay_cycles(500000*Freq_MHz);
    }
}
