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
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

#include "hci_tl_interface.h"
#include "custom.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h> //printf()
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#include "str_util.h"
#include "TypeDefs.h"
#include "Common.h"
#include "ci_func.h"
#include "cmd_interp.h"
#include "ConfigParams.h"
#include "PushButton.h"
#include "TBSAgent.h"
#include "LogAgent.h"
#include "TimeHelper.h"
#include "TerminalAgent.h"
#include "ScreenAgent.h"
#include "ConfigurationHelper.h"
#include "TBSAgent.h"
#include "BuzzerAgent.h"
	/* USER CODE END Includes */

	/* Exported types ------------------------------------------------------------*/
	/* USER CODE BEGIN ET */

	/* USER CODE END ET */

	/* Exported constants --------------------------------------------------------*/
	/* USER CODE BEGIN EC */

	/* USER CODE END EC */

	/* Exported macro ------------------------------------------------------------*/
	/* USER CODE BEGIN EM */

	/* USER CODE END EM */

	/* Exported functions prototypes ---------------------------------------------*/
	void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern void updateRCState(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AntiTamper_Pin GPIO_PIN_13
#define AntiTamper_GPIO_Port GPIOC
#define SPI2_MOSI___BLE_Pin GPIO_PIN_1
#define SPI2_MOSI___BLE_GPIO_Port GPIOC
#define SPI2_MISO___BLE_Pin GPIO_PIN_2
#define SPI2_MISO___BLE_GPIO_Port GPIOC
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
#define GPIO_BLE___EXTI_Pin GPIO_PIN_7
#define GPIO_BLE___EXTI_GPIO_Port GPIOE
#define GPIO_BLE___CS_Pin GPIO_PIN_8
#define GPIO_BLE___CS_GPIO_Port GPIOE
#define GPIO_TriggerButton_Pin GPIO_PIN_9
#define GPIO_TriggerButton_GPIO_Port GPIOE
#define GPIO_BLE___Reset_Pin GPIO_PIN_10
#define GPIO_BLE___Reset_GPIO_Port GPIOE
#define GPIO_ArmButton_Pin GPIO_PIN_11
#define GPIO_ArmButton_GPIO_Port GPIOE
#define SPI2_SCK___BLE_Pin GPIO_PIN_13
#define SPI2_SCK___BLE_GPIO_Port GPIOB
#define USART1_TX___TBS_Pin GPIO_PIN_14
#define USART1_TX___TBS_GPIO_Port GPIOB
#define USART1_RX___TBS_Pin GPIO_PIN_15
#define USART1_RX___TBS_GPIO_Port GPIOB
#define GPIO_CS___LCD_Pin GPIO_PIN_6
#define GPIO_CS___LCD_GPIO_Port GPIOC
#define USB_DM___White_Wire_Pin GPIO_PIN_11
#define USB_DM___White_Wire_GPIO_Port GPIOA
#define USB_DP___Green_Wire_Pin GPIO_PIN_12
#define USB_DP___Green_Wire_GPIO_Port GPIOA
#define TIM2_CH1___BL_LCD_Pin GPIO_PIN_15
#define TIM2_CH1___BL_LCD_GPIO_Port GPIOA
#define USART2_TX___BLE_VCP_Pin GPIO_PIN_5
#define USART2_TX___BLE_VCP_GPIO_Port GPIOD
#define USART2_RX___BLE_VCP_Pin GPIO_PIN_6
#define USART2_RX___BLE_VCP_GPIO_Port GPIOD
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

extern char terminalBuffer[1024];
extern float fwVersion;
extern float buildID;

extern bool isUSBConnected;

typedef enum
{
	PREINIT,
	INIT,
	OPERATIONAL,
	MAINTENANCE,
	UNKNOWN,
	IDLE,
	ARMED,
	TRIGGERED
} SYSTEMState;

typedef enum
{
	PWM,
	DIGITAL
} LINKType;

extern SYSTEMState rcState;

extern LINKType linkType;

extern SYSTEMState currentSMAState;
extern SYSTEMState desiredSMAState;
	/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
