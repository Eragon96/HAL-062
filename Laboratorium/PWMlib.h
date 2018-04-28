#ifndef PWMlib_H
#define PWMlib_H

#include "stm32f4xx.h"
//#include "CANlib.h"
#include "GPIOlib.h"
#include "PIDlib.h"
/*#include "ADClib.h"*/
#include <stdlib.h>

/*definicje dlugosci pulsow dla pozycji MIN, MAX, NOM - nominalna-startowa*/

int16_t servo_min_duty[3];
int16_t servo_max_duty[3];
int16_t servo_nom_duty[3];


/*katy do sterowania*/

int16_t servo_min_angle[3];
int16_t servo_max_angle[3];
int16_t servo_nom_angle[3];



void setPWM(volatile int16_t duty[7]);
void setServo (int16_t servo[4]);
void stopMotors(void);
void startMotors(void);
void initPwm(void);
void TIM2_IRQHandler(void);

#endif
