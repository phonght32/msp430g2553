/*
 * LCD_16x2.c
 *
 *  Created on: 3 thg 7, 2018
 *      Author: Phong
 */
#include "LCD.h"

extern void LCD_Init(void)
{
    //Khoi tao chuc nang I/O
    PORT_LCD_SEL &=~(BIT4 + BIT5 + BIT6 + BIT7);        //Chon chuc nang I/O
    PORT_LCD_SEL2 &=~(BIT4 + BIT5 + BIT6 + BIT7);
    PORT_LCD_DIR |= BIT4 + BIT5 + BIT6 + BIT7;          //Chon xuat du lieu cho 4 chan data
    PORT_LCD_REN &=~(BIT4 + BIT5 + BIT6 + BIT7);        //Khong co dien tro noi keo len
    PORT_LCD_OUT &=~(BIT4 + BIT5 + BIT6 + BIT7);        //Dau ra muc thap
    PORT_LCD_DIR |= BIT1 + BIT2 + BIT3;
    PORT_LCD_OUT &=~ (BIT1 + BIT2 + BIT3);


    _delay_cycles(1700*Freq_MHz);                       //delay 1.64mS


//    LCD_Write_Command(0x38);
//    _delay_cycles(50*Freq_MHz);
//
//    LCD_Write_Command(0x08);                        // Bat hien thi,tat con tro                     //delay 40uS
//    _delay_cycles(50*Freq_MHz);
//
//    LCD_Write_Command(0x06);                     //hien thi tang vao khong shift                     //delay 40uS
//    _delay_cycles(50*Freq_MHz);



    LCD_Write_Command(0x02);
    _delay_cycles(50*Freq_MHz);

    LCD_Write_Command(0x28);
    _delay_cycles(50*Freq_MHz);

    LCD_Write_Command(0x06);                        // Bat hien thi,tat con tro                     //delay 40uS
    _delay_cycles(50*Freq_MHz);

    LCD_Write_Command(0x0C);                     //hien thi tang vao khong shift                     //delay 40uS
    _delay_cycles(50*Freq_MHz);
    LCD_Write_Command(0x01);
    _delay_cycles(50*Freq_MHz);
}

extern void LCD_Write_Command(unsigned char command)
{
    unsigned char H_Nibble, L_Nibble, Temp_Data;
    Temp_Data = PORT_LCD_OUT&~(0xF0>>Shift_Data);

    H_Nibble = command&0xF0;
    L_Nibble = (command<<4)&0xF0;

    PORT_LCD_OUT = (H_Nibble>>Shift_Data)|Temp_Data;

    PORT_LCD_EN |= LCD_EN;
    PORT_LCD_EN &=~ LCD_EN;

    #ifdef USE_LCD_WAIT
        LCD_Wait();
    #else
        _delay_cycles(50*Freq_MHz);
    #endif

    PORT_LCD_OUT = (L_Nibble>>Shift_Data)|Temp_Data;

    PORT_LCD_EN |= LCD_EN;
    PORT_LCD_EN &=~ LCD_EN;

    #ifdef USE_LCD_WAIT
        LCD_Wait();
    #else
        _delay_cycles(50*Freq_MHz);
    #endif

}

extern void LCD_Clear(void)
{
    PORT_LCD_RS &=~ LCD_RS;
    LCD_Write_Command(0x01);
    #ifdef USE_LCD_WAIT
    LCD_Wait();
    #else
    _delay_cycles(1700*Freq_MHz);
    #endif

}
extern void LCD_Home(void)
{
    PORT_LCD_RS &=~ LCD_RS;
    LCD_Write_Command(0x02);
    #ifdef USE_LCD_WAIT
    LCD_Wait();
    #else
    _delay_cycles(1700*Freq_MHz);
    #endif

}
extern void LCD_Wait(void)
{
        char temp_val;
        PORT_LCD_DIR &=~(0xF0>>Shift_Data);       //Chuyen thanh cong in
        while(1)
        {
            PORT_LCD_RS &=~ LCD_RS;//RS = 0
            PORT_LCD_RW |= LCD_RW;//RW = 1
            temp_val = LCD_Read_Nibble();
            if((temp_val&0x80)==0)break;
        }
        PORT_LCD_RW &=~ LCD_RW;
        PORT_LCD_DIR |=(0xF0>>Shift_Data);        //Chuyen thanh cong out
}
extern char LCD_Read_Nibble(void)
{
    char H_Nibble,L_Nibble;
    PORT_LCD_OUT|=0xF0>>Shift_Data;

    PORT_LCD_EN |=LCD_EN;
    H_Nibble = (PORT_LCD_IN &(0xF0>>Shift_Data))<<Shift_Data;
    PORT_LCD_EN &=~LCD_EN;

    PORT_LCD_EN |=LCD_EN;
    L_Nibble = (PORT_LCD_IN &(0xF0>>Shift_Data))<<Shift_Data;
    PORT_LCD_EN &=~ LCD_EN;
    L_Nibble>>=4;
    return (H_Nibble|L_Nibble);

}
extern void LCD_Put_Char(char chr)
{
    PORT_LCD_RS |= LCD_RS;
    LCD_Write_Command(chr);

}
extern void LCD_Put_String(char *str)
{
    while(*str)
    {
        LCD_Put_Char(*str);
        str++;
    }
}
extern void LCD_Goto(uint8_t row, uint8_t col)
{
    PORT_LCD_RS &=~LCD_RS;
    if(row == 2)
        LCD_Write_Command(0xC0 + col);
    else
        LCD_Write_Command(0x80 + col);
}
extern void LCD_Cursor_Shift(unsigned char direct, unsigned char step)
{
    unsigned char i;
    PORT_LCD_RS &=~ LCD_RS;
    if (direct == 0)
        for(i=0;i<step;i++)
            LCD_Write_Command(0x10);
    else
        for(i=0;i<step;i++)
            LCD_Write_Command(0x14);
}

