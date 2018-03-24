/*
 * Neopixel.c
 *
 *  Created on: 14.03.2018
 *      Author: Joanna
 */

#include "Neopixel.h"

// Inicjalizacja tablicy kolorów
uint32_t Green_Table[234] = { High, High, High, High, High, High, High, High, //B
		Low, Low, Low, Low, Low, Low, Low, Low,
		Low, Low, Low, Low, Low, Low, Low, Low,
		High, High, High, High, High, High, High, High, //B
		Low, Low, Low, Low, Low, Low, Low, Low,
		Low, Low, Low, Low, Low, Low, Low, Low,
		High, High, High, High, High, High, High, High, //B
		Low, Low, Low, Low, Low, Low, Low, Low,
		Low, Low, Low, Low, Low, Low, Low, Low,
		High, High, High, High, High, High, High, High, //B
		Low, Low, Low, Low, Low, Low, Low, Low,
		Low, Low, Low, Low, Low, Low, Low, Low,
		High, High, High, High, High, High, High, High, //B
		Low, Low, Low, Low, Low, Low, Low, Low,
		Low, Low, Low, Low, Low, Low, Low, Low,
		High, High, High, High, High, High, High, High, //B
		Low, Low, Low, Low, Low, Low, Low, Low,
		Low, Low, Low, Low, Low, Low, Low, Low,
		High, High, High, High, High, High, High, High, //B
		Low, Low, Low, Low, Low, Low, Low, Low,
		Low, Low, Low, Low, Low, Low, Low, Low,
		High, High, High, High, High, High, High, High, //B
		Low, Low, Low, Low, Low, Low, Low, Low,
		Low, Low, Low, Low, Low, Low, Low, Low,
		//B
		0, 0, 0, 0, 0, 0, 0, 0, //R
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //R
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 //G
		};

uint32_t Red_Table[24] = { Low, Low, Low, Low, Low, Low, Low, Low, //B
		High, High, High, High, High, High, High, High, //R
		Low, Low, Low, Low, Low, Low, Low, Low  //G
		};

uint32_t Blue_Table[24] = { Low, Low, Low, Low, Low, Low, Low, Low, //B
		Low, Low, Low, Low, Low, Low, Low, Low, //R
		High, High, High, High, High, High, High, High  //G
		};

uint32_t White_Table[24] = { High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High, //R
		High, High, High, High, High, High, High, High }; //G};

uint32_t Black_Table[24] = { Low, Low, Low, Low, Low, Low, Low, Low, //B
		Low, Low, Low, Low, Low, Low, Low, Low, //R
		Low, Low, Low, Low, Low, Low, Low, Low //G
		};

///////////////////////////////////////////////
uint32_t Color_Matrix_DMA[234] = {
High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High, //R
		High, High, High, High, High, High, High, High,
		High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High, //R
		High, High, High, High, High, High, High, High,
		High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High, //R
		High, High, High, High, High, High, High, High,
		High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High,
		High, High, High, High, High, High, High, High,
		High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High, //R
		High, High, High, High, High, High, High, High,
		High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High, //R
		High, High, High, High, High, High, High, High,
		High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High, //R
		High, High, High, High, High, High, High, High,
		High, High, High, High, High, High, High, High, //B
		High, High, High, High, High, High, High, High, //R
		High, High, High, High, High, High, High, High, 0, 0, 0, 0, 0, 0, 0, 0, //B
		0, 0, 0, 0, 0, 0, 0, 0, //R
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //B
		0, 0, 0, 0, 0, 0, 0, 0, //R
		0, 0 };

//////////////////////////////////////////////
// **************KONIEC****************

