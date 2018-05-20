/*
 * RCC.h
 *
 *  Created on: 17.05.2018
 *      Author: Konrad
 */

#ifndef MANIPULATOR2_SIEKIERA_RCC_H_
#define MANIPULATOR2_SIEKIERA_RCC_H_

#include "main.h"

/*
 * UWAGA!!
 * Wymaga usuniêcia SysTick_Handler z stm32f4xx_it.c
 * Odwo³uje siê do
 */

void RCC_CONF(void);
void SysTick_Handler(void);
void delay(uint16_t time);

#endif /* MANIPULATOR2_SIEKIERA_RCC_H_ */
