#include "PIDlibF3.h"

//Funkcja moze zwracac strukture, struktura moze zawierac Array
float inertialGain = 0.001;

float currentGainP = 2;
float currentGainI = 0.01;
float currentGainK = 0.1;

//===============================================================================
int16_t velocityRegOut[3];
volatile int16_t velocityRegIntegral[3];
volatile int16_t velocityRegError[3];
volatile int16_t velocityRegSaturation[3];

void setPIVelocity(volatile int16_t referenceVelocity[3]) {
	for (int i = 0; i < 3; i++) {
		velocityRegError[i] = (referenceVelocity[i] - enkPredkosc[i])
				* velocityGainP;
		velocityRegIntegral[i] += (velocityRegError[i]
				- (velocityRegSaturation[i] * velocityGainK)) * velocityGainI;
		velocityRegOut[i] = velocityRegError[i] + velocityRegIntegral[i];
		if (velocityRegOut[i] > 2000) {
			velocityRegSaturation[i] = velocityRegOut[i] - 2000;
			velocityRegOut[i] = 2000;
		} else if (velocityRegOut[i] < -2000) {
			velocityRegSaturation[i] = velocityRegOut[i] + 2000;
			velocityRegOut[i] = -2000;
		}
		referenceData.referenceVelocity[i] = -velocityRegOut[i];
	}
}

//void setPIVelocityAvg(volatile int16_t referenceVelocityAvg[3]) {
//	for (int i = 0; i < 3; i++) {
//		velocityRegError[i] = (referenceVelocity[i] - enkPredkosc[i])
//				* velocityGainP;
//		velocityRegIntegral[i] += (velocityRegError[i]
//				- (velocityRegSaturation[i] * velocityGainK)) * velocityGainI;
//		velocityRegOut[i] = velocityRegError[i] + velocityRegIntegral[i];
//		if (velocityRegOut[i] > 2000) {
//			velocityRegSaturation[i] = velocityRegOut[i] - 2000;
//			velocityRegOut[i] = 2000;
//		} else if (velocityRegOut[i] < -2000) {
//			velocityRegSaturation[i] = velocityRegOut[i] + 2000;
//			velocityRegOut[i] = -2000;
//		}
//		referenceData.referenceVelocityAvg[i] = -velocityRegOut[i];
//	}
//}

//===============================================================================
volatile int16_t currentRegOut[3];
volatile float currentRegIntegral[3];
volatile float currentRegError[3];
volatile int16_t currentRegSaturation[3];

//NIE DZIA£A !!!!!!!! UWAGAA
//void setPICurrent(volatile int16_t referenceCurrent[3]) {
//	for (int i = 0; i < 3; i++) {
//		int16_t referenceValueC = referenceCurrent[i];
//		if (referenceCurrent[i] < 0) {
//			referenceValueC = -referenceValueC;
//		} else if (referenceValueC == 0) {
//			currentRegIntegral[i] = 0;
//		}
//		if (adcFilterValue[i] < 0) {
//			currentRegError[i] = referenceValueC * currentGainP;
//		} else {
//			currentRegError[i] = (referenceValueC - adcFilterValue[i])
//					* currentGainP;
//		}
//		currentRegIntegral[i] += (currentRegError[i]
//				- (currentRegSaturation[i] * currentGainK)) * currentGainI;
//		if (currentRegIntegral[i] < 0) {
//			currentRegIntegral[i] = 0;
//		}
//		currentRegOut[i] =
//				(int16_t) (currentRegError[i] + currentRegIntegral[i]);
//
//		if (currentRegOut[i] > 2000) {
//			currentRegSaturation[i] = currentRegOut[i] - 2000;
//			currentRegOut[i] = 2000;
//		} else if (currentRegOut[i] < 0) {
//			currentRegSaturation[i] = currentRegOut[i];
//			currentRegOut[i] = 0;
//		}
//		if (referenceCurrent[i] < 0) {
//			currentRegOut[i] = -currentRegOut[i];
//		} else if (referenceCurrent[i] == 0) {
//			currentRegOut[i] = 0;
//		}
//		referenceData.referenceCurrent[i] = currentRegOut[i];
//	}
//}

