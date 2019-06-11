/*
 * UART.c
 *
 *  Created on: 9 thg 7, 2018
 *      Author: Phong
 */

#include "UART/UART.h"


extern void UART_Init(void)
{
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
    UCA0CTL1 |= UCSWRST;
    UCA0CTL0 |= UCMODE_0;
    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0 = 104 ;
    UCA0BR1 = 00 ;
    UCA0MCTL |= UCBRF_0 + UCBRS_1;
    UCA0CTL1 &=~UCSWRST;
    IE2 |= UCA0RXIE;
    _bis_SR_register(GIE);
}

extern void UART_Put_String(char *str)
{
    while(*str != '\0')
    {
        while(!(IFG2&UCA0TXIFG));
        UCA0TXBUF = *str;
        str++;
    }
}

extern void UART_Put_Char(char chr)
{
    while(!(IFG2&UCA0TXIFG));
    UCA0TXBUF = chr;
}

extern void UART_Put_Int(unsigned long n)
{
    unsigned char buffer[16];
    unsigned char i,j;
    if(n==0)
    {
        UART_Put_Char('0');
    }

    for(i=15;i>0 && n>0;i--)
    {
        buffer[i] = (n%10)+ '0';
        n/=10;
    }

    for (j=i+1;j<=15;j++)
    {
        UART_Put_Char(buffer[j]);
    }
}

extern char UART_Get_Char()
{
    while(!(IFG2&UCA0RXIFG));
        return UCA0RXBUF;
}

extern void UART_Get_String(char *str)
{

    while(*str != '\0')
    {

        *str = UART_Get_Char();
        str++;
    }
}


#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
//    UART_Put_Char(UCA0RXBUF);
//    IFG2 &= ~UCA0RXIFG;
}
