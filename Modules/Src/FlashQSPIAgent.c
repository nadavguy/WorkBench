/*
 * FlashQSPIAgent.c
 *
 *  Created on: Jul 15, 2020
 *      Author: raing
 */

#include "main.h"
#include "FlashQSPIAgent.h"
#include "ff.h"
#include "stdint.h"
#include "quadspi.h"



FRESULT FS_ret;

QSPI_HandleTypeDef QSPIHandle;
__IO uint8_t CmdCplt, RxCplt, TxCplt, StatusMatch;

QSPI_CommandTypeDef sCommand;
QSPI_MemoryMappedTypeDef sMemMappedCfg;
__IO uint32_t qspi_addr = 0;
uint8_t *flash_addr;
__IO uint8_t step = 0;
uint32_t max_size, size;

/**
 * @brief  This function sends a Write Enable and waits until it is effective.
 * @param  hqspi: QSPI handle
 * @retval None
 */

/**
  * @brief  QSPI Init
  * @param  None
  * @retval HAL_ERROR or HAL_OK
  */
uint8_t QSPI_Init(void)
{
  /* Configuration of the dummy cycles on QSPI memory side */
  if (QSPI_DummyCyclesCfg(&hqspi) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
  * @brief  Erases the specified sector of the QSPI memory.
  * @param  SectorAddress: Block address to erase
  * @retval QSPI memory status
  */
uint8_t QSPI_Erase_Sector4K(uint32_t SectorAddress)
{
  QSPI_CommandTypeDef s_command;

  uint8_t reg1[6];

  if (QSPI_WriteEnable() != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Initialize the erase command */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = 0x20; //SUBSECTOR_ERASE_4_BYTE_ADDR_CMD;
  s_command.AddressMode = QSPI_ADDRESS_1_LINE;
  s_command.AddressSize = QSPI_ADDRESS_24_BITS; //QSPI_ADDRESS_32_BITS;
  s_command.Address = SectorAddress;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_NONE;
  s_command.DummyCycles = 0;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  // -------------------------------------------------------------------------------------

  //  if (QSPI_AutoPolling_Erase_in_progress(&hqspi, QSPI_SUBSECTOR_ERASE_MAX_TIME) != HAL_OK)  {    return HAL_ERROR;  }
  if (QSPI_AutoPolling_Write_in_progress(&hqspi, QSPI_SUBSECTOR_ERASE_MAX_TIME) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

//static bool QSPI_DMA_running = true;
//void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
//{
//  UNUSED(hqspi);
//  QSPI_DMA_running = false;
//}

/**
  * @brief  Writes an amount of data to the QSPI memory.
  * @param  pData: Pointer to data to be written
  * @param  WriteAddr: Write start address
  * @param  Size: Size of data to write
  * @retval QSPI memory status
  */
uint8_t QSPI_Write(uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
  QSPI_CommandTypeDef s_command;
  uint32_t end_addr = 0, current_size = 0, current_addr = 0;
  pData = pData - 1;
  /* Calculation of the size between the write address and the end of the page */
  current_addr = 0;
  while (current_addr <= WriteAddr)
  {
    current_addr += QSPI_PAGE_SIZE;
  }
  current_size = current_addr - WriteAddr;

  /* Check if the size of the data is less than the remaining place in the page */
  if (current_size > Size)
  {
    current_size = Size;
  }
  //  wr_time1 = systick_count_up;
  /* Initialize the address variables */
  current_addr = WriteAddr;
  end_addr = WriteAddr + Size;

  /* Initialize the program command */
//  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
//  s_command.Instruction = 0x02; // simple page programm //QPI_PAGE_PROG_4_BYTE_ADDR_CMD;
//  s_command.AddressMode = QSPI_ADDRESS_1_LINE;
//  s_command.AddressSize = QSPI_ADDRESS_24_BITS;
//  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
//  s_command.DataMode = QSPI_DATA_1_LINE;
//  s_command.DummyCycles = 0;
//  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
//  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
//  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = QUAD_IN_FAST_PROG_CMD; // simple page programm //QPI_PAGE_PROG_4_BYTE_ADDR_CMD;
  s_command.AddressMode = QSPI_ADDRESS_1_LINE;
  s_command.AddressSize = QSPI_ADDRESS_24_BITS;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;


  /* Perform the write page by page */
  do
  {
    /* Enable write operations */
    if (QSPI_WriteEnable() != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Configure the command */
    s_command.Address = current_addr;
    s_command.NbData = current_size;
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Transmission of the data */
    if (HAL_QSPI_Transmit(&hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    if (QSPI_AutoPolling_Write_in_progress(&hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Update the address and size variables for next page programming */
    current_addr += current_size;
    pData += current_size;
    current_size = ((current_addr + QSPI_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : QSPI_PAGE_SIZE;
  } while (current_addr < end_addr);

  return HAL_OK;
}

/**
  * @brief  Reads an amount of data from the QSPI memory.
  * @param  pData: Pointer to data to be read
  * @param  ReadAddr: Read start address
  * @param  Size: Size of data to read
  * @retval QSPI memory status
  */
uint8_t QSPI_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
  QSPI_CommandTypeDef s_command;

  /* Initialize the read command */
//  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
//  s_command.Instruction = 0x03; // simple data read // QPI_READ_4_BYTE_ADDR_CMD; //
//  s_command.AddressMode = QSPI_ADDRESS_1_LINE;
//  s_command.AddressSize = QSPI_ADDRESS_24_BITS;
//  s_command.Address = ReadAddr;
//  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
//  s_command.DataMode = QSPI_DATA_1_LINE;
//  s_command.DummyCycles = QSPI_DUMMY_CYCLES_READ;
//  s_command.NbData = Size;
//  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
//  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
//  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = QUAD_INOUT_FAST_READ_CMD; // simple data read // QPI_READ_4_BYTE_ADDR_CMD; //
  s_command.AddressMode = QSPI_ADDRESS_4_LINES;
  s_command.AddressSize = QSPI_ADDRESS_24_BITS;
  s_command.Address = ReadAddr;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_4_LINES;
  s_command.DummyCycles = QSPI_DUMMY_CYCLES_READ;
  s_command.NbData = Size;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(&hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @param  hqspi: QSPI handle
  * @retval None
  */
uint8_t QSPI_WriteEnable(void)
{
  QSPI_CommandTypeDef s_command;
  QSPI_AutoPollingTypeDef s_config;

  /* Enable write operations */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = WRITE_ENABLE_CMD; // ok
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_NONE;
  s_command.DummyCycles = 0;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Configure automatic polling mode to wait for write enabling */
  s_config.Match = QSPI_SR_WREN;
  s_config.Mask = QSPI_SR_WREN;
  s_config.MatchMode = QSPI_MATCH_MODE_AND;
  s_config.StatusBytesSize = 1;
  s_config.Interval = 1;
  s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

  s_command.Instruction = READ_STATUS_REG_CMD;
  s_command.DataMode = QSPI_DATA_1_LINE;

  if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

uint8_t QSPI_READMD(uint8_t *Mid, uint8_t *Did)
{
  QSPI_CommandTypeDef s_command;
  QSPI_AutoPollingTypeDef s_config;

  /* Enable write operations */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = 0x90; // ok
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE;
  s_command.DummyCycles = 0;
  s_command.NbData = 5;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }


 uint8_t reg2[6] = {0};
 HAL_QSPI_Receive(&hqspi, &(reg2), HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
 *Mid = reg2[3];
 *Did = reg2[4];
//  HAL_QSPI_Receive(&hqspi, &(reg2[1]), HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
//  HAL_QSPI_Receive(&hqspi, &(reg2[2]), HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
//  HAL_QSPI_Receive(&hqspi, &(reg2[3]), HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
//  HAL_QSPI_Receive(&hqspi, &(reg2[4]), HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
//  HAL_QSPI_Receive(&hqspi, &(reg2[5]), HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

  return HAL_OK;
}

uint8_t QSPI_ResetFlash(void)
{
  QSPI_CommandTypeDef s_command;
  QSPI_AutoPollingTypeDef s_config;

  /* Enable write operations */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = RESET_ENABLE_CMD; // ok
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Enable write operations */
    s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction = RESET_MEMORY_CMD; // ok
    s_command.AddressMode = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode = QSPI_DATA_1_LINE;
    s_command.DummyCycles = 0;
    s_command.NbData = 1;
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }
    HAL_Delay(40);

  return HAL_OK;
}


uint8_t QSPI_DeleteFlash(void)
{
  QSPI_CommandTypeDef s_command;
  QSPI_AutoPollingTypeDef s_config;

  QSPI_WriteEnable();
  /* Enable write operations */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = 0x60; // ok
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }
    HAL_Delay(40);

  return HAL_OK;
}
/**
  * @brief  This function read the SR of the memory and wait the EOP.
  * @param  hqspi: QSPI handle
  * @param  Timeout
  * @retval None
  */
uint8_t QSPI_AutoPolling_Write_in_progress(QSPI_HandleTypeDef *hqspi, uint32_t Timeout)
{
  QSPI_CommandTypeDef s_command;
  QSPI_AutoPollingTypeDef s_config;

  /* Configure automatic polling mode to wait for memory ready */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = READ_STATUS_REG_CMD;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE;
  s_command.DummyCycles = 0;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  s_config.Match = 0;
  //  s_config.Mask            = QSPI_SR_WIP;
  s_config.Mask = QSPI_SR_WIP; /*!< Write in progress */
  s_config.MatchMode = QSPI_MATCH_MODE_AND;
  s_config.StatusBytesSize = 1;
  s_config.Interval = 1; //0x10;
  s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling(hqspi, &s_command, &s_config, Timeout) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

static uint8_t QSPI_AutoPolling_Erase_in_progress(QSPI_HandleTypeDef *hqspi, uint32_t Timeout)
{
  QSPI_CommandTypeDef s_command;
  uint8_t reg1[2];

  /* Initialize the reading of status register */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; //QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = READ_STATUS_REG_CMD;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE; // QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.NbData = 2;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  do
  {
    /* Configure the command */
    if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Reception of the data */
    if (HAL_QSPI_Receive(hqspi, (uint8_t *)reg1, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return HAL_ERROR;
    }
  } while (reg1[1] & 2);
  return HAL_OK;
}

// Read Status Register-1 (05h), Status Register-2 (35h) & Status Register-3 (15h)
uint8_t QSPI_Read_Status_registers(QSPI_HandleTypeDef *hqspi, uint16_t *R1, uint16_t *R2, uint16_t *R3)
{
  QSPI_CommandTypeDef s_command;
  uint8_t reg1[6];
  uint8_t reg2[6];
  uint8_t reg3[6];

  /* Initialize the reading of status register */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; //QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = READ_STATUS_REG_CMD;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE; // QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(hqspi, (uint8_t *)reg1, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }
  *R1 = reg1[0];
  /* Initialize the reading of status register */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; //QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = READ_STATUS_REG_CMD2;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE; // QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(hqspi, (uint8_t *)reg2, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }
  *R2 = reg2[0];
  /* Initialize the reading of status register */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; //QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = READ_CFG_REG_CMD;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE; // QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(hqspi, (uint8_t *)reg3, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }
  *R3 = reg3[0];
}

// Reset Status Register-1 (05h), Status Register-2 (35h) & Status Register-3 (15h)
uint8_t QSPI_Reset_Status_registers(QSPI_HandleTypeDef *hqspi, uint16_t *R1, uint16_t *R2, uint16_t *R3)
{
  QSPI_CommandTypeDef s_command;

  QSPI_WriteEnable();

  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; //QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = WRITE_STATUS_CFG_REG_CMD;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE; // QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Transmission of the data */
  if (HAL_QSPI_Transmit(hqspi, (uint8_t *)R1, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  QSPI_WriteEnable();

  /* Initialize the reading of status register */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; //QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = 0x31;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE; // QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Transmission of the data */
  if (HAL_QSPI_Transmit(hqspi, (uint8_t *)R2, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  QSPI_WriteEnable();

  /* Initialize the reading of status register */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; //QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = 0x11;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE; // QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Transmission of the data */
  if (HAL_QSPI_Transmit(hqspi, (uint8_t *)R3, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  This function configure the dummy cycles on memory side.
  * @param  hqspi: QSPI handle
  * @retval None
  */
uint8_t QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef s_command;
  uint8_t reg[2];

  /* Initialize the reading of status register */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; //QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction = READ_STATUS_REG_CMD;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE; // QSPI_DATA_4_LINES;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(hqspi, &(reg[0]), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Initialize the reading of configuration register */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = READ_CFG_REG_CMD;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE;
  s_command.DummyCycles = 0;
  s_command.NbData = 1;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(hqspi, &(reg[1]), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Enable write operations */
  if (QSPI_WriteEnable() != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Update the configuration register with new dummy cycles */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = WRITE_STATUS_CFG_REG_CMD;
  s_command.AddressMode = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_1_LINE;
  s_command.DummyCycles = 0;
  s_command.NbData = 2;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* QSPI_DUMMY_CYCLES_READ_QUAD = 3 for 10 cycles in QPI mode */
  //  MODIFY_REG( reg[1], QSPI_CR_NB_DUMMY, (QSPI_DUMMY_CYCLES_READ_QUAD << POSITION_VAL(QSPI_CR_NB_DUMMY)));
  MODIFY_REG(reg[1], QSPI_CR_NB_DUMMY, (QSPI_DUMMY_CYCLES_READ << POSITION_VAL(QSPI_CR_NB_DUMMY)));

  /* Configure the write volatile configuration register command */
  if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Transmission of the data */
  if (HAL_QSPI_Transmit(hqspi, &(reg[0]), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* 40ms  Write Status/Configuration Register Cycle Time */
  HAL_Delay(40);

  return HAL_OK;
}

