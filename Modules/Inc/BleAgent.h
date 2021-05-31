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
#define BLE_RX_BUFFER				128

extern bool isBLEOn;

extern void checkBLEMessages(void);
extern void parseBLEMessage(void);

#endif /* INC_BLEAGENT_H_ */
