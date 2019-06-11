/*
 * SPI.h
 *
 *  Created on: Sep 11, 2018
 *      Author: ThanhPhong
 */

#include <msp430.h>
#include <stdint.h>
#include "../define.h"

#ifndef SPI_H_
#define SPI_H_

void SPI_A_Init(void);
void SPI_B_Init(void);

void Send_byte_A(int data, int time_ms);
void Send_byte_B(int data, int time_ms);
void SPI_A_Put_Data(int data, int time_ms);
void SPI_b_Put_Data(int data, int time_ms);





#endif /* SPI_H_ */
