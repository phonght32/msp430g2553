/*
 *          ------- Chicken Board Test Code  --------
 *                      ++ C18 Course ++
 *
 *
 *  Author:          Nguyen Thanh Tam - PIF Club
 */

/*************************************************************************
       USER GUIDE:
               + Connect 8 leds to Port1 by bus wire
               + Power on Chicken Board, led will run from 1 to 8 in 10 sec   ------ if fail -4
               + Buzzer will BUZZZZZZ two BUZZZZZZs                           ------ if fail -4
               + LED 7segs will run 0 to 8                                    ------ if fail -4
               + Disconnect bus wire
               + Press Button, if button is ok, buzzer will buzz two time     ------ if fail -4
               + To bypass Button test, press BTN1.3 in MSP430 launchpad
               + I2C init, time display is auto set at 14h                    -------if fail -4

       *//*******************************************************************************************/
#include <msp430g2553.h>
//#include <stdio.h>
#include <stdint.h>
// define 7segs
#define SEG1_BIT BIT5
#define SEG2_BIT BIT7
#define SEG3_BIT BIT6
#define SEG4_BIT BIT0
#define SEG1_PORT P2OUT
#define SEG2_PORT P2OUT
#define SEG3_PORT P2OUT
#define SEG4_PORT P1OUT
//define button
#define BTN1_BIT BIT2
#define BTN2_BIT BIT1
#define BTN3_BIT BIT4
#define BTN4_BIT BIT3
#define BTN_PORT P2OUT
#define BTN_PORT_IN P2IN

//define buzzer
#define BZ_BIT  BIT0
#define BZ_PORT P2OUT
//define hc595 spi
#define CLK BIT4  //11
#define SDI BIT3 //14
#define STR BIT5 //12
//
#define DS1307ADD 0x68
unsigned char  buffer[15];
unsigned char  led7s[]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uint8_t dot=0xfe;
unsigned char Write_Buffer[]={0x02,0x20,0x14,0x00,0x00,0x00,0x00};
uint8_t i;
uint8_t k=0x01;
uint16_t h;
// firmware init
void TimerInit(void);
void Clock_Init(void);
void IO_Init(void);
void I2C_USCI_Init(unsigned char addr);
void CCR0_Interrupt (void);
// firmware funtions
void Delay_ms (uint16_t ms);
void Hc595Trans(uint8_t byte);
void P1Write( uint8_t bit, uint8_t val );
void I2C_Write(unsigned char add_register, unsigned char numbyte, unsigned char * poi_send);
void I2C_Read(unsigned char add_register, unsigned char numbyte, unsigned char * poi_read);
// test funtions
void Buzzer(void);
void Led7segs(void);
void DS1307_Get(void);
void Button(void);
void Leds(void);
void Scanled(void);
/**
 * main.c
 */
int main(void)
{

WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

        Clock_Init();
        Buzzer();
        TimerInit();

                  Delay_ms(3000);
        // Button();
        TA0CCTL0 &=~CCIE;
//

        IO_Init();
        Buzzer();
        //Test part
//      Buzzer();
////
//      while(1)
        {
        Led7segs();
        }
////

        Button();
        I2C_USCI_Init(DS1307ADD);
        I2C_Write(0x00,7,Write_Buffer);
        Delay_ms(1000);

        Buzzer();

        while(1)
        {
            Scanled();

           // Led7segs();
        }

    return 0;
}
void Clock_Init(void)
{
    //8Mhz
      DCOCTL = CALDCO_8MHZ;
      BCSCTL1 = CALBC1_8MHZ;
      BCSCTL2 |= SELM_0;
}
void IO_Init(void)
{
    P1SEL |= 0;
    P2SEL |= 0;
    P1SEL2|= 0;
    P2SEL2|= 0;
    // Buzzer
    P2DIR |= BZ_BIT;
    BZ_PORT &= ~BZ_BIT;
    //Button
    P2DIR &= ~(BTN1_BIT+BTN2_BIT+BTN3_BIT+BTN4_BIT);
    BTN_PORT |= BTN1_BIT+BTN2_BIT+BTN3_BIT+BTN4_BIT;
    P2REN |= BTN1_BIT+BTN2_BIT+BTN3_BIT+BTN4_BIT;
    //HC595 SPI SW
    P1DIR |= STR + SDI + CLK;
    P1OUT &= ~(STR + SDI + CLK);
    //7segs
    P1DIR |= (SEG4_BIT);
    P2DIR |= (SEG1_BIT+SEG2_BIT+SEG3_BIT);
    P1DIR|=SEG4_BIT;
                  P2DIR|=(SEG1_BIT+SEG2_BIT+SEG3_BIT);
                  P2SEL &= ~(BIT6+BIT7);
                  P2OUT |=( SEG1_BIT+SEG2_BIT+SEG3_BIT);
                  P1OUT |=SEG4_BIT;
}
void Buzzer(void)
{

    uint8_t i;
    for (i=0;i<2;i++)
    {
        BZ_PORT |= BZ_BIT;
        Delay_ms(100);
        BZ_PORT &=~BZ_BIT;
        Delay_ms(100);
    }

}
void Delay_ms (uint16_t ms)
{
    uint16_t i;
    for (i=0;i<ms;i++)
    {
        __delay_cycles(8000);
    }
}
void Hc595Trans(uint8_t byte)
{
uint8_t i,K;
K=byte;
for(i=0;i<8;i++)
{
    P1Write( SDI, K&0x80);
    P1Write( CLK, 0);
    P1Write( CLK, 1);
    K<<=1;
} // 1 byte transmission
P1Write( STR, 0);
P1Write( STR, 1);
}
void P1Write( uint8_t bit, uint8_t val )
{
  if (val){
    P1OUT |= bit;
  } else {
    P1OUT &= ~bit;
  }
}
void Led7segs(void)
{
        SEG1_PORT &= ~SEG1_BIT;
        SEG2_PORT &= ~SEG2_BIT;
//        SEG3_PORT &= ~SEG3_BIT;
//        SEG4_PORT &= ~SEG4_BIT;
        Hc595Trans(0x00);
        Delay_ms(100);
        Hc595Trans(0xff);
        Delay_ms(100);
        uint8_t i;
        for (i=0;i<9;i++)
        {
            Hc595Trans(led7s[i]);
            Delay_ms(200);
        }
                SEG1_PORT |= SEG1_BIT;
               SEG2_PORT |= SEG2_BIT;
               SEG3_PORT &= ~SEG3_BIT;
               SEG4_PORT &= ~SEG4_BIT;
               Hc595Trans(0x00);
               Delay_ms(100);
               Hc595Trans(0xff);
               Delay_ms(100);
//               uint8_t i;
               for (i=0;i<9;i++)
               {
                   Hc595Trans(led7s[i]);
                   Delay_ms(200);
               }

}

