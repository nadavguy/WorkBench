/*
 * FlashQSPIAgent.h
 *
 *  Created on: Jul 15, 2020
 *      Author: raing
 */

#ifndef PERIPHERALS_INC_FLASHQSPIAGENT_H_
#define PERIPHERALS_INC_FLASHQSPIAGENT_H_

#include "ff.h"

extern FRESULT FS_ret;

extern unsigned int BytesWritten;

extern float free_kb;
extern float total_kb;

extern uint8_t buffer[_MAX_SS];

uint8_t QSPI_Init(void);
uint8_t QSPI_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t QSPI_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t QSPI_Erase_Sector4K(uint32_t SectorAddress);
uint8_t QSPI_WriteEnable(void);
uint8_t QSPI_AutoPollingMemReady  (QSPI_HandleTypeDef *hqspi, uint32_t Timeout);
uint8_t QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi);
uint8_t QSPI_Read_Status_registers(QSPI_HandleTypeDef *hqspi,uint16_t* R1,uint16_t* R2,uint16_t* R3);
uint8_t QSPI_Reset_Status_registers(QSPI_HandleTypeDef *hqspi,uint16_t* R1,uint16_t* R2,uint16_t* R3);
uint8_t QSPI_AutoPolling_Write_in_progress(QSPI_HandleTypeDef *hqspi, uint32_t Timeout);
uint8_t QSPI_READMD(uint8_t *Mid, uint8_t *Mim);
uint8_t QSPI_ResetFlash(void);
uint8_t QSPI_DeleteFlash(void);

extern void flashInit(void);

#define QSPI_FORCE_RESET()         __HAL_RCC_QSPI_FORCE_RESET()
#define QSPI_RELEASE_RESET()       __HAL_RCC_QSPI_RELEASE_RESET()

/* Definition for QSPI Pins */
#define QSPI_CS_PIN                GPIO_PIN_6
#define QSPI_CS_GPIO_PORT          GPIOB
#define GPIO_AF_CS                 GPIO_AF10_QUADSPI

#define QSPI_CLK_PIN               GPIO_PIN_2
#define QSPI_CLK_GPIO_PORT         GPIOB
#define GPIO_AF_CLK                GPIO_AF9_QUADSPI

//#define QSPI_D0_PIN                GPIO_PIN_11
//#define QSPI_D0_GPIO_PORT          GPIOD
//#define GPIO_AF_D0                 GPIO_AF9_QUADSPI
//
//#define QSPI_D1_PIN                GPIO_PIN_12
//#define QSPI_D1_GPIO_PORT          GPIOD
#define GPIO_AF_D1                 GPIO_AF9_QUADSPI

#define QSPI_D2_PIN                GPIO_PIN_2
#define QSPI_D2_GPIO_PORT          GPIOE
#define GPIO_AF_D2                 GPIO_AF9_QUADSPI

#define QSPI_D3_PIN                GPIO_PIN_13
#define QSPI_D3_GPIO_PORT          GPIOD
#define GPIO_AF_D3                 GPIO_AF9_QUADSPI

/* Definition for QSPI DMA */
#define QSPI_DMA_INSTANCE          DMA2_Stream7
#define QSPI_DMA_CHANNEL           DMA_CHANNEL_3
#define QSPI_DMA_IRQ               DMA2_Stream7_IRQn
#define QSPI_DMA_IRQ_HANDLER       DMA2_Stream7_IRQHandler

/* N25Q512A Micron memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE                      23
//#define QSPI_PAGE_SIZE                       256

/* End address of the QSPI memory */
#define QSPI_END_ADDR              (1 << QSPI_FLASH_SIZE)

