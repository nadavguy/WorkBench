/*
 * LogAgent.h
 *
 *  Created on: Mar 24, 2021
 *      Author: gilad
 */

#ifndef INC_LOGAGENT_H_
#define INC_LOGAGENT_H_

#include "main.h"

#define MAX_LOG_SIZE (100000)
#define MAX_LOG_ID 	 (99999)

extern char logsIndexFile[35];
extern char currentLogFilename[64];
extern char FileReadBuffer[1024];

extern bool sessionUnlocked;
extern uint32_t previousLogIndex;
extern uint32_t lastFileSizeCheck;

extern bool createNewLogFile(void);
extern void logData(char *dataToLog, bool doNotShowOnDisplay, bool displayOnly, bool doNotDisplayTime);
extern uint32_t getCurrentLogSize(void);
extern void monitorLogSize(void);
extern void logRCLinkStatus(bool forceLog);
extern void writeLogHeaders(void);
extern void deleteLogs(void);


#endif /* INC_LOGAGENT_H_ */
