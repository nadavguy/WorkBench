/*
 * Common.c
 *
 *  Created on: Mar 23, 2021
 *      Author: nadav
 */

#include <stdint.h>
#include <math.h>
#include "Common.h"

pFunction JumpToApplication;

uint8_t aFileName[FILE_NAME_LENGTH];
uint8_t key[256] = { 0x30, 0xAB, 0xC2, 0x12, 0x09, 0xCE, 0x56, 0x9A, 0xF8, 0x81, 0xD4, 0xA9
        , 0x05, 0x67, 0x5E, 0x6F, 0x79, 0x3F, 0x96, 0xC9, 0x11, 0x2F, 0x37, 0x1C, 0x60, 0xE3, 0x04, 0x7E
        , 0xB6, 0x93, 0x70, 0xEF, 0x4A, 0x45, 0x02, 0x6A, 0x97, 0x12, 0x27, 0x42, 0xEC, 0x51, 0x55, 0x70
        , 0x00, 0xCB, 0xA8, 0x61, 0x22, 0xE1, 0xF1, 0x78, 0x53, 0x18, 0xF8, 0xDA, 0xC9, 0x40, 0x08, 0x5D
        , 0x3F, 0x96, 0x09, 0xC5, 0x9B, 0x08, 0x34, 0xBD, 0x9C, 0xFA, 0x9F, 0x1D, 0x5F, 0x61, 0x77, 0xA0
        , 0x16, 0xC5, 0xB1, 0x76, 0x00, 0xF7, 0x97, 0x9A, 0x04, 0x09, 0x95, 0x8C, 0x44, 0x5A, 0xF3, 0x1E
        , 0xCE, 0x96, 0x24, 0xF7, 0xE1, 0x2B, 0x20, 0x5A, 0x67, 0x89, 0xEa, 0x6C, 0xBA, 0x73, 0x0B, 0x19
        , 0xE6, 0xA3, 0xCD, 0xFC, 0xA1, 0xAD, 0x7E, 0x65, 0x67, 0x0C, 0x9B, 0x48, 0x5E, 0x6A, 0x53, 0xBD
        , 0xBB, 0x22, 0xBC, 0x85, 0x17, 0x85, 0x2A, 0x07, 0x9A, 0xC0, 0x18, 0xB6, 0xEF, 0x90, 0x3C, 0x0E
        , 0x8E, 0x19, 0x5E, 0xA1, 0xE0, 0x06, 0x18, 0xD0, 0x56, 0x36, 0x30, 0xA0, 0xA8, 0x60, 0x77, 0x31
        , 0x4C, 0xDA, 0x3B, 0x5E, 0x75, 0x9C, 0xD5, 0xB6, 0x97, 0x59, 0x56, 0x47, 0xF8, 0xEB, 0x40, 0xF9
        , 0x99, 0x2F, 0xFB, 0xFA, 0xFE, 0x88, 0xF3, 0x49, 0xD2, 0xC7, 0xD6, 0x54, 0x6A, 0xBB, 0x02, 0x52
        , 0xCB, 0xC1, 0xCA, 0xA1, 0x23, 0x6D, 0x7F, 0xC9, 0x4F, 0x6B, 0xDE, 0x2E, 0xF3, 0xB5, 0x4A, 0x30
        , 0x46, 0xE5, 0x08, 0xB9, 0xCD, 0x1F, 0x07, 0x12, 0x89, 0x04, 0xD3, 0x03, 0x72, 0x96, 0x50, 0x0D
        , 0xF3, 0xB9, 0xB1, 0xD6, 0xAE, 0xF9, 0xB4, 0x3A, 0x95, 0x78, 0xCE, 0x7D, 0xA4, 0xA0, 0x55, 0x4C
        , 0xDF, 0xC2, 0x5C, 0x5A, 0x79, 0x91, 0xD8, 0x4D, 0xC8, 0x62, 0x8E, 0x8D, 0xA0, 0xED, 0xF0, 0xE6
        , 0xED, 0x59, 0x63, 0xE2};
HAL_StatusTypeDef FLASHStatus;

FLASH_EraseInitTypeDef EraseInitStruct;

uint32_t PAGEError = 0;
uint32_t JumpAddress;
uint32_t FlashProtection = 0;


int8_t sgn(int32_t sourceValue)
{
	return sourceValue > 0 ? 1 : (sourceValue < 0 ? -1 : 0);
}

