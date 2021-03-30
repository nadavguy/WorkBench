/*
 * iap.h
 *
 *  Created on: Mar 30, 2021
 *      Author: root
 */

#ifndef INC_IAP_H_
#define INC_IAP_H_

#include "main.h"
#pragma once
//-----------------------------------------------------------------------------
//
//#define IAP_SECTOR_ADDR_0 ((U32)0x08000000)
//#define IAP_SECTOR_ADDR_1 ((U32)0x08004000)
//#define IAP_SECTOR_ADDR_2 ((U32)0x08008000)
//#define IAP_SECTOR_ADDR_3 ((U32)0x0800C000)
//#define IAP_SECTOR_ADDR_4 ((U32)0x08010000)
//#define IAP_SECTOR_ADDR_5 ((U32)0x08020000)
//#define IAP_SECTOR_ADDR_6 ((U32)0x08040000)
//#define IAP_SECTOR_ADDR_7 ((U32)0x08060000)
//#define IAP_SECTOR_ADDR_8 ((U32)0x08080000)
//#define IAP_SECTOR_ADDR_9 ((U32)0x080A0000)
//#define IAP_SECTOR_ADDR_10 ((U32)0x080C0000)
//#define IAP_SECTOR_ADDR_11 ((U32)0x080E0000)

/// stm32F777
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 32 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08008000) /* Base @ of Sector 1, 32 Kbyte */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08010000) /* Base @ of Sector 2, 32 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x08018000) /* Base @ of Sector 3, 32 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08020000) /* Base @ of Sector 4, 128 Kbyte */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08040000) /* 1 Base @ of Sector 5, 256 Kbyte */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08080000) /* 2 Base @ of Sector 6, 256 Kbyte */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x080C0000) /* 3 Base @ of Sector 7, 256 Kbyte */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08100000) /* 1 Base @ of Sector 8, 256 Kbyte */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x08140000) /* 2 Base @ of Sector 9, 256 Kbyte */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x08180000) /* 3 Base @ of Sector 10, 256 Kbyte */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x081C0000) /* Base @ of Sector 11, 256 Kbyte */
//
//
//#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
//#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
//#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
//#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
//#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
//#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
//#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
//#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
//#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
//#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
//#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
//#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

//-----------------------------------------------------------------------------

extern uint32_t iap_sector_index;
//-----------------------------------------------------------------------------

void iap_init(void);
void iap_prepare_flash(void);
uint32_t iap_erase_sector(uint32_t addr);
uint32_t iap_write_sector(uint32_t addr, pU32 data, uint32_t data_length);
uint32_t iap_verify(pU32 buffer1, pU32 buffer2, uint32_t data_length);
uint32_t iap_get_sector(uint32_t addr);


#endif /* INC_IAP_H_ */
