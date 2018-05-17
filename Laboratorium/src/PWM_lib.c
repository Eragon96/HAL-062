#include "PWM_lib.h"


void PWM_Init()
{
	/*zerowanie silnikow*/

	for (int i=0; i<7;i++)
	{
		motor[i]=0;
	}
	motor_incr=40;		//ustawienie skoku sterowania
	/*Definicja struktur*/

	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef tim;
	NVIC_InitTypeDef NVIC_InitStructure;

	/*Inicjalizacja zegarow GPIO*/

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	/*Inicjalizacja zegarow TIMx*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);



	/*Konfiguracja pinow PWM*/
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);	//Motor BML
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_TIM2);	//Motor BMR
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);	//Motor 1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM13);	//Motor 2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM14);	//Motor 3
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);	//Motor 4
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);		//Motor 5
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);	//Motor 6


	gpio.GPIO_Pin =  GPIO_Pin_8;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &gpio);				//Motor 1

	gpio.GPIO_Pin =  GPIO_Pin_6;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpio);				//Motor 2

	gpio.GPIO_Pin =  GPIO_Pin_7;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpio);				//Motor 3

	gpio.GPIO_Pin =  GPIO_Pin_15;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpio);				//Motor 4

	gpio.GPIO_Pin =  GPIO_Pin_3;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &gpio);				//Motor 5

	gpio.GPIO_Pin =  GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &gpio);				//Motor 6

	gpio.GPIO_Pin =  GPIO_Pin_10;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &gpio);				//Motor BMR

	gpio.GPIO_Pin =  GPIO_Pin_11;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &gpio);				//Motor BML




	/*Konfiguracja pinow INA/B*/

	gpio.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15;		//2A/B, 3B
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &gpio);

	gpio.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_7;	//3A, 4A/B, 5A/B
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &gpio);

	gpio.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_2 |GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_14 |GPIO_Pin_15 ;	// 1A/B 6A/B BML/R
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &gpio);



	/*Konfiguracja timerow PWM silnikowy
	 140MHz -> 70Mhz APB2 -> 35Mhz APB1
	 ABP 1-> Period 7000 10Khz
	 APB 2-> Presclaer 2 Period 7000
	 */
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler = 1;
	tim.TIM_Period = 3500;
	TIM_TimeBaseInit(TIM2, &tim);
	TIM_TimeBaseInit(TIM13, &tim);
	TIM_TimeBaseInit(TIM14, &tim);
	tim.TIM_Prescaler = 4;
	tim.TIM_Period = 1750;
	TIM_TimeBaseInit(TIM10, &tim);
	TIM_TimeBaseInit(TIM11, &tim);



	/*Konfiguracja kanalow*/
	TIM_OCStructInit(&channel);
	channel.TIM_OCMode = TIM_OCMode_PWM1;
	channel.TIM_OutputState = TIM_OutputState_Enable;
	channel.TIM_Pulse = 0;

	TIM_OC3Init(TIM2, &channel);		//Motor BM_R
	TIM_OC4Init(TIM2, &channel);		//Motor BM_L
	TIM_OC1Init(TIM10, &channel);		//Motor 1
	TIM_OC1Init(TIM13, &channel);		//Motor 2
	TIM_OC1Init(TIM14, &channel);		//Motor 3
	TIM_OC1Init(TIM2, &channel);		//Motor 4
	TIM_OC2Init(TIM2, &channel);		//Motor 5
	TIM_OC1Init(TIM11, &channel);		//Motor 6

	/*Let's go*/
	TIM_Cmd(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);



	TIM_Cmd(TIM10, ENABLE);
	TIM_CtrlPWMOutputs(TIM10, ENABLE);

	TIM_Cmd(TIM11, ENABLE);
	TIM_CtrlPWMOutputs(TIM11, ENABLE);


	TIM_Cmd(TIM13, ENABLE);
	TIM_CtrlPWMOutputs(TIM13, ENABLE);


	TIM_Cmd(TIM14, ENABLE);
	TIM_CtrlPWMOutputs(TIM14, ENABLE);


	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM10, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM11, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM13, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
	GPIO_SetBits(GPIOE, GPIO_Pin_14);
	GPIO_SetBits(GPIOE, GPIO_Pin_15);

	/*NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM13, TIM_IT_Update, ENABLE);*/


}

void set_pwm(int16_t duty[7])
{

		/*Motor 1*/
		if (duty[0] > 0)
		{
			TIM_SetCompare4(TIM2, 0);
			TIM_SetCompare3(TIM2, duty[0]);
		}
		else
		{
			TIM_SetCompare3(TIM2, 0);
			TIM_SetCompare4(TIM2, -duty[0]);
		}
		if (duty[1] > 0)
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_2);
			GPIO_ResetBits(GPIOE, GPIO_Pin_3);
			TIM_SetCompare1(TIM10, duty[1]);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_3);
			GPIO_ResetBits(GPIOE, GPIO_Pin_2);
			TIM_SetCompare1(TIM10, -duty[1]);
		}

		/*Motor 2*/
		if (duty[2] > 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_14);
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			TIM_SetCompare1(TIM13, duty[2]);
		}
		else
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			GPIO_ResetBits(GPIOC, GPIO_Pin_14);
			TIM_SetCompare1(TIM13, -duty[2]);
		}


		/*Motor 3*/
		if (duty[3] > 0)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
			GPIO_ResetBits(GPIOC, GPIO_Pin_15);
			TIM_SetCompare1(TIM14, duty[3]);
		}
		else
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_15);
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
			TIM_SetCompare1(TIM14, -duty[3]);
		}


		/*Motor 4*/
		if (duty[4] > 0)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_1);
			GPIO_ResetBits(GPIOD, GPIO_Pin_0);
			TIM_SetCompare1(TIM2, duty[4]);
		}
		else
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_0);
			GPIO_ResetBits(GPIOD, GPIO_Pin_1);
			TIM_SetCompare1(TIM2, -duty[4]);
		}

		/*Motor 5*/
		if (duty[5] > 0)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_7);
			GPIO_ResetBits(GPIOD, GPIO_Pin_4);
			TIM_SetCompare2(TIM2, duty[5]);
		}
		else
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_4);
			GPIO_ResetBits(GPIOD, GPIO_Pin_7);
			TIM_SetCompare2(TIM2, -duty[5]);
		}


		/*Motor 6*/
		if (duty[6] > 0)
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_4);
			GPIO_ResetBits(GPIOE, GPIO_Pin_0);
			TIM_SetCompare1(TIM11, duty[6]);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_0);
			GPIO_ResetBits(GPIOE, GPIO_Pin_4);
			TIM_SetCompare1(TIM11, -duty[6]);
		}
		USART_SendData(USART2, duty[1]);

}
