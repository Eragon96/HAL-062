/*
 * Bibliotek do inicjalizacji GPIO
 * inicjalizacja GPIO powinna znajdowac sie przed inicjalizacja PWM
 */


#ifndef GPIOlib_H
#define GPIOlib_H

#include "stm32f4xx.h"

void initGpioMotors(void);
void initGpioLed(void);

#endif
