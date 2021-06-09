/*
 * EEPROMAgent.c
 *
 *  Created on: Jun 9, 2021
 *      Author: root
 */
#include "main.h"
#include "stm32f7xx_hal.h"
uint32_t BankNumber = 0;
FLASH_EraseInitTypeDef EraseInitStruct;
tFlashParams localFlashParams;
uint32_t FirstSector = 0, NbOfSectors = 0;
uint32_t Address = 0, SECTORError = 0;
FLASH_OBProgramInitTypeDef    OBInit;

uint32_t GetSector(uint32_t Address)
{
	uint32_t sector = 0;

	if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
	{
		sector = FLASH_SECTOR_0;
	}
	else if ((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
	{
		sector = FLASH_SECTOR_1;
	}
	else if ((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
	{
		sector = FLASH_SECTOR_2;
	}
	else if ((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
	{
		sector = FLASH_SECTOR_3;
	}
	else if ((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
	{
		sector = FLASH_SECTOR_4;
	}
	else if ((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
	{
		sector = FLASH_SECTOR_5;
	}
	else if ((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
	{
		sector = FLASH_SECTOR_6;
	}
	else if ((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
	{
		sector = FLASH_SECTOR_7;
	}
	else if ((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
	{
		sector = FLASH_SECTOR_8;
	}
	else if ((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
	{
		sector = FLASH_SECTOR_9;
	}
	else if ((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
	{
		sector = FLASH_SECTOR_10;
	}
#if defined(DUAL_BANK)
	else if ((Address < ADDR_FLASH_SECTOR_12) && (Address >= ADDR_FLASH_SECTOR_11))
	{
		sector = FLASH_SECTOR_11;
	}
	else if ((Address < ADDR_FLASH_SECTOR_13) && (Address >= ADDR_FLASH_SECTOR_12))
	{
		sector = FLASH_SECTOR_12;
	}
	else if ((Address < ADDR_FLASH_SECTOR_14) && (Address >= ADDR_FLASH_SECTOR_13))
	{
		sector = FLASH_SECTOR_13;
	}
	else if ((Address < ADDR_FLASH_SECTOR_15) && (Address >= ADDR_FLASH_SECTOR_14))
	{
		sector = FLASH_SECTOR_14;
	}
	else if ((Address < ADDR_FLASH_SECTOR_16) && (Address >= ADDR_FLASH_SECTOR_15))
	{
		sector = FLASH_SECTOR_15;
	}
	else if ((Address < ADDR_FLASH_SECTOR_17) && (Address >= ADDR_FLASH_SECTOR_16))
	{
		sector = FLASH_SECTOR_16;
	}
	else if ((Address < ADDR_FLASH_SECTOR_18) && (Address >= ADDR_FLASH_SECTOR_17))
	{
		sector = FLASH_SECTOR_17;
	}
	else if ((Address < ADDR_FLASH_SECTOR_19) && (Address >= ADDR_FLASH_SECTOR_18))
	{
		sector = FLASH_SECTOR_18;
	}
	else if ((Address < ADDR_FLASH_SECTOR_20) && (Address >= ADDR_FLASH_SECTOR_19))
	{
		sector = FLASH_SECTOR_19;
	}
	else if ((Address < ADDR_FLASH_SECTOR_21) && (Address >= ADDR_FLASH_SECTOR_20))
	{
		sector = FLASH_SECTOR_20;
	}
	else if ((Address < ADDR_FLASH_SECTOR_22) && (Address >= ADDR_FLASH_SECTOR_21))
	{
		sector = FLASH_SECTOR_21;
	}
	else if ((Address < ADDR_FLASH_SECTOR_23) && (Address >= ADDR_FLASH_SECTOR_22))
	{
		sector = FLASH_SECTOR_22;
	}
	else /* (Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_23) */
	{
		sector = FLASH_SECTOR_23;
	}
#else
	else /* (Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11) */
	{
		sector = FLASH_SECTOR_11;
	}
#endif /* DUAL_BANK */
	return sector;
}

void prepFlash()
{
//	HAL_FLASH_Unlock();
//
//	/* Clear OPTVERR bit set on virgin samples */
//	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR|
//			FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_ERSERR);
////	__HAL_FLASH_CLEAR_FLAG()
//
//
//	/* Fill EraseInit structure*/
//	EraseInitStruct.Banks = FLASH_BANK_BOTH;
//	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
//	EraseInitStruct.Sector = localFlashParams.pageOrSector;
//	EraseInitStruct.NbSectors =  1;
//	EraseInitStruct.VoltageRange = localFlashParams.voltageLevel;
////	FLASH_Erase_Sector(localFlashParams.pageOrSector, localFlashParams.voltageLevel);
//
//	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
//	{
//		/*
//	        Error occurred while mass erase.
//	        User can add here some code to deal with this error.
//	        To know the code error, user can call function 'HAL_FLASH_GetError()'
//		 */
//		/* Infinite loop */
//		while (1)
//		{
//			/* Make LED2 blink (100ms on, 2s off) to indicate error in Erase operation */
//			//        BSP_LED_On(LED2);
//			//        HAL_Delay(100);
//			//        BSP_LED_Off(LED2);
//			HAL_Delay(2000);
//		}
//	}
//	CLEAR_BIT (FLASH->CR, (FLASH_CR_SER));
//	CLEAR_BIT (FLASH->CR, (FLASH_CR_LOCK));


	if (localFlashParams.addDelayBeforeFlashOps)
	{
		HAL_Delay(2000);
	}
	HAL_FLASH_Unlock();
	/* Allow Access to option bytes sector */
	HAL_FLASH_OB_Unlock();
	/* Get the Dual bank configuration status */
	HAL_FLASHEx_OBGetConfig(&OBInit);

	FirstSector = GetSector(localFlashParams.startAddress);
	/* Get the number of sector to erase from 1st sector*/
	NbOfSectors = 4;//GetSector(FLASH_USER_END_ADDR) - FirstSector + 1;
	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange  = localFlashParams.voltageLevel;
	EraseInitStruct.Sector        = FirstSector;
	EraseInitStruct.NbSectors     = NbOfSectors;

	/* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	       you have to make sure that these data are rewritten before they are accessed during code
	       execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	       DCRST and ICRST bits in the FLASH_CR register. */
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	{
		/*
	        Error occurred while sector erase.
	        User can add here some code to deal with this error.
	        SECTORError will contain the faulty sector and then to know the code error on this sector,
	        user can call function 'HAL_FLASH_GetError()'

		 */
		HAL_FLASH_GetError();
		/* Infinite loop */
		while (1)
		{
			//			BSP_LED_On(LED3);
		}
	}
	CLEAR_BIT (FLASH->CR, (FLASH_CR_PSIZE));

}
uint32_t writeData(uint32_t startAddress, uint32_t* data, uint32_t data_length)
{
	uint32_t n;
	HAL_FLASH_Unlock();
//	prepFlash();
	while (__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) != RESET)
	{
		HAL_Delay(20);
	}

	for (n = 0; (n < data_length/4); n++)
	{
		//     if (FLASH_ProgramWord(addr, *data) == FLASH_COMPLETE)
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, startAddress, *(uint32_t *)data) == HAL_OK)
		{
			if (*(uint32_t*)startAddress != *data++)
			{
				return (2);
			}
			startAddress += 4;
		}
		else
		{
			uint32_t er = HAL_FLASH_GetError();
			return (1);
		}
	}
//	CLEAR_BIT (FLASH->CR, (FLASH_CR_PG));
	return (0);
}

tEE_DATA readData(uint32_t startAddress)
{
	tEE_DATA localEE;
	uint32_t localeeptr = &localEE;

	for(int i = 0; i< sizeof(localEE)/4;i++)
	{
		*(uint32_t *)localeeptr = *(uint32_t *)startAddress;
		localeeptr = localeeptr + 4;
		startAddress = startAddress + 4;
	}
	return localEE;
}

void reallocateData(uint32_t oldAddress, uint32_t newAddress)
{
	tEE_DATA localEE = readData(oldAddress);
	prepFlash();
	setFlashParams(localFlashParams.addDelayBeforeFlashOps, newAddress, localFlashParams.voltageLevel);
	prepFlash();
	uint32_t* data = &localEE;
	writeData(newAddress,data,sizeof(localEE));
}

void setFlashParams(bool addDelay,uint32_t startaddress, uint32_t voltageLevel)
{
	localFlashParams.addDelayBeforeFlashOps = addDelay;
	localFlashParams.startAddress = startaddress;
	localFlashParams.voltageLevel = voltageLevel;
}
