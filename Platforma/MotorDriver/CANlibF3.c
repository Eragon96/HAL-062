#include "CANlibF3.h"

//==================================================================================================
//Funkcja inicjalizuje CAN na pinach PA11 CAN_RX / PA12 CAN_TX
void initCan(void) {
	//inicjalizacja struktur
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	/* NVIC configuration ***********************************/
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//uruchomienie zegarów
	/* Enable GPIO clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	/* Enable CAN clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	//konfiguracja pinów CAN   PA11 CAN_RX / PA12 CAN_TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_9);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_9);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//konfiguracja CAN
	CAN_StructInit(&CAN_InitStructure);
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = ENABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	//ustawienie predkosci transmisji
	CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
	CAN_InitStructure.CAN_Prescaler = 4;

	//konfiguracja filtrow CAN
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;

	//Inicjalizacja CAN i filtrow
	CAN_DeInit(CAN1);
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_Init(CAN1, &CAN_InitStructure);
	CAN_FilterInit(&CAN_FilterInitStructure);

	/* Transmit Structure preparation */
	TxMessage.StdId = 0x0;
	TxMessage.ExtId = 0x0;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = 1;
}

void readSpeed(void); //deklaracja funkcji znajdujacej sie nizej
void pwmStartStop(void);
void setPowerFactor(void);
//==================================================================================================
//przerwanie odbiorcze CAN
//odczytuje wartosci predkosci z nadeslanej ramki i ustawia rzadana predkosc na odpowiednich silnikach
void USB_LP_CAN1_RX0_IRQHandler(void) {
	if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET) {
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
		switch (RxMessage.StdId) {
		case 101:
			pwmStartStop();
			break;
#ifdef plytkaPrawa
			case 102:
			readSpeed();
			resetCanWatchdog();
			break;
#endif
#ifdef plytkaLewa
		case 103:
			readSpeed();
			resetCanWatchdog();
			break;
#endif
		case 119:
			setPowerFactor();
			break;
		}

	}
}

///==================================================================================================
//Ustawia odpowiednie predkosci dla kolejnych silnikow wedlug zawartosci odebranej ramki CAN
void readSpeed() {
	static volatile int8_t read1;
	static volatile int8_t read2;
	static volatile int8_t read3;
#ifdef plytkaPrawa
	read1 = -RxMessage.Data[0];
	read2 = -RxMessage.Data[1];
	read3 = RxMessage.Data[2];
#endif
#ifdef plytkaLewa
	read1 = -RxMessage.Data[0];
	read2 = -RxMessage.Data[1];
	read3 = RxMessage.Data[2];
#endif
	setReferenceSpeed(read1, read2, read3);
}

void pwmStartStop() {
	if (RxMessage.Data[0] == '1') {
		startMotors();
	} else
		stopMotors();
}

void setPowerFactor(){
	if (RxMessage.Data[0] <= 20){
	powerFactor = RxMessage.Data[0] ;
	}
}

void sendSpeed(void) {
#ifdef plytkaPrawa
	TxMessage.StdId = 106;
#endif
#ifdef plytkaLewa
	TxMessage.StdId = 107;
#endif
	TxMessage.DLC = 6;
	TxMessage.Data[0] = enkPredkosc[0] & 0xFF;
	TxMessage.Data[1] = (enkPredkosc[0] & 0xFF00) >> 8;
	TxMessage.Data[2] = enkPredkosc[1] & 0xFF;
	TxMessage.Data[3] = (enkPredkosc[1] & 0xFF00) >> 8;
	TxMessage.Data[4] = enkPredkosc[2] & 0xFF;
	TxMessage.Data[5] = (enkPredkosc[2] & 0xFF00) >> 8;
	CAN_Transmit(CAN1, &TxMessage);
}

void sendCurrent(void) {
#ifdef plytkaPrawa
	TxMessage.StdId = 104;
#endif
#ifdef plytkaLewa
	TxMessage.StdId = 105;
#endif
	TxMessage.DLC = 6;
	TxMessage.Data[0] = adcFilterValue[0] & 0xFF;
	TxMessage.Data[1] = (adcFilterValue[0] & 0xFF00) >> 8;
	TxMessage.Data[2] = adcFilterValue[1] & 0xFF;
	TxMessage.Data[3] = (adcFilterValue[1] & 0xFF00) >> 8;
	TxMessage.Data[4] = adcFilterValue[2] & 0xFF;
	TxMessage.Data[5] = (adcFilterValue[2] & 0xFF00) >> 8;
	CAN_Transmit(CAN1, &TxMessage);
}

volatile uint8_t tempValue[3];

void adcToCelsiusConverter(void) {
	for (int i = 0; i < 3; i++) {
		tempValue[i] = (uint8_t) (((adcFilterValue[i + 3] * 660) / 4096) - 100);
	}
}

void sendTemp(void) {
#ifdef plytkaPrawa
	TxMessage.StdId = 113;
#endif
#ifdef plytkaLewa
	TxMessage.StdId = 114;
#endif
	adcToCelsiusConverter();
	TxMessage.DLC = 3;
	TxMessage.Data[0] = (uint8_t) (tempValue[0]);
	TxMessage.Data[1] = (uint8_t) (tempValue[1]);
	TxMessage.Data[2] = (uint8_t) (tempValue[2]);
	CAN_Transmit(CAN1, &TxMessage);
}

void sendStatus(void) {
#ifdef plytkaPrawa
	TxMessage.StdId = 116;
#endif
#ifdef plytkaLewa
	TxMessage.StdId = 117;
#endif
	TxMessage.DLC = 1;
	if (adcValue[6] >500) {
		if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_10) == Bit_SET) {
			TxMessage.Data[0] = 3;
		} else {
			TxMessage.Data[0] = 1;
		}
	} else {
		TxMessage.Data[0] = 2;
	}
	CAN_Transmit(CAN1, &TxMessage);
}

void sendParam(void) {
#ifdef plytkaLewa
	static int licznik = 0;
#else
	static int licznik = 50;
#endif
	licznik++;
	switch (licznik) {
	case 75:
		sendSpeed();
		break;
	case 150:
		sendCurrent();
		break;
	case 225:
		sendTemp();
		break;
	case 300:
		sendStatus();
		licznik = 0;
		break;
	}
}
