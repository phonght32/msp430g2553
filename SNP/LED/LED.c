/*
 * LED.c
 *
 *  Created on: Mar 19, 2019
 *      Author: Phong
 */

#include "LED.h"

extern void Led_Init(void)
{
    //Led 1 Init
    PORT_LED1_SEL  &=~ (PIN_LED1_RED + PIN_LED1_GREEN  +PIN_LED1_BLUE);
    PORT_LED1_SEL2 &=~ (PIN_LED1_RED + PIN_LED1_GREEN  +PIN_LED1_BLUE);
    PORT_LED1_DIR  |=  (PIN_LED1_RED + PIN_LED1_GREEN  +PIN_LED1_BLUE);

    //Led 2 Init
    PORT_LED2_SEL  &=~ (PIN_LED2_RED + PIN_LED2_GREEN  +PIN_LED2_BLUE);
    PORT_LED2_SEL2 &=~ (PIN_LED2_RED + PIN_LED2_GREEN  +PIN_LED2_BLUE);
    PORT_LED2_DIR  |=  (PIN_LED2_RED + PIN_LED2_GREEN  +PIN_LED2_BLUE);

    //Led 3 Init
    PORT_LED3_SEL  &=~ (PIN_LED3_RED + PIN_LED3_GREEN  +PIN_LED3_BLUE);
    PORT_LED3_SEL2 &=~ (PIN_LED3_RED + PIN_LED3_GREEN  +PIN_LED3_BLUE);
    PORT_LED3_DIR  |=  (PIN_LED3_RED + PIN_LED3_GREEN  +PIN_LED3_BLUE);

    //Led 4 Init
    PORT_LED4_SEL  &=~ (PIN_LED4_RED + PIN_LED4_GREEN  +PIN_LED4_BLUE);
    PORT_LED4_SEL2 &=~ (PIN_LED4_RED + PIN_LED4_GREEN  +PIN_LED4_BLUE);
    PORT_LED4_DIR  |=  (PIN_LED4_RED + PIN_LED4_GREEN  +PIN_LED4_BLUE);
}

/*
 * Led 1 Color
 */
extern void Led1_Red_On(void)
{
    PORT_LED1_OUT &=~ PIN_LED1_RED;
}
extern void Led1_Red_Off(void)
{
    PORT_LED1_OUT |= PIN_LED1_RED;
}
extern void Led1_Green_On(void)
{
    PORT_LED1_OUT &=~ PIN_LED1_GREEN;
}
extern void Led1_Green_Off(void)
{
    PORT_LED1_OUT |= PIN_LED1_GREEN;
}
extern void Led1_Blue_On(void)
{
    PORT_LED1_OUT &=~ PIN_LED1_BLUE;
}
extern void Led1_Blue_Off(void)
{
    PORT_LED1_OUT |= PIN_LED1_BLUE;
}
extern void Led1_White_On(void)
{
    PORT_LED1_OUT &=~ PIN_LED1_RED + PIN_LED1_GREEN + PIN_LED1_BLUE;
}
extern void Led1_White_Off(void)
{
    PORT_LED1_OUT |= PIN_LED1_RED + PIN_LED1_GREEN + PIN_LED1_BLUE;
}
extern void Led1_Yellow_On(void)
{
    PORT_LED1_OUT &=~ PIN_LED1_RED + PIN_LED1_GREEN;
}
extern void Led1_Yellow_Off(void)
{
    PORT_LED1_OUT |= PIN_LED1_RED + PIN_LED1_GREEN;
}
extern void Led1_Celadon_On(void)
{
    Led1_Green_On();
    Led1_Blue_On();
}
extern void Led1_Celadon_Off(void)
{
    Led1_Green_Off();
    Led1_Blue_Off();
}
/*
 * Led 2 color
 */