/* Size of buffers */
#define BUFFERSIZE                 (COUNTOF(aTxBuffer) - 1)

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)        (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* MX25L51245G Macronix memory */

//#define QSPI_FLASH_SIZE                  0x4000000 /* 512 MBits => 64MBytes */
//#define QSPI_SECTOR_SIZE                 0x10000   /* 1024 sectors of 64KBytes */
//#define QSPI_SUBSECTOR_SIZE              0x1000    /* 16384 subsectors of 4kBytes */
#define QSPI_PAGE_SIZE                   0x100     /* 262144 pages of 256 bytes */

#define QSPI_DUMMY_CYCLES_READ_QUAD      3
#define QSPI_DUMMY_CYCLES_READ           8
#define QSPI_DUMMY_CYCLES_READ_QUAD_IO   10
#define QSPI_DUMMY_CYCLES_READ_DTR       6
#define QSPI_DUMMY_CYCLES_READ_QUAD_DTR  8

#define QSPI_BULK_ERASE_MAX_TIME         600000
#define QSPI_SECTOR_ERASE_MAX_TIME       2000
#define QSPI_SUBSECTOR_ERASE_MAX_TIME    800

/**
  * @brief  QSPI Commands
  */
/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

/* Identification Operations */
#define READ_ID_CMD                          0x9F
#define MULTIPLE_IO_READ_ID_CMD              0xAF
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5A

/* Read Operations */
#define READ_CMD                             0x03
#define READ_4_BYTE_ADDR_CMD                 0x13

#define FAST_READ_CMD                        0x0B
#define FAST_READ_DTR_CMD                    0x0D
#define FAST_READ_4_BYTE_ADDR_CMD            0x0C

#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_OUT_FAST_READ_4_BYTE_ADDR_CMD   0x3C

#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define DUAL_INOUT_FAST_READ_DTR_CMD         0xBD
#define DUAL_INOUT_FAST_READ_4_BYTE_ADDR_CMD 0xBC

#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_OUT_FAST_READ_4_BYTE_ADDR_CMD   0x6C

#define QUAD_INOUT_FAST_READ_CMD             0xEB
#define QUAD_INOUT_FAST_READ_DTR_CMD         0xED
#define QPI_READ_4_BYTE_ADDR_CMD             0xEC

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define READ_CFG_REG_CMD                     0x15
#define READ_STATUS_REG_CMD2                 0x35
#define WRITE_STATUS_CFG_REG_CMD             0x01

#define READ_LOCK_REG_CMD                    0x2D
#define WRITE_LOCK_REG_CMD                   0x2C

#define READ_EXT_ADDR_REG_CMD                0xC8
#define WRITE_EXT_ADDR_REG_CMD               0xC5

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define QPI_PAGE_PROG_4_BYTE_ADDR_CMD        0x12

#define QUAD_IN_FAST_PROG_CMD                0x32
#define EXT_QUAD_IN_FAST_PROG_CMD            0x38
#define QUAD_IN_FAST_PROG_4_BYTE_ADDR_CMD    0x3E

/* Erase Operations */
#define SUBSECTOR_ERASE_CMD                  0x20
#define SUBSECTOR_ERASE_4_BYTE_ADDR_CMD      0x21

#define SECTOR_ERASE_CMD                     0xD8
#define SECTOR_ERASE_4_BYTE_ADDR_CMD         0xDC

#define BULK_ERASE_CMD                       0xC7

#define BULK_ERASE_CMD 0xC7

#define PROG_ERASE_RESUME_CMD 0x30
#define PROG_ERASE_SUSPEND_CMD 0xB0

/* 4-byte Address Mode Operations */
#define ENTER_4_BYTE_ADDR_MODE_CMD           0xB7
#define EXIT_4_BYTE_ADDR_MODE_CMD            0xE9

/* Quad Operations */
#define ENTER_QUAD_CMD                       0x35
#define EXIT_QUAD_CMD                        0xF5

#define READ_DEVICE_ID                       0x90
/**
  * @brief  QSPI Registers
  */
/* Status Register */
#define QSPI_SR_WIP                      ((uint8_t)0x01)    /*!< Write in progress */
#define QSPI_SR_WREN                     ((uint8_t)0x02)    /*!< Write enable latch */
#define QSPI_SR_BLOCKPR                  ((uint8_t)0x5C)    /*!< Block protected against program and erase operations */
#define QSPI_SR_PRBOTTOM                 ((uint8_t)0x20)    /*!< Protected memory area defined by BLOCKPR starts from top or bottom */
#define QSPI_SR_QUADEN                   ((uint8_t)0x40)    /*!< Quad IO mode enabled if =1 */
#define QSPI_SR_SRWREN                   ((uint8_t)0x80)    /*!< Status register write enable/disable */

/* Configuration Register */
#define QSPI_CR_ODS                      ((uint8_t)0x07)    /*!< Output driver strength */
#define QSPI_CR_ODS_30                   ((uint8_t)0x07)    /*!< Output driver strength 30 ohms (default)*/
#define QSPI_CR_ODS_15                   ((uint8_t)0x06)    /*!< Output driver strength 15 ohms */
#define QSPI_CR_ODS_20                   ((uint8_t)0x05)    /*!< Output driver strength 20 ohms */
#define QSPI_CR_ODS_45                   ((uint8_t)0x03)    /*!< Output driver strength 45 ohms */
#define QSPI_CR_ODS_60                   ((uint8_t)0x02)    /*!< Output driver strength 60 ohms */
#define QSPI_CR_ODS_90                   ((uint8_t)0x01)    /*!< Output driver strength 90 ohms */
#define QSPI_CR_TB                       ((uint8_t)0x08)    /*!< Top/Bottom bit used to configure the block protect area */
#define QSPI_CR_PBE                      ((uint8_t)0x10)    /*!< Preamble Bit Enable */
#define QSPI_CR_4BYTE                    ((uint8_t)0x20)    /*!< 3-bytes or 4-bytes addressing */
#define QSPI_CR_NB_DUMMY                 ((uint8_t)0xC0)    /*!< Number of dummy clock cycles */

#define QSPI_MANUFACTURER_ID               ((uint8_t)0xC2)
#define QSPI_DEVICE_ID_MEM_TYPE            ((uint8_t)0x20)
#define QSPI_DEVICE_ID_MEM_CAPACITY        ((uint8_t)0x1A)
#define QSPI_UNIQUE_ID_DATA_LENGTH         ((uint8_t)0x10)  /*JCC: not checked */


#endif /* PERIPHERALS_INC_FLASHQSPIAGENT_H_ */
