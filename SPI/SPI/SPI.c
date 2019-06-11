/*
 * SPI.c
 *
 *  Created on: Sep 11, 2018
 *      Author: ThanhPhong
 */

#include "SPI.h"
void SPI_A_Init(void) // Config module SPI USCIA
{
    //Config PIN
    P1SEL = BIT1 + BIT2 + BIT4;
    P1SEL2 = BIT1 + BIT2 + BIT4;
    //Config SPI
    UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;
        /*  UCSYNC     Sync-Mode
         *  UCCKPH     Mode: Clock Phase
         *  UCCKPL     Mode: Clock Polarity
         *  UCMST      Mode: Master Select
         *  UC7BIT     Mode: Data Bits  0:8-bits / 1:7-bits
         *  UCMSB      Mode: MSB first  0:LSB / 1:MSB
         *  UCMST      Mode: Master Select
         *  UCMODE_0   Mode: USCI Mode: 0; 3pin SPI default
         *  UCMODE_1    Mode: USCI Mode: 1; 4pin SPI
         *  UCMODE_2    Mode: USCI Mode: 2; 4pin SPI
         */
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
        /*UCSSEL_1 ACLK
         *UCSSEL_2 SMCLK
         *UCSSEL_3 SMCLK
         */
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

    UCA0BR0 |= 0x02;                          // f/2    for your choice
    UCA0BR1 = 0;                              //

    UCA0MCTL = 0;                             // No modulation

//  IE2 |= UCA0TXIE;                          // Enable USCI0 RX interrupt
    __delay_cycles(75);                       // Wait for slave to initialize
}


void SPI_B_Init(void) // Config module SPI USCIB
{
    //Config PIN
    P1SEL = BIT5 + BIT6 + BIT7;
    P1SEL2 = BIT5 + BIT6 + BIT7;
    //Config SPI
    UCB0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;
    /*  UCSYNC     Sync-Mode
     *  UCCKPH     Mode: Clock Phase
     *  UCCKPL     Mode: Clock Polarity
     *  UCMST      Mode: Master Select
     *  UC7BIT     Mode: Data Bits  0:8-bits / 1:7-bits
     *  UCMSB      Mode: MSB first  0:LSB / 1:MSB
     *  UCMST      Mode: Master Select
     *  UCMODE_0   Mode: USCI Mode: 0; 3pin SPI default
     *  UCMODE_1    Mode: USCI Mode: 1; 4pin SPI
     *  UCMODE_2    Mode: USCI Mode: 2; 4pin SPI
     */
    UCB0CTL1 |= UCSSEL_2;                     // SMCLK
    /*UCSSEL_1 ACLK
     *UCSSEL_2 SMCLK
     *UCSSEL_3 SMCLK
     */
    UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

    UCB0BR0 |= 0x02;                         // f/2   for your choice
    UCB0BR1 = 0;
//  IE2 |= UCA0TXIE;                         // Enable USCI0 RX interrupt
    __delay_cycles(75);                      // Wait for slave to initialize
}


void SPI_A_Put_Data(int data, int time_ms)     // Send 1 byte for module SPI USCIA
{
      int i_delay;
      while (!(IFG2 & UCA0TXIFG));          // USCI_A0 TX buffer ready?
      UCA0TXBUF = data;                     // Send next value
      for (i_delay = 0; i_delay*Freq_MHz<time_ms; i_delay++ )
      {
        _delay_cycles(1000);
      }
}

void SPI_B_Put_Data(int data, int time_ms)     // Send 1 byte for module SPI USCIB
{
      int i_delay;
      while (!(IFG2 & UCA0TXIFG));          // USCI_A0 TX buffer ready?
      UCB0TXBUF = data;                     // Send next value
      for (i_delay = 0; i_delay*Freq_MHz<time_ms; i_delay++ )
      {
        _delay_cycles(1000);
      }
}



