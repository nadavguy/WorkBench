/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v2.0_Cube
  * @brief          : This file implements the USB Device
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

/* USER CODE BEGIN Includes */
#include "main.h"
#include "cmd_interp.h"
#include "usbd_msc.h"
#include "usbd_desc_msc.h"
#include "usbd_storage_if.h"
#include "ci_func.h"
#include "Common.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t localCounter = 0;
uint8_t rotator;
uint16_t decryptionCounter = 0;
uint16_t localTimeout = 10;
char localCommand[COMMANDSMAXSIZE] = "";
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */
uint8_t usbRXArray[APP_RX_DATA_SIZE] = {0};
uint8_t usbTXArray[APP_TX_DATA_SIZE] = {0};
uint8_t retriesCounter = 0;

uint16_t previousPackID = 0;
uint16_t packID = 0;
uint16_t totalPackID = 0;
uint16_t receivedCRC = 0xEC0C;

uint32_t lastUSBDataRead = 0;
uint32_t lastPacketRequest = 0;
uint32_t totalBytesLengthInFile = 0;

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
uint16_t readUSBData(void)
{
	uint16_t usbBytesRead = 0;

	if ( (HAL_GetTick() - lastUSBDataRead >= localTimeout) && (!isMSCMode) )
	{
//		memset(usbRXArray, 0, APP_RX_DATA_SIZE);
		USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &usbRXArray[0]);
		USBD_CDC_ReceivePacket(&hUsbDeviceFS);
		uint8_t localArray[64] = {0};
		memcpy(localArray, usbRXArray, 64);
		usbBytesRead = strlen((char *)localArray);
		char * ptr;
		int    ch = '\r';

		if (isInfwUpdateMode)
		{
			ch = '#';
		}

		ptr = strchr((char *)localArray, ch );

		if ( (usbBytesRead >= 1) && (ptr == NULL) && (!isInfwUpdateMode))
		{
			localCommand[localCounter] = usbRXArray[0];
			localCounter++;

			memset(usbRXArray, 0, APP_RX_DATA_SIZE);
			usbBytesRead = 0;
		}
		else if ( (localArray[0] == 'T') && (localArray[NUBMEROFBYTESINFWMESSAGE + 3] == '#') && (localArray[NUBMEROFBYTESINFWMESSAGE + 4] == '\r') && (isInfwUpdateMode))
		{
			totalPackID = localArray[1] * 256 + localArray[2];
			totalBytesLengthInFile = localArray[3] * 65536 + localArray[4] * 256 + localArray[5];
			sprintf(terminalBuffer,"Total Number of Bytes in file: %ld", totalBytesLengthInFile);
			logData(terminalBuffer, false, false, false);

			rotator = totalBytesLengthInFile % 8;
			if (rotator == 0)
			{
				rotator = (totalBytesLengthInFile + 1) % 5;
			}
			if (rotator == 0)
			{
				rotator = 4;
			}
			sprintf(terminalBuffer,"Sector Used: %d", rotator);
			logData(terminalBuffer, false, false, false);
			lastPacketRequest = HAL_GetTick();

		}
		else if ( (localArray[0] == 'C') && (localArray[1] == 'R') && (localArray[2] == 'C') &&
				(localArray[NUBMEROFBYTESINFWMESSAGE + 3] == '#') && (localArray[NUBMEROFBYTESINFWMESSAGE + 4] == '\r') && (isInfwUpdateMode))
		{
			receivedCRC = 0x100 * localArray[3] + localArray[4];
		}
		else if ( (localArray[0] == 'P') && (localArray[NUBMEROFBYTESINFWMESSAGE + 3] == '#') && (localArray[NUBMEROFBYTESINFWMESSAGE + 4] == '\r') && (isInfwUpdateMode))
		{

			uint32_t writeAddress = 0;
			char localString[16] = "";
			writeAddress = localFlashParams.startAddress;
//			memcpy(&FileReadBuffer, (uint8_t *)usbRXArray, 35);
			packID = localArray[1] * 256 + localArray[2];
			if (packID == previousPackID + 1) // Packet received correctly
			{
				writeAddress = localFlashParams.startAddress + NUBMEROFBYTESINFWMESSAGE * (packID -1);
				uint8_t decryptedArray[32] = {0};
//				memcpy(decryptedArray, &usbRXArray[3], 32);
				for (int i = 0; i < NUBMEROFBYTESINFWMESSAGE ; i++)
				{
					uint8_t secondLeftRotate = rrotate(localArray[i + 3], 8 - rotator);
					uint8_t afterKey = (uint8_t)(secondLeftRotate ^ phrase[decryptionCounter]);
					uint8_t firstLeftRotation = rrotate(afterKey, rotator);
					decryptedArray[i] = firstLeftRotation;
					decryptionCounter++;
					if (decryptionCounter > 255)
					{
						decryptionCounter = 0;
					}
				}



				uint32_t write_ret = writeData(writeAddress, (uint32_t *)decryptedArray, NUBMEROFBYTESINFWMESSAGE);
				uint8_t retriesCount = 0;
				while ( (0 != write_ret) && (retriesCount <= 5) )
				{
					HAL_Delay(5);
					write_ret = writeData(writeAddress, (uint32_t *)decryptedArray, NUBMEROFBYTESINFWMESSAGE);
					retriesCount++;
				}
				if (retriesCount > 0)
				{
//					int c = 1;
				}
				previousPackID = packID;
				sprintf(localString,"P%06d\r",packID);
				lastPacketRequest = HAL_GetTick();
			}
			else if (packID == previousPackID) // Received duplicate packet
			{
				sprintf(localString,"P%06d\r",packID);
				HAL_Delay(5);
				lastPacketRequest = HAL_GetTick();
			}
//			else // Resend packet
//			{
//				sprintf(localString,"R%06d\r",previousPackID);
//				HAL_Delay(5);
//			}
			PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
			USB_FlushTxFifo(hpcd->Instance, 15);
			CDC_Transmit_FS((uint8_t*)localString, 16);
			memset(usbRXArray, 0, APP_RX_DATA_SIZE);
			usbBytesRead = 0;
		}
		else if  ( (usbBytesRead > 1) && (!isInfwUpdateMode) && (usbRXArray[0] == '\r') )
		{
			parse(localCommand);
			localCounter = 0;
			memset(localCommand,0,COMMANDSMAXSIZE);
			memset(usbRXArray, 0, APP_RX_DATA_SIZE);
			usbBytesRead = 0;
		}
		else if  ( (usbBytesRead > 1) && (!isInfwUpdateMode) )
		{
			parse((char *)usbRXArray);
			memset(usbRXArray, 0, APP_RX_DATA_SIZE);
			usbBytesRead = 0;
		}
		else if ( (usbBytesRead == 0) && (isInfwUpdateMode) && (previousPackID > 0) && (previousPackID < packID)
				&& (HAL_GetTick() - lastPacketRequest > 50) )
		{
			char localString[16] = "";
			sprintf(localString,"R%06d\r",previousPackID);
			PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
			USB_FlushTxFifo(hpcd->Instance, 15);
			CDC_Transmit_FS((uint8_t*)localString, 16);
			lastPacketRequest = HAL_GetTick();
		}
		else if ( (usbBytesRead == 0) && (isInfwUpdateMode) && (previousPackID > 0) && (previousPackID == packID)
				&& (HAL_GetTick() - lastPacketRequest > 50)  && (packID == totalPackID) && (totalPackID != 0) )
		{
			char localString[16] = "";
			sprintf(localString,"P%06d\r",previousPackID);
			PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
			USB_FlushTxFifo(hpcd->Instance, 15);
			CDC_Transmit_FS((uint8_t*)localString, 16);
			lastPacketRequest = HAL_GetTick();
		}
		else if ( (usbBytesRead == 0) && (isInfwUpdateMode) && (previousPackID > 0) && (previousPackID > packID)
				&& (HAL_GetTick() - lastPacketRequest > 50) )
		{
			char localString[16] = "";
			sprintf(localString,"R%06d\r",packID);
			PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
			USB_FlushTxFifo(hpcd->Instance, 15);
			CDC_Transmit_FS((uint8_t*)localString, 16);
			lastPacketRequest = HAL_GetTick();
			previousPackID = packID;
		}
		else if ( (localArray[0] == 'P') && (localArray[NUBMEROFBYTESINFWMESSAGE + 3] == '#')
		        && (localArray[NUBMEROFBYTESINFWMESSAGE + 4] == '\r')
				&& (isInfwUpdateMode) && (receivedCRC == 0xEC0C))
		{
			char localString[16] = "";
			sprintf(localString,"T%06d\r",packID);
			PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
			USB_FlushTxFifo(hpcd->Instance, 15);
			CDC_Transmit_FS((uint8_t*)localString, 16);
			lastPacketRequest = HAL_GetTick();
		}
		else if ( (usbBytesRead == 0) && (isInfwUpdateMode) && (previousPackID >= 0) && (previousPackID == packID)
				&& (packID == 0) && (HAL_GetTick() - lastPacketRequest > 50) && (totalPackID == 0) )
		{
			char localString[16] = "";
			sprintf(localString,"T%06d\r",packID);
			PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
			USB_FlushTxFifo(hpcd->Instance, 15);
			CDC_Transmit_FS((uint8_t*)localString, 16);
			lastPacketRequest = HAL_GetTick();
		}
		else if ( (usbBytesRead == 0) && (isInfwUpdateMode) && (previousPackID >= 0) && (previousPackID == packID)
				&& (packID == 0) && (HAL_GetTick() - lastPacketRequest > 50) && (totalPackID != 0))
		{
			char localString[16] = "";
			sprintf(localString,"P%06d\r",packID);
			PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
			USB_FlushTxFifo(hpcd->Instance, 15);
			CDC_Transmit_FS((uint8_t*)localString, 16);
			lastPacketRequest = HAL_GetTick();
		}
		else if ( (usbBytesRead == 0) && (isInfwUpdateMode) && (previousPackID >= 0) && (previousPackID == packID)
				&& (packID != 0) && (HAL_GetTick() - lastPacketRequest > 50) && (totalPackID != 0))
		{
			char localString[16] = "";
			sprintf(localString,"P%06d\r",packID);
			PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
			USB_FlushTxFifo(hpcd->Instance, 15);
			CDC_Transmit_FS((uint8_t*)localString, 16);
			lastPacketRequest = HAL_GetTick();
		}

		memset(usbRXArray, 0, APP_RX_DATA_SIZE);
		usbBytesRead = 0;
		lastUSBDataRead = HAL_GetTick();
		if ( (isInfwUpdateMode) && (totalPackID != 0) )
		{
			if ( (packID == totalPackID) && (packID != 0) )
			{
//				F_CRC_InicializaTabla();
				uint16_t localCalcCRC = F_CRC_CalculaCheckSumFromFlash(localFlashParams.startAddress, totalBytesLengthInFile);
				if (localCalcCRC == receivedCRC)
				{
					sprintf(terminalBuffer,"CRCs are identical");
					logData(terminalBuffer, false, false, false);
					isInfwUpdateMode = false;
					currentSmaStatus.smaState = UPDATE;
					reallocateData(0x8180000, 0x08000000, totalBytesLengthInFile);
	//				changeROP(1);
					ee.rcMode = 0;
					ee_save1();
					func_endUpdatePhase();
				}
				else
				{
					localFlashParams.startAddress = 0x8180000;
					prepFlash(1);
					sprintf(terminalBuffer,"CRCs are NOT identical");
					logData(terminalBuffer, false, false, false);
					packID = 1;
					previousPackID = 0;
					decryptionCounter = 0;
//					char localString[16] = "";
//					sprintf(localString,"R%06d\r",packID);
//					HAL_Delay(5);
//
//					PCD_HandleTypeDef *hpcd = hUsbDeviceFS.pData;
//					USB_FlushTxFifo(hpcd->Instance, 15);
//					CDC_Transmit_FS((uint8_t*)localString, 16);
//					memset(usbRXArray, 0, APP_RX_DATA_SIZE);
//					usbBytesRead = 0;
//					retriesCounter++;
				}
			}
		}

	}
	return usbBytesRead;
}

