#ifndef PIDlib_H
#define PIDlib_H

#include "stm32f4xx.h"
/*#include "ENKlib.h"*/
//#include "CANlib.h"
#include "PWMlib.h"
#include "ADClib.h"
/*#include "EXTIlib.h"*/


typedef struct {
	volatile int16_t referenceValu[7];
	volatile int16_t referenceVelocity[7];
	volatile int16_t referenceVelocityAvg[7];
	volatile int16_t referenceCurrent[7];
	volatile int16_t referenceCurrentLimit[7];
	volatile int16_t referenceInertial[7];

} regulatorOut_TypeDef;

regulatorOut_TypeDef referenceData;

void resetIntegralValue(void);
void setReferenceSpeed(int16_t speed[7]);
void regulatorSilnikow(void);

uint16_t velocityGainP;
uint16_t velocityGainI;
uint16_t velocityGainK;

float inertialGain;

#endif
