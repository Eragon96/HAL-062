/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 7.0.1   2018-02-18

The MIT License (MIT)
Copyright (c) 2009-2016 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "defines.h"

const char* string = "Connected\n\r";
char c = 'c';

/* Private macro */
#define PWM_Value 300
#define TIMEOUT 10 //in ms
#define SYSTICK_FREQ 100000000
#define TIMEOUT_CNT SYSTICK_FREQ*TIMEOUT/(1000)
/* Private variables */
volatile long keyTimeout = 0;
int vel1 = 200;
int vel2 = 400;

/* Private function prototypes */
void RCC_CONF();
void GPIO_CONF();
void USART_CONF();
void TIM_CONF();
void NVIC_Conf();

void send_char(char, USART_TypeDef*);
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
void send_string(const char*, USART_TypeDef*);


volatile RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
  RCC_CONF();
  GPIO_CONF();
  USART_CONF();
  NVIC_Conf();
  TIM_CONF();


  while (1)
  {
  }
}

/* Private functions */

// Clock configuration and initialization:
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
};

void GPIO_CONF(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	//MOTOR_1_PWM:

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);

	//MOTOR_2_PWM:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);

	//MOTOR_3_PWM:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);

	//MOTOR_4_PWM:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);

	//MOTOR_5_PWM:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

	//MOTOR_6_PWM:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);

	//BM_PWM:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_TIM2);

	//Servo PWM:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);

	/*//MOTOR_1_IN:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	GPIO_ResetBits(GPIOE, GPIO_Pin_2);*/

	/*//MOTOR_2_IN:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	GPIO_ResetBits(GPIOC, GPIO_Pin_14);*/

	/*//MOTOR_3_IN:

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_Pin_15);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);*/

	//MOTOR_4_IN (first degree):

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_0);
	GPIO_ResetBits(GPIOD, GPIO_Pin_1);

	//MOTOR_5_IN: (third degree)

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_4);
	GPIO_ResetBits(GPIOD, GPIO_Pin_7);

	//MOTOR_6_IN: (fourth degree)

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_4);
	GPIO_ResetBits(GPIOE, GPIO_Pin_0);

	//BM_ENABLE: (second degree)

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_14);
	GPIO_SetBits(GPIOE, GPIO_Pin_15);

	//LED_GREEN:
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);

	//USART_2:
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
};

void USART_CONF(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_InitTypeDef USART_Init_Structure;

	USART_Init_Structure.USART_BaudRate = 9600;
	USART_Init_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init_Structure.USART_WordLength = USART_WordLength_8b;
	USART_Init_Structure.USART_StopBits = USART_StopBits_1;
	USART_Init_Structure.USART_Parity = USART_Parity_No;
	USART_Init_Structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_Init_Structure);
	USART_Cmd(USART2, ENABLE);
}

void TIM_CONF(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_InitStructure;//50 MHz clock
	TIM_InitStructure.TIM_Prescaler = 50; // 1 MHz
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 1000; //1 KHz
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStructure);

	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = 0; //50%

	TIM_OC3Init(TIM4, &TIM_OCInitStruct);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM4, &TIM_OCInitStruct);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_Cmd(TIM4, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//50 MHz clock
	TIM_InitStructure.TIM_Prescaler = 125; // 200 kHz
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 4000; //1 KHz
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_InitStructure);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = 0; //10%

	TIM_OC1Init(TIM3, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_InitStructure.TIM_Prescaler = 50; // 1 MHz
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 1000; //1 KHz
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = 0;

	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_Cmd(TIM2, ENABLE);
};

