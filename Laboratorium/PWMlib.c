#include "PWMlib.h"


TIM_OCInitTypeDef channel;

//==================================================================================================
//funkcja inicjalizuje wszystkie niezbedne Timery w tryb PWM
void initPwm() {

	servo_min_duty[0] = 840;
	servo_max_duty[0] = 1680;
	servo_nom_duty[0] = 1260;

	servo_min_duty[1] = 840;
	servo_max_duty[1] = 1680;
	servo_nom_duty[1] = 1260;

	servo_min_duty[2] = 840;
	servo_max_duty[2] = 1680;
	servo_nom_duty[2] = 1260;

	servo_min_angle[0] = 0;
	servo_max_angle[0] = 180;
	servo_nom_angle[0] = 90;

	servo_min_angle[1] = 0;
	servo_max_angle[1] = 180;
	servo_nom_angle[1] = 90;

	servo_min_angle[2] = 0;
	servo_max_angle[2] = 180;
	servo_nom_angle[2] = 90;

	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef tim2;
	TIM_TimeBaseInitTypeDef tim3;
	TIM_TimeBaseInitTypeDef tim4;
	TIM_TimeBaseInitTypeDef tim10;
	TIM_TimeBaseInitTypeDef tim11;
	TIM_TimeBaseInitTypeDef tim13;
	TIM_TimeBaseInitTypeDef tim14;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//uruchamiamy szynê A
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//uruchamiamy szynê B
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//uruchamiamy szynê C
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//uruchamiamy szynê D


	/* uruchamiamy timery*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

//Motor BM TIM2 ch3 ch4
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);	//R
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_TIM2);	//L
//Motor1 TIM10 ch1
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);
//Motor2 TIM13 ch1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM13);
//Motor3 TIM14 ch1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM14);
//Motor4 TIM2 ch1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
//Motor5 TIM2 ch2
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
//Motor6 TIM11 ch1
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);
//OUT1 TIM4_CH4
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
//OUT2 TIM3_CH4
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);
//OUT3 TIM3_CH3
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);

	/*inicjalizacja pinow do AF*/

//GPIOA
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_15;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpio);
//GPIOB
	gpio.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &gpio);
//GPIOC
	gpio.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &gpio);
