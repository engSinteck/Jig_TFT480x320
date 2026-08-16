/*
 * log_cdc.c
 *
 *  Created on: 10 de jul. de 2026
 *      Author: rinaldo.santos
 */
#include "main.h"
#include "usart.h"
#include "log_cdc.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "queue.h"
#include "semphr.h"

#define CDC_TX_TIMEOUT_MS 200U


#define PRINT_BUFFER_SIZE 4096
char string_usb[PRINT_BUFFER_SIZE];

extern osMutexId_t MutexLogHandle;


/** Custom printf function in order to use HAL_UART_Transmit()
 * @param *fmt String to print
 * @param argp Parameters list
 */
void HAL_printf_valist(const char *fmt, va_list argp)
{
//	xSemaphoreTake(MutexLogHandle, portMAX_DELAY);
//
	int len = vsnprintf(string_usb, sizeof(string_usb), fmt, argp);
	if(len > 0) {
		HAL_UART_Transmit(&huart1, (uint8_t*)string_usb, strlen(string_usb), 1000);
	}
//
//	xSemaphoreGive(MutexLogHandle);
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
