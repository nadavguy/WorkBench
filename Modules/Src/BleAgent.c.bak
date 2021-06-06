/*
 * BleAgent.c
 *
 *  Created on: May 11, 2021
 *      Author: gilad
 */


#include "main.h"

bool isBLEOn = true;

uint8_t bleRXArray[BLE_RX_BUFFER] = {0};

void checkBLEMessages(void)
{
	if (isBLEOn)
	{
		HAL_UART_Receive_DMA(&BLE_UART, bleRXArray,BLE_RX_BUFFER);
//		HAL_Delay(2);
		uint8_t localRxArray[BLE_RX_BUFFER] = {0};
		memcpy(localRxArray,bleRXArray,BLE_RX_BUFFER);
		for (int i = 0; i < BLE_RX_BUFFER; i++)
		{
			if (localRxArray[0] == 0)
			{
				memcpy(&localRxArray[0],&localRxArray[1], BLE_RX_BUFFER - 1);
				localRxArray[BLE_RX_BUFFER - 1] = 0;
			}
			else if ( (localRxArray[0] != 0) && (localRxArray[BLE_RX_BUFFER - 1] != 0))
			{
				uint8_t lastCharInArray = localRxArray[BLE_RX_BUFFER - 1];
				memcpy(&localRxArray[1],&localRxArray[0], BLE_RX_BUFFER - 1);
				localRxArray[0] = lastCharInArray;
			}
		}

		if (strlen((char *)localRxArray) > 0)
		{
			parse((char *)localRxArray);
			memset(bleRXArray,0,BLE_RX_BUFFER);
		}
	}
}

void parseBLEMessage(void)
{
	uint8_t i = 0;
	uint8_t localRxArray[BLE_RX_BUFFER] = {0};
	memcpy(localRxArray,bleRXArray,BLE_RX_BUFFER);

	while ( i < BLE_RX_BUFFER - 3)
	{

	}
}
