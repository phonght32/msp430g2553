/*
 * I2C.H
 *
 *  Created on: 9 thg 7, 2018
 *      Author: Phong
 */
#include <msp430.h>
#include <stdint.h>

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

uint8_t I2C_Read_Buffer[];
uint8_t I2C_Write_Buffer[];

void I2C_Init(unsigned char slave_address);
void I2C_Write_Byte(unsigned char add_register, unsigned char Data);
unsigned char I2C_Read_Byte(unsigned char add_register);
void I2C_Write_Data(unsigned char add_register, unsigned char numbyte, unsigned char * poi_send);
void I2C_Read_Data(unsigned char add_register, unsigned char numbyte, unsigned char * poi_read);


#endif /* I2C_I2C_H_ */