int32_t limitInt32(int32_t minValue, int32_t value, int32_t maxValue)
{
	if (value < minValue)
	{
		return minValue;
	}
	else if (value > maxValue)
	{
		return maxValue;
	}
	return value;
}
uint32_t limitUInt32(uint32_t minValue, uint32_t value, uint32_t maxValue)
{
	if (value < minValue)
	{
		return minValue;
	}
	else if (value > maxValue)
	{
		return maxValue;
	}
	return value;
}

/**
  * @brief  Convert an Integer to a string
  * @param  p_str: The string output pointer
  * @param  intnum: The integer to be converted
  * @retval None
  */
void Int2Str(uint8_t *p_str, uint32_t intnum)
{
  uint32_t i, divider = 1000000000, pos = 0, status = 0;

  for (i = 0; i < 10; i++)
  {
    p_str[pos++] = (intnum / divider) + 48;

    intnum = intnum % divider;
    divider /= 10;
    if ((p_str[pos-1] == '0') & (status == 0))
    {
      pos = 0;
    }
    else
    {
      status++;
    }
  }
}

/**
  * @brief  Convert a string to an integer
  * @param  p_inputstr: The string to be converted
  * @param  p_intnum: The integer value
  * @retval 1: Correct
  *         0: Error
  */
uint32_t Str2Int(uint8_t *p_inputstr, uint32_t *p_intnum)
{
  uint32_t i = 0, res = 0;
  uint32_t val = 0;

  if ((p_inputstr[0] == '0') && ((p_inputstr[1] == 'x') || (p_inputstr[1] == 'X')))
  {
    i = 2;
    while ( ( i < 11 ) && ( p_inputstr[i] != '\0' ) )
    {
      if (ISVALIDHEX(p_inputstr[i]))
      {
        val = (val << 4) + CONVERTHEX(p_inputstr[i]);
      }
      else
      {
        /* Return 0, Invalid input */
        res = 0;
        break;
      }
      i++;
    }

    /* valid result */
    if (p_inputstr[i] == '\0')
    {
      *p_intnum = val;
      res = 1;
    }
  }
  else /* max 10-digit decimal input */
  {
    while ( ( i < 11 ) && ( res != 1 ) )
    {
      if (p_inputstr[i] == '\0')
      {
        *p_intnum = val;
        /* return 1 */
        res = 1;
      }
      else if (((p_inputstr[i] == 'k') || (p_inputstr[i] == 'K')) && (i > 0))
      {
        val = val << 10;
        *p_intnum = val;
        res = 1;
      }
      else if (((p_inputstr[i] == 'm') || (p_inputstr[i] == 'M')) && (i > 0))
      {
        val = val << 20;
        *p_intnum = val;
        res = 1;
      }
      else if (ISVALIDDEC(p_inputstr[i]))
      {
        val = val * 10 + CONVERTDEC(p_inputstr[i]);
      }
      else
      {
        /* return 0, Invalid input */
        res = 0;
        break;
      }
      i++;
    }
  }

  return res;
}

/**
  * @brief  Print a string on the HyperTerminal
  * @param  p_string: The string to be printed
  * @retval None
  */
void Serial_PutString_(uint8_t *p_string)
{
  uint16_t length = 0;

  while (p_string[length] != '\0')
  {
    length++;
  }
//  CDC_Transmit_FS((uint8_t*)p_string, strlen(p_string));
//  HAL_UART_Transmit(&huart1, p_string, length, TX_TIMEOUT);
}

/**
  * @brief  Transmit a byte to the HyperTerminal
  * @param  param The byte to be sent
  * @retval HAL_StatusTypeDef HAL_OK if OK
  */

HAL_StatusTypeDef Serial_PutByte( uint8_t param )
{
  /* May be timeouted... */
//  if ( huart1.gState == HAL_UART_STATE_TIMEOUT )
//  {
//	  huart1.gState = HAL_UART_STATE_READY;
//  }
//  return CDC_Transmit_FS(param, 1);//HAL_UART_Transmit(&huart1, &param, 1, TX_TIMEOUT);
	return HAL_OK;
}

void Serial_PutString6(uint8_t *p_string)
{
//  uint16_t length = 0;

//  while (p_string[length] != '\0')
//  {
//    length++;
//  }
//  HAL_UART_Transmit(&huart_t, p_string, length, TX_TIMEOUT);
}

/**
  * @brief  Transmit a byte to the HyperTerminal
  * @param  param The byte to be sent
  * @retval HAL_StatusTypeDef HAL_OK if OK
  */
