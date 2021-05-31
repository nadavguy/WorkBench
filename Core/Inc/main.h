/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "TypeDefs.h"
#include "str_util.h"
#include "TimeHelper.h"
#include "MenuHelper.h"
#include "ItemHelper.h"
#include "PopupHelper.h"
#include "FrameHelper.h"
#include "fonts.h"

#include "LogAgent.h"
#include "cmd_interp.h"
#include "ConfigParams.h"
#include "ConfigurationHelper.h"
#include "TBSAgent.h"
#include "ScreenAgent.h"
#include "PushButton.h"
#include "BuzzerAgent.h"
#include "TerminalAgent.h"
#include "ymodem.h"
#include "Common.h"
#include "BleAgent.h"
#include "ci_func.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef enum {PWM, DIGITAL} LINKType;

typedef struct sGPSPOSITION
{
	float Latitude;
	float Longitude;
	float Altitude;
}tGPSPOSITION;


#define smaCritBat		1
#define smaLowBat 		2
#define smaFlashError 	4
#define smaOutOfBounds 	8
#define smaPyroError 	16
#define rcLowBat 		32
#define manualTrigger	64
#define geoFencing 		128
#define autoPilot 		256
#define freeFall 		512
#define criticalAngle	1024

#define terminalRXBufferSize 1024
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
extern char terminalBuffer[terminalRXBufferSize];
extern float fwVersion;
extern float buildID;

extern bool isLowBattery;
extern bool isEmptyBattery;
extern bool isUSBConnected;
extern bool isMSCMode;
extern bool isSignalLow;
extern bool isNoSignal;
extern bool shouldUpdateStatusText;
extern bool shouldRedrawBatteryIcon;
extern bool shouldRedrawSignalStrengthIcon;
extern bool shouldDrawRedAlertIcon;
extern bool shouldReDrawPlatformIcon;
extern bool shouldUpdatePlatformText;
extern bool shouldReDrawAutoPilotIcon;
extern bool shouldReDrawBluetoothIcon;
extern bool shouldReDrawTriggerModeIcon;
extern bool shouldClearDisplayedWarning;
extern bool forceDisarmEnabled;
extern bool formatSDEnabled;
extern bool waitForAckResponse;
extern bool shouldRedrawSafeAirBatteryIcon;

extern SYSTEMConnectionStatus bluetoothConnection;

extern SIGNALStrength batteryStrength;
extern SIGNALStrength tbsLink;

extern SYSTEMState rcState;
extern LINKType linkType;
extern tWarning displayWarning;

extern SYSTEMState desiredSMAState;

extern tCURSOR_DATA currentCursorPosition;

extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;

extern tGPSPOSITION lastKnownPosition;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern void updateRCState(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO_LeftButton_Pin GPIO_PIN_3
#define GPIO_LeftButton_GPIO_Port GPIOE
#define GPIO_RightButton_Pin GPIO_PIN_4
#define GPIO_RightButton_GPIO_Port GPIOE
#define GPIO_ArmButton_Pin GPIO_PIN_5
#define GPIO_ArmButton_GPIO_Port GPIOE
#define AntiTamper_Pin GPIO_PIN_13
#define AntiTamper_GPIO_Port GPIOC
#define GPIO_WakeUp_Pin GPIO_PIN_0
#define GPIO_WakeUp_GPIO_Port GPIOA
#define ADC1_3_3V_Pin GPIO_PIN_1
#define ADC1_3_3V_GPIO_Port GPIOA
#define ADC1_5_0V_Pin GPIO_PIN_2
#define ADC1_5_0V_GPIO_Port GPIOA
#define ADC1_Battery_Pin GPIO_PIN_3
#define ADC1_Battery_GPIO_Port GPIOA
#define SPI1_SCK___LCD_Pin GPIO_PIN_5
#define SPI1_SCK___LCD_GPIO_Port GPIOA
#define SPI1_MISO___LCD_Pin GPIO_PIN_6
#define SPI1_MISO___LCD_GPIO_Port GPIOA
#define SPI1_MOSI___LCD_Pin GPIO_PIN_7
#define SPI1_MOSI___LCD_GPIO_Port GPIOA
#define GPIO_DC___LCD_Pin GPIO_PIN_4
#define GPIO_DC___LCD_GPIO_Port GPIOC
#define GPIO_RST___LCD_Pin GPIO_PIN_5
#define GPIO_RST___LCD_GPIO_Port GPIOC
#define TIM3_CH3___BL_LCD_Pin GPIO_PIN_0
#define TIM3_CH3___BL_LCD_GPIO_Port GPIOB
#define GPIO_3_3Mux_Stat_Pin GPIO_PIN_1
#define GPIO_3_3Mux_Stat_GPIO_Port GPIOB
#define GPIO_BLE___AppOrConfig_Pin GPIO_PIN_8
#define GPIO_BLE___AppOrConfig_GPIO_Port GPIOE
#define GPIO_TriggerButton_Pin GPIO_PIN_9
#define GPIO_TriggerButton_GPIO_Port GPIOE
#define GPIO_BLE___Reset_Pin GPIO_PIN_10
#define GPIO_BLE___Reset_GPIO_Port GPIOE
#define USART_TX___TBS_Pin GPIO_PIN_14
#define USART_TX___TBS_GPIO_Port GPIOB
#define USART_RX___TBS_Pin GPIO_PIN_15
#define USART_RX___TBS_GPIO_Port GPIOB
#define USART3_TX___BLE_Pin GPIO_PIN_8
#define USART3_TX___BLE_GPIO_Port GPIOD
#define USART3_RX___BLE_Pin GPIO_PIN_9
#define USART3_RX___BLE_GPIO_Port GPIOD
#define GPIO_CS___LCD_Pin GPIO_PIN_6
#define GPIO_CS___LCD_GPIO_Port GPIOC
#define USB_DM___White_Wire_Pin GPIO_PIN_11
#define USB_DM___White_Wire_GPIO_Port GPIOA
#define USB_DP___Green_Wire_Pin GPIO_PIN_12
#define USB_DP___Green_Wire_GPIO_Port GPIOA
#define GPIO_UpButton_Pin GPIO_PIN_3
#define GPIO_UpButton_GPIO_Port GPIOD
#define GPIO_DownButton_Pin GPIO_PIN_4
#define GPIO_DownButton_GPIO_Port GPIOD
#define USART_TX___Retrofit_Pin GPIO_PIN_5
#define USART_TX___Retrofit_GPIO_Port GPIOD
#define USART_RX___Retrofit_Pin GPIO_PIN_6
#define USART_RX___Retrofit_GPIO_Port GPIOD
#define GPIO_ApproveButton_Pin GPIO_PIN_7
#define GPIO_ApproveButton_GPIO_Port GPIOD
#define GPIO_Buzzer_Pin GPIO_PIN_0
#define GPIO_Buzzer_GPIO_Port GPIOE
#define GPIO_ChargeEN_Pin GPIO_PIN_1
#define GPIO_ChargeEN_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

#define DC_Pin GPIO_PIN_14
#define DC_GPIO_Port GPIOB
#define RST_Pin GPIO_PIN_13
#define RST_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_15
#define CS_GPIO_Port GPIOB

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
