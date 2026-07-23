/*
 * log_cdc.c
 *
 *  Created on: 10 de jul. de 2026
 *      Author: rinaldo.santos
 */
#include "log_cdc.h"
#include "usbd_cdc_if.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "queue.h"
#include "semphr.h"

#define CDC_TX_TIMEOUT_MS 200U

extern USBD_HandleTypeDef hUsbDeviceFS;

#define PRINT_BUFFER_SIZE 4096
char string_usb[PRINT_BUFFER_SIZE];

static HAL_StatusTypeDef CDC_Transmit_Wait(uint8_t *buf, uint16_t len)
{
    uint32_t tick = HAL_GetTick();
    USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;

    if (hcdc == NULL)
        return HAL_ERROR;

    /* Aguarda TxState liberar */
    while (hcdc->TxState != 0)
    {
        if ((HAL_GetTick() - tick) > CDC_TX_TIMEOUT_MS)
            return HAL_TIMEOUT;

        osDelay(1);
    }

    return (CDC_Transmit_FS(buf, len) == USBD_OK) ? HAL_OK : HAL_ERROR;
}

/** Custom printf function in order to use HAL_UART_Transmit()
 * @param *fmt String to print
 * @param argp Parameters list
 */
void HAL_printf_valist(const char *fmt, va_list argp)
{
	//xSemaphoreTake(MutexLog, portMAX_DELAY);

	int len = vsnprintf(string_usb, sizeof(string_usb), fmt, argp);
	if (len > 0) {
		CDC_Transmit_Wait((uint8_t*)string_usb, (uint16_t)len);
	} else {
		CDC_Transmit_Wait((uint8_t*)"E - Print\n", 10);
	}

	//xSemaphoreGive(MutexLog);
}

/** Custom printf function, only translate to va_list arg HAL_UART.
 * @param *fmt String to print
 * @param ... Data
 */
void HAL_printf(const char *fmt, ...)
{
  va_list argp;

  va_start(argp, fmt);
  HAL_printf_valist(fmt, argp);
  va_end(argp);
}

/** Generic LOG procedure
 * @param Log level
 * @param *fmt String to print
 * @param argp Parameters list
 */
void logUSB(const char *fmt, va_list argp)
{
	//HAL_printf("%d - ", level);
	HAL_printf_valist(fmt, argp);
}

/** LOG procedure - Info
 * @param *fmt String to print
 * @param ... Parameters list
 */
void logI(const char* fmt, ...)
{
	va_list argp;

	va_start(argp, fmt);
	logUSB(fmt, argp);
	va_end(argp);
}
