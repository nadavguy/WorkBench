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
#include "dma.h"
#include "fatfs.h"
#include "quadspi.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "math.h"
#include "ff.h"
#include "PushButton.h"
#include "TBSAgent.h"
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
#include "UniqueImages.h"
#include "LCD_Test.h"
#include "stm32746g_qspi.h"
#include "w25q128fv.h"
#include "LCD_1in8.h"
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

float fwVersion = 1.000;
float buildID = 1.330;

SYSTEMState rcState = PREINIT;

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

uint16_t fullFrameDelay = 5000;

uint32_t UID1 = 0;
uint32_t UID2 = 0;
uint32_t UID3 = 0;
uint32_t A[9] = {0};
uint32_t lastScreenUpdate = 0;
uint32_t lastLogEntry = 0;

SYSTEMConnectionStatus bluetoothConnection = DISCONNECTED;

SIGNALStrength tbsLink = NOSIGNAL;
SIGNALStrength batteryStrength = STRONG;

tCURSOR_DATA currentCursorPosition;

tWarning displayWarning;

float batteryVoltage = 4.2;
float chargingMaxValue = 0;

unsigned int BytesWritten = 0;

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

tGPSPOSITION lastKnownPosition;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
	SCB->VTOR = 0x8020000; /* NVIC Vector Table Relocation in Internal FLASH */
