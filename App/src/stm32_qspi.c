/**
  ******************************************************************************
  * @file    stm32_qspi.c
  * @brief   Driver do W25Q128FV sobre OCTOSPI1 (XSPI HAL) para STM32H5.
  *
  *  Reescrito a partir do driver original (portado do QUADSPI F7) para o
  *  XSPI do STM32H5. Principais correcoes:
  *   - Todas as structs de comando sao zeradas ({0}) e os campos obrigatorios
  *     do H5 (OperationType, InstructionWidth, *DTRMode, DQSMode) sao setados.
  *   - AutoPolling: MatchValue / MatchMask / IntervalTime agora sao preenchidos
  *     (antes ficavam com lixo da stack -> WriteEnable / WaitReady falhavam).
  *   - QSPI_AutoPollingMemReady() agora seta DataLength = 1 no comando.
  *   - Memory-Mapped usa OperationType = READ_CFG e TimeoutPeriodClock definido.
  *   - Adicionada BSP_QSPI_ReadID() (JEDEC 0x9F) para validacao no bring-up.
  ******************************************************************************
  */

#include "stm32_qspi.h"
#include "octospi.h"

#define QSPIHandle hxspi1

static uint8_t QSPI_ResetMemory         (void);
static uint8_t QSPI_WriteEnable         (void);
static uint8_t QSPI_AutoPollingMemReady (uint32_t Timeout);

volatile uint8_t rx_complete = 0;

/* ==========================================================================
 *  Init
 * ========================================================================== */
