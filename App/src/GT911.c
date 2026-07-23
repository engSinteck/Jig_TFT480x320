/*
 * GT911.c
 *
 *  Created on: 13 de jul. de 2026
 *      Author: rinaldo.santos
 */
#include "main.h"
#include "GT911.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "semphr.h"

#include <../App/src/log_cdc.h>

/* Private variables ---------------------------------------------------------*/
static uint8_t GT911_Config[] = {
		0x83, 0x40, 0x01, 0xE0, 0x01, 0x0A, 0x34, 0x00, 0x01, 0xC8, 0x28, 0x05, 0x50,	// 0x8047 - 0x8053
		0x32, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x00, 0x18, 0x1A, 0x1E,	// 0x8054 - 0x8060
		0x14, 0x87, 0x29, 0x0A, 0x2C, 0x2E, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x9A, 0x02,	// 0x8061 - 0x806D
		0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E,	// 0x806E - 0x807A
		0x46, 0x94, 0xD5, 0x02, 0x07, 0x00, 0x00, 0x04, 0xAA, 0x20, 0x00, 0x91, 0x26,	// 0x807B - 0x8087
		0x00, 0x7D, 0x2D, 0x00, 0x6B, 0x36, 0x00, 0x5D, 0x40, 0x00, 0x5D, 0x00, 0x00,	// 0x8088 - 0x8094
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// 0x8095 - 0x80A1
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// 0x80A2 - 0x80AD
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x12, 0x10, 0x0E, 0x0C,	// 0x80AE - 0x80BA
		0x0A, 0x08, 0x06, 0x04, 0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,	// 0x80BB - 0x80C7
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// 0x80C8 - 0x80D4
		0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x1D, 0x28, 0x26, 0x24, 0x22, 0x21, 0x20,	// 0x80D5 - 0x80E1
		0x1F, 0x1E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,	// 0x80E2 - 0x80EE
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// 0x80EF - 0x80FB
		0x00, 0x00, 0x0E, 0x01   												    	// 0x80FC - 0x80FF
};

static GT911_Status_t CommunicationResult;
static uint8_t TxBuffer[200] = {0};
static uint8_t RxBuffer[200] = {0};
uint8_t productID[10] = {0};
uint8_t gt911_fresh = 0xFF;
uint8_t value_reg[200] = {0};
uint8_t read_config_g911[200] = {0};

/* Private function prototypes -----------------------------------------------*/
static void GT911_Reset(void);
static void GT911_CalculateCheckSum(void);
static GT911_Status_t GT911_SetCommandRegister(uint8_t command);
static GT911_Status_t GT911_GetProductID(uint8_t* id);
static GT911_Status_t GT911_SendConfig(void);
static GT911_Status_t GT911_GetStatus(uint8_t* status);
static GT911_Status_t GT911_SetStatus(uint8_t status);
static GT911_Status_t GT911_GetFresh(uint8_t* fresh);
static GT911_Status_t GT911_GetRegister(uint16_t addr, uint8_t* reg, uint8_t size);

/* API Implementation --------------------------------------------------------*/
GT911_Status_t GT911_Init(GT911_Config_t config)
{
//	Set X resolution
//	GT911_Config[1] = config.X_Resolution & 0x00FF;
//	GT911_Config[2] = (config.X_Resolution >> 8) & 0x00FF;
//	Set Y resolution
//	GT911_Config[3] = config.Y_Resolution & 0x00FF;
//	GT911_Config[4] = (config.Y_Resolution >> 8) & 0x00FF;
//  Set touch number
//	GT911_Config[5] = config.Number_Of_Touch_Support;
//  set reverse Y
//	GT911_Config[6] = 0;
//	GT911_Config[6] |= config.ReverseY << 7;
//  set reverse X
//	GT911_Config[6] |= config.ReverseX << 6;
//  set switch X2Y
//	GT911_Config[6] |= config.SwithX2Y << 3;
//  set Sito
//	GT911_Config[6] |= config.SoftwareNoiseReduction << 2;

	//Reset chip
	GT911_Reset();

	//Get product ID
	CommunicationResult = GT911_GetProductID(&productID[0]);
	if(CommunicationResult != GT911_OK){
		return CommunicationResult;
	}
	//logI("GT911 product_ID:%c%c%c%c\n", productID[0], productID[1], productID[2], productID[3]);

	// Get Firmware Version
	CommunicationResult = GT911_GetRegister(GOODIX_REG_FW_VER, &value_reg[0], 2);
	if(CommunicationResult != GT911_OK){
		return CommunicationResult;
	}
	//logI("GT911 Fimware Version: %X %X\n", value_reg[0], value_reg[1] );

	// Send GT911 Config
	CommunicationResult = GT911_SendConfig();
	if(CommunicationResult != GT911_OK){
		return CommunicationResult;
	}

	// Modo Leitura
	CommunicationResult = GT911_SetCommandRegister(0x010);
	if(CommunicationResult != GT911_OK){
		return CommunicationResult;
	}

	osDelay(200);

	CommunicationResult = GT911_GetFresh(&gt911_fresh);
	if(CommunicationResult != GT911_OK){
		return CommunicationResult;
	}
	//logI("GT911 Fresh:%d\n", gt911_fresh);

	// Leitura Reg Config
	CommunicationResult = GT911_GetRegister(GOODIX_REG_CONFIG_DATA, &read_config_g911[0], 186);
	if(CommunicationResult != GT911_OK){
		return CommunicationResult;
	}

	//logI("GT911 Reg: %X %X %X X%\n", read_config_g911[0],
	//		                         read_config_g911[1],
	//								 read_config_g911[2],
	//								 read_config_g911[3] );

	return GT911_OK;
}

