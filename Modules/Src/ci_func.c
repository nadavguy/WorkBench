#include "main.h"
#include "usart.h"
#include "ff.h"
#include "fatfs.h"
#include "FlashQSPIAgent.h"
#include "usb_device.h"


bool isReportParametersActive = false;

eCI_RESULT func_debug(void)
{
	if (get_param_count() > 0)
	{
		ee.debugLevel = get_param_int(0);
		ee_save1();
		sprintf(terminalBuffer,"Debug level set to: %d",ee.debugLevel);
		logData(terminalBuffer, false, false, false);
	}
	return CI_OK;
}

eCI_RESULT func_updateRCVersion(void)
{
//	HAL_UART_DMAStop(&huart1);
//
//	SerialDownload(true);
//
//	if(HAL_UART_Receive_DMA(&huart1, (uint8_t *)&aRxBufferCh1, 1 ) != HAL_OK)
//	{
//
//	} //  Error_Handler();
	//HAL_FLASH_Lock(); Is it realy needed?
	return CI_OK;
}

eCI_RESULT func_versionReport(void)
{
	sprintf(terminalBuffer,"RC Firmware version: %6.2f, BuildID: %6.2f",fwVersion, buildID);
	logData(terminalBuffer, false, true, false);
	return CI_OK;
}

eCI_RESULT func_endUpdatePhase(void)
{
//	HAL_UART_DMAStop(&huart2);
//
//	HAL_Delay(100);
//	JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
//	/* Jump to user application */
//	JumpToApplication = (pFunction) JumpAddress;
//	/* Initialize user application's Stack Pointer */
//	__set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
//	JumpToApplication();
	//TODO: show Flash process finished
	return CI_OK;
}

eCI_RESULT func_resetRC(void)
{
	NVIC_SystemReset();
	return CI_OK;
}

eCI_RESULT func_showAvailableCommands(void)
{
	return CI_OK;
}

eCI_RESULT func_armPWMOff(void)
{
	if (get_param_count() > 0)
	{
		ee.armPWMOffValue = get_param_int(0);
		ee_save1();
		sprintf(terminalBuffer,"Arm PWM Off value set to: %d",ee.armPWMOffValue);
		logData(terminalBuffer, false, false, false);
	}
	return CI_OK;
}

eCI_RESULT func_armPWMOn(void)
{
	if (get_param_count() > 0)
	{
		ee.armPWMOnValue = get_param_int(0);
		ee_save1();
		sprintf(terminalBuffer,"Arm PWM On value set to: %d",ee.armPWMOnValue);
		logData(terminalBuffer, false, false, false);
	}
	return CI_OK;
}

eCI_RESULT func_triggerPWMOff(void)
{
	if (get_param_count() > 0)
	{
		ee.triggerPWMOffValue = get_param_int(0);
		ee_save1();
		sprintf(terminalBuffer,"Trigger PWM Off value set to: %d",ee.triggerPWMOffValue);
		logData(terminalBuffer, false, false, false);
	}
	return CI_OK;
}

eCI_RESULT func_triggerPWMOn(void)
{
	if (get_param_count() > 0)
	{
		ee.triggerPWMOnValue = get_param_int(0);
		ee_save1();
		sprintf(terminalBuffer,"Trigger PWM On value set to: %d",ee.triggerPWMOnValue);
		logData(terminalBuffer, false, false, false);
	}
	return CI_OK;
}

eCI_RESULT func_linkType(void)
{
	if (get_param_count() > 0)
	{
		ee.linkType = get_param_int(0);
		ee_save1();
		sprintf(terminalBuffer,"Link type set to: %s",(ee.linkType==PWM) ? "PWM" : "Digital");
		logData(terminalBuffer, false, false, false);
	}
	return CI_OK;
}

eCI_RESULT func_systemConfiguration(void)
{
	printRCConfiguration(true);
	return CI_OK;
}

eCI_RESULT func_backLight(void)
{
	if (get_param_count() > 0)
	{
		ee.backLight = get_param_int(0);
		ee_save1();
		sprintf(terminalBuffer,"Backlight value set to: %3.1f per-cent",ee.backLight/10.0);
		logData(terminalBuffer, false, false, false);
	}
	return CI_OK;
}

eCI_RESULT func_massStorage(void)
{
	isMSCMode = true;
	MX_MSC_DEVICE_Init();
	return CI_OK;
}

eCI_RESULT func_importFile(void)
{
	  char *res = 0;
//	  uint16_t slen = 0;
	  bool _endFile = false;
//	  char *fn = get_param_str(0);
	  FIL fileToRead;
//	  f_close(&fileToRead);
	  char fullFileName[64] = "";
	  sprintf(fullFileName, "%s",get_param_str(0));
	  if (f_open(&fileToRead, fullFileName, FA_READ) == FR_OK)
	  {
	    while (!_endFile)
	    {
	      res = f_gets(terminalBuffer, terminalRXBufferSize, &fileToRead);
	      if (res != 0x00)
	      {
	    	  logData(terminalBuffer, false, true, true);
	      }
	      else
	      {
	        _endFile = true;
	        logData("EOF", false, true, true);
	      }
	    }
	  }
	  f_close(&fileToRead);
	  return CI_OK;
}

