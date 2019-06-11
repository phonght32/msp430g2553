#include "msp430.h"
#include "stdio.h"
#include <stdint.h>

#define lcd_delay   500
uint16_t adc_result;
uint16_t f=0; // f dem so lan tran timer
uint16_t heart_beat;

void config_ADC10(void);
void config_capture(void);
void LCD_Init_write(unsigned char b);
void LCD_Command(unsigned char chr);
char LCD_Read2Nib();
void LCD_Init();
void LCD_Clear();
void LCD_Home();
void LCD_Wait();
void LCD_Display(unsigned char chr);
void LCD_Goto(unsigned char row, unsigned char column);
/* Dich chuyen con tro sang trai(direct=0) hoac sang phai(direct=1) "step" vi tri */
void LCD_CursorShift(unsigned char direct, unsigned char step);
void LCD_PrintString(char *str);
/* In ra man hinh so nguyen n voi so cho hien thi bang length(chua ke vi tri cua dau) */
void LCD_PrintDecimal(long n, unsigned char length);
/* In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma */
void LCD_PrintUnDecimal(long n, unsigned char length);
void LCD_PrintFloat(float x, unsigned char length, unsigned char coma);

void main()
{
       WDTCTL = WDTPW | WDTHOLD;
       DCOCTL = CALDCO_1MHZ;
       BCSCTL1 = CALBC1_1MHZ;
       P1SEL &=~ BIT5;
       P1SEL2 &=~ BIT5;
       P1DIR |= BIT5;
       config_capture();
       config_ADC10();

       LCD_Init();
       LCD_Clear();
       LCD_Home();
       LCD_PrintString("Heart Beat: ");
       LCD_Goto(2,4);
       LCD_PrintString("PIF.C17");

       while(1)
       {
           ADC10CTL0 |= ENC + ADC10SC;
           _bis_SR_register(LPM0_bits + GIE);
           LCD_Goto(1,11);
           LCD_PrintDecimal(heart_beat,3);

       }
}
void config_capture(void)
{
        P1SEL |= BIT2;
        P1SEL2 &=~BIT2;
        P1DIR &=~BIT2;
        P1IE |=BIT2;
        P1IFG &=~ BIT2;

        WDTCTL = WDTPW + WDTHOLD;
        TA0CTL = TASSEL_2 + MC_2 + TAIE;
        TA0CCTL1 |= CM_1 +CCIS_0+CAP+CCIE;
        TA0R =0;
        _BIS_SR(GIE);
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TA0IV_Interrupt (void)
{
    switch(TA0IV)
    {
        case 10 :          //tran timer
        {
            f=f+1;
            break;
        }
        case 2 :
        {
            double capture_value;

                 capture_value = TACCR1+f*65536;
                 TA0R = 0;
                 f=0;
                 heart_beat= 60/(capture_value/1000000);
        }
    }
}

void config_ADC10(void)
{
    ADC10CTL0 = SREF_0 + ADC10SHT_1 + ADC10ON +ADC10IE;
    ADC10CTL1 = INCH_0 + ADC10DIV_1 + ADC10SSEL_3;
    ADC10AE0 |= BIT0;
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_Interrupt(void)
{
    adc_result = ADC10MEM;
    if(adc_result>800)
           {
                P1OUT |= BIT5;
                _delay_cycles(3000);
           }
    else
                P1OUT &=~ BIT5;
    _bic_SR_register_on_exit(LPM0_bits);
}

void LCD_Init()
{
    P2SEL &=~(BIT4 + BIT5 + BIT6 + BIT7);
    P2SEL2 &=~(BIT4 + BIT5 + BIT6 + BIT7);
    P2DIR |= BIT4 + BIT5 + BIT6 + BIT7;
    P2REN &=~(BIT4 + BIT5 + BIT6 + BIT7);
    P2OUT &=~(BIT4 + BIT5 + BIT6 + BIT7);
    P2DIR |= BIT1 + BIT2 + BIT3;
    P2OUT &=~ (BIT1 + BIT2 + BIT3);

    _delay_cycles(lcd_delay*40);
    LCD_Init_write(0x20);                    //4 bit mode
    LCD_Command(0x28);
    _delay_cycles(lcd_delay);
    LCD_Command(0x0e);                    // Bat hien thi,tat con tro                     //delay 40uS
    _delay_cycles(lcd_delay);
    LCD_Command(6);                     //hien thi tang vao khong shift                     //delay 40uS
    _delay_cycles(lcd_delay);
}


void LCD_Init_write(unsigned char b)
{
    P2OUT &=~(BIT4 + BIT5 + BIT6 + BIT7);
    P2OUT &=~ 0x02;
    _delay_cycles(lcd_delay*40);

    P2OUT |=b;
    P2OUT |= 0x08;
    _delay_cycles(lcd_delay);
    P2OUT &=~ 0x08;
    _delay_cycles(lcd_delay*40);
}

void LCD_Command(unsigned char chr)
{
    unsigned char HNib,LNib,temp_data;
    temp_data=(P2OUT &~(0xF0));
    HNib=chr&0xF0;
    LNib=(chr<<4)&0xF0;

    P2OUT =((HNib)|temp_data);
    P2OUT |= 0x08;
    P2OUT &=~ 0x08 ;
    _delay_cycles(lcd_delay);
    P2OUT =((LNib)|temp_data);
    P2OUT |= 0x08;
    P2OUT &=~0x08;
    _delay_cycles(lcd_delay);

}


char LCD_Read2Nib()
{
    char HNib,LNib;
    P2OUT|=0xF0;
    P2OUT |= 0x08;
    HNib = (P2IN &(0xF0));
    P2OUT &=~0x08;

    P2OUT |= 0x08;
    LNib = (P2IN &(0xF0));
    P2OUT &=~ 0x08;
    LNib>>=4;
    return (HNib|LNib);
}


void LCD_Clear()
{
    P2OUT &=~ 0x02;
    LCD_Command(0x01);
    _delay_cycles(lcd_delay*40);
}

void LCD_Home()
{
    P2OUT &=~0x02;
    LCD_Command(0x02);
    _delay_cycles(lcd_delay*40);
}

void LCD_Wait()
{
    char temp_val;
    P2DIR &=~(0xF0);       //Chuyen thanh cong in
    while(1)
    {
        P2OUT &=~0x02;
        P2OUT |= 0x04;
        temp_val = LCD_Read2Nib();
        if((temp_val&0x80)==0)break;
    }
    P2OUT &=~ 0x04;
    P2DIR |=(0xF0);
}



void LCD_Display(unsigned char chr)
{
    P2OUT |=0x02;
    LCD_Command(chr);
}



void LCD_Goto(unsigned char row, unsigned char column)
{
    P2OUT &=~ 0x02;
    if(row == 2)
        LCD_Command(0xC0 + column);
    else
        LCD_Command(0x80 + column);
}

/* Dich chuyen con tro sang trai(direct=0) hoac sang phai(direct=1) "step" vi tri */
void LCD_CursorShift(unsigned char direct, unsigned char step)
{
    unsigned char i;
    P2OUT &=~ 0x02;
    if (direct == 0)
        for(i=0;i<step;i++)
            LCD_Command(0x10);
    else
        for(i=0;i<step;i++)
            LCD_Command(0x14);
}



void LCD_PrintString(char *str)
{
    while(*str)
    {
        LCD_Display(*str);
        str++;
    }
}


/* In ra man hinh so nguyen n voi so cho hien thi bang length(chua ke vi tri cua dau) */
void LCD_PrintDecimal(long n, unsigned char length)
{
    unsigned char du,luu=length;
    // de trong 1 ki tu o dau cho hien thi dau
    if(n>=0)
        LCD_Display(' ');       //In so duong
    else
    {
        LCD_Display('-');           //In so am
        n*=-1;
    }


    LCD_CursorShift(1,length-1);    // dich con tro sang phai length-1 vi tri
    P2OUT &=~  0x02;

    _delay_cycles(lcd_delay);

    LCD_Command(0x04);        // chuyen sang che do in lui
    // Bat dau in lan luot cac chu so tu hang don vi
    while(length)
    {
        du = n % 10;
        n = n / 10;
        LCD_Display(0x30 + du);
        length--;
    }
    LCD_CursorShift(1,luu);     // dua con tro sang phai length+1 vi tri de in tiep
    P2OUT &=~ 0x02;

    _delay_cycles(lcd_delay);

    LCD_Command(0x06);        // chuyen lai ve che do in xuoi


}

void LCD_PrintUnDecimal(long n, unsigned char length)
{
    unsigned char du,luu=length;
    LCD_CursorShift(1,length-1);    // dich con tro sang phai length-1 vi tri
    P2OUT &=~ 0x02;

    _delay_cycles(lcd_delay);

    LCD_Command(0x04);       // chuyen sang che do in lui
    // Bat dau in lan luot cac chu so tu hang don vi
    while(length)
    {
        du = n % 10;
        n = n / 10;
        LCD_Display(0x30 + du);
        length--;
    }
    LCD_CursorShift(1,luu+1);       // dua con tro sang phai length+1 vi tri de in tiep
    P2OUT &=~0x02;

    _delay_cycles(lcd_delay);

    LCD_Command(0x06);        // chuyen lai ve che do in xuoi


}

/* In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma */
void LCD_PrintFloat(float x, unsigned char length, unsigned char coma)
{
    // de trong 1 ki tu o dau cho hien thi dau
    if(x>=0)LCD_Display(' ');
    else
    {
        LCD_Display('-');           //In so am
        x*=-1;
    }
    unsigned long n;
    unsigned char store,temp;
    store = length;                     // Luu lai do dai so thuc.
    length--;                               // Giam di 1 cho dau "."
    for(temp=0;temp<coma;temp++)
        x = x*10;

    n = x;                                  // Chuyan thanh so nguyen.
    if((x-n)>=0.5)
        n++;

    LCD_CursorShift(1,length);              // Dich chuyen con tro sang phai
    P2OUT &=~0x02;

    _delay_cycles(lcd_delay);

    LCD_Command(0x04);                // Chuyen sang che do in nguoc.

    while(coma)                             // In ra phan truoc dau phay
    {
        temp = n % 10;
        n = n / 10;
        LCD_Display(0x30 + temp);
        coma--;
        length--;
    }

    LCD_Display('.');                           // In ra dau "."

        while(length)                           // In ra phan thap phan
        {
            temp = n % 10;
            n = n / 10;
            //if(temp!=n)
            LCD_Display(0x30 + temp);
            length--;
        }
    P2OUT &=~ 0x02;

    _delay_cycles(lcd_delay);

    LCD_Command(0x06);                // Chuyen lai che do in thuan.
    LCD_CursorShift(1,store+1);                 // Nhay den vi tri tiep theo.
}
