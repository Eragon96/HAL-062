/*
 * CAN.h
 *
 *  Created on: 17.05.2018
 *      Author: Konrad
 */

#ifndef MANIPULATOR2_SIEKIERA_CAN_H_
#define MANIPULATOR2_SIEKIERA_CAN_H_

#include"main.h"

CanTxMsg txMessage;
CanRxMsg rxMessage;

void initCan(void);
void CAN1_RX0_IRQHandler(void);

void CAN_send_data(void);

#endif /* MANIPULATOR2_SIEKIERA_CAN_H_ */