extern void Led2_Red_On(void)
{
    PORT_LED2_OUT &=~ PIN_LED2_RED;
}
extern void Led2_Red_Off(void)
{
    PORT_LED2_OUT |= PIN_LED2_RED;
}
extern void Led2_Green_On(void)
{
    PORT_LED2_OUT &=~ PIN_LED2_GREEN;
}
extern void Led2_Green_Off(void)
{
    PORT_LED2_OUT |= PIN_LED2_GREEN;
}
extern void Led2_Blue_On(void)
{
    PORT_LED2_OUT &=~ PIN_LED2_BLUE;
}
extern void Led2_Blue_Off(void)
{
    PORT_LED2_OUT |= PIN_LED2_BLUE;
}
extern void Led2_White_On(void)
{
    PORT_LED2_OUT &=~ PIN_LED2_RED + PIN_LED2_GREEN + PIN_LED2_BLUE;
}
extern void Led2_White_Off(void)
{
    PORT_LED2_OUT |= PIN_LED2_RED + PIN_LED2_GREEN + PIN_LED2_BLUE;
}
extern void Led2_Yellow_On(void)
{
    PORT_LED2_OUT &=~ PIN_LED2_RED + PIN_LED2_GREEN;
}
extern void Led2_Yellow_Off(void)
{
    PORT_LED2_OUT |= PIN_LED2_RED + PIN_LED2_GREEN;
}
extern void Led2_Celadon_On(void)
{
    Led2_Green_On();
    Led2_Blue_On();
}
extern void Led2_Celadon_Off(void)
{
    Led2_Green_Off();
    Led2_Blue_Off();
}

/*
 * Led 3 color
 */
extern void Led3_Red_On(void)
{
    PORT_LED3_OUT &=~ PIN_LED3_RED;
}
extern void Led3_Red_Off(void)
{
    PORT_LED3_OUT |= PIN_LED3_RED;
}
extern void Led3_Green_On(void)
{
    PORT_LED3_OUT &=~ PIN_LED3_GREEN;
}
extern void Led3_Green_Off(void)
{
    PORT_LED3_OUT |= PIN_LED3_GREEN;
}
extern void Led3_Blue_On(void)
{
    PORT_LED3_OUT &=~ PIN_LED3_BLUE;
}
extern void Led3_Blue_Off(void)
{
    PORT_LED3_OUT |= PIN_LED3_BLUE;
}
extern void Led3_White_On(void)
{
    PORT_LED3_OUT &=~ PIN_LED3_RED + PIN_LED3_GREEN + PIN_LED3_BLUE;
}
extern void Led3_White_Off(void)
{
    PORT_LED3_OUT |= PIN_LED3_RED + PIN_LED3_GREEN + PIN_LED3_BLUE;
}
extern void Led3_Yellow_On(void)
{
    PORT_LED3_OUT &=~ PIN_LED3_RED + PIN_LED3_GREEN;
}
extern void Led3_Yellow_Off(void)
{
    PORT_LED3_OUT |= PIN_LED3_RED + PIN_LED3_GREEN;
}
extern void Led3_Celadon_On(void)
{
    Led3_Green_On();
    Led3_Blue_On();
}
extern void Led3_Celadon_Off(void)
{
    Led3_Green_Off();
    Led3_Blue_Off();
}

/*
 * Led 4 color
 */
