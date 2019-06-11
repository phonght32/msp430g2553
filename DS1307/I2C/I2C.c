/*
 * I2C.c
 *
 *  Created on: 9 thg 7, 2018
 *      Author: Phong
 */

#include "I2C.h"

void I2C_Init(unsigned char slave_address)
{
    P1SEL |= BIT6 + BIT7;
    P1SEL2 |= BIT6 + BIT7;
    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 |= UCMST + UCMODE_3 + UCSYNC;
    UCB0CTL1 |= UCSSEL_2;
    UCB0BR0 = 12;
    UCB0BR1 = 0;
    UCB0I2CSA = slave_address;
    UCB0CTL1 &=~ UCSWRST;
}
void I2C_Write(unsigned char add_register, unsigned char numbyte, unsigned char * poi_send)
{
    while (UCB0CTL1 & UCTXSTP);                // Loop until I2C STT is sent
        UCB0CTL1 |= UCTR + UCTXSTT;                // I2C TX, start condition

        while(!(IFG2&UCB0TXIFG));
        //if(UCB0STAT & UCNACKIFG)
            //return UCB0STAT;
        UCB0TXBUF = add_register;

        while(!(IFG2&UCB0TXIFG));
        unsigned char i=0;
        for(i=0; i< numbyte; i++)
        {
            UCB0TXBUF= *(poi_send+i);
            while (!(IFG2&UCB0TXIFG));
        }

         UCB0CTL1 |= UCTXSTP;                       // I2C stop condition after 1st TX
         IFG2 &= ~UCB0TXIFG;
}

void I2C_Read(unsigned char add_register, unsigned char numbyte, unsigned char * poi_read)
{
    while(UCB0CTL1&UCTXSTP);
    UCB0CTL1 |= UCTR + UCTXSTT;

    while(!(IFG2&UCB0TXIFG));
    UCB0TXBUF = add_register;

    while(!(IFG2&UCB0TXIFG));
    UCB0CTL1 &=~ UCTR;
    UCB0CTL1 |= UCTXSTT;
    IFG2 &=~ UCB0TXIFG;

    while(UCB0CTL1&UCTXSTP);
    while(!(IFG2&UCB0RXIFG));
    unsigned char i;
    for (i=0;i<numbyte;i++)
    {
        *(poi_read+i-1) = UCB0RXBUF;
        while(!(IFG2&UCB0RXIFG));
    }
    UCB0CTL1 |= UCTXSTP;
}

