#include <msp430.h> 
#include "LCD/LCD.h"
#include "define.h"

/**
 * main.c
 */



void main(void)
{
    unsigned int x=100;
    float y=1.2347;

    WDTCTL = WDTPW | WDTHOLD;           //Stop Watchdog
    DCOCTL = CALDCO_1MHZ;             // Clock=1Mhz
    BCSCTL1 = CALBC1_1MHZ;

    LCD_Init();

    while(1)
    {
//        LCD_Clear();
        LCD_Home();
        LCD_Put_String("Ho Thanh Phong");
        LCD_Goto(2,0);
        LCD_Put_Decimal(x,4);
        LCD_Goto(2,8);
        LCD_Put_Float(y,5,3);


        _delay_cycles(100000*Freq_MHz);
    }
}