uint16_t fastUSBData(void)
{
//	uint16_t usbBytesRead = 0;
//	if ( (HAL_GetTick() - lastUSBDataRead >= 15) && (!isMSCMode) )
//	{
//		//	memset(usbRXArray, 0, APP_RX_DATA_SIZE);
//		USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &usbRXArray[0]);
//		uint8_t ret = USBD_CDC_ReceivePacket(&hUsbDeviceFS);
//		char * ptr;
//		int    ch = '#';
//
//		ptr = strchr((char *)usbRXArray, ch );
//		if (ptr != NULL)
//		{
//			int a = 1;
//		}
//		for (int i = 0 ; i < 65; i++)
//		{
//			if (usbRXArray[i] != 0)
//			{
//				usbBytesRead = i;
//			}
//		}
//
//		if (usbBytesRead >= 1)
//		{
//			memcpy(&FileReadBuffer, (uint8_t *)usbRXArray, 35);
//			//		usbBytesRead = 0;
//			int a = 1;
//			a = a+ 1;
//		}
//
//		lastUSBDataRead = HAL_GetTick();
//	}
//	return usbBytesRead;
	uint16_t usbBytesRead = 0;
	if ( (HAL_GetTick() - lastUSBDataRead >= 10) && (!isMSCMode) )
	{
//		memset(usbRXArray, 0, APP_RX_DATA_SIZE);
		USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &usbRXArray[0]);
		USBD_CDC_ReceivePacket(&hUsbDeviceFS);
		usbBytesRead = strlen((char *)usbRXArray);
		char * ptr;
		int    ch = '\r';

		ptr = strchr((char *)usbRXArray, ch );

		if ( (usbBytesRead >= 1) && (ptr == NULL) )
		{
//			//TODO: move before release
//			if ( (usbRXArray[0] == '\r') && (!isInfwUpdateMode) )
//			{
//				parse(localCommand);
//				localCounter = 0;
//				memset(localCommand,0,COMMANDSMAXSIZE);
//			}
//			else
//			{
				localCommand[localCounter] = usbRXArray[0];
				localCounter++;
//			}
			memset(usbRXArray, 0, APP_RX_DATA_SIZE);
			usbBytesRead = 0;
		}
		else if  ( (usbBytesRead > 1) && (!isInfwUpdateMode) && (usbRXArray[0] == '\r') )
		{
			parse(localCommand);
			localCounter = 0;
			memset(localCommand,0,COMMANDSMAXSIZE);
			memset(usbRXArray, 0, APP_RX_DATA_SIZE);
			usbBytesRead = 0;
		}
		else if  ( (usbBytesRead > 1) && (!isInfwUpdateMode) )
		{
			parse((char *)usbRXArray);
			memset(usbRXArray, 0, APP_RX_DATA_SIZE);
			usbBytesRead = 0;
		}
		lastUSBDataRead = HAL_GetTick();
	}
	return usbBytesRead;
}

void MX_MSC_DEVICE_Init(void)
{
	USBD_DeInit(&hUsbDeviceFS);
	HAL_Delay(1500);
	if (USBD_Init(&hUsbDeviceFS, &FS_MSC_Desc, DEVICE_FS) != USBD_OK)
	{
		Error_Handler();
	}
	if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_MSC) != USBD_OK)
	{
		Error_Handler();
	}
	if (USBD_MSC_RegisterStorage(&hUsbDeviceFS, &USBD_Storage_Interface_fops_FS) != USBD_OK)
	{
		Error_Handler();
	}
	if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
	{
		Error_Handler();
	}
}
/* USER CODE END 1 */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{
  /* USER CODE BEGIN USB_DEVICE_Init_PreTreatment */

  /* USER CODE END USB_DEVICE_Init_PreTreatment */

  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN USB_DEVICE_Init_PostTreatment */

  /* USER CODE END USB_DEVICE_Init_PostTreatment */
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
