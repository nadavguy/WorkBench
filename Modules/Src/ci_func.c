#include "main.h"
#include "usart.h"
#include "ff.h"
#include "fatfs.h"
#include "FlashQSPIAgent.h"


bool isReportParametersActive = false;

eCI_RESULT func_debug(void)
{
	if (get_param_count() > 0)
	{
		ee.debugLevel = get_param_int(0);
		ee_save1();
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
	sprintf(terminalBuffer,"%s, RC Firmware version: %6.2f, BuildID: %6.2f",CT(), fwVersion, BuildID);
	logData(terminalBuffer, false, true);
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
	}
	return CI_OK;
}

eCI_RESULT func_armPWMOn(void)
{
	if (get_param_count() > 0)
	{
		ee.armPWMOnValue = get_param_int(0);
		ee_save1();
	}
	return CI_OK;
}

eCI_RESULT func_triggerPWMOff(void)
{
	if (get_param_count() > 0)
	{
		ee.triggerPWMOffValue = get_param_int(0);
		ee_save1();
	}
	return CI_OK;
}

eCI_RESULT func_triggerPWMOn(void)
{
	if (get_param_count() > 0)
	{
		ee.triggerPWMOnValue = get_param_int(0);
		ee_save1();
	}
	return CI_OK;
}

eCI_RESULT func_linkType(void)
{
	if (get_param_count() > 0)
	{
		ee.linkType = get_param_int(0);
		ee_save1();
	}
	return CI_OK;
}

eCI_RESULT func_systemConfiguration(void)
{
	printRCConfiguration(true);
	return CI_OK;
}

eCI_RESULT func_dir(void)
{
    FILINFO fno1;
    DIR dp1;
    f_opendir(&dp1, "\\");
    f_findfirst(&dp1, &fno1, "\\", "LOG_*");
    while( (f_findnext(&dp1, &fno1) == FR_OK) && (fno1.fname[0] != 0) )
    {
    	f_stat("\\", &fno1);
    	sprintf(terminalBuffer,"%s\t%ld",fno1.fname, fno1.fsize);
    	logData(terminalBuffer, false, true);
    }
    f_closedir(&dp1);
	return CI_OK;
}

eCI_RESULT func_fmt(void)
{
	sprintf(terminalBuffer, "\r\n%s!Formatting Flash...restart required!\n\r", CT());
	logData(terminalBuffer, false, false);
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