//GPIOD
	gpio.GPIO_Pin =  GPIO_Pin_15;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOD, &gpio);


	/* Czestotliowsc na timerach - 42 MHz. Docelowo na silnikach 10 kHz*/
	TIM_TimeBaseStructInit(&tim2);
	tim2.TIM_CounterMode = TIM_CounterMode_Up;
	tim2.TIM_Prescaler = 1;
	tim2.TIM_Period = 4200;
	TIM_TimeBaseInit(TIM2, &tim2);

	TIM_TimeBaseStructInit(&tim10);
	tim10.TIM_CounterMode = TIM_CounterMode_Up;
	tim10.TIM_Prescaler = 1;
	tim10.TIM_Period = 4200;
	TIM_TimeBaseInit(TIM10, &tim10);

	TIM_TimeBaseStructInit(&tim11);
	tim11.TIM_CounterMode = TIM_CounterMode_Up;
	tim11.TIM_Prescaler = 1;
	tim11.TIM_Period = 4200;
	TIM_TimeBaseInit(TIM11, &tim11);

	TIM_TimeBaseStructInit(&tim13);
	tim13.TIM_CounterMode = TIM_CounterMode_Up;
	tim13.TIM_Prescaler = 1;
	tim13.TIM_Period = 4200;
	TIM_TimeBaseInit(TIM13, &tim13);

	TIM_TimeBaseStructInit(&tim14);
	tim14.TIM_CounterMode = TIM_CounterMode_Up;
	tim14.TIM_Prescaler = 1;
	tim14.TIM_Period = 4200;
	TIM_TimeBaseInit(TIM14, &tim14);

	/*SERWA - 50Hz*/
	/*42Mhz. Prescaler=20 -> 2100Khz. Period =42000 ->50Hz */
	TIM_TimeBaseStructInit(&tim3);
	tim3.TIM_CounterMode = TIM_CounterMode_Up;
	tim3.TIM_Prescaler = 20;
	tim3.TIM_Period = 42000;
	TIM_TimeBaseInit(TIM3, &tim3);


	TIM_TimeBaseStructInit(&tim4);
	tim4.TIM_CounterMode = TIM_CounterMode_Up;
	tim4.TIM_Prescaler = 20;
	tim4.TIM_Period = 42000;
	TIM_TimeBaseInit(TIM4, &tim4);


	/*inicjalizacja PWM*/
	TIM_OCStructInit(&channel);
	/*Ustawienia w funkcji start motors*/

	channel.TIM_Pulse = 1260;


	TIM_OC3Init(TIM3, &channel);
	TIM_OC4Init(TIM3, &channel);
	TIM_OC4Init(TIM4, &channel);



	TIM_Cmd(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
	TIM_Cmd(TIM10, ENABLE);
	TIM_CtrlPWMOutputs(TIM10, ENABLE);
	TIM_Cmd(TIM11, ENABLE);
	TIM_CtrlPWMOutputs(TIM11, ENABLE);
	TIM_Cmd(TIM13, ENABLE);
	TIM_CtrlPWMOutputs(TIM13, ENABLE);
	TIM_Cmd(TIM14, ENABLE);
	TIM_CtrlPWMOutputs(TIM14, ENABLE);



//konfiguracja wektorow przerwan
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn | TIM3_IRQn | TIM4_IRQn |TIM1_UP_TIM10_IRQn |TIM1_TRG_COM_TIM11_IRQn |
			TIM8_UP_TIM13_IRQn | TIM8_TRG_COM_TIM14_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM10, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM11, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM13, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);

	resetIntegralValue();
}
//==================================================================================================
//Ustawia pedkosci kolejnych silnikow (wypelnieniePWM)
void setPWM(volatile int16_t duty[7]) {

	/*Motor BM*/

	if (duty[0] > 0)
	{
		TIM_SetCompare2(TIM2, 0);
		TIM_SetCompare3(TIM2, duty[0]);
	}
	else
	{
		TIM_SetCompare3(TIM2, 0);
		TIM_SetCompare2(TIM2, -duty[0]);
	}
	/*Motor 1*/
	if (duty[1] > 0)
	{
		GPIO_SetBits(GPIOE, GPIO_Pin_2);
		GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	}
	else
	{
		GPIO_SetBits(GPIOE, GPIO_Pin_3);
		GPIO_ResetBits(GPIOE, GPIO_Pin_2);
	}
	TIM_SetCompare1(TIM10, abs(duty[1]));

	/*Motor 2*/
	if (duty[2] > 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_14);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	}
	else
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_14);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	}
	TIM_SetCompare1(TIM13, abs(duty[2]));

	/*Motor 3*/
	if (duty[3] > 0)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);
	}
	else
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_15);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	}
	TIM_SetCompare1(TIM14, abs(duty[3]));

	/*Motor 4*/
	if (duty[4] > 0)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_1);
		GPIO_ResetBits(GPIOD, GPIO_Pin_0);
	}
	else
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_0);
		GPIO_ResetBits(GPIOD, GPIO_Pin_1);
	}
	TIM_SetCompare1(TIM2, abs(duty[4]));

	/*Motor 5*/
	if (duty[5] > 0)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_7);
		GPIO_ResetBits(GPIOD, GPIO_Pin_4);
	}
	else
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_4);
		GPIO_ResetBits(GPIOD, GPIO_Pin_7);
	}
	TIM_SetCompare2(TIM2, abs(duty[5]));

	/*Motor 6*/
	if (duty[6] > 0)
	{
		GPIO_SetBits(GPIOE, GPIO_Pin_4);
		GPIO_ResetBits(GPIOE, GPIO_Pin_0);
	}
	else
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_0);
		GPIO_ResetBits(GPIOD, GPIO_Pin_4);
	}
	TIM_SetCompare1(TIM11, abs(duty[6]));


}

//=================================================================================================
void setServo(int16_t servo[4])
{

}
//==================================================================================================
//Funkcja odblokowuje wszystkie silniki
void startMotors() {

	channel.TIM_OCMode = TIM_OCMode_PWM1;
	channel.TIM_OutputState = TIM_OutputState_Enable;
	channel.TIM_Pulse = 0;
	TIM_OC1Init(TIM2, &channel);
	TIM_OC2Init(TIM2, &channel);
	TIM_OC3Init(TIM2, &channel);
	TIM_OC4Init(TIM2, &channel);
	TIM_OC1Init(TIM10, &channel);
	TIM_OC1Init(TIM11, &channel);
	TIM_OC1Init(TIM13, &channel);
    TIM_OC1Init(TIM14, &channel);
    GPIO_SetBits(GPIOE, GPIO_Pin_14);
    GPIO_SetBits(GPIOE, GPIO_Pin_15);
}
//==================================================================================================
//Funkcja zatrzymuje wszystkie silniki
void stopMotors() {
	channel.TIM_OCMode = TIM_OCMode_PWM1;
	channel.TIM_OutputState = TIM_OutputState_Disable;
	channel.TIM_Pulse = 0;
	TIM_OC1Init(TIM2, &channel);
	TIM_OC2Init(TIM2, &channel);
	TIM_OC3Init(TIM2, &channel);
	TIM_OC4Init(TIM2, &channel);
	TIM_OC1Init(TIM10, &channel);
	TIM_OC1Init(TIM11, &channel);
	TIM_OC1Init(TIM13, &channel);
    TIM_OC1Init(TIM14, &channel);
}

//==================================================================================================
//przerwanie z regulatorem PI pr¹du
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		//lowPassFilterFIR();
		lowPassFilterIIR();
		//setPICurrent(referenceData.referenceInertial);
		//setPWMreg(referenceData.referenceCurrent);
		//setPWMreg(referenceData.referenceCurrent);
		regulatorSilnikow();
	}
}



