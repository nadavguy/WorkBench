/*
 * BleAgent.h
 *
 *  Created on: May 11, 2021
 *      Author: gilad
 */

#ifndef INC_BLEAGENT_H_
#define INC_BLEAGENT_H_

#include "main.h"
#include "usart.h"
#define BLE_UART					huart3
#define BLE_RX_BUFFER				256
#define BLE_TX_BUFFER				32

typedef struct sBLEPARAMS
{
	char macAddress[12];
	char bleName[12];
}tBLEPARAMS;

extern bool isBLEOn;
extern tBLEPARAMS bleParameters;

extern void initBLE(void);
extern void checkBLEMessages(void);
extern void parseBLEMessage(void);

#endif /* INC_BLEAGENT_H_ */
