/*
 * OneWire.h
 *
 *  Created on: Aug 14, 2018
 *      Author: Phong
 */

#include <msp430.h>
#include "../define.h"

#ifndef ONEWIRE_ONEWIRE_H_
#define ONEWIRE_ONEWIRE_H_



#define PORT_OneWire_DIR    P2DIR
#define PORT_OneWire_IN     P2IN
#define PORT_OneWire_OUT    P2OUT
#define PORT_OneWire_REN    P2REN
#define PIN_OneWire_DQ      BIT0

extern void OneWire_Write_Byte(char Data);
extern unsigned char OneWire_Read_Byte(void);
extern void OneWire_Pin_Low(void);
extern void OneWire_Pin_High(void);
extern unsigned char OneWire_Reset(void);




#endif /* ONEWIRE_ONEWIRE_H_ */
