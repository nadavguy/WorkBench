/*
 * BleAgent.c
 *
 *  Created on: May 11, 2021
 *      Author: gilad
 */


#include "main.h"

bool isBLEOn = true;

uint8_t bleRXArray[BLE_RX_BUFFER] = {0};

tBLEPARAMS bleParameters;

void initBLE(void)
{
	if (ee.bluetoothStatus == 0)
	{
		isBLEOn = false;
	}
	else
	{
		isBLEOn = true;
		char lt[32] = "$$$";
		HAL_UART_Transmit(&BLE_UART, (uint8_t *)lt, 3, 100);
		checkBLEMessages();
		sprintf(lt,"+\r");
		HAL_UART_Transmit(&BLE_UART, (uint8_t *)lt, 2, 100);
		checkBLEMessages();
		sprintf(lt,"D\r");
		HAL_UART_Transmit(&BLE_UART, (uint8_t *)lt, 2, 100);
		HAL_Delay(20);
		checkBLEMessages();
		if (!strcmp(bleParameters.macAddress, "ParaZero_RC"))
		{
			sprintf(lt,"SN,ParaZero_RC\r");
			HAL_UART_Transmit(&BLE_UART, (uint8_t *)lt, 15, 100);  //SN,MyDevice
			checkBLEMessages();
		}
		sprintf(lt,"---\r");
		HAL_UART_Transmit(&BLE_UART, (uint8_t *)lt, 4, 100);
	}
}

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

		if ( (strlen((char *)localRxArray) > 0) && (rcState != INIT) )
		{
			parse((char *)localRxArray);
			memset(bleRXArray,0,BLE_RX_BUFFER);
		}
		else if ( (strlen((char *)localRxArray) > 0) && (rcState == INIT) )
		{
			const char chEqual = '=';
			const char chCR = '\r';
			char *retEqual;
			char *retCR;
			char localText[32] = "";

			if (memchr(localRxArray, chEqual, strlen((char *)localRxArray)))
			{
				retEqual = memchr(localRxArray, chEqual, strlen((char *)localRxArray));
				retCR = memchr(retEqual, chCR, strlen((char *)localRxArray));
				memcpy(localText, &retEqual[1], retCR - retEqual - 1);
				memcpy(bleParameters.macAddress,localText,strlen(localText));
				memset(localText, 0, 12);

				retEqual = memchr(retCR, chEqual, strlen((char *)localRxArray));
				retCR = memchr(retEqual, chCR, strlen((char *)localRxArray));
				memcpy(localText, &retEqual[1], retCR - retEqual - 1);
				memcpy(bleParameters.bleName, localText, strlen(localText));
			}
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
