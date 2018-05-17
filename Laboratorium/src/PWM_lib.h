#ifndef PWM_LIB_H_
#define PWM_LIB_H_

#include "stm32f4xx.h"


TIM_OCInitTypeDef channel;
int16_t motor_incr;
volatile int16_t motor[7];



void PWM_Init();

void set_pwm(int16_t duty[7]);

#endif /* USART_LIB_H_ */
