#include "USART_lib.h"

void usart_Init()
{

			GPIO_InitTypeDef gpio;
			USART_InitTypeDef uart;
			NVIC_InitTypeDef NVIC_InitStructure;

			/*USART*/
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);


			GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

			gpio.GPIO_Pin = GPIO_Pin_5;
			gpio.GPIO_Speed = GPIO_Speed_50MHz;
			gpio.GPIO_Mode = GPIO_Mode_AF;
			GPIO_Init(GPIOD, &gpio);

			gpio.GPIO_Pin = GPIO_Pin_6;
			gpio.GPIO_Speed = GPIO_Speed_50MHz;
			gpio.GPIO_Mode = GPIO_Mode_AF;
			GPIO_Init(GPIOD, &gpio);

			uart.USART_BaudRate = 115200;
			uart.USART_WordLength = USART_WordLength_8b;
			uart.USART_StopBits = USART_StopBits_1;
			uart.USART_Parity = USART_Parity_No;
			uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

			USART_Init(USART2, &uart);
			USART_Cmd(USART2, ENABLE);

			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}
void USART2_IRQHandler() {
	//ODBIERANIE ZNAKÓW
	int16_t serwo=750;
	char inputChar;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		inputChar = USART_ReceiveData(USART2);
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);

	switch (inputChar)
			{
				/*Motor BM*/
				case 'q':
				motor[0]+= motor_incr;
				break;
				case 'a':
				motor[0]=0;
				break;
				case 'z':
				motor[0]-= motor_incr;
				break;

				/*Motor 1*/
				case 'w':
				motor[1]+= motor_incr;
				GPIO_ToggleBits(GPIOB, GPIO_Pin_2);
				GPIO_ToggleBits(GPIOE, GPIO_Pin_1);


				break;
				case 's':
				motor[1]=0;
				break;
				case 'x':
				motor[1]-= motor_incr;
				break;

				/*Motor 2*/
				case 'e':
				motor[2]+= motor_incr;
				break;
				case 'd':
				motor[2]=0;
				break;
				case 'c':
				motor[2]-= motor_incr;
				break;

				/*Motor 3*/
				case 'r':
				motor[3]+= motor_incr;
				break;
				case 'f':
				motor[3]=0;
				break;
				case 'v':
				motor[3]-= motor_incr;
				break;

				/*Motor 4*/
				case 't':
				motor[4]+= motor_incr;
				break;
				case 'g':
				motor[4]=0;
				break;
				case 'b':
				motor[4]-= motor_incr;
				break;


				/*Motor 5*/
				case 'y':
				motor[5]+= motor_incr;
				break;
				case 'h':
				motor[5]=0;
				break;
				case 'n':
				motor[5]-= motor_incr;
				break;

				/*Motor 6*/
				case 'u':
				motor[6]+= motor_incr;
				break;
				case 'j':
				motor[6]=0;
				break;
				case 'm':
				motor[6]-= motor_incr;
				break;

				/*Servo*/
				case 'i':
				serwo+=2;
				break;
				case 'k':
				serwo=0;
				break;
				case '.':
				serwo-=2;
				break;


			}
			for (int i=0;i<7;i++)
				{
					if (motor[i]>=7000)
					{
						motor[i]=6999;
					}
					if (motor[i]<=-7000)
					{
						motor[i]=-6999;
					}
				}
			set_pwm(motor);
			//set_servo(serwo);

	}

	//wysylanie znaków



}
