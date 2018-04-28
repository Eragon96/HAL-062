/*
 * CommunicationF3.h
 *
 *  Created on: 26.04.2018
 *      Author: Konrad
 */

#ifndef COMMUNICATIONF3_H_
#define COMMUNICATIONF3_H_

#include "main.h"


void loadCommandList(void);
uint8_t getLength(uint8_t dataId);
void runCanAction(CanRxMsg * a);


typedef struct command{
	uint8_t Id;
	uint8_t length;
	void (*reciveCanAction) (CanRxMsg * a);
}command;

command commandList[150];

#endif /* COMMUNICATIONF3_H_ */