void LCD_Put_Decimal(long n, unsigned char length)
{
    unsigned char du,luu=length;
    // de trong 1 ki tu o dau cho hien thi dau
    if(n>=0)LCD_Put_Char(' ');       //In so duong
    else
    {
        LCD_Put_Char('-');           //In so am
        n*=-1;
    }

 //   length--;
    LCD_Cursor_Shift(1,length-1);    // dich con tro sang phai length-1 vi tri
    PORT_LCD_RS &=~LCD_RS;
    #ifdef USE_LCD_WAIT
    LCD_Wait();
    #else
    _delay_cycles(50*Freq_MHz);
    #endif
    LCD_DEC_CUR_SHIFT_OFF();        // chuyen sang che do in lui
    // Bat dau in lan luot cac chu so tu hang don vi
    while(length)
    {
        du = n % 10;
        n = n / 10;
        LCD_Put_Char(0x30 + du);
        length--;
    }
    LCD_Cursor_Shift(1,luu);     // dua con tro sang phai length+1 vi tri de in tiep
    PORT_LCD_RS &=~LCD_RS;
    #ifdef USE_LCD_WAIT
    LCD_Wait();
    #else
    _delay_cycles(50*Freq_MHz);
    #endif
    LCD_INC_CUR_SHIFT_OFF();        // chuyen lai ve che do in xuoi


}

void LCD_Put_Un_Decimal(long n, unsigned char length)
{
    unsigned char du,luu=length;
    LCD_Cursor_Shift(1,length-1);    // dich con tro sang phai length-1 vi tri
    PORT_LCD_RS &=~ LCD_RS;
    #ifdef USE_LCD_WAIT
    LCD_Wait();
    #else
    _delay_cycles(50*Freq_MHz);
    #endif
    LCD_DEC_CUR_SHIFT_OFF();        // chuyen sang che do in lui
    // Bat dau in lan luot cac chu so tu hang don vi
    while(length)
    {
        du = n % 10;
        n = n / 10;
        LCD_Put_Char(0x30 + du);
        length--;
    }
    LCD_Cursor_Shift(1,luu+1);       // dua con tro sang phai length+1 vi tri de in tiep
    PORT_LCD_RS &=~LCD_RS;
    #ifdef USE_LCD_WAIT
    LCD_Wait();
    #else
    _delay_cycles(50*Freq_MHz);
    #endif
    LCD_INC_CUR_SHIFT_OFF();        // chuyen lai ve che do in xuoi


}

/* In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma */
void LCD_Put_Float(float x, unsigned char length, unsigned char coma)
{
    // de trong 1 ki tu o dau cho hien thi dau
    if(x>=0)LCD_Put_Char(' ');
    else
    {
        LCD_Put_Char('-');           //In so am
        x*=-1;
    }
    unsigned long n;
    unsigned char store,temp;
    store = length;                     // Luu lai do dai so thuc.
    length--;                               // Giam di 1 cho dau "."
    for(temp=0;temp<coma;temp++)
        x = x*10;

    n = x;                                  // Chuyan thanh so nguyen.
    if((x-n)>=0.5)n++;

    LCD_Cursor_Shift(1,length);              // Dich chuyen con tro sang phai
    PORT_LCD_RS &=~ LCD_RS;
    #ifdef USE_LCD_WAIT
    LCD_Wait();
    #else
    _delay_cycles(50*Freq_MHz);
    #endif
    LCD_DEC_CUR_SHIFT_OFF();                // Chuyen sang che do in nguoc.

    while(coma)                             // In ra phan truoc dau phay
    {
        temp = n % 10;
        n = n / 10;
        LCD_Put_Char(0x30 + temp);
        coma--;
        length--;
    }

    LCD_Put_Char('.');                           // In ra dau "."

        while(length)                           // In ra phan thap phan
        {
            temp = n % 10;
            n = n / 10;
            //if(temp!=n)
            LCD_Put_Char(0x30 + temp);
            length--;
        }
    PORT_LCD_RS &=~LCD_RS;
    #ifdef USE_LCD_WAIT
    LCD_Wait();
    #else
    _delay_cycles(50*Freq_MHz);
    #endif
    LCD_INC_CUR_SHIFT_OFF();                // Chuyen lai che do in thuan
    LCD_Cursor_Shift(1,store+1);                 // Nhay den vi tri tiep theo.
}


