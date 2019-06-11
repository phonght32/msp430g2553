/*
 * DS18B20.c
 *
 *  Created on: Aug 11, 2018
 *      Author: Phong
 */


#include "DS18B20.h"


extern float DS18B20_Get_Temp(void)
{
    unsigned char a,b;
    float Temp;

    DS18B20_Set_Resolution(DS18B20_RESOLUTION);

    while(DS18B20_Reset())
    {

    }
    DS18b20_Write_Byte(0xCC);
    DS18b20_Write_Byte(0x44);
    DS18B20_DQ_High();

    switch(DS18B20_RESOLUTION)
    {
    case 9:  _delay_cycles(100000*Freq_MHz); break;
    case 10: _delay_cycles(200000*Freq_MHz); break;
    case 11: _delay_cycles(400000*Freq_MHz); break;
    case 12: _delay_cycles(800000*Freq_MHz); break;
    default: _delay_cycles(800000*Freq_MHz); //==> default 12bits
    }

    while(DS18B20_Reset())
    {

    }
    DS18b20_Write_Byte(0xCC);
    DS18b20_Write_Byte(0xBE);

    a = DS18B20_Read_Byte();
    b = DS18B20_Read_Byte();

    Temp=((float)(a&0x0f))/16;              // Lay phan thuc cua gia tri nhiet do

    a =((a&0xf0)>>4)|((b&0x0f)<<4) ;    // Lay phan nguyen cua gia tri nhiet do
    Temp=Temp+a;

    return Temp;
}

extern unsigned char DS18B20_Reset(void)
{
    return OneWire_Reset();
}

extern unsigned char DS18B20_Read_Byte(void)
{
        return OneWire_Read_Byte();;
}

extern void DS18b20_Write_Byte(char Data)
{
    OneWire_Write_Byte(Data);
}

extern void DS18B20_DQ_High(void)
{
    OneWire_Pin_High();
}
extern void DS18B20_DQ_Low(void)
{
    OneWire_Pin_Low();
}

extern void DS18B20_Set_Resolution(unsigned int Resolution)
{
    unsigned char resolution_bin;
    switch(Resolution)
    {
    case 9: resolution_bin = 0x1F; break; //09bit = xx ~ R1R0 ~ 00
    case 10: resolution_bin = 0x3F; break; //10bit = xx ~ R1R0 ~ 01
    case 11: resolution_bin = 0x5F; break; //11bit = xx ~ R1R0 ~ 10
    case 12: resolution_bin = 0x7F; break; //12bit = xx ~ R1R0 ~ 11
    default: resolution_bin = 0x7F; //==> default 12bits
    }
    DS18B20_Reset();
    DS18b20_Write_Byte(0xCC);                // Skip ROM
    DS18b20_Write_Byte(0x4E);                // WRITE_SCRATCHPAD
    DS18b20_Write_Byte(0x7f);                //
    DS18b20_Write_Byte(0x80);                //
    DS18b20_Write_Byte(resolution_bin);      // 0xx11111 xx=resolution (9-12 bits)
}




