#include <msp430.h> 
#include <stdint.h>
#include <stdio.h>

#include "DS1307/DS1307.h"
#include "I2C/I2C.h"
#include "LCD/LCD.h"
#include "UART/UART.h"
#include "DS18B20/DS18B20.h"
#include "Capture/Capture.h"
#include "ADC10/ADC10.h"
#include "Button/Button.h"
#include "define.h"



#define Time_Blink_Cursor   100000

extern uint8_t Count_Display=0;
uint8_t Mode = 0;
extern uint8_t Mode_Calib_Time=0;

float Temperature;

uint16_t Heart_Beat;

unsigned char Read_Buffer[10];
int sec, min, hour, day , date , month, year;
unsigned char Write_Buffer[]={0x00,0x07,0x23,0x03,0x30,0x10,0x18};
//                             sec,min ,hour ,day,date,mon ,year


void Display(void);
void Display_Time(void);
void Display_Temp(void);
void Display_Heart_Beat(void);
void Display_Change_Time(void);


/**
 * main.c
 */

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    DCOCTL =CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 = SELM_0;

    Button_Init();


    LCD_Init();
    LCD_Clear();
    LCD_Home();

    Capture_Init();
    ADC10_Init();

    I2C_Init(DS1307);
//    I2C_Write(Time_Add,7,Write_Buffer);

    while(1)
    {
        Display();
    }
}

void Display(void)
{
    switch (Mode)
            {
                case Mode_Display_Time:
                {
                    Display_Time();
                    break;
                }
                case Mode_Display_Temp:
                {
                    Display_Temp();
                    break;
                }
                case Mode_Display_Heart_Beat:
                {
                    Display_Heart_Beat();
                    break;
                }
                case Mode_Change_Time:
                {
                    Display_Change_Time();
                    break;
                }
                default:
                {
                    break;
                }
            }
            Button_Detect_Mode();
}



void Display_Change_Time(void)
{


    LCD_Home();
    switch (Mode_Calib_Time)
        {
            case Mode_Change_Time_Hour:
            {
                LCD_Goto(2, 0);
                LCD_Put_String("hour");
                break;
            }
            case Mode_Change_Time_Min:
            {
                LCD_Goto(2, 0);
                LCD_Put_String("min");
                break;
            }
            case Mode_Change_Time_Sec:
            {
                LCD_Goto(2, 0);
                LCD_Put_String("sec");
                break;
            }
            case Mode_Change_Time_Day:
            {
                LCD_Goto(2, 0);
                LCD_Put_String("day");
                break;
            }
            case Mode_Change_Time_Date:
            {
                LCD_Goto(2, 0);
                LCD_Put_String("date");
                break;
            }
            case Mode_Change_Time_Mon:
            {
                LCD_Goto(2, 0);
                LCD_Put_String("mon");
                break;
            }
            case Mode_Change_Time_Year:
            {
                LCD_Goto(2, 0);
                LCD_Put_String("year");
                break;
            }
            default:
            {
                break;
            }
        }
}

void Display_Time(void)
{
    DS1307_Get_Time();
    LCD_Home();
    DS1307_LCD_Put_Time();
}

void Display_Temp(void)
{
    Temperature = DS18B20_Get_Temp();
    LCD_Home();
    LCD_Put_String("Temp:");
    LCD_Put_Float(Temperature, 4, 1);
    LCD_Put_Char(0xDF);
    LCD_Put_Char('C');
}

void Display_Heart_Beat(void)
{

    LCD_Home();
    LCD_Put_String("  Do nhip tim ");

    LCD_Goto(2,2);
    LCD_Put_String(" Nhan Start ");

    if((PORT_BUTTON_IN&PIN_BUTTON_START_PULSE_SENSOR)==0)
        {
            _delay_cycles(Time_Debounce*Freq_MHz);
            if((PORT_BUTTON_IN&PIN_BUTTON_START_PULSE_SENSOR)==0)
            {
                uint8_t i;
                for(i=20;i>0;i--)
                {
                    ADC10_Get_Value();
                    LCD_Goto(2, 3);
                    LCD_Put_String("Xin cho ");
                    LCD_Put_Un_Decimal(i, 2);
                    LCD_Put_String("s");

                    uint32_t k;
                    for(k=0;k<12000;k++)
                    {
                        ADC10_Get_Value();
                    }

//                    _delay_cycles(1000000*Freq_MHz);
                }

                LCD_Clear();
                if((Heart_Beat<40)||(Heart_Beat>120))
                {
                    LCD_Clear();
                    LCD_Home();
                    LCD_Put_String("Vui long thu lai");
                    _delay_cycles(4000000);
                    LCD_Clear();
                }
                else
                {
                    LCD_Clear();
                    LCD_Home();
                    LCD_Put_String("   Nhip tim: ");
                    LCD_Goto(2, 1);
                    LCD_Put_Decimal(Heart_Beat, 3);
                    LCD_Goto(2, 6);
                    LCD_Put_String("Nhip/phut");
                    _delay_cycles(4000000);
                    LCD_Clear();
                }
            }
        }

//    Heart_Beat = 0;
//    ADC10_Get_Value();
//    LCD_Goto(1,10);
//    LCD_Put_Decimal(Heart_Beat,3);

//    Button_Detect_Start_Pulse_Sensor();

//    uint8_t i;
//    for(i=5;i>0;i--)
//    {
//        LCD_Goto(2, 3);
//        LCD_Put_String("Xin cho ");
//        LCD_Put_Un_Decimal(i, 1);
//        LCD_Put_String("s");
//        _delay_cycles(1000000*Freq_MHz);
//    }

}