void NVIC_Conf(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_SetPriority(USART2_IRQn, 1);
	NVIC_EnableIRQ(USART2_IRQn);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

//Sending data over USART:

void send_char(char c, USART_TypeDef* USART)
{
    while (USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET);
    USART_SendData(USART, c);
}

void send_string(const char* s, USART_TypeDef* USART)
{
    while (*s)
        send_char(*s++, USART);
}

void USART2_IRQHandler (void) {
	   if(USART_GetITStatus(USART2, USART_IT_RXNE))
	   {
		   keyTimeout = 0;
		   char received = USART_ReceiveData(USART2);
		   send_char(received, USART2);
		   switch(received)
		        {
		            case 'a':
		            	GPIO_SetBits(GPIOD, GPIO_Pin_0);
		            	GPIO_ResetBits(GPIOD, GPIO_Pin_1);
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	TIM_SetCompare1(TIM2,400);
		                break;
		            case 'q':
		            	GPIO_ResetBits(GPIOD, GPIO_Pin_0);
		            	GPIO_SetBits(GPIOD, GPIO_Pin_1);
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	TIM_SetCompare1(TIM2,400);
		                break;
		            case 'w':
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	TIM_SetCompare3(TIM2,250);
		            	TIM_SetCompare4(TIM2,0);
		                break;
		            case 's':
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	TIM_SetCompare3(TIM2,0);
		            	TIM_SetCompare4(TIM2,250);
		                break;
		            case 'e':
		            	GPIO_SetBits(GPIOD, GPIO_Pin_4);
		            	GPIO_ResetBits(GPIOD, GPIO_Pin_7);
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	TIM_SetCompare2(TIM2,1000);
		                break;
		            case 'd':
		            	GPIO_ResetBits(GPIOD, GPIO_Pin_4);
		            	GPIO_SetBits(GPIOD, GPIO_Pin_7);
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	TIM_SetCompare2(TIM2,1000);
		                break;
		            case 'r':
		            	GPIO_SetBits(GPIOE, GPIO_Pin_0);
		            	GPIO_ResetBits(GPIOE, GPIO_Pin_4);
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	TIM_SetCompare4(TIM4,200);
		                break;
		            case 'f':
		            	GPIO_ResetBits(GPIOE, GPIO_Pin_0);
		            	GPIO_SetBits(GPIOE, GPIO_Pin_4);
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	TIM_SetCompare4(TIM4,200);
		                break;
		            case 't':
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	vel1-=10;
		            	vel2+=10;
		            	//if(vel1 < 200){
		            	//	vel1 = 200;
		            	//}
		            	//if(vel2 > 400){
		            	//	vel2 = 400;
		            	//}
		            	send_char(vel1, USART2);
		            	TIM_SetCompare1(TIM3, vel1);
		            	TIM_SetCompare2(TIM3, vel2);
		                break;
		            case 'g':
		            	GPIO_SetBits(GPIOB, GPIO_Pin_2);
		            	vel1+=10;
		            	vel2-=10;
		            	//if(vel2 < 200){
		            	//	vel2 = 200;
		            	//}
		            	//if(vel1 > 400){
		            		//vel1 = 400;
		            	//}
		            	send_char(vel1, USART2);
		            	TIM_SetCompare1(TIM3,vel1);
		            	TIM_SetCompare2(TIM3,vel2);
		                break;
		            case 'h':
		            	TIM_SetCompare1(TIM3,400);
		            	TIM_SetCompare2(TIM3,400);
		            	break;
		            default:
		            	TIM_SetCompare1(TIM2,0);
		            	TIM_SetCompare2(TIM2,0);
		            	TIM_SetCompare3(TIM2,0);
		            	TIM_SetCompare4(TIM2,0);
		            	TIM_SetCompare1(TIM3,0);
		            	TIM_SetCompare2(TIM3,0);
		            	TIM_SetCompare3(TIM4,0);
		            	TIM_SetCompare4(TIM4,0);
		                break;
		        }
	      USART_ClearITPendingBit(USART2, USART_FLAG_RXNE);
	      GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	   }
}

void SysTick_Handler(void)
{
	if(keyTimeout++ > TIMEOUT)
	{
    	TIM_SetCompare1(TIM2,0);
    	TIM_SetCompare2(TIM2,0);
    	TIM_SetCompare3(TIM2,0);
    	TIM_SetCompare4(TIM2,0);
    	//TIM_SetCompare1(TIM3,0);
    	//TIM_SetCompare2(TIM3,0);
    	TIM_SetCompare3(TIM4,0);
    	TIM_SetCompare4(TIM4,0);
		keyTimeout = 0;
	}
}