extern void DS1307_LCD_Put_Time(void)
{
    if (day==2)
        LCD_Put_String("Mon");
    if (day==3)
        LCD_Put_String("Tue");
    if (day==4)
        LCD_Put_String("Wed");
    if (day==5)
        LCD_Put_String("Thu");
    if (day==6)
        LCD_Put_String("Fri");
    if (day==7)
        LCD_Put_String("Sat");
    if (day==1)
        LCD_Put_String("Sun");

    LCD_Put_String(", ");
    LCD_Put_Un_Decimal(date,2);
    LCD_Put_Char('/');
    LCD_Put_Un_Decimal(month,2);
    LCD_Put_Char('/');
    LCD_Put_Un_Decimal(20,2);
    LCD_Put_Un_Decimal(year,2);

    LCD_Goto(2,0);
    LCD_Put_String("    ");
    LCD_Put_Un_Decimal(hour,2);
    LCD_Put_String(":");
    LCD_Put_Un_Decimal(min,2);
    LCD_Put_String(":");
    LCD_Put_Un_Decimal(sec,2);

//    LCD_Cursor_Shift(1,3);
}

extern void DS1307_LCD_Put_Time_Blink_Hour(void)
{
    LCD_Goto(2, 6);
    LCD_Put_String("  ");
    _delay_cycles(Time_Blinky*Freq_MHz);

    LCD_Goto(2, 6);
    LCD_Put_Un_Decimal(hour,2);
    _delay_cycles(Time_Blinky*Freq_MHz);
}

extern void DS1307_LCD_Put_Time_Blink_Min(void)
{
    LCD_Goto(2, 9);
    LCD_Put_String("  ");
    _delay_cycles(Time_Blinky*Freq_MHz);

    LCD_Goto(2, 9);
    LCD_Put_Un_Decimal(min,2);
    _delay_cycles(Time_Blinky*Freq_MHz);
}

extern void DS1307_LCD_Put_Time_Blink_Sec(void)
{
    LCD_Goto(2, 12);
    LCD_Put_String("  ");
    _delay_cycles(Time_Blinky*Freq_MHz);

    LCD_Goto(2, 12);
    LCD_Put_Un_Decimal(sec,2);
    _delay_cycles(Time_Blinky*Freq_MHz);
}


extern void DS1307_LCD_Put_Time_Blink_Day(void)
{
    LCD_Goto(1, 0);
    LCD_Put_String("   ");
    _delay_cycles(Time_Blinky*Freq_MHz);

    if (day==2)
        LCD_Put_String("Mon");
    if (day==3)
        LCD_Put_String("Tue");
    if (day==4)
        LCD_Put_String("Wed");
    if (day==5)
        LCD_Put_String("Thu");
    if (day==6)
        LCD_Put_String("Fri");
    if (day==7)
        LCD_Put_String("Sat");
    if (day==1)
        LCD_Put_String("Sun");
    _delay_cycles(Time_Blinky*Freq_MHz);
}

extern void DS1307_LCD_Put_Time_Blink_Date(void)
{
    LCD_Goto(1, 5);
    LCD_Put_String("  ");
    _delay_cycles(Time_Blinky*Freq_MHz);

    LCD_Goto(1, 5);
    LCD_Put_Un_Decimal(date,2);
    _delay_cycles(Time_Blinky*Freq_MHz);
}

extern void DS1307_LCD_Put_Time_Blink_Mon(void)
{
    LCD_Goto(1, 8);
    LCD_Put_String("  ");
    _delay_cycles(Time_Blinky*Freq_MHz);

    LCD_Goto(1, 8);
    LCD_Put_Un_Decimal(month,2);
    _delay_cycles(Time_Blinky*Freq_MHz);
}

extern void DS1307_LCD_Put_Time_Blink_Year(void)
{
    LCD_Goto(1, 11);
    LCD_Put_String("    ");
    _delay_cycles(Time_Blinky*Freq_MHz);

    LCD_Goto(1, 5);
    LCD_Put_Un_Decimal(20,2);
    LCD_Put_Un_Decimal(year,2);
    _delay_cycles(Time_Blinky*Freq_MHz);
}










