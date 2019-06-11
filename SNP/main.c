#include <msp430.h> 
#include <stdint.h>

#include "LED/LED.h"
#include "Button/Button.h"
#include "define.h"


uint8_t status=0;
void Display_Status_0(void);
void Display_Status_1(void);
void Display_Status_2(void);
void Display_Status_3(void);
void Display_Status_4(void);
void Display_Status_5(void);
void Display_Status_6(void);

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALBC1_1MHZ;
	
	Led_Init();
	Button_Init();
	P1OUT = 0xff;
	P2OUT = 0xff;

	_bis_SR_register(GIE);

	while(1)
	{
//        LedAll_Red_On();
//        _delay_cycles(500000);
//        LedAll_Red_Off();
//        _delay_cycles(500000);
//
//        LedAll_Green_On();
//        _delay_cycles(500000);
//        LedAll_Green_Off();
//        _delay_cycles(500000);
//
//	    LedAll_Blue_On();
//	    _delay_cycles(500000);
//        LedAll_Blue_Off();
//        _delay_cycles(500000);
//
//        LedAll_White_On();
//        _delay_cycles(500000);
//        LedAll_White_Off();
//        _delay_cycles(500000);
//
//        LedAll_Yellow_On();
//        _delay_cycles(500000);
//        LedAll_Yellow_Off();
//        _delay_cycles(500000);


	    switch (status)
	    {
            case 0:
            {
                Display_Status_0();
                break;
            }
            case 1:
            {
                Display_Status_1();
                break;
            }
            case 2:
            {
                Display_Status_2();
                break;
            }
            case 3:
            {
                Display_Status_3();
                break;
            }
            case 4:
            {
                Display_Status_4();
                break;
            }
            case 5:
            {
                Display_Status_5();
                break;
            }
        }
	}
}
void Display_Status_0(void)
{
    LedAll_Blue_On();
}
void Display_Status_1(void)
{
    LedAll_Green_On();
}
void Display_Status_2(void)
{
    LedAll_Red_On();
}
void Display_Status_3(void)
{
    LedAll_White_On();
}
void Display_Status_4(void)
{
    LedAll_Yellow_On();
}
void Display_Status_5(void)
{
    LedAll_Red_On();
}
void Display_Status_6(void)
{
    LedAll_Celadon_On();
    _delay_cycles(500000);
    LedAll_Celadon_Off();

    LedAll_Green_On();
    _delay_cycles(500000);
    LedAll_Green_Off();

    LedAll_Blue_On();
    _delay_cycles(500000);
    LedAll_Blue_Off();

    LedAll_Red_On();
    _delay_cycles(500000);
    LedAll_Red_Off();

    LedAll_White_On();
    _delay_cycles(500000);
    LedAll_White_Off();
}
#pragma vector = PORT1_VECTOR
__interrupt void Button_Interrupt(void)
{
    if(PORT_BUTTON_IFG&PIN_BUTTON)
    {
        _delay_cycles(30000*Freq_MHz);
        if(!(PORT_BUTTON_IN&PIN_BUTTON))
        {
            status++;
            if(status>4)
            {
                status = 0;
            }
        }
    }
    LedOffAll();
    PORT_BUTTON_IFG &=~ PIN_BUTTON;
}
