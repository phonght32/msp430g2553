/*
 * DS18B20.h
 *
 *  Created on: Aug 11, 2018
 *      Author: Phong
 */
#include <msp430.h>
#include "../OneWire/OneWire.h"
#include "../define.h"

#ifndef DS18B20_DS18B20_H_
#define DS18B20_DS18B20_H_

#define DS18B20_RESOLUTION      11



extern unsigned char DS18B20_Reset(void);
extern unsigned char DS18B20_Read_Byte(void);
extern void DS18b20_Write_Byte(char dat);
extern void DS18B20_DQ_High(void);
extern void DS18B20_DQ_Low(void);
extern float DS18B20_Get_Temp(void);
extern void DS18B20_Set_Resolution(unsigned int resolution);



#endif /* DS18B20_DS18B20_H_ */
