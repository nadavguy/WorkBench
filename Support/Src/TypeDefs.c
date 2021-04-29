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

