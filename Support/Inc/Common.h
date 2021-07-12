/*
 * Common.h
 *
 *  Created on: Mar 23, 2021
 *      Author: nadav
 */
#include "ymodem.h"
#include "main.h"

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#define TX_TIMEOUT          ((uint32_t)100)

#define IS_CAP_LETTER(c)    (((c) >= 'A') && ((c) <= 'F'))
#define IS_LC_LETTER(c)     (((c) >= 'a') && ((c) <= 'f'))
#define IS_09(c)            (((c) >= '0') && ((c) <= '9'))
#define ISVALIDHEX(c)       (IS_CAP_LETTER(c) || IS_LC_LETTER(c) || IS_09(c))
#define ISVALIDDEC(c)       IS_09(c)
#define CONVERTDEC(c)       (c - '0')

#define CONVERTHEX_ALPHA(c) (IS_CAP_LETTER(c) ? ((c) - 'A'+10) : ((c) - 'a'+10))
#define CONVERTHEX(c)       (IS_09(c) ? ((c) - '0') : CONVERTHEX_ALPHA(c))

typedef  void (*pFunction)(void);

extern uint8_t aFileName[FILE_NAME_LENGTH];
extern uint8_t key[256];
extern HAL_StatusTypeDef FLASHStatus;

extern uint32_t JumpAddress;
extern pFunction JumpToApplication;

extern FLASH_EraseInitTypeDef EraseInitStruct;

extern uint32_t PAGEError;

extern int8_t sgn(int32_t sourceValue);

extern int32_t limitInt32(int32_t minValue, int32_t value, int32_t maxValue);

extern uint32_t limitUInt32(uint32_t minValue, uint32_t value, uint32_t maxValue);

void Int2Str(uint8_t *p_str, uint32_t intnum);
uint32_t Str2Int(uint8_t *inputstr, uint32_t *intnum);
void Serial_PutString(uint8_t *p_string);
void Serial_PutString6(uint8_t *p_string);
HAL_StatusTypeDef Serial_PutByte(uint8_t param);
HAL_StatusTypeDef Serial_PutByte6(uint8_t param);
extern uint32_t SerialDownload(bool move);
extern unsigned char lrotate(unsigned char val, int n);
extern unsigned char rrotate(unsigned char val, int n);


#endif /* INC_COMMON_H_ */