extern void Led4_Red_On(void)
{
    PORT_LED4_OUT &=~ PIN_LED4_RED;
}
extern void Led4_Red_Off(void)
{
    PORT_LED4_OUT |= PIN_LED4_RED;
}
extern void Led4_Green_On(void)
{
    PORT_LED4_OUT &=~ PIN_LED4_GREEN;
}
extern void Led4_Green_Off(void)
{
    PORT_LED4_OUT |= PIN_LED4_GREEN;
}
extern void Led4_Blue_On(void)
{
    PORT_LED4_OUT &=~ PIN_LED4_BLUE;
}
extern void Led4_Blue_Off(void)
{
    PORT_LED4_OUT |= PIN_LED4_BLUE;
}
extern void Led4_White_On(void)
{
    PORT_LED4_OUT &=~ PIN_LED4_RED + PIN_LED4_GREEN + PIN_LED4_BLUE;
}
extern void Led4_White_Off(void)
{
    PORT_LED4_OUT |= PIN_LED4_RED + PIN_LED4_GREEN + PIN_LED4_BLUE;
}
extern void Led4_Yellow_On(void)
{
    PORT_LED4_OUT &=~ PIN_LED4_RED + PIN_LED4_GREEN;
}
extern void Led4_Yellow_Off(void)
{
    PORT_LED4_OUT |= PIN_LED4_RED + PIN_LED4_GREEN;
}
extern void Led4_Celadon_On(void)
{
    Led4_Green_On();
    Led4_Blue_On();
}
extern void Led4_Celadon_Off(void)
{
    Led4_Green_Off();
    Led4_Blue_Off();
}

/*
 * Led Animation
 */
extern void LedAll_Red_On(void)
{
    PORT_LED1_OUT &=~ PIN_LED1_RED;
    PORT_LED2_OUT &=~ PIN_LED2_RED;
    PORT_LED3_OUT &=~ PIN_LED3_RED;
    PORT_LED4_OUT &=~ PIN_LED4_RED;
}
extern void LedAll_Red_Off(void)
{
    PORT_LED1_OUT |= PIN_LED1_RED;
    PORT_LED2_OUT |= PIN_LED2_RED;
    PORT_LED3_OUT |= PIN_LED3_RED;
    PORT_LED4_OUT |= PIN_LED4_RED;
}
extern void LedAll_Green_On(void)
{
    PORT_LED1_OUT &=~ PIN_LED1_GREEN;
    PORT_LED2_OUT &=~ PIN_LED2_GREEN;
    PORT_LED3_OUT &=~ PIN_LED3_GREEN;
    PORT_LED4_OUT &=~ PIN_LED4_GREEN;
}
extern void LedAll_Green_Off(void)
{
    PORT_LED1_OUT |= PIN_LED1_GREEN;
    PORT_LED2_OUT |= PIN_LED2_GREEN;
    PORT_LED3_OUT |= PIN_LED3_GREEN;
    PORT_LED4_OUT |= PIN_LED4_GREEN;
}
extern void LedAll_Blue_On(void)
{
    PORT_LED1_OUT &=~ PIN_LED1_BLUE;
    PORT_LED2_OUT &=~ PIN_LED2_BLUE;
    PORT_LED3_OUT &=~ PIN_LED3_BLUE;
    PORT_LED4_OUT &=~ PIN_LED4_BLUE;
}
extern void LedAll_Blue_Off(void)
{
    PORT_LED1_OUT |= PIN_LED1_BLUE;
    PORT_LED2_OUT |= PIN_LED2_BLUE;
    PORT_LED3_OUT |= PIN_LED3_BLUE;
    PORT_LED4_OUT |= PIN_LED4_BLUE;
}
extern void LedAll_White_On(void)
{
    LedAll_Red_On();
    LedAll_Green_On();
    LedAll_Blue_On();
}
extern void LedAll_White_Off(void)
{
    LedAll_Red_Off();
    LedAll_Green_Off();
    LedAll_Blue_Off();
}
extern void LedAll_Yellow_On(void)
{
    LedAll_Red_On();
    LedAll_Green_On();
}
extern void LedAll_Yellow_Off(void)
{
    LedAll_Red_Off();
    LedAll_Green_Off();
}
extern void LedAll_Celadon_On(void)
{
    LedAll_Green_On();
    LedAll_Blue_On();
}
extern void LedAll_Celadon_Off(void)
{
    Led1_Green_Off();
    Led1_Blue_Off();
}
extern void LedOffAll(void)
{
    LedAll_Red_Off();
    LedAll_Green_Off();
    LedAll_Blue_Off();
    LedAll_White_Off();
    LedAll_Yellow_Off();
    LedAll_Celadon_Off();
}



