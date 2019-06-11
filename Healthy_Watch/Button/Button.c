/*
 * Button.c
 *
 *  Created on: Sep 6, 2018
 *      Author: Phong
 */

#include "Button.h"

extern void Button_Init(void)
{
    PORT_BUTTON_SEL &=~ (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
    PORT_BUTTON_SEL2 &=~ (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
    PORT_BUTTON_DIR &=~ (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
    PORT_BUTTON_REN |= (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
    PORT_BUTTON_OUT |= (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);

//    PORT_BUTTON_IE |= (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
//    PORT_BUTTON_IES |= (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE); //NGAT CANH XUONG
//    PORT_BUTTON_IFG &=~ (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
    __enable_interrupt();
    __bis_SR_register(GIE);
}



//extern void Button_Detect_Mode(void)
//{
//    if((PORT_BUTTON_IN&PIN_BUTTON_MODE)==0)
//    {
//        _delay_cycles(500000*Freq_MHz);
//        if((PORT_BUTTON_IN&PIN_BUTTON_MODE)==0)
//        {
//            Mode++;
//            if(Mode>2)
//                Mode = 0;
//        }
//        LCD_Clear();
//    }
//}

extern void Button_Detect_Mode(void)
{
    if(Mode==Mode_Display_Time)
    {
        if((PORT_BUTTON_IN&PIN_BUTTON_CHANGE_TIME)==0)
        {
            _delay_cycles(Time_Debounce*Freq_MHz);
            if((PORT_BUTTON_IN&PIN_BUTTON_CHANGE_TIME)==0)
            {
//                _delay_cycles(Time_Debounce*Freq_MHz);
//                if((PORT_BUTTON_IN&PIN_BUTTON_CHANGE_TIME)==0)
//                {
//                    Mode=Mode_Change_Time;
//                    Button_Interrupt_En();
//                    LCD_Clear();
//                }
//                else
//                {
//                    Mode++;
//                    if(Mode>1)
//                        Mode = 0;
//                }

                Mode++;
                if(Mode>1)
                    Mode = 0;
                LCD_Clear();
            }
        }
    }

//    else if(Mode==Mode_Change_Time)
//    {
//
//    }

    else
    {
        if((PORT_BUTTON_IN&PIN_BUTTON_MODE)==0)
        {
            _delay_cycles(Time_Debounce*Freq_MHz);
            if((PORT_BUTTON_IN&PIN_BUTTON_MODE)==0)
            {
                Mode++;
                if(Mode>1)
                    Mode = 0;
            }
            LCD_Clear();
        }
    }
}
extern void Button_Detect_Start_Pulse_Sensor(void)
{
    if((PORT_BUTTON_IN&PIN_BUTTON_START_PULSE_SENSOR)==0)
    {
        _delay_cycles(Time_Debounce*Freq_MHz);
        if((PORT_BUTTON_IN&PIN_BUTTON_START_PULSE_SENSOR)==0)
        {
            uint8_t i;
            for(i=5;i>0;i--)
            {
//                ADC10_Get_Value();
                LCD_Goto(2, 3);
                LCD_Put_String("Xin cho ");
                LCD_Put_Un_Decimal(i, 1);
                LCD_Put_String("s");
                _delay_cycles(1000000*Freq_MHz);
            }
            LCD_Clear();
            LCD_Home();
            LCD_Put_String("Nhip tim: ");
//            LCD_Put_Decimal(Heart_Beat, 3)
        }
    }

}


extern void Button_Interrupt_En(void)
{
    PORT_BUTTON_IE |= (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
    PORT_BUTTON_IES |= (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE); //NGAT CANH XUONG
    PORT_BUTTON_IFG &=~ (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
}

extern void Button_Interrupt_Dis(void)
{
    PORT_BUTTON_IE &=~ (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
}

//#pragma vector = PORT1_VECTOR
//__interrupt void Button_Interrupt(void)
//{
//    if(PORT_BUTTON_IFG&PIN_BUTTON_CHANGE_TIME)
//    {
//         Mode_Calib_Time++;
//         Count_Display=0;
//         if(Mode_Calib_Time>7)
//         {
//             Mode_Calib_Time=1;
//         }
//    }
//    LCD_Clear();
//    PORT_BUTTON_IFG &=~ (PIN_BUTTON_CHANGE_TIME+PIN_BUTTON_START_PULSE_SENSOR+PIN_BUTTON_MODE);
//}