int16_t maxCurrent = 1000;

void setPICurrentLimit(volatile int16_t referenceCurrent[3]) {
	for (int i = 0; i < 3; i++) {
		if (currentRegIntegral[i] != 0 || adcFilterValue[i] > maxCurrent) {
			currentRegError[i] = ((float) (maxCurrent - adcFilterValue[i]))
					* currentGainP;
			currentRegIntegral[i] += (currentRegError[i]
					- (currentRegSaturation[i] * currentGainK)) * currentGainI;
			currentRegOut[i] = (int16_t) (currentRegError[i]
					+ currentRegIntegral[i]);

			if (currentRegOut[i] > 0) {
				currentRegSaturation[i] = currentRegOut[i];
				currentRegOut[i] = 0;
			} else if (referenceCurrent[i] > 0) {
				if (currentRegOut[i] < -referenceCurrent[i]) {
					currentRegSaturation[i] = currentRegOut[i]
							+ referenceCurrent[i];
					currentRegOut[i] = -referenceCurrent[i];
				}
			} else {
				if (currentRegOut[i] < referenceCurrent[i]) {
					currentRegSaturation[i] = currentRegOut[i]
							+ referenceCurrent[i];
					currentRegOut[i] = referenceCurrent[i];
				}
			}
		}
		if (referenceCurrent[i] < 0) {
			referenceData.referenceCurrentLimit[i] = referenceCurrent[i]
			- currentRegOut[i];
		} else if (referenceCurrent[i] > 0) {
			referenceData.referenceCurrentLimit[i] = referenceCurrent[i]
			+ currentRegOut[i];
		} else {
			currentRegIntegral[i] = 0;
			currentRegOut[i] = 0;
			referenceData.referenceCurrentLimit[i] = 0;
			currentRegSaturation[i] = 0;
		}
	}
}

//===============================================================================
volatile float inertialRawData[3];

void setInertialInput(volatile int16_t referenceInput[3]) {
	for (int i = 0; i < 3; i++) {
		inertialRawData[i] += (inertialGain
				* (referenceInput[i] - referenceData.referenceInertial[i]));
		referenceData.referenceInertial[i] = (int16_t) inertialRawData[i];
	}
}

//===============================================================================
void setReferenceSpeed(int16_t speed1, int16_t speed2, int16_t speed3) {
	referenceData.referenceValu[0] = speed1 * powerFactor;
	referenceData.referenceValu[1] = speed2 * powerFactor;
	referenceData.referenceValu[2] = speed3 * powerFactor;
}

//===============================================================================
void resetIntegralValue(void) {
	setPWM(0, 0, 0);
	for (int i = 0; i < 3; i++) {
		currentRegIntegral[i] = 0;
		currentRegSaturation[i] = 0;
		referenceData.referenceCurrent[i] = 0;
		velocityRegIntegral[i] = 0;
		velocityRegSaturation[i] = 0;
		referenceData.referenceVelocity[i] = 0;
		referenceData.referenceValu[i] = 0;
		referenceData.referenceInertial[i] = 0;
	}
}

//===============================================================================
//-2000 to 2000 value
void setPWMreg(volatile int16_t referenceDuty[3]) {
	setPWM(referenceDuty[0], referenceDuty[1], referenceDuty[2]);
}

//===============================================================================
void regulatorSilnikow(void) {
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_10) == Bit_SET) {
		setInertialInput(referenceData.referenceValu);
		setPICurrentLimit(referenceData.referenceInertial);
		setPWMreg(referenceData.referenceCurrentLimit);
		//setPWMreg(referenceData.referenceValu);
	}
}