void GT911_PrintConfig(void)
{
	for(uint8_t x = 0; x < 187; x++) {

		logI("0x%02X,", read_config_g911[x]);
	}
	logI("\n\r");
}

GT911_Status_t GT911_ReadTouch(TouchCordinate_t *cordinate, uint8_t *number_of_cordinate)
{
	uint8_t StatusRegister;
	GT911_Status_t Result = GT911_NotResponse;

	Result = GT911_GetStatus(&StatusRegister);
	if (Result != GT911_OK) {
		return Result;
	}

	if ((StatusRegister & 0x80) != 0) {
		*number_of_cordinate = StatusRegister & 0x0F;
		if (*number_of_cordinate != 0) {
			for (uint8_t i = 0; i < *number_of_cordinate; i++) {
				TxBuffer[0] = ((GOODIX_POINT1_X_ADDR + (i* 8)) & 0xFF00) >> 8;
				TxBuffer[1] = (GOODIX_POINT1_X_ADDR + (i* 8)) & 0xFF;
				GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2);
				GT911_I2C_Read(GOODIX_ADDRESS, RxBuffer, 6);
				cordinate[i].x = RxBuffer[0];
				cordinate[i].x = (RxBuffer[1] << 8) + cordinate[i].x;
				cordinate[i].y = RxBuffer[2];
				cordinate[i].y = (RxBuffer[3] << 8) + cordinate[i].y;
			}
		}
		GT911_SetStatus(0);
	}
	return GT911_OK;
}

//Private functions Implementation ---------------------------------------------------------*/
static void GT911_Reset(void)
{
	GT911_INT_Output();

	HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(TP_IRQ_GPIO_Port, TP_IRQ_Pin, GPIO_PIN_RESET);
	GT911_Delay(10); // Aguarda 10ms

	// 2. Para definir o endereço I2C como 0xBA (7-bit: 0x5D) e liberar a escrita:
	// O pino INT deve estar em nível BAIXO no momento em que o RST sobe para nível ALTO.
	HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_RESET);
	GT911_Delay(2);

	HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_SET); // Sobe o Reset
	GT911_Delay(10); // Aguarda o chip inicializar internamente

	GT911_INT_Input();

	GT911_Delay(100);
}

static void GT911_CalculateCheckSum(void)
{
	GT911_Config[184] = 0;
	for(uint8_t i = 0 ; i < 184 ; i++){
		GT911_Config[184] += GT911_Config[i];
	}
	GT911_Config[184] = (~GT911_Config[184]) + 1;
}

static GT911_Status_t GT911_SetCommandRegister(uint8_t command)
{
	TxBuffer[0] = (GOODIX_REG_COMMAND & 0xFF00) >> 8;
	TxBuffer[1] = GOODIX_REG_COMMAND & 0xFF;
	TxBuffer[2] = command;
	return GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 3);
}

static GT911_Status_t GT911_GetProductID(uint8_t* id)
{
	TxBuffer[0] = (GOODIX_REG_ID & 0xFF00) >> 8;
	TxBuffer[1] = GOODIX_REG_ID & 0xFF;
	GT911_Status_t Result = GT911_NotResponse;
	Result = GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2);
	if(Result == GT911_OK){
		Result = GT911_I2C_Read(GOODIX_ADDRESS, RxBuffer, 4);
		if( Result == GT911_OK){
			memcpy(id, RxBuffer, 4);
		}
	}
	return Result;
}

static GT911_Status_t GT911_SendConfig(void)
{
	GT911_CalculateCheckSum();

	TxBuffer[0] = (GOODIX_REG_CONFIG_DATA & 0xFF00) >> 8;
	TxBuffer[1] = GOODIX_REG_CONFIG_DATA & 0xFF;

	memcpy(&TxBuffer[2], GT911_Config, sizeof(GT911_Config));

	return GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, sizeof(GT911_Config) + 2);
}

static GT911_Status_t GT911_GetStatus(uint8_t* status)
{
	TxBuffer[0] = (GOODIX_READ_COORD_ADDR & 0xFF00) >> 8;
	TxBuffer[1] = GOODIX_READ_COORD_ADDR & 0xFF;
	GT911_Status_t Result = GT911_NotResponse;
	Result = GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2);
	if(Result == GT911_OK){
		Result = GT911_I2C_Read(GOODIX_ADDRESS, RxBuffer, 1);
		if( Result == GT911_OK){
			*status = RxBuffer[0];
		}
	}
	return Result;
}

