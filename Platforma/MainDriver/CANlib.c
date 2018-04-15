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

	//inicjalizacja przerwaï¿½
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//uruchomienie zegarï¿½w
	/* Enable GPIO clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	/* Enable CAN clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	//konfiguracja pinï¿½w CAN  PB8 CAN_RX/ PB9 CAN_TX
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
	CAN_InitStructure.CAN_NART = ENABLE; //po wprowadzeniu wadomoï¿½ci do rejestru wiadomosc wysyï¿½ana jest tylko jeden raz
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	//ustawienie predkosc tarnsmijsi
	CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
	CAN_InitStructure.CAN_Prescaler = 5;

	//konfiguracja Filtrï¿½w CAN
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;

	//inicjalizacja CAN i filtrï¿½w
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
		switch (rxMessage.StdId) {
		case 101:
			//BMS napiêcia baterii
			sendUartParam(8, 106);
			break;
		case 102:
			//Nastawy prêdkoœci silników, prawe
			break;
		case 103:
			//Nastawy prêdkoœci silników, lewe
			break;
		case 104:
			//Pr¹d silników, prawe
			sendUartParam(6, 102);
			break;
		case 105:
			//Pr¹d silników, lewe
			sendUartParam(6, 103);
			break;
		case 106:
			//Prêdkoœci kó³, prawe
			sendUartParam(6, 104);
			break;
		case 107:
			//Prêdkoœci kó³, lewe
			sendUartParam(6, 105);
			break;
		case 108:
			//BMS temperatura baterii
			sendUartParam(6, 107);
			break;
		case 109:
			//Temp silników, prawe
			sendUartParam(3, 111);
			break;
		case 110:
			//Temp silników, lewe
			sendUartParam(3, 112);
			break;
		case 111:
			//Status sterowników silników prawe
			sendUartParam(1, 114);
			break;
		case 112:
			//Status sterowników silników lewe
			sendUartParam(1, 115);
			break;
		default:
			break;
		}
	}
}
//====================================================================================================
/**
 * @brief  Funkcja wysyï¿½a prï¿½dkosc do sterownika silnikow
 * @note   wysyla zadane predkosci do wszystkich trzech silnikÃ³w
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

void sendPower(uint8_t power) {
	txMessage.StdId = 110;
	txMessage.DLC = 1;
	txMessage.Data[0] = power;
}
//====================================================================================================
/**
 * @brief  Funkcja uruchamia lub zatrzymuje silniki (generowanie PWM w sterowniku)
 * @note   zatrzymanie silinkÃ³w oznacza ich wyÅ‚Ä…czenie, pojazd moze zaczac siÄ™ poruszc
 * 		pod wlacnym ciezarem. Funkcja wysyla polecenie zatrzymania po magistrali CAN
 * 		w razie uszkodzenia magistrali funkcja nie zatrzyma silnikÃ³w.
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

//====================================================================================================
/**
 * @brief  Funkcja ustawia nastawy regulatora PI oraz warosc K wzmocnienia antywindup'owego
 * @note  	po zmianie nastawÃ³w pojazd zostaje automatycznie zatrzymany, trzeba ponownie uruchomic napedy
 * @param  P - wartosc wzmocnienia czlonu P (od 0 do 255)
 * @param 	Ilow - stala czasowa czÅ‚onu calkujacego(czesc niska wartosci 16 bitowej)(od 0 do 65535)
 * @param 	Ihigh - stala czasowa czÅ‚onu calkujacego(czesc wysok wartosci 16 bitowej)(od 0 do 65535)
 * @param  K - wartosc wzmocnienia roznicy sygnalu przed i po nasyceniu (antywindup)(od 0 do 255)
 * @retval None
 */
void sendPid(uint8_t P, uint8_t Ilow, uint8_t Ihigh, uint8_t K) {
	txMessage.StdId = 0x00;
	txMessage.DLC = 5;
	txMessage.Data[0] = 'p';
	txMessage.Data[1] = P;
	txMessage.Data[2] = Ilow;
	txMessage.Data[3] = Ihigh;
	txMessage.Data[4] = K;
	CAN_Transmit(CAN1, &txMessage);
}

//====================================================================================================
/**
 * @brief  Przesyla otrzymane parametry predkosci i pradu z silnika (przez CAN) do sterowanika (przez UART2)
 * @note  	funkcja w nie modyfikuje otrzymanych danych a jedynie przesyÅ‚a je dalej
 * 		dane sÄ… odczytywane bezpoÅ›rednioa z rxMessage.Data[]
 * @retval None
 */
void sendUartParam(uint8_t dataLength, uint8_t dataId) {
	static uint8_t sendBuffor[20][9];
	static uint8_t buffNum = 0;
	sendBuffor[buffNum][0] = '#';
	sendBuffor[buffNum][1] = dataId;
	for (int i = 0; i <= dataLength; i++) {
		sendBuffor[buffNum][i + 2] = rxMessage.Data[i];
	}
	UART2wyslij(&sendBuffor[buffNum][0], dataLength + 2);
	buffNum++;
	if (buffNum == 20) {
		buffNum = 0;
	}
}
