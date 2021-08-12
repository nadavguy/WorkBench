/*
 * EEPROMAgent.c
 *
 *  Created on: Jun 9, 2021
 *      Author: root
 */
#include "main.h"
#include "stm32f7xx_hal.h"
#include "usb_device.h"
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

void prepFlash(uint8_t numberOfSectors)
{
	if (localFlashParams.addDelayBeforeFlashOps)
	{
		HAL_Delay(2000);
	}
	// // changeROP(0);
	HAL_FLASH_Unlock();
	/* Allow Access to option bytes sector */
	HAL_FLASH_OB_Unlock();
	/* Get the Dual bank configuration status */
	HAL_FLASHEx_OBGetConfig(&OBInit);

	FirstSector = GetSector(localFlashParams.startAddress);
	/* Get the number of sector to erase from 1st sector*/
	NbOfSectors = numberOfSectors;//GetSector(FLASH_USER_END_ADDR) - FirstSector + 1;
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
			return (1);
		}
	}
	return (0);
}

//tEE_DATA readData(uint32_t startAddress)
//{
//	tEE_DATA localEE;
//	uint32_t localeeptr = &localEE;
//
//	for(int i = 0; i< sizeof(localEE)/4;i++)
//	{
//		*(uint32_t *)localeeptr = *(uint32_t *)startAddress;
//		localeeptr = localeeptr + 4;
//		startAddress = startAddress + 4;
//	}
//	return localEE;
//}

void reallocateData(uint32_t oldAddress, uint32_t newAddress, uint32_t totalNumberOfBytesToAllocate)
{
	uint8_t localArray[1024] = {0xFF};
	uint16_t localMaxNumberOfArrays = totalNumberOfBytesToAllocate / 1024;
	localFlashParams.startAddress = newAddress;
	prepFlash(4);
	for (int i = 0 ; i < localMaxNumberOfArrays ; i++)
	{
		memcpy(localArray, (uint32_t *)(oldAddress + 1024*i), 1024);
		writeData(newAddress + 1024*i, (uint32_t *)localArray, 1024);
//		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, newAddress + 1024*i, *(uint32_t *)localArray);
		memset(localArray, 0xFF, 1024);
	}
	uint32_t reminderOfData = totalBytesLengthInFile - 1024 * localMaxNumberOfArrays;
	memcpy(localArray, (uint32_t *)(oldAddress + 1024*localMaxNumberOfArrays), reminderOfData);
//	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, newAddress + 1024*localMaxNumberOfArrays, *(uint32_t *)localArray);
	writeData(newAddress + 1024*localMaxNumberOfArrays, (uint32_t *)localArray, reminderOfData);
	localFlashParams.startAddress = oldAddress;
	prepFlash(1);
}

void setFlashParams(bool addDelay,uint32_t startaddress, uint32_t voltageLevel)
{
	localFlashParams.addDelayBeforeFlashOps = addDelay;
	localFlashParams.startAddress = startaddress;
	localFlashParams.voltageLevel = voltageLevel;
}

void changeROP(uint8_t ProtectionLevel)
{
	FLASH_OBProgramInitTypeDef OB_Init;
	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();
	OB_Init.OptionType = OPTIONBYTE_RDP;
	if (ProtectionLevel == 0)
	{
		OB_Init.RDPLevel = OB_RDP_LEVEL_0;
	}
	else if (ProtectionLevel == 1)
	{

		OB_Init.RDPLevel = OB_RDP_LEVEL_1;
	}
	else if (ProtectionLevel == 2)
	{

		OB_Init.RDPLevel = OB_RDP_LEVEL_2;
	}
	else
	{
//		status = RDPLevel_Error;
//		return status;
	}
	HAL_FLASHEx_OBProgram(&OB_Init);
	HAL_FLASH_OB_Launch();
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}

crc checkCRC(uint32_t startAddress, uint32_t length)
{
 return 0;
}
