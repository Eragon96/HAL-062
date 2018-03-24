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
#define Diodes 8 // ilo�c di�d na pasku
// Kolory na kt�re miga pasek
#define Blink_color_1 green
#define Blink_color_2 red
#define Blink_color_3 blue
#define Blink_color_4 red
/******************KONIEC********************************/

#define High 70// ew. Je�eli okres 90 to 57
#define Low 35 // Je�eli okres 90 to 28

// Definicje kolor�w
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



uint32_t COLOR_VECTOR[(Diodes*24+42)]; //zmienna przechowuj�ca stan bity kolor�w

uint16_t DMA_iterations; // zmienna przechowuj�ca ilo�c wyslan tablicy kolor�w- potrzebne jest ok 10000 (12,5ms)

uint8_t Neopixel_current_color; //zmienna przechowuj�ca kolor, na jaki ma si� zmienic pasek

uint8_t Neopixel_delay; //zmienna przechowuj�ca aktualny okres zmian kolor�w

uint8_t Neopixel_current_mode; //zmienna przechowuj�ca obecny, zmiany dokonywane poprzez wpisanie do rejestru ARR

uint8_t strip_status; //aktualny stan paska podczas mrygania


void InitNeoPixel();
void send_char(char c);
void send_string(const char* s);
/*
 * @brief: Funkcja inicjalizacyjna kolor�w ka�dej z di�d
 * @param: d1-d8 - Kolor dla ka�dej z di�d
 * @note: kolory mog� byc dobrane z odpowiedniej definicji
 */
void Set_colors_DMA(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5,
		uint8_t d6, uint8_t d7, uint8_t d8);


/*
 * @brief: Funkcja inicjalizacyjna kolor�w ka�dej z di�d na ten sam kolor
 * @param: p_color - kolor
 * @note: kolory mog� byc dobrane z odpowiedniej definicji
 */
void Set_strip(uint8_t p_color);
/*
 * @brief: Funkcja inicjalizacyjna kolor�w konkretnej z di�d na ten sam kolor
 * @param: p_diode - numer diody
 * @param: p_color - kolor
 * @note: kolory mog� byc dobrane z odpowiedniej definicji
 */
void Set_single(uint8_t p_diode, uint8_t p_color);
/*
 * @brieg: Funkcja zmieniaj�ca tryb dzia�ania paska
 * @param: p_mode- tryb dzia�ania wybierany z 4 zdefiniowanych
 * @param: p_color- kolor paska
 * @param: p_speed- odst�p czasowy od�wie�ania paska
 */
void Neopixel_change_mode(uint8_t p_mode,uint8_t p_color, uint8_t p_speed);

void Play_rainbow();

#endif /* SRC_NEOPIXEL_H_ */