#endif
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	RCC_OscInitTypeDef RCC_test = {0};
	HAL_RCC_GetOscConfig(&RCC_test);

	if (RCC_test.HSEState == 0x10000)
	{
		//	  __HAL_RCC_SYSCLK_CONFIG(4);
		HAL_RCC_DeInit();
	}
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_FATFS_Init();
	MX_QUADSPI_Init();
	MX_SPI1_Init();
	MX_USB_DEVICE_Init();
	MX_ADC1_Init();
	MX_TIM3_Init();
	MX_USART1_UART_Init();
	MX_USART3_UART_Init();
	MX_RTC_Init();
	MX_ADC2_Init();
	MX_ADC3_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	//
	//  char test[8] = "Testtset";
	//  HAL_UART_Transmit(&huart2, (uint8_t *)test, 8, 20);
	UID1 = (*(__I uint32_t *) 0x1FF0F420);
	UID2 = (*(__I uint32_t *) 0x1FF0F424);
	UID3 = (*(__I uint32_t *) 0x1FF0F428);

	BSP_QSPI_Init();

	//  HAL_Delay(1000);

	fileSystemInit();
	createNewLogFile();

	ee_init1((pU32)&ee, sizeof(ee));
	if (!ee_validate1())
	{
		sprintf(terminalBuffer,"EEPROM1 Error, set default values");
		logData(terminalBuffer, true, false, false);
		ee_save1();
	}

	initMenuPages();
	initMenuItems();
	initPopupMessages();
	initBuzzerPatterns();

	channelPWMValues[0] =  ((ee.armPWMOffValue - 1500) * 2);
	channelPWMValues[1] = ((ee.triggerPWMOffValue - 1500) * 2);
	CheckButtons();

	rcState = INIT;
	rcLinkStatus.UplinkRSSIAnt1 = 0xFF;
	rcLinkStatus.UplinkRSSIAnt2 = 0xFF;
	tbsLink = NOSIGNAL;

	printRCConfiguration(false);

	screenInit();

	screenClear();
	renderCompleteFrame = true;
	CheckButtons();
	createEmptyFrame(false, false);

	//  createPingMessage();
	nextPattern = &noBuzzerPattern;
	setBuzzerPattern(*nextPattern);

	measureVoltages(true);

	initBLE();

	currentCursorPosition.cursorPosition = 0;
	currentCursorPosition.menuDepth = 0;
	if ( (tbsLink == NOSIGNAL) && (isChargingMode) )
	{
		memcpy(&popupToShow, &tbsInChargeModeMessage, sizeof(popupToShow));
		waitForPopupInput();
	}
	if ( (tbsLink == NOSIGNAL) && (!isChargingMode) )
	{
		memcpy(&popupToShow, &noConnectionMessage, sizeof(popupToShow));
		waitForPopupInput();
	}

	/* Debug Init */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1)
	{
		if (!isChargingMode)
		{
			CheckButtons();
			waitForPopupInput();
			sendChannelMessageToTBS();
			HAL_UART_Receive_DMA(&TBS_UART, tbsRXArray,TBS_RX_BUFFER);
			HAL_Delay(2);
			parseTBSMessage();
			//TODO: Backward compatibility of SafeAir unit with old FW
			// if there is telemetry messages without 0xDD message
			// Allow only basic functionality
			updateRCState();
			monitorLogSize();

			readUSBData();

			checkBLEMessages();
		}
		if (!renderCompleteFrame)
		{
			if (HAL_GetTick() - lastScreenUpdate > 100)
			{
				screenUpdate(true);
				lastScreenUpdate = HAL_GetTick();
			}
		}
		else
		{
			if (!isChargingMode)
			{
				if ( (HAL_GetTick() - lastFullFrameDisplayed > fullFrameDelay) && (!isMenuDisplayed) && (!isPopupDisplayed) )
				{
					createEmptyFrame(false, true);
					setFullDisplay();
					screenUpdate(false);
					lastFullFrameDisplayed = HAL_GetTick();
				}
				else
				{
					screenUpdate(true);
				}
			}
			else
			{
				LCD_1IN8_SetBackLight(4000);
				createEmptyFrame(false, false);
				//			  screenUpdate(false);
				setIconPositionOnScreen();
				Paint_DrawImage(gImage_ChargingMode, ChargingModeImageX, ChargingModeImageY, 43, 86);
				char localText[12] = "";
				chargingMaxValue = fmax(chargingMaxValue, batteryVoltage);
				int8_t localPercent = (int8_t)(chargingMaxValue * (142.847) - 500);
				if (localPercent > 100)
				{
					localPercent = 100;
				}
				else if (localPercent < 0)
				{
					localPercent = 0;
				}

				sprintf(localText, "%03d%%", localPercent);
				centeredString(ChargingModePercentTextX, ChargingModePercentTextY, localText, BLACK, BACKGROUND, 14, Font16);
				centeredString(ChargingModePercentTextX, ChargingModeImageY - 24, "Charging", BLACK, BACKGROUND, 14, Font16);
			}
			updateNextFrame();
		}
		updateBuzzerStatus();
		checkChargerMux();
		measureVoltages(false);

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
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	/** Configure LSE Drive Capability
	 */
	HAL_PWR_EnableBkUpAccess();
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
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_TIM|RCC_PERIPHCLK_RTC
			|RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
			|RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_CLK48;
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV25;
	PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
	PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
	PeriphClkInitStruct.TIMPresSelection = RCC_TIMPRES_ACTIVATED;

	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Enables the Clock Security System
	 */
	HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */
void updateRCState(void)
{
	if ( (rcState == INIT) && (!isNoSignal) )
	{
		rcState = OPERATIONAL;
	}
	else if ( (rcState == OPERATIONAL) && (isNoSignal) )
	{
		rcState = INIT;
	}

	if  ( (isUSBConnected) )
	{
		if ( (batteryStrength != CHARGING) )
		{
			isLowBattery = false;
			isEmptyBattery = false;
			shouldRedrawBatteryIcon = true;
			batteryStrength = CHARGING;
			displayWarning.BITStatus &= ~rcLowBat;
		}
		//Show charging symbol
	}
	else
	{
		if ( (batteryVoltage <= 3.3) && (batteryStrength < EMPTY))
		{
			isLowBattery = true;
			isEmptyBattery = true;
			shouldRedrawBatteryIcon = true;
			batteryStrength = EMPTY;
			displayWarning.BITStatus |= rcLowBat;
			sprintf(terminalBuffer,"RC Battery is Empty");
			logData(terminalBuffer, false, false, false);
		}
		else if ( (batteryVoltage > 3.3) && (batteryVoltage <= 3.45) && (batteryStrength < LOW))
		{
			shouldRedrawBatteryIcon = true;
			batteryStrength = LOW;
			displayWarning.BITStatus |= rcLowBat;
			sprintf(terminalBuffer,"RC Battery is Low");
			logData(terminalBuffer, false, false, false);
		}
		else if ( (batteryVoltage > 3.45) && (batteryVoltage <= 3.8) && (batteryStrength < MEDIUM) )
		{
			shouldRedrawBatteryIcon = true;
			batteryStrength = MEDIUM;
			displayWarning.BITStatus &= ~rcLowBat;
			sprintf(terminalBuffer,"RC Battery is Partially Full");
			logData(terminalBuffer, false, false, false);
		}
		else if ( (batteryVoltage > 3.8) && (batteryStrength != STRONG))
		{
			shouldRedrawBatteryIcon = true;
			batteryStrength = STRONG;
			displayWarning.BITStatus &= ~rcLowBat;
			sprintf(terminalBuffer,"RC Battery is Full");
			logData(terminalBuffer, false, false, false);
		}
	}

	if ( (HAL_GetTick() - lastReceivedCRSFMessage > 3000) && (!isTBSDisconnected) )
	{
		isNoSignal = true;
		shouldRedrawSignalStrengthIcon = true;
		tbsLink = NOSIGNAL;
		isTBSDisconnected = true;
		sprintf(terminalBuffer,"No connection with TBS TX");
		logData(terminalBuffer, true, false, false);
	}
	else if ( (rcLinkStatus.UplinkRSSIAnt1 == 0xFF) && (rcLinkStatus.UplinkRSSIAnt2 == 0xFF) )
	{
		if (tbsLink != NOSIGNAL)
		{
			isNoSignal = true;
			shouldRedrawSignalStrengthIcon = true;
			tbsLink = NOSIGNAL;
			logRCLinkStatus(true);
		}
		//Show no signal icon
	}
	else if ( (rcLinkStatus.DownlinkPSRLQ <= 50) && (tbsLink != LOW) )
	{
		isNoSignal = false;
		isSignalLow = true;
		shouldRedrawSignalStrengthIcon = true;
		tbsLink = LOW;
		logRCLinkStatus(true);
	}
	else if ( (rcLinkStatus.DownlinkPSRLQ > 50) && (rcLinkStatus.DownlinkPSRLQ <= 75) && (tbsLink != MEDIUM) )
	{
		isNoSignal = false;
		isSignalLow = true;
		shouldRedrawSignalStrengthIcon = true;
		tbsLink = MEDIUM;
		logRCLinkStatus(true);
	}
	else if ( (rcLinkStatus.DownlinkPSRLQ > 75) && (tbsLink != STRONG) )
	{
		isNoSignal = false;
		isSignalLow = false;
		shouldRedrawSignalStrengthIcon = true;
		tbsLink = STRONG;
		logRCLinkStatus(true);
	}

	if (previousSmaStatus.smaPlatfom != currentSmaStatus.smaPlatfom)
	{
		shouldReDrawPlatformIcon = true;
	}
	else
	{
		shouldReDrawPlatformIcon = false;
	}

	if (previousSmaStatus.smaPlatformName != currentSmaStatus.smaPlatformName)
	{
		shouldUpdatePlatformText = true;
	}
	else
	{
		shouldUpdatePlatformText = false;
	}

	if ( ( ((displayWarning.BITStatus != previousBITStatus) && (displayWarning.BITStatus != 0x00)) ||
			( ((batteryStrength == LOW) || (batteryStrength == EMPTY)) && (shouldRedrawBatteryIcon) ) )
			&& (currentSmaStatus.smaState != TRIGGERED) )
	{
		displayWarning.displayWarning = true;
		shouldDrawRedAlertIcon = true;
		shouldUpdateStatusText = true;
		if (displayWarning.BITStatus != 0x00)
		{
			previousBITStatus = displayWarning.BITStatus;
		}
	}
	else if ( ( (currentSmaStatus.smaState == IDLE) || (currentSmaStatus.smaState == ARMED) )
			&& (displayWarning.BITStatus == 0) && (previousBITStatus != 0) )
	{
		shouldUpdateStatusText = true;
		shouldClearDisplayedWarning = true;
		displayWarning.displayWarning = false;
	}
	else
	{
		//		displayWarning.displayWarning = false;
	}

	if (previousSmaStatus.isAutoPilotConnected != currentSmaStatus.isAutoPilotConnected)
	{
		shouldReDrawAutoPilotIcon = true;
	}
	else
	{
		shouldReDrawAutoPilotIcon = false;
	}

	if (previousSmaStatus.safeairTriggerMode != currentSmaStatus.safeairTriggerMode)
	{
		shouldReDrawTriggerModeIcon = true;
	}
	else
	{
		shouldReDrawTriggerModeIcon = false;
	}



	if ( (currentSmaStatus.smaState == 0x4) && (previousSmaStatus.smaState != UNKNOWN) )
	{
		//Sound SMA Error
		previousSmaStatus.smaState = UNKNOWN;
		shouldUpdateStatusText = true;
	}
	else if ( (currentSmaStatus.smaState == 0x05) && (previousSmaStatus.smaState != MAINTENANCE) )
	{
		//Sound SMA Maintenance?
		previousSmaStatus.smaState = MAINTENANCE;
		shouldUpdateStatusText = true;
	}
	else if (currentSmaStatus.smaState == 0x03)
	{
		//Sound SMA triggered
		if (previousSmaStatus.smaState != TRIGGERED)
		{
			previousSmaStatus.smaState = TRIGGERED;
			shouldUpdateStatusText = true;
		}
		nextPattern = &triggeredSafeAirPattern;
		//		setBuzzerPattern(*nextPattern);
	}
	else if ( (currentSmaStatus.smaState == 0x02) && (previousSmaStatus.smaState != ARMED) )
	{
		//Sound SMA Armed
		previousSmaStatus.smaState = ARMED;
		nextPattern = &armedBuzzerPattern;
		shouldUpdateStatusText = true;
	}
	else if ( (currentSmaStatus.smaState == 0x01) && (previousSmaStatus.smaState != IDLE) )
	{
		if (isBuzzerCycleEnded)
		{
			//Sound SMA Disarmed
			nextPattern = &idleBuzzerPattern;
			previousSmaStatus.smaState = IDLE;
			shouldUpdateStatusText = true;
		}
	}
	else if (currentSmaStatus.batteryVoltage < 3.8)
	{
		//Sound SMA low battery
	}
	else if (isNoSignal)
	{
		//Sound no Link
		nextPattern = &noTelemetryPattern;
	}
	else if (isSignalLow)
	{
		//Sound Low signal
		nextPattern = &lowTelemetryPattern;
	}
	else if (isLowBattery)
	{
		// Sound low RC battery
		nextPattern = &lowRCBatteryPattern;
	}
	else
	{
		//Sound nothing
		nextPattern = &noBuzzerPattern;
	}
	if (isBuzzerCycleEnded)
	{
		setBuzzerPattern(*nextPattern);
	}

	if ( (isScreenBrightFull) && (HAL_GetTick() - lastAnyButtonPress > 120000) )
	{
		LCD_1IN8_SetBackLight(2000);
		//		LCD_1IN8_SetBackLight(ee.backLight);
		isScreenBrightFull = false;
	}
	else if ( (!isScreenBrightFull) && (HAL_GetTick() - lastAnyButtonPress < 2000) )
	{
		LCD_1IN8_SetBackLight(ee.backLight * 2000);
		isScreenBrightFull = true;
	}

	if ( (shouldUpdateStatusText  || shouldReDrawTriggerModeIcon || shouldReDrawAutoPilotIcon || shouldRedrawBatteryIcon
			|| shouldUpdatePlatformText || shouldReDrawPlatformIcon ) && (HAL_GetTick() - lastLogEntry > 50) )// || shouldDrawRedAlertIcon
	{
		//		sprintf(terminalBuffer,"SmartAir state: %d, trigger mode: %d",
		//				currentSmaStatus.smaState, currentSmaStatus.triggerMode);
		//		logData(terminalBuffer, false, false, false);
		//		sprintf(terminalBuffer,"SmartAir Battery: %6.3f",currentSmaStatus.batteryVoltage);
		//		logData(terminalBuffer, false, false, false);
		//		sprintf(terminalBuffer,"SmartAir Altitude: %6.3f, Acceleration: %6.3f",
		//				currentSmaStatus.Altitude, currentSmaStatus.Acceleration);
		//		logData(terminalBuffer, false, false, false);

		sprintf(terminalBuffer,"SMA, %d, %d, %6.3f, %6.3f, %6.3f",currentSmaStatus.smaState, currentSmaStatus.triggerMode,
				currentSmaStatus.batteryVoltage, currentSmaStatus.Altitude, currentSmaStatus.Acceleration);
		logData(terminalBuffer, true, false, false);
		lastLogEntry = HAL_GetTick();
	}

}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
////	for (int i =0; i<3; i++)
////	{
////	  adc[i] = buffer[i];
////	}
////
////	temperature = (((adc[2]*vsense)-.76)/.0025)+25;
//	int a = 1;
//	a = 2;
//	  A[3] = HAL_ADC_GetValue(&hadc1);
//	  A[4] = HAL_ADC_GetValue(&hadc2);
//	  A[5] = HAL_ADC_GetValue(&hadc3);
//}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
