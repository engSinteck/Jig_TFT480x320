/*
 * GT911_User.c
 *
 *  Created on: 13 de jul. de 2026
 *      Author: rinaldo.santos
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "GT911.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "semphr.h"

extern osMutexId_t myMutexI2C3Handle;

/* Private user code ---------------------------------------------------------*/
void GT911_INT_Input(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = TP_IRQ_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(TP_IRQ_GPIO_Port, &GPIO_InitStruct);
}

void GT911_INT_Output(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = TP_IRQ_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(TP_IRQ_GPIO_Port, &GPIO_InitStruct);
}

void GT911_RST_Control(bool high_or_low)
{
	if(high_or_low)
		HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_RESET);
}

void GT911_INT_Control(bool high_or_low)
{
	if(high_or_low)
		HAL_GPIO_WritePin(TP_IRQ_GPIO_Port, TP_IRQ_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(TP_IRQ_GPIO_Port, TP_IRQ_Pin, GPIO_PIN_RESET);
}


void GT911_Delay(uint16_t ms)
{
	HAL_Delay(ms);
}

GT911_Status_t GT911_I2C_Init(void)
{
	return GT911_OK;
}

GT911_Status_t GT911_I2C_Write(uint8_t Addr, uint8_t *write_data, uint16_t write_length)
{
	HAL_StatusTypeDef ret;
	uint8_t Address = Addr << 1;

	ret = HAL_I2C_Master_Transmit(&hi2c1, Address, write_data, write_length, HAL_MAX_DELAY);

	switch (ret) {
		case HAL_OK:
			return GT911_OK;
			break;
		case HAL_ERROR:
			return GT911_Error;
			break;
		case HAL_BUSY:
		case HAL_TIMEOUT:
			return GT911_NotResponse;
			break;
	}

	return GT911_Error;
}

GT911_Status_t GT911_I2C_Read(uint8_t Addr, uint8_t* read_data, uint16_t read_length)
{
	HAL_StatusTypeDef ret;
	uint8_t Address = Addr << 1;

	ret = HAL_I2C_Master_Receive(&hi2c1, Address, read_data, read_length, HAL_MAX_DELAY);

	switch (ret) {
		case HAL_OK:
			return GT911_OK;
			break;
		case HAL_ERROR:
			return GT911_Error;
			break;
		case HAL_BUSY:
		case HAL_TIMEOUT:
			return GT911_NotResponse;
			break;
	}

	return HAL_ERROR;
}