void I2C_USCI_Init(unsigned char addr)
{
    P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST+UCMODE_3+UCSYNC;         // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2+UCSWRST;              // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                             // fSCL = SMCLK/40 = ~400kHz
    UCB0BR1 = 0;
    UCB0I2CSA = addr;                         // Set slave address
    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
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
void DS1307_Get(void)
{
    I2C_Read(0x00, 8, buffer);
}
void Button(void)
{
    P2DIR &= ~(BTN1_BIT+BTN2_BIT+BTN3_BIT+BTN4_BIT);
        BTN_PORT |= BTN1_BIT+BTN2_BIT+BTN3_BIT+BTN4_BIT;
        P2REN |= BTN1_BIT+BTN2_BIT+BTN3_BIT+BTN4_BIT;
        P1DIR &= ~ BIT3;
        P1REN |= BIT3;
        P1OUT |= BIT3;
    uint8_t i=0;
    while (i != (0x1E))
    {
        if((BTN_PORT_IN & BTN1_BIT)==0)
                {
                    i |=  BTN1_BIT;
                    Buzzer();
                }
        if((BTN_PORT_IN & BTN2_BIT)==0)
                {
                    i |=  BTN2_BIT;
                    Buzzer();
                }
        if((BTN_PORT_IN & BTN3_BIT)==0)
                {
                    i |=  BTN3_BIT;
                    Buzzer();
                }
        if((BTN_PORT_IN & BTN4_BIT)==0)
                {
                    i |=  BTN4_BIT;
                    Buzzer();
                }
        if ((P1IN & BIT3)==0)
        {
            i = 0x1E;
        }

    }
    IO_Init();
    Buzzer();
}
void Leds(void)
{
    uint8_t i;
    P1OUT |= 0x00;
    Delay_ms(500);
    P1OUT |= 0xff;
    Delay_ms(500);

    for (i=0;i<9;i++)
    {
        P1OUT |= 0x00;
           Delay_ms(500);
           P1OUT |= 0xff;
           Delay_ms(500);
    }
   // Buzzer()   ;
}
void Scanled(void)
{
    DS1307_Get();
                Hc595Trans((led7s[((buffer[2]&0xf0)>>4)]));
                P1OUT &= ~SEG4_BIT;

                __delay_cycles(8*1000*4);
                P1OUT |=SEG4_BIT;

                if((buffer[0]&0x0f)%2)
                {
                    Hc595Trans((((led7s[buffer[2]&0x0f]))^0x80));
                }
                else
                {
                    Hc595Trans(led7s[buffer[2]&0x0f]);
                }
                P2OUT &= ~SEG3_BIT;
                __delay_cycles(8*1000*4);
                P2OUT |=SEG3_BIT;

                Hc595Trans(led7s[((buffer[1]&0xf0)>>4)]);
                P2OUT &= ~SEG2_BIT;
                __delay_cycles(8*1000*4);

                P2OUT |=SEG2_BIT;
                Hc595Trans(led7s[buffer[1]&0x0f]);
                P2OUT &= ~SEG1_BIT;
                __delay_cycles(8*1000*4);

                P2OUT |=SEG1_BIT;
}

void TimerInit(void)
{
        P1DIR =0xff;
        P1OUT =0x00;
        TA0CTL = TASSEL_2 + MC_1 + ID_3;
        TA0CCR0 = 150;
        TA0CCTL0=CCIE;
        __enable_interrupt();

}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void CCR0_Interrupt (void)
{
    if(h==1000)
    {
        k=k<<1;
        h=0;
        if(k==0x00)
        {
            k=0x01;
        }
        P1OUT=0x00;
    }
    P1OUT |= (k);
    i++;
    if (i<20)
    {
        P1OUT |= (k>>1);
    }
    else
    {
        P1OUT &= ~(k>>1);
    }

    if (i<3)
     {

          P1OUT |= (k>>2);
      }
      else
      {
          P1OUT &= ~(k>>2);
      }
    if(i==100)
           i=0;
    h++;

//
}
