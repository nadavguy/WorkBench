/*
 * TypeDefs.c
 *
 *  Created on: Feb 7, 2021
 *      Author: gilad
 */


#include "main.h"
#include "TypeDefs.h"
#include "iap.h"

pU32 ee_ram_base1;
pU32 ee_ram_ptr1;
pU32 ee_flash_base1;
pU32 ee_flash_ptr1;
uint32_t ee_size1;
uint32_t ee_count1;

uint32_t startAddressEEPROM1  = 0x081C0000;

uint8_t phrase[256] = { 0x30, 0xAB, 0xC2, 0x12, 0x09, 0xCE, 0x56, 0x9A, 0xF8, 0x81, 0xD4, 0xA9
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
//-----------------------------------------------------------------------------

uint32_t ee_validate_data(eEEV_DATA_TYPE data_type, void* value_ptr, void* eev_ptr)
{
	uint32_t ee_invalid_counter = 0;

	switch (data_type)
	{
	case EEV_U08:
		if (*(pU08)value_ptr < (*(pEEV_U08)eev_ptr).min ||
				*(pU08)value_ptr > (*(pEEV_U08)eev_ptr).max)
		{
			*(pU08)value_ptr = (*(pEEV_U08)eev_ptr).std;
			ee_invalid_counter++;
		}
		break;

	case EEV_S08:
		if (*(pS08)value_ptr < (*(pEEV_S08)eev_ptr).min ||
				*(pS08)value_ptr > (*(pEEV_S08)eev_ptr).max)
		{
			*(pS08)value_ptr = (*(pEEV_S08)eev_ptr).std;
			ee_invalid_counter++;
		}
		break;

	case EEV_U16:
		if (*(pU16)value_ptr < (*(pEEV_U16)eev_ptr).min ||
				*(pU16)value_ptr > (*(pEEV_U16)eev_ptr).max)
		{
			*(pU16)value_ptr = (*(pEEV_U16)eev_ptr).std;
			ee_invalid_counter++;
		}
		break;

	case EEV_S16:
		if (*(pS16)value_ptr < (*(pEEV_S16)eev_ptr).min ||
				*(pS16)value_ptr > (*(pEEV_S16)eev_ptr).max)
		{
			*(pS16)value_ptr = (*(pEEV_S16)eev_ptr).std;
			ee_invalid_counter++;
		}
		break;

	case EEV_U32:
		if ( (*(pU32)value_ptr < (*(pEEV_U32)eev_ptr).min) || (*(pU32)value_ptr > (*(pEEV_U32)eev_ptr).max) )
		{
			*(pU32)value_ptr = (*(pEEV_U32)eev_ptr).std;
			ee_invalid_counter++;
		}
		break;

	case EEV_S32:
		if (*(pS32)value_ptr < (*(pEEV_S32)eev_ptr).min ||
				*(pS32)value_ptr > (*(pEEV_S32)eev_ptr).max)
		{
			*(pS32)value_ptr = (*(pEEV_S32)eev_ptr).std;
			ee_invalid_counter++;
		}
		break;

	case EEV_FLOAT:
		if (*(pU32)value_ptr == 0xFFFFFFFF)
		{
			*(pFLOAT)value_ptr = (*(pEEV_FLOAT)eev_ptr).std;
			ee_invalid_counter++;
		}

		if (*(pFLOAT)value_ptr < (*(pEEV_FLOAT)eev_ptr).min ||
				*(pFLOAT)value_ptr > (*(pEEV_FLOAT)eev_ptr).max)
		{
			*(pFLOAT)value_ptr = (*(pEEV_FLOAT)eev_ptr).std;
			ee_invalid_counter++;
		}
		break;
	}

	return (ee_invalid_counter);
}
//-----------------------------------------------------------------------------

static void ee_set_start1(void)
{
  ee_ram_ptr1 = ee_ram_base1;
  ee_flash_ptr1 = ee_flash_base1;
  ee_count1 = ee_size1;
}

void ee_init1(pU32 data_base1, uint32_t data_size1)
{
  ee_ram_base1 = data_base1;
  if (data_size1 % 4 == 0)
  {
	  ee_size1 = data_size1 / 4;
  }
  else
  {
	  ee_size1 = data_size1 / 4 + 1;
  }
  ee_flash_base1 = (pU32)(uint32_t)startAddressEEPROM1;
  ee_set_start1();

  while (ee_count1--)
  {
    *ee_ram_ptr1++ = *ee_flash_ptr1++;
  }
}

bool ee_save1(void)
{

  ee_set_start1();

  if (iap_erase_sector((uint32_t)ee_flash_base1) != 0)
  {
	  sprintf(terminalBuffer, "Failed to save EEPROM1");
	  logData(terminalBuffer, true, false, false);
	  return false;
  }

  if (iap_write_sector((uint32_t)ee_flash_base1, (pU32)ee_ram_ptr1, ee_size1) != 0)
  {
	  sprintf(terminalBuffer, "Failed to write EEPROM1");
	  logData(terminalBuffer, true, false, false);
	  return false;
  }

  if (iap_verify((pU32)ee_flash_base1, (pU32)ee_ram_ptr1, ee_size1) != 0)
  {
	  sprintf(terminalBuffer, "Failed to verify EEPROM1");
	  logData(terminalBuffer, true, false, false);
	  return false;
  }
  HAL_FLASH_Lock();

  return true;
}

bool ee_erase_sector1(void)
{
	ee_set_start1();

	if (iap_erase_sector((uint32_t)ee_flash_base1) != 0)
	{
		return false;
	}

	return true;
}

