/*
 * RCC.c
 *
 *  Created on: 17.05.2018
 *      Author: Konrad
 */

/*Inicjalziacja zegara
 * SYSCLK 144 MHz
 * HCLK 144MHz
 * PCLK1 36MHz
 * PCLK2 72MHZ
 * Systick - 1kHz
 *
 *  */

#include "RCC.h"

void RCC_CONF(void){
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_WaitForHSEStartUp() != SUCCESS);

	RCC_PLLConfig(RCC_PLLSource_HSE, 4, 144, 2, 4);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_PCLK2Config(RCC_HCLK_Div2);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

	//SysTick initialisation:
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	if (SysTick_Config(RCC_Clocks.SYSCLK_Frequency/ 1000)) {
		/* Capture error */
		while (1)
			;
	}
};

volatile uint16_t delayTimer;

void delay(uint16_t time){
	delayTimer= time;
	while(delayTimer!=0){
		;
	}
}

void TimingDelay_Decrement(void){
	if(delayTimer>0){
		delayTimer--;
	}
}


void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}