uint8_t BSP_QSPI_Init(void)
{
    XSPI_RegularCmdTypeDef s_command = {0};
    uint8_t value = W25Q128FV_FSR_QE;   /* QE = bit1 do SR2 (0x02) */

    /* Reset da memoria */
    if (QSPI_ResetMemory() != QSPI_OK) {
        return QSPI_NOT_SUPPORTED;
    }

    /* Habilita escrita (para gravar o SR2) */
    if (QSPI_WriteEnable() != QSPI_OK) {
        return QSPI_ERROR;
    }

    /* Grava SR2 com QE=1 (Winbond: 0x31 escreve o SR2 isoladamente) */
    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = WRITE_STATUS_REG2_CMD;
    s_command.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_1_LINE;
    s_command.DataLength         = 1;
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    if (HAL_XSPI_Transmit(&QSPIHandle, &value, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    if (QSPI_AutoPollingMemReady(W25Q128FV_SUBSECTOR_ERASE_MAX_TIME) != QSPI_OK) {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/* ==========================================================================
 *  Leitura do JEDEC ID (0x9F) - use no bring-up. Esperado: EF 40 18
 * ========================================================================== */
uint8_t BSP_QSPI_ReadID(uint8_t *pID)
{
    XSPI_RegularCmdTypeDef s_command = {0};

    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = READ_JEDEC_ID_CMD;
    s_command.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_1_LINE;
    s_command.DataLength         = 3;
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    if (HAL_XSPI_Receive(&QSPIHandle, pID, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/* ==========================================================================
 *  Leitura (modo indireto, polling). Usada apenas fora do Memory-Mapped.
 * ========================================================================== */
uint8_t BSP_QSPI_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
    XSPI_RegularCmdTypeDef s_command = {0};

    s_command.OperationType        = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode      = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth     = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode   = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction          = QUAD_INOUT_FAST_READ_CMD;   /* 0xEB */
    s_command.AddressMode          = HAL_XSPI_ADDRESS_4_LINES;
    s_command.AddressWidth         = HAL_XSPI_ADDRESS_24_BITS;
    s_command.AddressDTRMode       = HAL_XSPI_ADDRESS_DTR_DISABLE;
    s_command.Address              = ReadAddr;
    s_command.AlternateBytesMode   = HAL_XSPI_ALT_BYTES_4_LINES;
    s_command.AlternateBytesWidth  = HAL_XSPI_ALT_BYTES_8_BITS;
    s_command.AlternateBytesDTRMode= HAL_XSPI_ALT_BYTES_DTR_DISABLE;
    s_command.AlternateBytes       = 0x00;                       /* M7-M0 = 0 */
    s_command.DataMode             = HAL_XSPI_DATA_4_LINES;
    s_command.DataLength           = Size;
    s_command.DummyCycles          = W25Q128FV_DUMMY_CYCLES_READ;
    s_command.DataDTRMode          = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode              = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode             = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    if (HAL_XSPI_Receive(&QSPIHandle, pData, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/* ==========================================================================
 *  Escrita (pagina a pagina). Usada apenas fora do Memory-Mapped.
 * ========================================================================== */
uint8_t BSP_QSPI_Write(uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
    XSPI_RegularCmdTypeDef s_command = {0};
    uint32_t end_addr, current_size, current_addr;

    /* Espaco ate o fim da primeira pagina */
    current_size = W25Q128FV_PAGE_SIZE - (WriteAddr % W25Q128FV_PAGE_SIZE);
    if (current_size > Size) {
        current_size = Size;
    }

    current_addr = WriteAddr;
    end_addr     = WriteAddr + Size;

    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = QUAD_INPUT_PAGE_PROG_CMD;   /* 0x32 */
    s_command.AddressMode        = HAL_XSPI_ADDRESS_1_LINE;
    s_command.AddressWidth       = HAL_XSPI_ADDRESS_24_BITS;
    s_command.AddressDTRMode     = HAL_XSPI_ADDRESS_DTR_DISABLE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_4_LINES;
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    do {
        s_command.Address    = current_addr;
        s_command.DataLength = current_size;

        if (QSPI_WriteEnable() != QSPI_OK) {
            return QSPI_ERROR;
        }
        if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
            return QSPI_ERROR;
        }
        if (HAL_XSPI_Transmit(&QSPIHandle, pData, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
            return QSPI_ERROR;
        }
        if (QSPI_AutoPollingMemReady(W25Q128FV_SUBSECTOR_ERASE_MAX_TIME) != QSPI_OK) {
            return QSPI_ERROR;
        }

        current_addr += current_size;
        pData        += current_size;
        current_size  = ((current_addr + W25Q128FV_PAGE_SIZE) > end_addr)
                            ? (end_addr - current_addr)
                            : W25Q128FV_PAGE_SIZE;
    } while (current_addr < end_addr);

    return QSPI_OK;
}

/* ==========================================================================
 *  Erase de 1 subsetor (4 KB)
 * ========================================================================== */
uint8_t BSP_QSPI_Erase_Block(uint32_t BlockAddress)
{
    XSPI_RegularCmdTypeDef s_command = {0};

    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = SECTOR_ERASE_CMD;     /* 0x20 = 4 KB */
    s_command.AddressMode        = HAL_XSPI_ADDRESS_1_LINE;
    s_command.AddressWidth       = HAL_XSPI_ADDRESS_24_BITS;
    s_command.AddressDTRMode     = HAL_XSPI_ADDRESS_DTR_DISABLE;
    s_command.Address            = BlockAddress;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_NONE;
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (QSPI_WriteEnable() != QSPI_OK) {
        return QSPI_ERROR;
    }
    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    if (QSPI_AutoPollingMemReady(W25Q128FV_SUBSECTOR_ERASE_MAX_TIME) != QSPI_OK) {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/* ==========================================================================
 *  Erase do chip inteiro
 * ========================================================================== */
uint8_t BSP_QSPI_Erase_Chip(void)
{
    XSPI_RegularCmdTypeDef s_command = {0};

    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = CHIP_ERASE_CMD;
    s_command.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_NONE;
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (QSPI_WriteEnable() != QSPI_OK) {
        return QSPI_ERROR;
    }
    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    if (QSPI_AutoPollingMemReady(W25Q128FV_BULK_ERASE_MAX_TIME) != QSPI_OK) {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/* ==========================================================================
 *  Status
 * ========================================================================== */
uint8_t BSP_QSPI_GetStatus(void)
{
    XSPI_RegularCmdTypeDef s_command = {0};
    uint8_t reg;

    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = READ_STATUS_REG1_CMD;
    s_command.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_1_LINE;
    s_command.DataLength         = 1;
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }
    if (HAL_XSPI_Receive(&QSPIHandle, &reg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    return (reg & W25Q128FV_FSR_BUSY) ? QSPI_BUSY : QSPI_OK;
}

uint8_t BSP_QSPI_GetInfo(QSPI_Info *pInfo)
{
    pInfo->FlashSize          = W25Q128FV_FLASH_SIZE;
    pInfo->EraseSectorSize    = W25Q128FV_SUBSECTOR_SIZE;
    pInfo->EraseSectorsNumber = (W25Q128FV_FLASH_SIZE / W25Q128FV_SUBSECTOR_SIZE);
    pInfo->ProgPageSize       = W25Q128FV_PAGE_SIZE;
    pInfo->ProgPagesNumber    = (W25Q128FV_FLASH_SIZE / W25Q128FV_PAGE_SIZE);
    return QSPI_OK;
}

/* ==========================================================================
 *  MEMORY-MAPPED  (Fast Read Quad I/O 0xEB)
 *  Depois de chamar isto, o W25Q128 fica legivel em 0x90000000.
 *  NAO emita comandos indiretos (Read/Write/Erase) enquanto mapeado.
 * ========================================================================== */
uint8_t BSP_QSPI_MemoryMappedMode(void)
{
    XSPI_RegularCmdTypeDef   s_command = {0};
    XSPI_MemoryMappedTypeDef s_mem_cfg = {0};

    /* Configura o comando de LEITURA usado pelo controlador no modo mapeado */
    s_command.OperationType        = HAL_XSPI_OPTYPE_READ_CFG;
    s_command.InstructionMode      = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth     = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode   = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction          = QUAD_INOUT_FAST_READ_CMD;   /* 0xEB */
    s_command.AddressMode          = HAL_XSPI_ADDRESS_4_LINES;
    s_command.AddressWidth         = HAL_XSPI_ADDRESS_24_BITS;
    s_command.AddressDTRMode       = HAL_XSPI_ADDRESS_DTR_DISABLE;
    s_command.AlternateBytesMode   = HAL_XSPI_ALT_BYTES_4_LINES;
    s_command.AlternateBytesWidth  = HAL_XSPI_ALT_BYTES_8_BITS;
    s_command.AlternateBytesDTRMode= HAL_XSPI_ALT_BYTES_DTR_DISABLE;
    s_command.AlternateBytes       = 0x00;
    s_command.DataMode             = HAL_XSPI_DATA_4_LINES;
    s_command.DummyCycles          = W25Q128FV_DUMMY_CYCLES_READ;
    s_command.DataDTRMode          = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode              = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode             = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    /* --------------------------------------------------------------------
     *  Configura tambem o comando de ESCRITA (WRITE_CFG).
     *  Necessario nesta HAL: com apenas o READ_CFG o estado para em
     *  READ_CMD_CFG, e HAL_XSPI_MemoryMapped() exige CMD_CFG. O WRITE_CFG
     *  a partir de READ_CMD_CFG e que leva o estado ate CMD_CFG.
     *  Como o XIP e so-leitura, este comando nunca chega a ser executado.
     * ------------------------------------------------------------------ */
    s_command.OperationType      = HAL_XSPI_OPTYPE_WRITE_CFG;
    s_command.Instruction        = QUAD_INPUT_PAGE_PROG_CMD;   /* 0x32 */
    s_command.AddressMode        = HAL_XSPI_ADDRESS_1_LINE;
    s_command.AddressWidth       = HAL_XSPI_ADDRESS_24_BITS;
    s_command.AddressDTRMode     = HAL_XSPI_ADDRESS_DTR_DISABLE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_4_LINES;
    s_command.DummyCycles        = 0;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    /* Para leitura pura, desabilita o timeout counter (mantem o CS ativo) */
    s_mem_cfg.TimeOutActivation  = HAL_XSPI_TIMEOUT_COUNTER_DISABLE;
    s_mem_cfg.TimeoutPeriodClock = 0;

    if (HAL_XSPI_MemoryMapped(&QSPIHandle, &s_mem_cfg) != HAL_OK) {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

/* ==========================================================================
 *  Helpers privados
 * ========================================================================== */
static uint8_t QSPI_ResetMemory(void)
{
    XSPI_RegularCmdTypeDef s_command = {0};

    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = RESET_ENABLE_CMD;
    s_command.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_NONE;
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    s_command.Instruction = RESET_MEMORY_CMD;
    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    /* tRST ~ 30us; um pequeno atraso garante que o chip esteja pronto */
    HAL_Delay(1);

    return QSPI_OK;
}

static uint8_t QSPI_WriteEnable(void)
{
    XSPI_RegularCmdTypeDef  s_command = {0};
    XSPI_AutoPollingTypeDef s_config  = {0};

    /* Envia Write Enable (0x06) */
    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = WRITE_ENABLE_CMD;
    s_command.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_NONE;
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    /* Espera WEL=1 (SR1 bit1) via auto-polling */
    s_command.Instruction = READ_STATUS_REG1_CMD;
    s_command.DataMode    = HAL_XSPI_DATA_1_LINE;
    s_command.DataLength  = 1;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    s_config.MatchValue    = W25Q128FV_FSR_WREN;   /* 0x02 */
    s_config.MatchMask     = W25Q128FV_FSR_WREN;   /* 0x02 */
    s_config.MatchMode     = HAL_XSPI_MATCH_MODE_AND;
    s_config.AutomaticStop = HAL_XSPI_AUTOMATIC_STOP_ENABLE;
    s_config.IntervalTime  = 0x10;

    if (HAL_XSPI_AutoPolling(&QSPIHandle, &s_config, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

static uint8_t QSPI_AutoPollingMemReady(uint32_t Timeout)
{
    XSPI_RegularCmdTypeDef  s_command = {0};
    XSPI_AutoPollingTypeDef s_config  = {0};

    s_command.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    s_command.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    s_command.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    s_command.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    s_command.Instruction        = READ_STATUS_REG1_CMD;
    s_command.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    s_command.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    s_command.DataMode           = HAL_XSPI_DATA_1_LINE;
    s_command.DataLength         = 1;      /* <-- faltava no driver original */
    s_command.DummyCycles        = 0;
    s_command.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    s_command.DQSMode            = HAL_XSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    if (HAL_XSPI_Command(&QSPIHandle, &s_command, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return QSPI_ERROR;
    }

    s_config.MatchValue    = 0x00;                 /* espera BUSY=0 */
    s_config.MatchMask     = W25Q128FV_FSR_BUSY;   /* 0x01 */
    s_config.MatchMode     = HAL_XSPI_MATCH_MODE_AND;
    s_config.AutomaticStop = HAL_XSPI_AUTOMATIC_STOP_ENABLE;
    s_config.IntervalTime  = 0x10;

    if (HAL_XSPI_AutoPolling(&QSPIHandle, &s_config, Timeout) != HAL_OK) {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

void HAL_XSPI_RxCpltCallback(XSPI_HandleTypeDef *hxspi)
{
    (void)hxspi;
    rx_complete = 1;
}