static GT911_Status_t GT911_GetFresh(uint8_t* fresh)
{
	TxBuffer[0] = (GOODIX_REG_CONFIG_FRESH & 0xFF00) >> 8;
	TxBuffer[1] = GOODIX_REG_CONFIG_FRESH & 0xFF;
	GT911_Status_t Result = GT911_NotResponse;
	Result = GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2);
	if(Result == GT911_OK){
		Result = GT911_I2C_Read(GOODIX_ADDRESS, RxBuffer, 1);
		if( Result == GT911_OK){
			*fresh = RxBuffer[0];
		}
	}
	return Result;
}

static GT911_Status_t GT911_GetRegister(uint16_t addr, uint8_t* reg, uint8_t size)
{
	TxBuffer[0] = (addr & 0xFF00) >> 8;
	TxBuffer[1] = addr & 0xFF;
	GT911_Status_t Result = GT911_NotResponse;
	Result = GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2);
	if(Result == GT911_OK){
		Result = GT911_I2C_Read(GOODIX_ADDRESS, RxBuffer, size);
		if( Result == GT911_OK){
			memcpy(reg, RxBuffer, size);
		}
	}
	return Result;
}

static GT911_Status_t GT911_SetStatus(uint8_t status)
{
	TxBuffer[0] = (GOODIX_READ_COORD_ADDR & 0xFF00) >> 8;
	TxBuffer[1] = GOODIX_READ_COORD_ADDR & 0xFF;
	TxBuffer[2] = status;
	return GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 3);
}


// Função auxiliar de mapeamento linear
//static int32_t map_coordinate(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
//{
//    int32_t result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//    if (result < out_min) result = out_min;
//    if (result > out_max) result = out_max;
//
//    return result;
//}

void touch_read_cb(lv_indev_t * indev, lv_indev_data_t* data)
{
    uint8_t number;
    uint8_t touched = 0;
    TouchCordinate_t cordinate[5] = {0};

    touched = GT911_ReadTouch_LVGL(cordinate, &number);

    if (touched != 0) {
    	// 1. Inverte eixos X e Y (SwithX2Y)
    	uint16_t temp_x = cordinate[0].y;
    	uint16_t temp_y = cordinate[0].x;

    	//int16_t mapped_raw_x = map_coordinate(temp_x, 0, 479, 0, 479);
    	//int16_t mapped_raw_y = map_coordinate(temp_y, 0, 319, 0, 319);

    	// 2. Corrige a origem de Y para o Superior Esquerdo (0,0)
    	// Se o LCD tem 320 de altura no novo eixo Y:
    	data->point.x = 480 - temp_x;
    	data->point.y = temp_y;

    	data->state = LV_INDEV_STATE_PRESSED;
    	//logI("Touch_X: RAW:[%d] L:[%d] M:[%d]  -  Touch_Y: RAW:[%d] L:[%d] M:[%d]\n", temp_x, data->point.x, mapped_raw_x,
    	//		                                                                      temp_y, data->point.y, mapped_raw_y);
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

uint8_t GT911_ReadTouch_LVGL(TouchCordinate_t *cordinate, uint8_t *number_of_cordinate)
{
    uint8_t StatusRegister = 0;
    uint8_t raw_data[40] = {0}; // Local para evitar condições de corrida

    // 1. Lê o Status Register
    if (GT911_GetStatus(&StatusRegister) != GT911_OK) {
        return 0;
    }

    // Verifica se há novos dados prontos e o número de toques
    if ((StatusRegister & 0x80) != 0) {
        *number_of_cordinate = StatusRegister & 0x0F;

        if (*number_of_cordinate > 0 && *number_of_cordinate <= 5) {
            // Configura endereço inicial de leitura (0x8150)
            TxBuffer[0] = (GOODIX_POINT1_X_ADDR & 0xFF00) >> 8;
            TxBuffer[1] = GOODIX_POINT1_X_ADDR & 0xFF;

            if (GT911_I2C_Write(GOODIX_ADDRESS, TxBuffer, 2) == GT911_OK) {
                // Lê em lote contínuo (8 bytes por ponto de toque ativo)
                uint8_t bytes_to_read = (*number_of_cordinate) * 8;
                if (GT911_I2C_Read(GOODIX_ADDRESS, raw_data, bytes_to_read) == GT911_OK) {
                    for (uint8_t i = 0; i < *number_of_cordinate; i++) {
                        uint8_t offset = i * 8;
                        // Monta coordenadas garantindo a conversão de tipo adequada
                        cordinate[i].x = ((uint16_t)raw_data[offset + 1] << 8) | raw_data[offset + 0];
                        cordinate[i].y = ((uint16_t)raw_data[offset + 3] << 8) | raw_data[offset + 2];
                    }
                }
            }
        }

        // Reseta o registrador de status para receber a próxima leitura
        GT911_SetStatus(0);
        return (*number_of_cordinate > 0) ? 1 : 0;
    }
    return 0;
}
