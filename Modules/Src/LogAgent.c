/*
 * LogAgent.c
 *
 *  Created on: Mar 24, 2021
 *      Author: gilad
 */

#include "main.h"
#include "usbd_cdc_if.h"

bool sessionUnlocked = true;

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

//        fwrite(localString, strlen(localString) + 1, 1, logFileHandler);
//        fflush(logFileHandler);
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
