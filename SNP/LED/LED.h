/*
 * LED.h
 *
 *  Created on: Mar 19, 2019
 *      Author: Phong
 */

#include <msp430.h>
#include "../define.h"



/*
 * LED 1 define
 */

#define PORT_LED1_SEL   P2SEL
#define PORT_LED1_SEL2  P2SEL2
#define PORT_LED1_DIR   P2DIR
#define PORT_LED1_IN    P2IN
#define PORT_LED1_OUT   P2OUT
#define PORT_LED1_REN   P2REN
#define PORT_LED1_IE    P2IE
#define PORT_LED1_IES   P2IES
#define PORT_LED1_IFG   P2IFG

#define PIN_LED1_RED    BIT3
#define PIN_LED1_GREEN  BIT4
#define PIN_LED1_BLUE   BIT5

/*
 * LED 2 define
 */

#define PORT_LED2_SEL   P2SEL
#define PORT_LED2_SEL2  P2SEL2
#define PORT_LED2_DIR   P2DIR
#define PORT_LED2_IN    P2IN
#define PORT_LED2_OUT   P2OUT
#define PORT_LED2_REN   P2REN
#define PORT_LED2_IE    P2IE
#define PORT_LED2_IES   P2IES
#define PORT_LED2_IFG   P2IFG

#define PIN_LED2_RED    BIT0
#define PIN_LED2_GREEN  BIT1
#define PIN_LED2_BLUE   BIT2

/*
 * LED 3 define
 */

#define PORT_LED3_SEL   P1SEL
#define PORT_LED3_SEL2  P1SEL2
#define PORT_LED3_DIR   P1DIR
#define PORT_LED3_IN    P1IN
#define PORT_LED3_OUT   P1OUT
#define PORT_LED3_REN   P1REN
#define PORT_LED3_IE    P1IE
#define PORT_LED3_IES   P1IES
#define PORT_LED3_IFG   P1IFG

#define PIN_LED3_RED    BIT3
#define PIN_LED3_GREEN  BIT4
#define PIN_LED3_BLUE   BIT5

/*
 * LED 4 define
 */

#define PORT_LED4_SEL   P1SEL
#define PORT_LED4_SEL2  P1SEL2
#define PORT_LED4_DIR   P1DIR
#define PORT_LED4_IN    P1IN
#define PORT_LED4_OUT   P1OUT
#define PORT_LED4_REN   P1REN
#define PORT_LED4_IE    P1IE
#define PORT_LED4_IES   P1IES
#define PORT_LED4_IFG   P1IFG

#define PIN_LED4_RED    BIT0
#define PIN_LED4_GREEN  BIT1
#define PIN_LED4_BLUE   BIT2



#ifndef LED_LED_H_
#define LED_LED_H_

extern void Led_Init(void);
extern void LedOffAll(void);

/*
 * Led 1 Color Prototype
 */
extern void Led1_Red_On(void);
extern void Led1_Red_Off(void);
extern void Led1_Green_On(void);
extern void Led1_Green_Off(void);
extern void Led1_Blue_On(void);
extern void Led1_Blue_Off(void);
extern void Led1_White_On(void);
extern void Led1_White_Off(void);
extern void Led1_Yellow_On(void);
extern void Led1_Yellow_Off(void);
extern void Led1_Celadon_On(void);
extern void Led1_Celadon_Off(void);
/*
 * Led 2 Color Prototype
 */
extern void Led2_Red_On(void);
extern void Led2_Red_Off(void);
extern void Led2_Green_On(void);
extern void Led2_Green_Off(void);
extern void Led2_Blue_On(void);
extern void Led2_Blue_Off(void);
extern void Led2_White_On(void);
extern void Led2_White_Off(void);
extern void Led2_Yellow_On(void);
extern void Led2_Yellow_Off(void);
extern void Led2_Celadon_On(void);
extern void Led2_Celadon_Off(void);

/*
 * Led 3 Color Prototype
 */
extern void Led3_Red_On(void);
extern void Led3_Red_Off(void);
extern void Led3_Green_On(void);
extern void Led3_Green_Off(void);
extern void Led3_Blue_On(void);
extern void Led3_Blue_Off(void);
extern void Led3_White_On(void);
extern void Led3_White_Off(void);
extern void Led3_Yellow_On(void);
extern void Led3_Yellow_Off(void);
extern void Led3_Celadon_On(void);
extern void Led3_Celadon_Off(void);

/*
 * Led 4 Color Prototype
 */
extern void Led4_Red_On(void);
extern void Led4_Red_Off(void);
extern void Led4_Green_On(void);
extern void Led4_Green_Off(void);
extern void Led4_Blue_On(void);
extern void Led4_Blue_Off(void);
extern void Led4_White_On(void);
extern void Led4_White_Off(void);
extern void Led4_Yellow_On(void);
extern void Led4_Yellow_Off(void);
extern void Led4_Celadon_On(void);
extern void Led4_Celadon_Off(void);

/*
 * Led Animation
 */
extern void LedAll_Red_On(void);
extern void LedAll_Red_Off(void);
extern void LedAll_Green_On(void);
extern void LedAll_Green_Off(void);
extern void LedAll_Blue_On(void);
extern void LedAll_Blue_Off(void);
extern void LedAll_White_On(void);
extern void LedAll_White_Off(void);
extern void LedAll_Yellow_On(void);
extern void LedAll_Yellow_Off(void);
extern void LedAll_Celadon_On(void);
extern void LedAll_Celadon_Off(void);




#endif /* LED_LED_H_ */
