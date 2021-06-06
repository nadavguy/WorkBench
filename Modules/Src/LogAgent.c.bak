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

void logData(char *dataToLog, bool doNotShowOnDisplay, bool displayOnly, bool doNotDisplayTime)
{
    char localString[1024] = "";
    if ( (strcmp(dataToLog,"") != 0) && (!doNotDisplayTime) )
    {
        sprintf(localString, "%s, %s\r\n", CT(), dataToLog);
    }
    else if ( (strcmp(dataToLog,"") != 0) && (doNotDisplayTime) )
    {
        sprintf(localString, "%s\r\n", dataToLog);
    }
    else
    {
        sprintf(localString, "\r\n");
    }
    //TODO: disable sessionUnlocked and replace with debugLevel
    if (displayOnly)
    {
        CDC_Transmit_FS((uint8_t*)localString, strlen(localString));
    }
    else if (!displayOnly || !doNotShowOnDisplay)
    {
    	f_write(&USERFile, localString, strlen(localString), &BytesWritten);
    	if (!doNotShowOnDisplay)
    	{
    		CDC_Transmit_FS((uint8_t*)localString, strlen(localString));
    	}
    }
}

bool createNewLogFile(void)
{
    bool localret = false;
    char localIndex[6] = "";
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
    	localIndex[5] = '\0';
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

    writeLogHeaders();

    return localret;
}

uint32_t getCurrentLogSize(void)
{
    FILINFO fno1;
    DIR dp1;
    f_opendir(&dp1, "\\");
    f_findfirst(&dp1, &fno1, "\\", "LOG_*");
    while( (f_findnext(&dp1, &fno1) == FR_OK) && (fno1.fname[0] != 0x00) )
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
		f_sync(&USERFile);
		if (getCurrentLogSize() > MAX_LOG_SIZE)
		{
			sprintf(terminalBuffer, "%s, Closing current log file\r\n", CT());
			logData(terminalBuffer, false, false, false);
			f_close(&USERFile);
			createNewLogFile();
		}
		lastFileSizeCheck = HAL_GetTick();
	}
}

void logRCLinkStatus(bool forceLog)
{
	if ( (HAL_GetTick() - lastLoggedLinkMessage > 5000) || (forceLog) )
	{
//		sprintf(terminalBuffer,"Uplink RSSI1: %d, RSSI2: %d, LQ: %d, SNR: %d",
//				rcLinkStatus.UplinkRSSIAnt1, rcLinkStatus.UplinkRSSIAnt2, rcLinkStatus.UplinkPSRLQ,
//				rcLinkStatus.UplinkSNR);
//		logData(terminalBuffer, true, false, false);
//		sprintf(terminalBuffer,"Uplink Diversity: %d, RFMode: %d, TX: %d",
//				rcLinkStatus.DiversityActiveAntena, rcLinkStatus.RFMode,
//				rcLinkStatus.UplinkTXPower);
//		logData(terminalBuffer, true, false, false);
//		sprintf(terminalBuffer,"Downlink RSSI: %d, LQ: %d, SNR: %d",
//				rcLinkStatus.DownlinkRSSI, rcLinkStatus.DownlinkPSRLQ,
//				rcLinkStatus.DownlinkSNR);
//		logData(terminalBuffer, true, false, false);

		sprintf(terminalBuffer,"LNK, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
				rcLinkStatus.UplinkRSSIAnt1, rcLinkStatus.UplinkRSSIAnt2, rcLinkStatus.UplinkPSRLQ, rcLinkStatus.UplinkSNR,
				rcLinkStatus.DiversityActiveAntena, rcLinkStatus.RFMode, rcLinkStatus.UplinkTXPower, rcLinkStatus.DownlinkRSSI,
				rcLinkStatus.DownlinkPSRLQ, rcLinkStatus.DownlinkSNR);
		logData(terminalBuffer, true, false, false);
		lastLoggedLinkMessage = HAL_GetTick();
	}
}

void writeLogHeaders(void)
{
	sprintf(terminalBuffer,"LNK, UL-RSSI1, UL-RSSI2, UL-PSRLQ, UL-SNR, DA-Ant, RFMode, UL-TxPWR, DL-RSSI, DL-PSRLQ, DL_SNR");
	logData(terminalBuffer, true, false, false);
	sprintf(terminalBuffer,"SMA, State, TriggerMode, Battery[V], Altitude[m], Acceleration[m/Sec^2]");
	logData(terminalBuffer, true, false, false);
}

void deleteLogs(void)
{
	FILINFO fno1;
	DIR dp1;
	FATFS *getFreeFs;
	DWORD free_clusters, free_sectors, total_sectors;

	FS_ret = f_getfree("\\", &free_clusters, &getFreeFs);
	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	free_sectors = free_clusters * getFreeFs->csize;
	free_kb = (float)free_sectors*(float)(SECTOR_SIZE)/1048576;
	total_kb = (float)total_sectors*(float)(SECTOR_SIZE)/1048576;

	f_opendir(&dp1, "\\");
	f_findfirst(&dp1, &fno1, "\\", "LOG_*");

	while( (fno1.fname[0] != 0) && (free_kb <= 10) )
	{
		sprintf(terminalBuffer,"Deleted log: %s",fno1.fname);
		logData(terminalBuffer, false, false, false);
		FS_ret = f_unlink(&fno1.fname[0]);
		f_findnext(&dp1, &fno1);
		FS_ret = f_getfree("\\", &free_clusters, &getFreeFs);
		total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
		free_sectors = free_clusters * getFreeFs->csize;
		free_kb = (float)free_sectors*(float)(SECTOR_SIZE)/1048576;
	}
	f_closedir(&dp1);
	logData("EOD", false, true, true);
}
