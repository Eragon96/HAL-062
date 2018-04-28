/*
 * GPS.h
 *
 *  Created on: 6 mar 2018
 *      Author: asd
 */

#ifndef GPS_H_
#define GPS_H_

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>

volatile float dl;
volatile float sz;

void GPSinit(void);           // inicjalizacja UART
void USART1_IRQHandler(void);

#endif /* GPS_H_ */
