/*
 * ComuniactionLib.h
 *
 *  Created on: 18.04.2018
 *      Author: Konrad
 */

#ifndef COMMUNIACTIONLIB_H_
#define COMMUNIACTIONLIB_H_

#include "UARTlib.h"
#include "CANlib.h"
#include "main.h"

void loadCommandList(void);
uint8_t getLength(uint8_t dataId);
void runCanAction(CanRxMsg * a);
void runUartAction(uint8_t * a);



typedef struct command{
	uint8_t Id;
	uint8_t length;
	void (*reciveUartAction) (uint8_t * a);
	void (*reciveCanAction) (CanRxMsg * a);
}command;

command commandList[150];

#endif /* COMMUNIACTIONLIB_H_ */
