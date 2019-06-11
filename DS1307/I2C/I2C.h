/*
 * I2C.H
 *
 *  Created on: 9 thg 7, 2018
 *      Author: Phong
 */
#include <msp430.h>

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

void I2C_Init(unsigned char slave_address);
void I2C_Write(unsigned char add_register, unsigned char numbyte, unsigned char * poi_send);
void I2C_Read(unsigned char add_register, unsigned char numbyte, unsigned char * poi_read);


#endif /* I2C_I2C_H_ */
