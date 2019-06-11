#include <msp430.h>
#include <stdio.h>
#include <stdint.h>
#include "ADC10/ADC10.h"
#include "LCD/LCD.h"
#include "Capture/Capture.h"
#include "define.h"

uint16_t Heart_Beat;

void main()
{
       WDTCTL = WDTPW | WDTHOLD;
       DCOCTL = CALDCO_1MHZ;
       BCSCTL1 = CALBC1_1MHZ;

       Capture_Init();
       ADC10_Init();

       LCD_Init();
       LCD_Clear();
       LCD_Home();
       LCD_Put_String("Heart Beat: ");
       LCD_Goto(2,4);
       LCD_Put_String("PIF.C17");

       while(1)
       {
           ADC10_Get_Value();
//           ADC10CTL0 |= ENC + ADC10SC;
//           _bis_SR_register(LPM0_bits + GIE);
           LCD_Goto(1,11);
           LCD_Put_Decimal(Heart_Beat,3);
       }
}








