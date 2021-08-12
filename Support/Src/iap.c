/*
 * iap.c
 *
 *  Created on: Mar 30, 2021
 *      Author: root
 */


#include "main.h"
#include "iap.h"
//-----------------------------------------------------------------------------

uint32_t iap_sector_index;
//-----------------------------------------------------------------------------

void iap_init(void)
{
}
//-----------------------------------------------------------------------------

void iap_prepare_flash(void)
{
	/* Clear pending flags (if any) */
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
			FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR /* | FLASH_FLAG_PGSERR*/);


	HAL_FLASH_Unlock();
}
//-----------------------------------------------------------------------------

uint32_t iap_erase_sector(uint32_t addr)
{
	uint32_t UserStartSector;
	uint32_t SectorError;
	FLASH_EraseInitTypeDef pEraseInit;

	iap_prepare_flash();
	UserStartSector = iap_get_sector(addr);
	pEraseInit.TypeErase = TYPEERASE_SECTORS;
	pEraseInit.Sector = UserStartSector;
	pEraseInit.NbSectors =  1;
	pEraseInit.VoltageRange = VOLTAGE_RANGE_3;

	if (HAL_FLASHEx_Erase(&pEraseInit, &SectorError) != HAL_OK)
	{
		return (1);
	}

	return (0);
}
//-----------------------------------------------------------------------------

uint32_t iap_write_sector(uint32_t addr, pU32 data, uint32_t data_length)
{
	uint32_t n;

	iap_prepare_flash();

	for (n = 0; (n < data_length); n++)
	{
		//     if (FLASH_ProgramWord(addr, *data) == FLASH_COMPLETE)
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, *(uint32_t*)data) == HAL_OK)
		{
			if (*(uint32_t*)addr != *data++)
			{
				return (2);
			}

			addr += 4;
		}
		else
		{
			return (1);
		}
	}

	return (0);
}
//-----------------------------------------------------------------------------

uint32_t iap_verify(pU32 buffer1, pU32 buffer2, uint32_t data_length)
{
	uint32_t n;

	for (n = 0; (n < data_length); n++)
	{
		if (*buffer1++ != *buffer2++)
		{
			return (1);
		}
	}
	return (0);
}
//-----------------------------------------------------------------------------

uint32_t iap_get_sector(uint32_t Address)
{
	uint32_t sector = 0;

	if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
	{
		sector = FLASH_SECTOR_0;
	}
	else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
	{
		sector = FLASH_SECTOR_1;
	}
	else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
	{
		sector = FLASH_SECTOR_2;
	}
	else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
	{
		sector = FLASH_SECTOR_3;
	}
	else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
	{
		sector = FLASH_SECTOR_4;
	}
	else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
	{
		sector = FLASH_SECTOR_5;
	}
	else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
	{
		sector = FLASH_SECTOR_6;
	}
	else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
	{
		sector = FLASH_SECTOR_7;
	}
	else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
	{
		sector = FLASH_SECTOR_8;
	}
	else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
	{
		sector = FLASH_SECTOR_9;
	}
	else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
	{
		sector = FLASH_SECTOR_10;
	}
	else /*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
	{
		sector = FLASH_SECTOR_11;
	}
	return sector;

}
