#include "main.h"

//===================================================================================================

int main(void) {
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	if (SysTick_Config(SystemCoreClock / 1000)) {
		/* Capture error */
		while (1)
			;
	}
	initGPIO();
	GPSinit();
	IMUinit();
	MAGinit();
	initCan();
	loadCommandList();
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==Bit_RESET){
		initUart3();
		useBluetooth=1;
	}else{
		initUart2();
		useBluetooth=0;
	}
	buzzerInit();
	lazikRuch = 1;
	buzzerOn(250, 500, 2);
	GPIO_SetBits(GPIOH, GPIO_Pin_1);
	GPIO_ResetBits(GPIOH, GPIO_Pin_0);
	while (1) {
		delay(300);
	}
}

//==================================================================================================
/**
 * @brief  Inicjalizacaj GPIO PC0 PC1 jako wyjœcia
 * @note  	Inicjalizacja pinów pod³¹czonych do diod LED jako wyjœcia
 * 			PC0 - czerwona dioda
 * 			PC1 - zolta dioda
 * @retval None
 */
void initGPIO() {

	GPIO_InitTypeDef gpio;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_StructInit(&gpio); // domyslna konfiguracja
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOH, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOH, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio);
}

//==================================================================================================
/**
 * @brief  funkcja relizujaca opóŸnienie
 * @note   funkcja wykorzystuje systick do dok³adengo okreslenia czasu
 * @param  nTime wartosc okresljajaca opoznienie w ms (od 0 do 32bit)
 * @retval None
 */
void delay(__IO uint32_t nTime) {
	opoznienie = nTime;

	while (opoznienie != 0)
		;
}

//==================================================================================================
/**
 * @brief  funkcja resetujaca Timer
 * @note   funkcja wykorzystuje systick do dok³adengo okreslenia czasu
 * 		   funkcja uzywana do testowania komunikacji jesli wartosc timingDelay
 * 		   spadnie do 0 lazik zatrzyma sie
 * @retval None
 */
void ResetTimer() {
	lazikRuch = 1;
	timingDelay = wartoscOpoznienia;
}

//==================================================================================================
/**
 * @brief  przerwanie od Systick co 1ms
 * @note   synchronizuje czasowo inne funkcje
 * @retval None
 */
void SysTick_Handler(void) {
	static int8_t a;
	if (timingDelay != 0) {
		timingDelay--;
	}
	if (opoznienie != 0) {
		opoznienie--;
	}
	if (timingDelay == 0 && lazikRuch != 0) {
		sendStop(STOP);
		lazikRuch = 0;
	}
	if(a==20){
		I2CstartDataAcquisition();
		I2C3startDataAcquisition();
		a=0;
	}
	a++;
}

