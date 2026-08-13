/**
  ******************************************************************************
  * @file    stm32_qspi.h
  * @brief   Prototipos do driver do W25Q128FV sobre OCTOSPI1 (XSPI) - STM32H5.
  ******************************************************************************
  */
#ifndef __STM32_QSPI_H
#define __STM32_QSPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32h5xx_hal.h"
#include "w25q128fv.h"

/* Codigos de retorno */
#define QSPI_OK            ((uint8_t)0x00)
#define QSPI_ERROR         ((uint8_t)0x01)
#define QSPI_BUSY          ((uint8_t)0x02)
#define QSPI_NOT_SUPPORTED ((uint8_t)0x04)
#define QSPI_SUSPENDED     ((uint8_t)0x08)

/* Ponteiro para a base memory-mapped (0x90000000) ja como uint8_t* */
#define QSPI_MAPPED_ADDR   ((const uint8_t *)W25Q128FV_MAPPED_BASE)

typedef struct {
  uint32_t FlashSize;
  uint32_t EraseSectorSize;
  uint32_t EraseSectorsNumber;
  uint32_t ProgPageSize;
  uint32_t ProgPagesNumber;
} QSPI_Info;

uint8_t BSP_QSPI_Init            (void);
uint8_t BSP_QSPI_ReadID          (uint8_t *pID);          /* JEDEC 0x9F: EF 40 18 */
uint8_t BSP_QSPI_Read            (uint8_t *pData, uint32_t ReadAddr, uint32_t Size);
uint8_t BSP_QSPI_Write           (uint8_t *pData, uint32_t WriteAddr, uint32_t Size);
uint8_t BSP_QSPI_Erase_Block     (uint32_t BlockAddress);
uint8_t BSP_QSPI_Erase_Chip      (void);
uint8_t BSP_QSPI_GetStatus       (void);
uint8_t BSP_QSPI_GetInfo         (QSPI_Info *pInfo);
uint8_t BSP_QSPI_MemoryMappedMode(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32_QSPI_H */