HAL_StatusTypeDef Serial_PutByte6( uint8_t param )
{
  /* May be timeouted... */
//  if ( UartHandle.gState == HAL_UART_STATE_TIMEOUT )
//  {
//    UartHandle.gState = HAL_UART_STATE_READY;
//  }
//  return HAL_UART_Transmit(&huart_t, &param, 1, TX_TIMEOUT);
	return HAL_OK;
}


unsigned char lrotate(unsigned char val, int n)
{
	unsigned int t,i;
	t = val;
	for(i = 0; i < n; i++)
	{
		t = t <<1;
		if ((t&256))
		{
			t = t | 1;
		}
	}
	return t;
}

unsigned char rrotate(unsigned char val, int n)
{
	unsigned int t,i;
	t = val;
	t =  t <<8;
	for(i = 0; i<n;i++)
	{
		t = t >>1;
		if ((t&128))
		{
			t = t | 32768;
		}
	}
	t =  t >>8;
	return t;
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
uint32_t SerialDownload(bool move)
{
  uint32_t size = 0;
  static uint32_t ck;
  uint32_t B4;
  uint8_t *B4_Addr;
  uint32_t FlashDestination1, FlashDestination2;

  COM_StatusTypeDef result;

  result = Ymodem_Receive( &size );
  if (result == COM_OK)
  {
//	  Buzzer_Set_Mode(1);
    if (move)
    {

//     FLASH_If_Erase(APPLICATION_ADDRESS,size);
     HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);

     FlashDestination1 = APPLICATION_ADDRESS;
     FlashDestination2 = DOWNLOAD_ADDRESS;

     for (int j = 0;j < size;j += 4)
      {  //     SECONDS = 0;
              B4_Addr = (uint8_t*)&B4;
              B4 = *(uint32_t*)FlashDestination2;
              B4_Addr[0] = rrotate((rrotate(B4_Addr[0],5)^key[ck]),3); ck++; if (ck>255) ck = 0;
              B4_Addr[1] = rrotate((rrotate(B4_Addr[1],5)^key[ck]),3); ck++; if (ck>255) ck = 0;
              B4_Addr[2] = rrotate((rrotate(B4_Addr[2],5)^key[ck]),3); ck++; if (ck>255) ck = 0;
              B4_Addr[3] = rrotate((rrotate(B4_Addr[3],5)^key[ck]),3); ck++; if (ck>255) ck = 0;
              FLASHStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FlashDestination1, B4);
              if (FLASHStatus!=HAL_OK)
                {
//            	  sprintf(term_buffer,"Error: Image move %lu %d\n\r",size,j);
//                   PRINT();
                   return 0;
                }
              if (*(uint32_t*)FlashDestination1 != B4)
                {
//            	  sprintf(term_buffer,"Error: Image check move %lu %d\n\r",size,j);
//                  PRINT();
//                  sprintf(term_buffer,"\r\n%s|Error moving to AppAddr. Name: %s Size: %d bytes",CT(),aFileName,size); PRINT();
//                  return;
                }
              FlashDestination1 += 4; FlashDestination2 += 4;
      }
//      sprintf(term_buffer,"\r\n%s|SmartAir FW programming completed Successfully. Name: %s Size: %d bytes",CT(),aFileName,size); PRINT();
    }
    else
    {
//    	sprintf(term_buffer,"\r\n%s|SenseAir file loading completed Successfully. Name: %s Size: %d bytes",CT(),aFileName,size); PRINT();
    }

  }
  else if (result == COM_LIMIT)
  {
	  size = 0;
//    sprintf(term_buffer,"\r\n%s|Error. The image size is higher than the allowed space memory!",CT()); PRINT();
//    Buzzer_Set_Mode(6);
  }
  else if (result == COM_DATA)
  {
	  size = 0;
//    sprintf(term_buffer,"\r\n%s|Error. Verification failed. Try again.",CT()); PRINT();
//    Buzzer_Set_Mode(6);
  }
  else if (result == COM_ABORT)
  {
	  size = 0;
//    sprintf(term_buffer,"\r\n%s|Error. Try again command.",CT()); PRINT();
//    ci_reset();
//    Buzzer_Set_Mode(6);
  }
  else
  {
	  size = 0;
//    sprintf(term_buffer,"\r\n%s|Error. Failed to receive the file.",CT()); PRINT();
//    ci_reset();
//    Buzzer_Set_Mode(6);
  }
  return size;
}


/**
  * @}
  */
