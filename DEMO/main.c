#include <msp430.h> 
#include <stdint.h>

#include "Button/Button.h"
#include "Led/Led.h"

#define     Freq_Mhz    1       //tan so hoat dong (MHz),hay tim hieu cong dung cua Freq_Mhz ?


uint8_t Mode = 0;
/*
 *  Mode = x    : hien thi trang thai thu x
 */


void Clock_Init(void);          //ham khoi tao xung clock

void Display_State_0(void);     //sang ca 2 led
void Display_State_1(void);     //sang led xanh, tat led do
void Display_State_2(void);     //sang led do, tat led xanh
void Display_State_3(void);     //sang tat 2 led luan phien 0.5s

/*
toan tu dich bit la :
	>> : dich sang phai
	<< : dich sang trai
	Cac ban hay tim hieu, sau do dung them cau truc vong lap for 
	de viet hieu ung cho led chay tu trai sai phai hoac phai sang trai
*/


/**
 * main.c
 */



void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	Clock_Init();               //goi ham khoi tao Clock

	Button_Init();              //goi ham khoi tao nut nhan
    Led_Init();                 //goi ham khoi tao Led

	_bis_SR_register(GIE);      //cho phep ngat

	while(1)
	{
	    //dung cau truc switch_case de xet gia tri cua Mode
	    switch (Mode)
	    {
	        case 0:
	        {
	            Display_State_0();
	        }

            case 1:
            {
                Display_State_1();
                break;
            }

            case 2:
            {
                Display_State_2();
                break;
            }

            case 3:
            {
                Display_State_3();
                break;
            }


            default:
            {
                P1OUT &=~ (LED_GREEN+LED_RED);
                break;
            }

        }

	}
}

void Display_State_0(void)
{
    PORT_LED_OUT |= (LED_GREEN+LED_RED);
}

void Display_State_1(void)
{
    PORT_LED_OUT &=~ LED_RED;
    PORT_LED_OUT |= LED_GREEN;
}
void Display_State_2(void)
{
    PORT_LED_OUT &=~ LED_GREEN;
    PORT_LED_OUT |= LED_RED;
}
void Display_State_3(void)
{
    PORT_LED_OUT ^= (LED_RED+LED_GREEN);
    _delay_cycles(500000*Freq_Mhz);
}

void Clock_Init(void)
{
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
}

#pragma vector = PORT1_VECTOR                   //dia chi vector ngat
__interrupt void Button_Interrupt(void)
{
    if(PORT_BUTTON_IFG&PIN_BUTTON)              //kiem tra co ngat
    {
        _delay_cycles(5000*Freq_Mhz);           //dung delay de chong rung nut nhan
        if((PORT_BUTTON_IN&PIN_BUTTON)==0)
        {
            Mode =  Mode + 1;                   //neu nut nhan P1.3 duoc nhan thi tang gia tri Mode len 1
            if(Mode>3)                          //het mode de hien thi se quay tro ve trang thai ban dau: khong lam gi ca
            {
                Mode = 0;
            }
        }
    }

    PORT_BUTTON_IFG &=~ (PIN_BUTTON);           //ngat xong phai xoa co ngat
}
