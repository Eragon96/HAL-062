/**
 * autor: Konrad Aleksiejuk Data: 24.11.16r
 * Bibliotek do pomiaru napi�cia (proporcjonalnego do pr�du) w sterownikach silnik�w
 * pomiar na 3 kana�ach, dane przesy�ane za pomoc� DMA do tablicy: "adcWartosc[]"
 * Po inicjalizacji funkcja praktycznie nie zajmuje procesora
 *
 */

#ifndef ADClib_H
#define ADClib_H

#include "stm32f4xx.h"

#define ADC12_CDR_ADDRESS    (uint32_t)0x40012308

void initADC(void);

volatile int16_t adcValue[7];
volatile int16_t adcFilterValue[7];
int16_t offset[7];
void lowPassFilterIIR(void);

void adcSetOffset(void);

#define alfa 0.01
#define alfaTemp  0.001

#endif
