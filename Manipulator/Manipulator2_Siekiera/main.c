#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitStructure;
void RCC_CONF();
volatile RCC_ClocksTypeDef RCC_Clocks;
void usart_Init();

int main(void) {
	RCC_CONF();

	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_2);

	usart_Init();
int i=0;
	while (1) {

		//GPIO_ToggleBits(GPIOE, GPIO_Pin_1);
		//GPIO_ToggleBits(GPIOB, GPIO_Pin_2);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET) {
			;
		}
		USART_SendData(USART2, 'c');
		RCC_GetClocksFreq(&RCC_Clocks);
	}
}

/* Private functions */

// Clock configuration and initialization:
void RCC_CONF() {
	//SYSCLK 100MHz:
	RCC_DeInit();

	RCC_HSEConfig(RCC_HSE_ON);
	while (RCC_WaitForHSEStartUp() != SUCCESS)
		;

	RCC_PLLConfig(RCC_PLLSource_HSE, 4, 140, 2, 4);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_PCLK2Config(RCC_HCLK_Div2);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_PLLCmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET)
		;

	//SysTick initialisation:
	//SysTick_Config(TIMEOUT_CNT);
	RCC_GetClocksFreq(&RCC_Clocks);
	if (SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 1000)) {
		while (1) {
			GPIO_ToggleBits(GPIOE, GPIO_Pin_1);
			GPIO_ToggleBits(GPIOB, GPIO_Pin_2);
		}
	}
}
;

void SysTickfun(void) {
	GPIO_ToggleBits(GPIOE, GPIO_Pin_1);
	GPIO_ToggleBits(GPIOB, GPIO_Pin_2);
}

void usart_Init() {

	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	NVIC_InitTypeDef NVIC_InitStructure;

	/*USART*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_5;
	gpio.GPIO_Speed = GPIO_High_Speed;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOD, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOD, &gpio);

	uart.USART_BaudRate = 115200;
	uart.USART_WordLength = USART_WordLength_8b;
	uart.USART_StopBits = USART_StopBits_2;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &uart);
	USART_Cmd(USART2, ENABLE);

//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

