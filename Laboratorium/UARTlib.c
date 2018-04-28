#include "UARTlib.h"
#include "PIDlib.h"

void initUART() {

	for (int i=0;i<7;i++)
		{
			motor [i]=0;
		}
	incriment_motor=1;
	incriment_servo=1;
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

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
	char inputChar;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		inputChar = USART_ReceiveData(USART2);
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	switch (inputChar)
		{
			/*Motor BM*/
			case '1':
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			GPIO_SetBits(GPIOE,GPIO_Pin_1);
			break;
			case 'q':
			motor[0]+=incriment_motor;
			break;
			case 'a':
			motor[0]=0;
			break;
			case 'z':
			motor[0]-=incriment_motor;

			/*Motor 1*/
			case 'w':
			motor[1]+=incriment_motor;
			break;
			case 's':
			motor[1]=0;
			break;
			case 'x':
			motor[1]-=incriment_motor;

			/*Motor 2*/
			case 'e':
			motor[2]+=incriment_motor;
			break;
			case 'd':
			motor[2]=0;
			break;
			case 'c':
			motor[2]-=incriment_motor;

			/*Motor 3*/
			case 'r':
			motor[3]+=incriment_motor;
			break;
			case 'f':
			motor[3]=0;
			break;
			case 'v':
			motor[3]-=incriment_motor;

			/*Motor 4*/
			case 't':
			motor[4]+=incriment_motor;
			break;
			case 'g':
			motor[4]=0;
			break;
			case 'b':
			motor[4]-=incriment_motor;

			/*Motor 5*/
			case 'y':
			motor[5]+=incriment_motor;
			break;
			case 'h':
			motor[5]=0;
			break;
			case 'n':
			motor[5]-=incriment_motor;

			/*Motor 6*/
			case 'u':
			motor[6]+=incriment_motor;
			break;
			case 'j':
			motor[6]=0;
			break;
			case 'm':
			motor[6]-=incriment_motor;
			break;

			/*servo 0*/
			case 'i':
			servo[0]+=incriment_servo;
			break;
			case 'k':
			servo[0]=servo_nom_angle[0];
			break;
			case ',':
			servo[0]-=incriment_servo;
			break;

			/*servo 1*/
			case 'o':
			servo[1]+=incriment_servo;
			break;
			case 'l':
			servo[1]=servo_nom_angle[1];
			break;
			case '.':
			servo[1]-=incriment_servo;
			break;

			/*servo 2*/
			case 'p':
			servo[2]+=incriment_servo;
			break;
			case ';':
			servo[2]=servo_nom_angle[2];
			break;
			case '/':
			servo[2]-=incriment_servo;
			break;
		}
			for (int i=0;i<7;i++)
			{
				if (motor[i]>=100)
				{
					motor[i]=99;
				}
				if (motor[i]<=-100)
				{
					motor[i]=-99;
				}
			}
			for (int i=0;i<3;i++)
			{
				if (servo[i]>servo_max_angle[i]) {servo[i]=servo_max_angle[i];}
				if (servo[i]<servo_min_angle[i]) {servo[i]=servo_min_angle[i];}
			}
			//setReferenceSpeed(motor);
			//setServo(servo);
	}

	//wysylanie znaków
	if (USART_GetITStatus(USART2, USART_IT_TXE)) {
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
		 USART_SendData(USART2, 'X');

	}
}