void InitNeoPixel() {
	TIM_TimeBaseInitTypeDef tim;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 105; //800kHz
	tim.TIM_RepetitionCounter = 0;
	tim.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM3, &tim); // Timer Neopixela


	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OC1Init(TIM3, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	/* Init DMA for TIM3 */
	TIM_DMAConfig(TIM3, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	DMA_DeInit(DMA1_Stream4);

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &TIM3->CCR1; // Physical address of Timer 3 CCR1
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) COLOR_VECTOR; // Memory address where the DMA will read the data
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;	// Transfert from RAM memory to peripheral
	DMA_InitStructure.DMA_BufferSize = (Diodes * 24 + 42); // Number of Half-words (16 bits) to be transfered
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // Do no increment peripheral address
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	// Automatically increment buffer (RAM) index
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // TIM3 is a 16 bits counter -> transfert 16bits at a time
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_Channel = DMA_Channel_5;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

	/* Enable IRQ for DMA */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_ITConfig(DMA1_Stream4, DMA_IT_TC, ENABLE);

	/* Start the DMA */
	DMA_ClearFlag(DMA1_Stream4,
			DMA_FLAG_FEIF4 | DMA_FLAG_DMEIF4 | DMA_FLAG_TEIF4 | DMA_FLAG_HTIF4
					| DMA_FLAG_TCIF4);
	DMA_Cmd(DMA1_Stream4, DISABLE);
	while (DMA1_Stream4->CR & DMA_SxCR_EN)
		;
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);

	DMA_iterations = 0;

	// Inicjalizacja timera mrugania
	tim.TIM_Prescaler = 180000;// 1kHz
	tim.TIM_Period = 1000; //domyœlna wartoœc
	TIM_TimeBaseInit(TIM2, &tim);

	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);


	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

}

void DMA1_Stream4_IRQHandler(void) {
	if (DMA_GetITStatus(DMA1_Stream4, DMA_IT_TCIF4) != RESET) {
		DMA_iterations++;
		if (DMA_iterations == 10000) {
			TIM_Cmd(TIM3, DISABLE);
			DMA_Cmd(DMA1_Stream4, DISABLE);
			DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
			DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_TCIF4);
		}
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		TIM_ClearFlag(TIM2, TIM_IT_Update);

		switch (Neopixel_current_mode) {
		case CONST:
			Set_strip(Neopixel_current_color);
			break;
		case Blink: //DEBUG=0, normalnie Blink
			if (strip_status == 1) {
				Set_strip(Blink_color_1);
				strip_status = 0;
			} else {
				Set_strip(Blink_color_2);
				strip_status = 1;
			}
			break;
		case Wave: //DEBUG=0, normalnie Wave
			if(strip_status==8)
				strip_status=0;
			Set_single(strip_status,Neopixel_current_color);
			strip_status++;
			break;
		case STOP:
			Set_strip(black);
			break;
		default:
			break;
		}
	}
}

void Set_colors_DMA(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5,
		uint8_t d6, uint8_t d7, uint8_t d8) {
	uint8_t param_buffer[8] = { d1, d2, d3, d4, d5, d6, d7, d8 };

	for (uint8_t i = 0; i < 8; i++) {
		switch (param_buffer[i]) {
		case white:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[i * 24 + j] = White_Table[j];
			break;
		case black:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[i * 24 + j] = Black_Table[j];
			break;
		case blue:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[i * 24 + j] = Blue_Table[j];
			break;
		case red:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[i * 24 + j] = Red_Table[j];
			break;
		case green:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[i * 24 + j] = Green_Table[j];
			break;
		default:
			break;

		}
	}
}

void Set_strip(uint8_t p_color) {

	Set_colors_DMA(p_color, p_color, p_color, p_color, p_color, p_color,
			p_color, p_color);

	DMA_SetCurrDataCounter(DMA1_Stream4, ((Diodes * 24) + 42));
	DMA_Cmd(DMA1_Stream4, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_DMACmd(TIM3, TIM_DMA_CC1, ENABLE);
}

void Set_single(uint8_t p_diode, uint8_t p_color) {

	for(uint8_t i=0; i<(Diodes*24); i++)
		COLOR_VECTOR[i]=Low;

	for (uint8_t i = 0; i < 24; i++)
		switch (p_color) {
		case white:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[p_diode * 24 + j] = White_Table[j];
			break;
		case black:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[p_diode * 24 + j] = Black_Table[j];
			break;
		case blue:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[p_diode * 24 + j] = Blue_Table[j];
			break;
		case red:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[p_diode * 24 + j] = Red_Table[j];
			break;
		case green:
			for (uint8_t j = 0; j < 24; j++)
				COLOR_VECTOR[p_diode * 24 + j] = Green_Table[j];
			break;
		default:
			break;

		}

	DMA_SetCurrDataCounter(DMA1_Stream4, ((Diodes * 24) + 42));
	DMA_Cmd(DMA1_Stream4, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_DMACmd(TIM3, TIM_DMA_CC1, ENABLE);
}

void Neopixel_change_mode(uint8_t p_mode,uint8_t p_color, uint8_t p_speed){

	if(p_speed<1001)
		TIM2->ARR=p_speed;
	Neopixel_current_mode=p_mode;
	Neopixel_current_color=p_color;
}
