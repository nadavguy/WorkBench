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

#include "ConfigParams.h"
#include "ScreenAgent.h"
#include "PushButton.h"
#include "BuzzerAgent.h"
#include "TerminalAgent.h"
#include "ymodem.h"
#include "Common.h"
#include "PowerAgent.h"
#include "EEPROMAgent.h"
#include "Pitches.h"
#include <crcAgent.h>
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
#define abnormalGyro	4096
#define abnormalAcceleration	8192
#define abnormalAngle	16384
#define smaButtonStuck	32768

#define terminalRXBufferSize 1024

#define MCURefVoltage 3.3

#define MASTERCHIEF 117
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
extern char terminalBuffer[terminalRXBufferSize];

extern float fwVersion;
extern float buildID;
extern float batteryVoltage;
extern float chargingMaxValue;

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
extern bool shouldDrawSafeAirAltitude;
extern bool isScreenBrightFull;
extern bool testMotorCut;
extern bool isDisableButtonDetection;
extern bool isFirstCycleAfterUSBDisconnection;
extern bool shouldRedrawButtonDotIcon;
extern bool markGPSPosition;
extern bool armDroneRequest;

extern uint16_t fullFrameDelay;

extern uint32_t UID1;
extern uint32_t UID2;
extern uint32_t UID3;
//uint32_t A[9];

extern unsigned int BytesWritten;

extern LINKType linkType;

extern tCURSOR_DATA currentCursorPosition;

extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;

extern tGPSPOSITION lastKnownPosition;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern void UpdateScreenBrightness(bool screenBrightfullnessLevel);
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
#define GPIO_TriggerButton_Pin GPIO_PIN_9
#define GPIO_TriggerButton_GPIO_Port GPIOE
#define GPIO_CS___LCD_Pin GPIO_PIN_6
#define GPIO_CS___LCD_GPIO_Port GPIOC
#define GPIO_ChargeDetect_Pin GPIO_PIN_9
#define GPIO_ChargeDetect_GPIO_Port GPIOA
#define GPIO_UpButton_Pin GPIO_PIN_3
#define GPIO_UpButton_GPIO_Port GPIOD
#define GPIO_DownButton_Pin GPIO_PIN_4
#define GPIO_DownButton_GPIO_Port GPIOD
#define GPIO_ApproveButton_Pin GPIO_PIN_7
#define GPIO_ApproveButton_GPIO_Port GPIOD
#define TIM3_CH1_LED_PWM_Pin GPIO_PIN_4
#define TIM3_CH1_LED_PWM_GPIO_Port GPIOB
#define GPIO_Buzzer_Pin GPIO_PIN_0
#define GPIO_Buzzer_GPIO_Port GPIOE
#define GPIO_ChargeEN_Pin GPIO_PIN_1
#define GPIO_ChargeEN_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

#define DC_Pin GPIO_PIN_4
#define DC_GPIO_Port GPIOC
#define RST_Pin GPIO_PIN_5
#define RST_GPIO_Port GPIOC
#define CS_Pin GPIO_PIN_6
#define CS_GPIO_Port GPIOC

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
