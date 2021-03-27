/*
 * LogAgent.h
 *
 *  Created on: Mar 24, 2021
 *      Author: gilad
 */

#ifndef INC_LOGAGENT_H_
#define INC_LOGAGENT_H_


#define MAX_LOG_SIZE (100000)
extern int previousLogIndex;

extern char logsIndexFile[35];
extern char currentLogFilename[64];

extern bool sessionUnlocked;

//extern bool initFile(char *newFile);
//extern bool initFileWithData(char *newFile, char *dataToWrite);
//extern bool createNewLogFile(void);
//extern FILE *openFile(char *fileToOpen);
extern void logData(char *dataToLog, bool forceToDisplay, bool displayOnly);
//extern void writeLogHeader(void);


#endif /* INC_LOGAGENT_H_ */
