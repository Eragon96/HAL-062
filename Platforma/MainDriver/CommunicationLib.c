#include "CommuniactionLib.h"

void ignoreUART(uint8_t * a);
void ignoreCAN(CanRxMsg * a);
void transferToUart(CanRxMsg * a);
void transferToCan(uint8_t * a);
void ustawPredkosc2(uint8_t * a);

void loadCommandList(void) {
	int i = 0;
	//Sterowanie X,Y
	commandList[i].Id = 100;
	commandList[i].length = 2;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = ustawPredkosc2;
	i++;
	//Sterowanie start,stop
	commandList[i].Id = 101;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = transferToCan;
	i++;
	//Zadana prêdkoœci silników prawa
	commandList[i].Id = 102;
	commandList[i].length = 3;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Zadana prêdkoœci silinków lewa
	commandList[i].Id = 103;
	commandList[i].length = 3;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Pr¹d silinków prawa
	commandList[i].Id = 104;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Pr¹d silinków lewa
	commandList[i].Id = 105;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Prêdkoœci silinków prawa
	commandList[i].Id = 106;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Prêdkoœci silinków lewa
	commandList[i].Id = 107;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Napiêcie baterii
	commandList[i].Id = 108;
	commandList[i].length = 8;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Temperatura baterii
	commandList[i].Id = 109;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Wspó³rzêdne GPS
	commandList[i].Id = 110;
	commandList[i].length = 8;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Dane IMU
	commandList[i].Id = 111;
	commandList[i].length = 12;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Dane Magnetometr
	commandList[i].Id = 112;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Temperatura silinków prawa
	commandList[i].Id = 113;
	commandList[i].length = 3;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Temperatura silinków lewa
	commandList[i].Id = 114;
	commandList[i].length = 3;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Moc silników
	commandList[i].Id = 115;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = transferToCan;
	i++;
	//Status sterowników silinków prawa
	commandList[i].Id = 116;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Status sterowników silinków lewa
	commandList[i].Id = 117;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Status BMS
	commandList[i].Id = 118;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Ograniczenie prêdkoœci
	commandList[i].Id = 119;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = transferToCan;
	i++;
	//Ograniczenie pr¹du
	commandList[i].Id = 120;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = transferToCan;
	i++;
}

uint8_t getLength(uint8_t dataId) {
	for (int i = 0; i < 150; i++) {
		if (commandList[i].Id == dataId) {
			return commandList[i].length;
		}
	}
	return 0;
}

void runCanAction(CanRxMsg * a) {
	for (int i = 0; i < 150; i++) {
		if (commandList[i].Id == a->StdId) {
			commandList[i].reciveCanAction(a);
			return;
		}
	}
}

void runUartAction(uint8_t * a) {
	for (int i = 0; i < 150; i++) {
		if (commandList[i].Id == *a) {
			commandList[i].reciveUartAction(a);
			return;
		}
	}
}

void transferToUart(CanRxMsg * a) {
	static uint8_t sendBuffor[20][9];
	static uint8_t buffNum = 0;
	sendBuffor[buffNum][0] = '#';
	sendBuffor[buffNum][1] = a->StdId;
	for (int i = 0; i <= a->DLC; i++) {
		sendBuffor[buffNum][i + 2] = a->Data[i];
	}
	UARTwyslij(&sendBuffor[buffNum][0], a->DLC + 2);
	buffNum++;
	if (buffNum == 20) {
		buffNum = 0;
	}
}

void transferToCan(uint8_t * a) {
	txMessage.StdId = *a;
	txMessage.DLC = getLength(*a);
	for(int i=0;i<txMessage.DLC;i++) {
		a++;
		txMessage.Data[i] = *a;
	}
	CAN_Transmit(CAN1, &txMessage);

}

void ignoreCAN(CanRxMsg * a) {
	;
}

void ignoreUART(uint8_t * a) {
	;
}

void ustawPredkosc2(uint8_t * a) {

	a++;
	int8_t wskazanieY=-*a;
	a++;
	int8_t wskazanieX=-*a;

	//wskazanieY = -polecenie[1];
	//wskazanieX = -polecenie[2];
	int predkoscPrawa;
	int predkoscLewa;
	predkoscPrawa = (int) (wskazanieX) + wskazanieY;
	predkoscLewa = (int) (wskazanieX) - wskazanieY;

	if (predkoscPrawa > 100) {
		predkoscPrawa = 100;
	} else if (predkoscPrawa < -100) {
		predkoscPrawa = -100;
	}
	if (predkoscLewa > 100) {
		predkoscLewa = 100;
	} else if (predkoscLewa < -100) {
		predkoscLewa = -100;
	}
	sendSpeed(LEWA, predkoscLewa, predkoscLewa, predkoscLewa);
	sendSpeed(PRAWA, predkoscPrawa, predkoscPrawa, predkoscPrawa);
	ResetTimer();
}
