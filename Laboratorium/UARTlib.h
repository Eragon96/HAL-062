#ifndef UARTlib_H
#define UARTlib_H

#include "stm32f4xx.h"
#include "PWMlib.h"

void initUART();
void USART2_IRQHandler();

int16_t motor[7];
int16_t servo[4];
int8_t incriment_motor;
int8_t incriment_servo;


#endif
