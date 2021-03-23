/*
 * TypeDefs.c
 *
 *  Created on: Feb 7, 2021
 *      Author: gilad
 */


#include "main.h"
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
