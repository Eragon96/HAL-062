#include "main.h"
//#include "CANlib.h"
#include "PWMlib.h"
#include "GPIOlib.h"
#include "ADClib.h"
/*#include "ENKlib.h"*/
#include "PIDlib.h"
#include "UARTlib.h"
/*#include "EXTIlib.h"*/

#define TIMEOUT 10 //in ms
#define SYSTICK_FREQ 100000000
#define TIMEOUT_CNT SYSTICK_FREQ*TIMEOUT/(1000)
void RCC_CONF(){
    //SYSCLK 100MHz:
    RCC_DeInit();

    RCC_HSEConfig(RCC_HSE_ON);
    while(RCC_WaitForHSEStartUp() != SUCCESS);

    RCC_PLLConfig(RCC_PLLSource_HSE, 8, 200, 4, 4);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div4);
    RCC_PCLK2Config(RCC_HCLK_Div2);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

    //SysTick initialisation:
    SysTick_Config(TIMEOUT_CNT);
}
//==================================================================================================
int main(void) {
	RCC_CONF();
	RCC_GetClocksFreq(&RCC_Clocks);
	if (SysTick_Config(SystemCoreClock / 1000)) {
		while (1)
			;
	}
	//initCan();
	//initENK();
	initGpioMotors();
	initGpioLed();
	initPwm();
	startMotors();
	int16_t test[7];
	test[0]=0;
	test[1]=1000;
	test[2]=1000;
	test[3]=1000;
	test[4]=1000;
	test[5]=1000;
	test[6]=1000;
	setPWM(test);
	//initADC();
	initUART();
	//Delay(500);
	//adcSetOffset();
	//Delay(200);
//	startMotors();
//	Delay(200);
	//adcSetOffset();
	//setReferenceSpeed(50, 50, 50);
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	while (1) {

			while(USART_GetFlagStatus(USART2, USART_FLAG_TXE)==RESET);
			USART_SendData(USART2, 'X');
		}


		//Delay(500);
		//GPIO_SetBits(GPIOB,GPIO_Pin_2);
		//GPIO_SetBits(GPIOB,GPIO_Pin_2);
		//Delay(500);
		//GPIO_ResetBits(GPIOB,GPIO_Pin_2);

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
	//sendParam();
}

