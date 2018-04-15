#include "main.h"
#include "CANlibF3.h"
#include "PWMlibF3.h"
#include "GPIOlibF3.h"
#include "ADClibF3.h"
#include "ENKlibF3.h"
#include "PIDlibF3.h"
#include "UARTlibF3.h"
#include "EXTIlibF3.h"

//==================================================================================================
int main(void) {
	RCC_GetClocksFreq(&RCC_Clocks);
	if (SysTick_Config(SystemCoreClock / 1000)) {
		while (1)
			;
	}
	initCan();
	initENK();
	initGpioMotors();
	initGpioLed();
	initPwm();
	initADC();
	//initUART();
	Delay(500);
	//adcSetOffset();
	Delay(200);
//	startMotors();
//	Delay(200);
	adcSetOffset();
	//setReferenceSpeed(50, 50, 50);
	while (1) {
		Delay(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_9);
		Delay(500);
		GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	}
}

//==================================================================================================
void Delay(__IO uint32_t nTime) {
	TimingDelay = nTime;

	while (TimingDelay != 0)
		;
}

uint16_t canWatchdogCounter;

void resetCanWatchdog(void) {
	canWatchdogCounter = 400;
}

void canWatchdog(void) {
	canWatchdogCounter--;
	if (canWatchdogCounter == 0) {
		stopMotors();
	}
}

//==================================================================================================
void TimingDelay_Decrement(void) {
	if (TimingDelay != 0x00) {
		TimingDelay--;
	}
	canWatchdog();
	sendParam();
}

