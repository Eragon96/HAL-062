#include "CANlib.h"

//====================================================================================================
/**
 * @brief  Funkcja inicjaluzje CAN1 na pinach PB8 i PB9
 * @retval None
 */
void initCan(void) {
	//inicjalizacja struktur
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	//inicjalizacja przerwa�
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//uruchomienie zegar�w
	/* Enable GPIO clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	/* Enable CAN clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	//konfiguracja pin�w CAN  PB8 CAN_RX/ PB9 CAN_TX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//konfiguracja CAN
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = ENABLE; //po wprowadzeniu wadomo�ci do rejestru wiadomosc wysy�ana jest tylko jeden raz
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	//ustawienie predkosc tarnsmijsi
	CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
	CAN_InitStructure.CAN_Prescaler = 5;

	//konfiguracja Filtr�w CAN
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;

	//inicjalizacja CAN i filtr�w
	CAN_DeInit(CAN1);
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_Init(CAN1, &CAN_InitStructure);
	CAN_FilterInit(&CAN_FilterInitStructure);
	/* Transmit Structure preparation */
	txMessage.StdId = 0x00;
	txMessage.ExtId = 0x00;
	txMessage.RTR = CAN_RTR_DATA;
	txMessage.IDE = CAN_ID_STD;
	txMessage.DLC = 3;

}

//====================================================================================================
/**
 * @brief  Obsluga przerwania odbiorczego
 * @note   Okreslenie typu wiadomosci za pomoca adresu (rxMessage.StdId)
 * @retval None
 */
void CAN1_RX0_IRQHandler(void) {
	if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET) {
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_Receive(CAN1, CAN_FIFO0, &rxMessage);
		runCanAction(&rxMessage);
	}
}
//====================================================================================================
/**
 * @brief  Funkcja wysy�a pr�dkosc do sterownika silnikow
 * @note   wysyla zadane predkosci do wszystkich trzech silników
 * 		sterowanych przez wybrany sterownik
 * @param  strona : Lewa - wyslanie do lewego sterownika
 * 				 Prawa - wyslanie do prawego sterowanika
 * @param predkosc(1/2/3): watrosc predkosci kolejnych silnikow
 * 						liczba w zakresie -100, 100
 * @retval None
 */
void sendSpeed(Silniki_strona strona, int predkosc1, int predkosc2,
		int predkosc3) {
	switch (strona) {
	case PRAWA:
		txMessage.StdId = 102;
		break;
	case LEWA:
		txMessage.StdId = 103;
		break;
	}
	txMessage.DLC = 3;
	txMessage.Data[0] = predkosc1;
	txMessage.Data[1] = predkosc2;
	txMessage.Data[2] = predkosc3;
	CAN_Transmit(CAN1, &txMessage);
}

//====================================================================================================
/**
 * @brief  Funkcja uruchamia lub zatrzymuje silniki (generowanie PWM w sterowniku)
 * @note   zatrzymanie silinków oznacza ich wyłączenie, pojazd moze zaczac się poruszc
 * 		pod wlacnym ciezarem. Funkcja wysyla polecenie zatrzymania po magistrali CAN
 * 		w razie uszkodzenia magistrali funkcja nie zatrzyma silników.
 * @param  zezwolenie: STOP - silnik zostaje zatrzymany
 * 					START - silnik zostaje uruchomiony
 * @retval None
 */
void sendStop(Silnik_enable zezwolenie) {
	txMessage.StdId = 100;
	txMessage.DLC = 1;
	txMessage.Data[0] = zezwolenie;
	CAN_Transmit(CAN1, &txMessage);
}
