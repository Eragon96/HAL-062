/*
 * CommuniactionF3.c
 *
 *  Created on: 26.04.2018
 *      Author: Konrad
 */

#include "CommunicationF3.h"

void ignoreCAN(CanRxMsg * a);

void loadCommandList(void) {
	int i = 0;
	//Sterowanie X,Y
	commandList[i].Id = 100;
	commandList[i].length = 2;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Sterowanie start,stop
	commandList[i].Id = 101;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Zadana prêdkoœci silników prawa
	commandList[i].Id = 102;
	commandList[i].length = 3;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Zadana prêdkoœci silinków lewa
	commandList[i].Id = 103;
	commandList[i].length = 3;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Pr¹d silinków prawa
	commandList[i].Id = 104;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Pr¹d silinków lewa
	commandList[i].Id = 105;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Prêdkoœci silinków prawa
	commandList[i].Id = 106;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Prêdkoœci silinków lewa
	commandList[i].Id = 107;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = ignoreCAN;
	//Napiêcie baterii
	commandList[i].Id = 108;
	commandList[i].length = 8;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Temperatura baterii
	commandList[i].Id = 109;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Wspó³rzêdne GPS
	commandList[i].Id = 110;
	commandList[i].length = 8;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Dane IMU
	commandList[i].Id = 111;
	commandList[i].length = 12;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Dane Magnetometr
	commandList[i].Id = 112;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Temperatura silinków prawa
	commandList[i].Id = 113;
	commandList[i].length = 3;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Temperatura silinków lewa
	commandList[i].Id = 114;
	commandList[i].length = 3;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Moc silników
	commandList[i].Id = 115;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Status sterowników silinków prawa
	commandList[i].Id = 116;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Status sterowników silinków lewa
	commandList[i].Id = 117;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Status BMS
	commandList[i].Id = 118;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Ograniczenie prêdkoœci
	commandList[i].Id = 119;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	i++;
	//Ograniczenie pr¹du
	commandList[i].Id = 120;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
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

void ignoreCAN(CanRxMsg * a) {
	;
}
