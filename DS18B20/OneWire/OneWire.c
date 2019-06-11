/*
 * OneWire.c
 *
 *  Created on: Aug 14, 2018
 *      Author: Phong
 */
#include "OneWire.h"

extern void OneWire_Write_Byte(char Data)
{
    unsigned char i=0;
    for(i=0;i<8;i++)
    {
        if(Data&0x01)
        {
            OneWire_Pin_Low();
            _delay_cycles(5*Freq_MHz);
            OneWire_Pin_High();
            _delay_cycles(65*Freq_MHz);
        }
        else
        {
            OneWire_Pin_Low();
            _delay_cycles(70*Freq_MHz);
            OneWire_Pin_High();
        }
        _delay_cycles(5*Freq_MHz);
        Data =  Data>>1;
    }
}

extern unsigned char OneWire_Read_Byte(void)
{
    unsigned char i=0;
    unsigned char Data=0,bit;
    for(i=0;i<8;i++)
    {
        OneWire_Pin_Low();
        _delay_cycles(2*Freq_MHz);
        OneWire_Pin_High();
        _delay_cycles(2*Freq_MHz);
        PORT_OneWire_DIR &=~PIN_OneWire_DQ;
        if(PORT_OneWire_IN&PIN_OneWire_DQ)
        {
            bit = 1<<i;
        }
        else
        {
            bit = 0<<i;
        }
        _delay_cycles(45*Freq_MHz);
        Data = Data + bit;
        OneWire_Pin_High();
        _delay_cycles(5*Freq_MHz);
    }
    return Data;
}

extern unsigned char OneWire_Reset(void)
{
    OneWire_Pin_Low();
    _delay_cycles(500*Freq_MHz);
    OneWire_Pin_High();
    _delay_cycles(80*Freq_MHz);
    PORT_OneWire_DIR &=~ PIN_OneWire_DQ;
    if(!(PORT_OneWire_IN&PIN_OneWire_DQ))
    {
        return 0;       //Device is OK
    }
    OneWire_Pin_High();
    return 1;           //Device don't transmit a presence pulse
}

extern void OneWire_Pin_Low(void)
{
    PORT_OneWire_DIR |= PIN_OneWire_DQ;
    PORT_OneWire_OUT &=~ PIN_OneWire_DQ;
}
extern void OneWire_Pin_High(void)
{
    PORT_OneWire_DIR |= PIN_OneWire_DQ;
    PORT_OneWire_OUT |= PIN_OneWire_DQ;
}




