#include <msp430.h>
#include <stdio.h>
#include <stdint.h>
#include "DS18B20/DS18B20.h"
#include "LCD/LCD.h"
#include "define.h"



/**
 * main.c
 */


float Temperature;
//volatile int ta = 0;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;

	DCOCTL =CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
	BCSCTL2 = SELM_0;

//	TA0CCTL0 = CCIE;
//	TA0CCR0 = 5000;                            //5ms with DCO = 1MHz
//	TA0CCR1 = 0;
//	TA0CCTL1 = OUTMOD_7;
//	TA0CTL = TASSEL_2 + MC_1;

	LCD_Init();
	LCD_Clear();
	LCD_Home();
	Temperature = DS18B20_Get_Temp();
	__bis_SR_register(GIE);

    while(1)
    {
        Temperature = DS18B20_Get_Temp();
        LCD_Clear();
        LCD_Home();
        LCD_Put_String("Temp:");
        LCD_Put_Float(Temperature, 4, 1);
        LCD_Put_Char(0xDF);
        LCD_Put_Char('C');
        _delay_cycles(1000000*Freq_MHz);
    }
}


//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void Timer_A0 (void)
//{
//  ta++;
//  if(ta==200)
//  {
//      Temperature = DS18B20_Get_Temp();
//      ta=0;
//  }
//}

