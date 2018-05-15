/*
 * GPS.c
 *
 *  Created on: 6 mar 2018
 */

//====================================================================================================
/**
 //Nazwa: GPS.c
 //Autor: Mateusz Nowakowski
 //Projekt: £azik marsjañski KNR
 //Created on: 12 Luty 2018

 ===============================================================================
 ##### How to use this driver #####
 ===============================================================================
 (#) Za³¹cz biblioteki do swojego programu "gps.h"
 (#) Wywo³aj funkcje UART_USB() w main();

 *******************************************KONIEC***************************************************
 */
#include "GPS.h"

float przelicznik(char*, char*);
void getField(char* buffer, int index);
void getgetSzerokosc(char*, char*, int);
void getDlugosc(char*, char*, int);

GPIO_InitTypeDef gpio;
USART_InitTypeDef uart;
NVIC_InitTypeDef nvic;

volatile static int OutputLicznik = 0;
volatile int ilosc;

char szerok[15];
char dlugos[16];
char szerok1[15];
char dlugos1[16];
char stopDl[15];
char minDl[15];
char stopSz[15];
char minSz[15];

volatile char GPS[100];    //tablice bazowe
volatile char GPSdata[100];

//====================================================================================================
void GGA_Table(void) {

	for (int i = 0; i <= ilosc; i++) {
		GPS[i] = GPSdata[i];
		GPSdata[i] = 0;
	}

}
//====================================================================================================

//====================================================================================================
float przelicznik(char* bufer, char*bufer1) {
	float a;
	float b;
	float c;
	a = (float) atof(bufer);
	b = (float) atof(bufer1);
	c = (a + b / 60.0f);
	return c;
}
//====================================================================================================
void getField(char* buffer, int index) {
	int fieldPos = 0;

	int commaCount = 0;
	for (int i = 0; i <= ilosc; i++) {
		if (GPS[i] == ',') {
			commaCount++;
			i++;
		}
		if (commaCount == index) {

			buffer[fieldPos] = GPS[i];
			fieldPos++;

		}

	}

}
//====================================================================================================
void getSzerokosc(char* buffer, char* buffer1, int index) {
	int fieldPos = 0;
	int fieldPos1 = 0;
	int commaCount = 0;
	for (int i = 0; i <= ilosc; i++) {
		if (GPS[i] == ',') {
			commaCount++;
			i++;
		}
		if (commaCount == index) {
			if (fieldPos < 2) {
				buffer[fieldPos] = GPS[i];
				fieldPos++;
			} else {
				buffer1[fieldPos1] = GPS[i];
				fieldPos1++;
			}
		}

	}

}
//====================================================================================================
void getDlugosc(char* buffer, char* buffer1, int index) {
	int fieldPos = 0;
	int fieldPos1 = 0;
	int commaCount = 0;
	for (int i = 0; i <= ilosc; i++) {
		if (GPS[i] == ',') {
			commaCount++;
			i++;
		}
		if (commaCount == index) {
			if (fieldPos < 3) {
				buffer[fieldPos] = GPS[i];
				fieldPos++;
			} else {
				buffer1[fieldPos1] = GPS[i];
				fieldPos1++;
			}
		}

	}

}
//====================================================================================================
/**
 * @brief  Inicjalizacja UART_GPS
 * @note  Wykorzytamy USART1 RX PIN PA2 oraz USART2 TX PIN PA10
 * @retval None
 */
//====================================================================================================
void GPSinit(void) {

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOC, &gpio);

	USART_StructInit(&uart);     //odbiera
	uart.USART_BaudRate = 9600;
	USART_Init(USART6, &uart);

	GPIO_PinAFConfig( GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig( GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

	nvic.NVIC_IRQChannel = USART6_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART6, ENABLE);

}
//====================================================================================================
/**
 * @brief  Przerwanie USART1
 * @note  Odbieranie znaków z GPS
 * @retval zapis do tablicy GPS[]
 */
//====================================================================================================
void USART6_IRQHandler(void) {
	volatile static uint8_t odbiorRamki = 0;
	if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET) {
		USART_ClearITPendingBit(USART6, USART_IT_RXNE);
		char inputChar = USART_ReceiveData(USART6);
		GPSdata[odbiorRamki] = inputChar;
		odbiorRamki++;
		if (odbiorRamki > 0 && inputChar == '*' && GPSdata[3] == 'G'
				&& GPSdata[4] == 'G' && GPSdata[5] == 'A') {
			ilosc = odbiorRamki;
			GGA_Table(); // talbica GGA
			getField(szerok, 2); // dane bezposrednio z GPS
			getField(dlugos, 4);

			getSzerokosc(stopSz, minSz, 2); //rodzielamy na stopnie i minuty
			getDlugosc(stopDl, minDl, 4);

			if (przelicznik(stopSz, minSz) != 0
					&& przelicznik(stopDl, minDl) != 0) {
				sz = przelicznik(stopSz, minSz);   // przeliczamy na stopnie
				dl = przelicznik(stopDl, minDl);

				//sprintf(szerok1, "%2.6f", sz); //przerzucamy na char aby wyslac na uart2
				//sprintf(dlugos1, "%2.6f", dl);
			}
			odbiorRamki = 0; //wyzerowanie ramki , cykl od poczatku
		} else if (inputChar == '$') {
			GPSdata[0] = '$';
			odbiorRamki = 1;
		}
	}
}
