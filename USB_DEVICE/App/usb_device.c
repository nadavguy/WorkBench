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
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t localCounter = 0;
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

uint32_t lastUSBDataRead = 0;
/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
uint16_t readUSBData(void)
{
	uint16_t usbBytesRead = 0;
	if (HAL_GetTick() - lastUSBDataRead >= 10)
	{
//		memset(usbRXArray, 0, APP_RX_DATA_SIZE);
		USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &usbRXArray[0]);
		USBD_CDC_ReceivePacket(&hUsbDeviceFS);
		usbBytesRead = strlen((char *)usbRXArray);
		char * ptr;
		int    ch = '\r';

		ptr = strchr( usbRXArray, ch );

		if ( (usbBytesRead >= 1) && (ptr == NULL) )
		{
			//TODO: move before release
			if ( (usbRXArray[0] == '\r') && (!isInfwUpdateMode) )
			{
				parse(localCommand);
				localCounter = 0;
				memset(localCommand,0,COMMANDSMAXSIZE);
			}
			else
			{
				localCommand[localCounter] = usbRXArray[0];
				localCounter++;
			}
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

uint16_t fastUSBData(void)
{
	uint16_t usbBytesRead = 0;

//	memset(usbRXArray, 0, APP_RX_DATA_SIZE);
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &usbRXArray[0]);
	uint8_t ret = USBD_CDC_ReceivePacket(&hUsbDeviceFS);
	if (ret != USBD_OK)
	{
		int a = 1;
	}
	for (int i = 0 ; i < 1024; i++)
	{
		if (usbRXArray[i] != 0)
		{
			usbBytesRead = i;
		}
	}

	if (usbBytesRead >= 1)
	{
		memcpy(&FileReadBuffer, (uint8_t *)usbRXArray, 35);
//		usbBytesRead = 0;
		int a = 1;
		a = a+ 1;
	}

	lastUSBDataRead = HAL_GetTick();
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
