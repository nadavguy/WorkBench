/*
 * LogAgent.c
 *
 *  Created on: Mar 24, 2021
 *      Author: gilad
 */

#include "main.h"
#include "LogAgent.h"
#include "FlashQSPIAgent.h"
#include "usbd_cdc_if.h"
#include "fatfs.h"

bool sessionUnlocked = true;
uint32_t previousLogIndex = 0;
uint32_t lastFileSizeCheck = 0;

char currentLogFilename[64] = "";
char FileReadBuffer[1024] = "";

void logData(char *dataToLog, bool forceToDisplay, bool displayOnly)
{
    char localString[1024] = "";
    if (strcmp(dataToLog,"") != 0)
    {
        sprintf(localString, "%s, %s\r\n", CT(), dataToLog);
    }
    else
    {
        sprintf(localString, "\r\n");
    }
    //TODO: disable sessionUnlocked and replace with debugLevel
    if (forceToDisplay || displayOnly)
    {
        CDC_Transmit_FS((uint8_t*)localString, strlen(localString));
    }
    if (!displayOnly)
    {
    	f_write(&USERFile, localString, strlen(localString), &BytesWritten);
    }
    uint32_t logFileSize = 0;  // ftell(logFileHandler);
    if (logFileSize > MAX_LOG_SIZE )
    {
//        sprintf(localString, "%s, Closing current log file\r\n", CT());
//        fwrite(localString, strlen(localString) + 1, 1, logFileHandler);
//        fflush(logFileHandler);
//        fclose(logFileHandler);
//
//        //TODO: rename previous file name to have start and end time
//        if (!createNewLogFile())
//        {
//            printf("Log file creation failed\n");
//        }
    }
}

bool createNewLogFile(void)
{
    bool localret = false;
    char localIndex[5] = "";
	unsigned int br = 0;

    FS_ret = f_open(&USERFile, "Index.txt", FA_READ);
    FS_ret = f_read(&USERFile, &FileReadBuffer, sizeof(FileReadBuffer), &br);

	if (FS_ret != FR_OK)
	{
		do
		{
			HAL_Delay(1);
			FS_ret = f_open(&USERFile, "Index.txt", FA_OPEN_APPEND | FA_WRITE);
		} while ( (FS_ret != FR_OK) );

		FS_ret = f_write(&USERFile, "00000\t", strlen("00000\t"), &BytesWritten);
		FS_ret = f_close(&USERFile);
	}

    if (br == 6)
    {
    	memcpy(localIndex, FileReadBuffer, 5);
    	previousLogIndex = atoi(localIndex);
    }
    else
    {
    	//TODO: what if br is not 6
    	// recreate index, etc.
    }
    FS_ret = f_close(&USERFile);
    FS_ret = f_open(&USERFile, "Index.txt", FA_OPEN_EXISTING | FA_WRITE);
    char tempString[15] = "";
    if (previousLogIndex + 1 < MAX_LOG_ID)
    {

    }
    else
    {
    	previousLogIndex = 0;
    }
    sprintf(tempString,"%05ld\t",previousLogIndex+1);
    FS_ret = f_write(&USERFile, tempString, strlen(tempString), &BytesWritten);
    FS_ret = f_close(&USERFile);

    sprintf(currentLogFilename,"LOG_%05ld.CSV", previousLogIndex+1);
    FS_ret = f_open(&USERFile, currentLogFilename, FA_CREATE_ALWAYS | FA_WRITE);

    return localret;
}

uint32_t getCurrentLogSize(void)
{
    FILINFO fno1;
    DIR dp1;
    f_opendir(&dp1, "\\");
    f_findfirst(&dp1, &fno1, "\\", "LOG_*");
    while( f_findnext(&dp1, &fno1) == FR_OK)
    {
    	f_stat("\\", &fno1);
    	if(strcmp(currentLogFilename, fno1.fname) == 0)
    	{
    		return fno1.fsize;
    	}
    }
    f_closedir(&dp1);
    return 0;
}

void monitorLogSize(void)
{
	if (HAL_GetTick() - lastFileSizeCheck > 10000)
	{
		if (getCurrentLogSize() > MAX_LOG_SIZE)
		{
			sprintf(terminalBuffer, "%s, Closing current log file\r\n", CT());
			logData(terminalBuffer, false, false);
			f_close(&USERFile);
			createNewLogFile();
		}
		lastFileSizeCheck = HAL_GetTick();
	}
}