eCI_RESULT func_screenOrientation(void)
{
	if (get_param_count() > 0)
	{
		if ( (get_param_int(0) <= 1) && (get_param_int(0) >= 0) )
		{
			ee.screenOreintation = get_param_int(0);
			ee_save1();
			screenInit();
			setFullDisplay();
		}

		if (ee.screenOreintation == 0)
		{
			logData("Screen orientation set to Landscape", false, false, false);
		}
		else
		{
			logData("Screen orientation set to Portrait", false, false, false);
		}
	}
	return CI_OK;
}

eCI_RESULT func_setDateTime(void)
{
  int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;

//  if (!SessionUnlocked)
//  {
//    return CI_COMMAND_ERROR;
//  }
  if (get_param_count() > 0)
  {
    sprintf(terminalBuffer, "Received Date & Time:\'%s\'", get_param_str(0));
    logData(terminalBuffer, false, false, false);

    sscanf(get_param_str(0), "%02d/%02d/%02d %02d:%02d:%02d", &year, &month, &day, &hour, &minute, &second);

    if ( (year >= 0) && (year <= 99) && (hour >= 0) && (hour < 24) &&
    		(minute >= 0) && (minute < 60) && (day > 0) && (day < 32) && (month > 0) && (month < 13) && (second >= 0) && (second < 60) )
    {
    	sendSafeAirConfigurationMessage(true);
//    	L_hour = hour;
//    	L_min = minute;
//    	L_sec = second;
//    	L_ms = 0;
//    	L_month = month;
//    	L_day = day;
//    	L_year = 2000 + year;
//
    	sTime.Hours = hour;
    	sTime.Minutes = minute;
    	sTime.Seconds = second;
//    	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
//    	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
//    	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
//    	{
//    		_Error_Handler(__FILE__, __LINE__);
//    	}
//    	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
    	sDate.Month = month;
    	sDate.Date = day;
    	sDate.Year = year;
//
//    	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
//    	{
//    		_Error_Handler(__FILE__, __LINE__);
//    	}
//    	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F4);
//
//    	ee2.TimeSinceLastLogSync = 0;
    	//ee_save2();
    	sendSafeAirConfigurationMessage(true);
    }
    else
    {
    	sprintf(terminalBuffer, "Wrong date time:\'%s\'",get_param_str(0));
    	logData(terminalBuffer, false, false, false);
    }
  }

  return (CI_OK);
}

eCI_RESULT func_gpsLocation(void)
{
	if (get_param_count() == 3)
	{
		lastKnownPosition.Latitude = get_param_float(0);
		lastKnownPosition.Longitude = get_param_float(1);
		lastKnownPosition.Altitude = get_param_float(3);

		sprintf(terminalBuffer, "Received GPS position - Lat: %4.6f Long: %4.6f Alt: %5.1f",get_param_float(0), get_param_float(1), get_param_float(2));
		logData(terminalBuffer, false, false, false);

	}
	else
	{
		sprintf(terminalBuffer, "Received partial GPS position");
		logData(terminalBuffer, false, false, false);
	}
	return CI_OK;
}

eCI_RESULT func_dir(void)
{
    FILINFO fno1;
    DIR dp1;
    f_opendir(&dp1, "\\");
    f_findfirst(&dp1, &fno1, "\\", "LOG_*");

    while( (fno1.fname[0] != 0) )
    {
//    	f_stat("\\", &fno1);
    	sprintf(terminalBuffer,"%s\t %lu",fno1.fname, (long int)fno1.fsize);
    	logData(terminalBuffer, false, true, true);
    	f_findnext(&dp1, &fno1);
    }
    f_closedir(&dp1);
    logData("EOD", false, true, true);
	return CI_OK;
}

eCI_RESULT func_fmt(void)
{
	sprintf(terminalBuffer, "\r\n%s!Formatting Flash...restart required!\n\r", CT());
	logData(terminalBuffer, false, false, false);
	f_sync(&USERFile);
	f_close(&USERFile);

	if (f_mkfs("\\", FM_FAT, 0, buffer, sizeof(buffer)) != FR_OK)
	{
		//TODO: Add screen indication for faulty Flash
	}
	return CI_OK;
}

typedef struct
{
    char *string;
    eCI_RESULT (*func)(void);
} functionsList;

functionsList cases [] =
{
		{ "ver"	, func_versionReport },
		{ "dbg"	, func_debug },
		{ "urcv", func_updateRCVersion },
		{ "end" , func_endUpdatePhase },
		{ "rst" , func_resetRC },
		{ "help", func_showAvailableCommands },
		{ "apof", func_armPWMOff },
		{ "apon", func_armPWMOn },
		{ "tpof", func_triggerPWMOff },
		{ "tpon", func_triggerPWMOn },
		{ "lnkt", func_linkType },
		{ "ee?"	, func_systemConfiguration },
		{ "bklt", func_backLight },
		{ "msc", func_massStorage },
		{ "imp", func_importFile },
		{ "scor", func_screenOrientation },
		{ "dtm", func_setDateTime},
		{ "gps", func_gpsLocation},
		{ "dir" , func_dir },
		{ "fmt" , func_fmt }
};

uint8_t funcTable( char* token )
{
	for( functionsList* pCase = cases; pCase != cases + sizeof( cases ) / sizeof( cases[0] ); pCase++ )
	{
		if( 0 == strcmp( pCase->string, token ) )
		{
			(*pCase->func)();
			return 1;
			break;
		}
	}
	return 0;
}
