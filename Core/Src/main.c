/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "math.h"
#include "PushButton.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include "image.h"
#include "BatteryImages.h"
#include "LogoImages.h"
#include "LocationImages.h"
#include "AutoPilotImages.h"
#include "SignalImages.h"
#include "SafeAirImages.h"
#include "BluetoothImages.h"
#include "PlatformImages.h"
#include "LCD_Test.h"
#include "LCD_1in8.h"
#include "crcAgent.h"
#include "ScreenSaverImages.h"
#include "DataTransferImages.h"
//#include "swap.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define __USE_BOOT_LOADER__
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char terminalBuffer[terminalRXBufferSize] = {0};
//char *ttt;

float fwVersion = 1.040;
float buildID = 1.300;

bool isLowBattery = false;
bool isEmptyBattery = false;
bool isUSBConnected = false;
bool isMSCMode = false;
bool isSignalLow = false;
bool isNoSignal = false;
bool shouldUpdateStatusText = true;
bool shouldRedrawBatteryIcon = true;
bool shouldRedrawSignalStrengthIcon = true;
bool shouldDrawRedAlertIcon = false;
bool shouldReDrawPlatformIcon = true;
bool shouldUpdatePlatformText = true;
bool shouldReDrawAutoPilotIcon = true;
bool shouldReDrawBluetoothIcon = true;
bool shouldReDrawTriggerModeIcon = true;
bool shouldClearDisplayedWarning = true;
bool forceDisarmEnabled = false;
bool formatSDEnabled = false;
bool waitForAckResponse = false;
bool shouldRedrawSafeAirBatteryIcon = true;
bool isScreenBrightFull = true;
bool shouldDrawSafeAirAltitude = true;
bool testMotorCut = false;
bool isDisableButtonDetection = false;
bool isFirstCycleAfterUSBDisconnection = false;
bool shouldRedrawButtonDotIcon = true;
bool markGPSPosition = false;
bool armDroneRequest = false;


uint16_t fullFrameDelay = 5000;

uint32_t UID1 = 0;
uint32_t UID2 = 0;
uint32_t UID3 = 0;
uint32_t A[9] = {0};
uint32_t lastScreenUpdate = 0;
uint32_t lastLogEntry = 0;
uint32_t lastOpModeCycle = 0;


tCURSOR_DATA currentCursorPosition;


float batteryVoltage = 4.25;
float chargingMaxValue = 0;
float previousBatteryVoltage = 0;

unsigned int BytesWritten = 0;

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

tGPSPOSITION lastKnownPosition;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
#ifdef __USE_BOOT_LOADER__
// 	SCB->VTOR = 0x8020000; /* NVIC Vector Table Relocation in Internal FLASH */
#endif
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
//	RCC_OscInitTypeDef RCC_test = {0};
//	HAL_RCC_GetOscConfig(&RCC_test);
//
//	if (RCC_test.HSEState == 0x10000)
//	{
//		//	  __HAL_RCC_SYSCLK_CONFIG(4);
//		HAL_RCC_DeInit();
//	}
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_RTC_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

	UID1 = (*(__I uint32_t *) 0x1FF0F420);
	UID2 = (*(__I uint32_t *) 0x1FF0F424);
	UID3 = (*(__I uint32_t *) 0x1FF0F428);




	ee_init1((pU32)&ee, sizeof(ee));
//	if (!ee_validate1())
//	{
//		sprintf(terminalBuffer,"EEPROM1 Error, set default values");
//		logData(terminalBuffer, true, false, false);
//		ee_save1();
//	}

	initMenuPages();
	initMenuItems();
	initPopupMessages();
	initBuzzerPatterns();


	screenInit();
	nextPattern = &testBuzzerPattern;
	setBuzzerPattern(*nextPattern);
	screenClear();
	renderCompleteFrame = true;
	CheckButtons();
	createEmptyFrame(false);

//	createPingMessage();
//	nextPattern = &noBuzzerPattern;
//	setBuzzerPattern(*nextPattern);

	/* Debug Init */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1)
	{

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_TIM;
  PeriphClkInitStruct.TIMPresSelection = RCC_TIMPRES_ACTIVATED;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void UpdateScreenBrightness(bool screenBrightfullnessLevel)
{
	if ( (screenBrightfullnessLevel) && (HAL_GetTick() - lastAnyButtonPress > 120000) )
	{
		LCD_1IN8_SetBackLight(4000);
		//		LCD_1IN8_SetBackLight(ee.backLight);
		isScreenBrightFull = false;
	}
	else if ( (!screenBrightfullnessLevel)
			&& (HAL_GetTick() - lastAnyButtonPress < 2000) )
	{
		LCD_1IN8_SetBackLight(ee.backLight * 2000);
		isScreenBrightFull = true;
		isDisableButtonDetection = true;
	}
}
void updateRCState(void)
{

}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
