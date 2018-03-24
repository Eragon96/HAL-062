/*
 * Neopixel.h
 *
 *  Created on: 14.03.2018
 *      Author: Joanna
 */

#ifndef SRC_NEOPIXEL_H_
#define SRC_NEOPIXEL_H_

#include "stm32f4xx.h"
/*******************DEFINICJE KONFIGURACYJNE*************/
#define Diodes 8 // iloœc diód na pasku
// Kolory na które miga pasek
#define Blink_color_1 green
#define Blink_color_2 red
#define Blink_color_3 blue
#define Blink_color_4 red
/******************KONIEC********************************/

#define High 70// ew. Je¿eli okres 90 to 57
#define Low 35 // Je¿eli okres 90 to 28

// Definicje kolorów
#define black 0
#define red 1
#define green 2
#define blue 3
#define white 4

// Definicje sekwencji
#define CONST 10
#define Blink 11
#define Wave 12
#define STOP 13



uint32_t COLOR_VECTOR[(Diodes*24+42)]; //zmienna przechowuj¹ca stan bity kolorów

uint16_t DMA_iterations; // zmienna przechowuj¹ca iloœc wyslan tablicy kolorów- potrzebne jest ok 10000 (12,5ms)

uint8_t Neopixel_current_color; //zmienna przechowuj¹ca kolor, na jaki ma siê zmienic pasek

uint8_t Neopixel_delay; //zmienna przechowuj¹ca aktualny okres zmian kolorów

uint8_t Neopixel_current_mode; //zmienna przechowuj¹ca obecny, zmiany dokonywane poprzez wpisanie do rejestru ARR

uint8_t strip_status; //aktualny stan paska podczas mrygania


void InitNeoPixel();
void send_char(char c);
void send_string(const char* s);
/*
 * @brief: Funkcja inicjalizacyjna kolorów ka¿dej z diód
 * @param: d1-d8 - Kolor dla ka¿dej z diód
 * @note: kolory mog¹ byc dobrane z odpowiedniej definicji
 */
void Set_colors_DMA(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5,
		uint8_t d6, uint8_t d7, uint8_t d8);


/*
 * @brief: Funkcja inicjalizacyjna kolorów ka¿dej z diód na ten sam kolor
 * @param: p_color - kolor
 * @note: kolory mog¹ byc dobrane z odpowiedniej definicji
 */
void Set_strip(uint8_t p_color);
/*
 * @brief: Funkcja inicjalizacyjna kolorów konkretnej z diód na ten sam kolor
 * @param: p_diode - numer diody
 * @param: p_color - kolor
 * @note: kolory mog¹ byc dobrane z odpowiedniej definicji
 */
void Set_single(uint8_t p_diode, uint8_t p_color);
/*
 * @brieg: Funkcja zmieniaj¹ca tryb dzia³ania paska
 * @param: p_mode- tryb dzia³ania wybierany z 4 zdefiniowanych
 * @param: p_color- kolor paska
 * @param: p_speed- odstêp czasowy odœwie¿ania paska
 */
void Neopixel_change_mode(uint8_t p_mode,uint8_t p_color, uint8_t p_speed);

void Play_rainbow();

#endif /* SRC_NEOPIXEL_H_ */
