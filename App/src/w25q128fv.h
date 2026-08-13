/**
  ******************************************************************************
  * @file    w25q128fv.h
  * @brief   Description / command set for the Winbond W25Q128FV (128 Mbit) NOR.
  *
  *  CORRIGIDO: os tamanhos anteriores estavam configurados para um W25Q512
  *  (64 MByte). O W25Q128FV e 128 Mbit = 16 MByte.
  ******************************************************************************
  */

#ifndef __W25Q128FV_H
#define __W25Q128FV_H

#ifdef __cplusplus
 extern "C" {
#endif

/* ==========================================================================
 *  W25Q128FV : 128 Mbit = 16 MByte
 * ========================================================================== */
#define W25Q128FV_FLASH_SIZE          0x1000000  /* 16 MByte                 */
#define W25Q128FV_SECTOR_SIZE         0x10000    /* 256 setores de 64 KByte  */
#define W25Q128FV_SUBSECTOR_SIZE      0x1000     /* 4096 subsetores de 4 KB  */
#define W25Q128FV_PAGE_SIZE           0x100      /* 65536 paginas de 256 B   */

#define W25Q128FV_SECTOR_COUNT        256        /* setores de 64 KB         */
#define W25Q128FV_SUBSECTOR_COUNT     4096       /* subsetores de 4 KB       */
#define W25Q128FV_PAGE_COUNT          65536

/* Endereco base do W25Q128 quando o OCTOSPI1 esta em Memory-Mapped */
#define W25Q128FV_MAPPED_BASE         0x90000000UL   /* == OCTOSPI1_BASE      */

/* JEDEC ID esperado (comando 0x9F): EF 40 18 */
#define W25Q128FV_JEDEC_ID            0xEF4018

/* Dummy cycles do Fast Read Quad I/O (0xEB): 2 clk do byte de modo + 4 dummy */
#define W25Q128FV_DUMMY_CYCLES_READ           4
#define W25Q128FV_DUMMY_CYCLES_READ_QUAD      10
#define W25Q128FV_DUMMY_CYCLES_READ_DTR       6
#define W25Q128FV_DUMMY_CYCLES_READ_QUAD_DTR  8

#define W25Q128FV_BULK_ERASE_MAX_TIME         480000
#define W25Q128FV_SECTOR_ERASE_MAX_TIME       3000
#define W25Q128FV_SUBSECTOR_ERASE_MAX_TIME    800

/* ---------------------------------------------------------------------------
 *  Comandos
 * ------------------------------------------------------------------------- */
/* Reset */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

#define ENTER_QPI_MODE_CMD                   0x38
#define EXIT_QPI_MODE_CMD                    0xFF

/* Identificacao */
#define READ_ID_CMD                          0x90
#define DUAL_READ_ID_CMD                     0x92
#define QUAD_READ_ID_CMD                     0x94
#define READ_JEDEC_ID_CMD                    0x9F

/* Leitura */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* Escrita */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Registradores de status */
#define READ_STATUS_REG1_CMD                 0x05
#define READ_STATUS_REG2_CMD                 0x35
#define READ_STATUS_REG3_CMD                 0x15

#define WRITE_STATUS_REG1_CMD                0x01
#define WRITE_STATUS_REG2_CMD                0x31
#define WRITE_STATUS_REG3_CMD                0x11

/* Programacao */
#define PAGE_PROG_CMD                        0x02
#define QUAD_INPUT_PAGE_PROG_CMD             0x32

/* Erase */
#define SECTOR_ERASE_CMD                     0x20   /* apaga 1 subsetor 4 KB  */
#define BLOCK_ERASE_64K_CMD                  0xD8
#define CHIP_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

/* Bits do Status Register */
#define W25Q128FV_FSR_BUSY                   ((uint8_t)0x01)   /* SR1 bit0     */
#define W25Q128FV_FSR_WREN                   ((uint8_t)0x02)   /* SR1 bit1 WEL */
#define W25Q128FV_FSR_QE                     ((uint8_t)0x02)   /* SR2 bit1 QE  */

#ifdef __cplusplus
}
#endif

#endif /* __W25Q128FV_H */
