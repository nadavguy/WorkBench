#include "main.h"
#include "usart.h"


bool isReportParametersActive = false;

eCI_RESULT func_debug(void)
{
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

eCI_RESULT func_dir(void)
{
	return CI_OK;
}

eCI_RESULT func_fmt(void)
{
	return CI_OK;
}

typedef struct
{
    char *string;
    eCI_RESULT (*func)(void);
} functionsList;

functionsList cases [] =
{
		{ "ver ", func_versionReport },
		{ "dbg ", func_debug },
		{ "urcv", func_updateRCVersion },
		{ "end" , func_endUpdatePhase },
		{ "rst" , func_resetRC },
		{ "help", func_showAvailableCommands },
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
