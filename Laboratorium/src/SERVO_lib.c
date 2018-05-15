#include "SERVO_lib.h"

void SERVO_Init()
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef tim;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef servo;				//zeby sie nie klocilo z channel globalnym w PWM_lib()

	/*Inicjalizacja zegarow GPIO*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/*Inicjalizacja zegarow TIM*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/*Konfiguracja pinow PWM*/
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);	//OUT1
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);		//OUT2
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);		//OUT3

	gpio.GPIO_Pin =  GPIO_Pin_15;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOD, &gpio);

	gpio.GPIO_Pin =  GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &gpio);

	gpio.GPIO_Pin =  GPIO_Pin_8;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &gpio);

	//PRESCALER 4, SYSTICK 168MHz, w rzeczywistosci 53,76Mhz -> TIM_Freq = 13,44 Mhz -> 50Hz
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler = 27;
	tim.TIM_Period = 10000;
	TIM_TimeBaseInit(TIM3, &tim);
	TIM_TimeBaseInit(TIM4, &tim);

	TIM_OCStructInit(&servo);
	servo.TIM_OCMode = TIM_OCMode_PWM1;
	servo.TIM_OutputState = TIM_OutputState_Enable;
	servo.TIM_Pulse = 750;

	TIM_OC3Init(TIM3, &servo);
	TIM_OC4Init(TIM3, &servo);
	TIM_OC4Init(TIM4, &servo);

	TIM_Cmd(TIM3, ENABLE);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);

	TIM_Cmd(TIM4, ENABLE);
	TIM_CtrlPWMOutputs(TIM4, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn | TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);



}
void set_servo(int16_t duty)
{
	TIM_SetCompare4(TIM4, duty);
	USART_SendData(USART2, (duty-750));
}
