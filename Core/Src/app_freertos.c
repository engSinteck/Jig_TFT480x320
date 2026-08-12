/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"

#include "string.h"
#include "../App/src/ILI9488.h"
#include "../App/src/GT911.h"
#include "../App/src/file_handle.h"

#include "../App/UI/screen_dac.h"
#include "../App/UI/screen_debug.h"
#include "../App/UI/screen_gpio.h"
#include "../App/UI/screen_mp3.h"
#include "../App/UI/screen_tuner.h"
#include "../App/UI/screen_boot.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern void MX_USB_Device_Init(void);

extern volatile uint8_t rx_buffer[1024];
extern volatile uint8_t rx_flag;
extern uint8_t rx_byte;
extern volatile uint16_t head;
extern uint16_t tail;

// Defini��o dos comandos esperados
const uint8_t CMD1[8] = {0x81, 0x03, 0x00, 0x00, 0x00, 0x7C, 0x5B, 0xEB};
const uint8_t CMD2[8] = {0x81, 0x03, 0x01, 0x00, 0x00, 0x78, 0x5B, 0xD4};

const uint8_t RESP1[253] = { 0x51, 0x03, 0xF8, 0x0F, 0x00, 0x0F, 0x06, 0x0F,
		                     0x02, 0x0F, 0x03, 0x0F, 0x00, 0x0F, 0x06, 0x0F,
		                     0x0A, 0x0F, 0x0A, 0x0F, 0x0A, 0x0F, 0x03, 0x0F,
							 0x02, 0x0F, 0x08, 0x0F, 0x03, 0x0E, 0xFF, 0x00,
		                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x00, 0x41, 0x00, 0x41, 0x00,
							 0x42, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x02, 0x1A, 0x75, 0x30, 0x03,
							 0xE8, 0x00, 0x1F, 0x00, 0x0E, 0x00, 0x04, 0x0F,
		                     0x0A, 0x00, 0x07, 0x0E, 0xFF, 0x00, 0x0E, 0x00,
							 0x0B, 0x00, 0x42, 0x00, 0x03, 0x00, 0x41, 0x00,
		                     0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x03, 0xE8, 0x00, 0x02, 0x00, 0x00, 0x75,
		                     0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x0F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x46, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x75, 0x30, 0x1A, 0x07, 0x1C,
							 0x0E, 0x06, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75,
							 0x30, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00,
		                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0xC1, 0xC8 };

const uint8_t RESP2[245] = { 0x51, 0x03, 0xF0, 0x00, 0x01, 0x00, 0x0E, 0x00,
		                     0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86,
							 0xA0, 0x00, 0x00, 0x9C, 0x40, 0x00, 0x03, 0xEE,
		                     0x14, 0x00, 0x02, 0x86, 0xCB, 0x00, 0x28, 0x00,
							 0x28, 0x00, 0x00, 0x0C, 0x80, 0x01, 0x68, 0x03,
	 	                     0xE8, 0x02, 0xEE, 0x00, 0x01, 0x00, 0x01, 0x0B,
							 0xB8, 0x00, 0x0A, 0x00, 0x0A, 0x00, 0x0A, 0x00,
		                     0x32, 0x00, 0x0A, 0x00, 0xA5, 0x00, 0x01, 0x00,
							 0x00, 0x1A, 0x07, 0x1C, 0x0E, 0x06, 0x16, 0x31,
		                     0x32, 0x33, 0x34, 0x35, 0x36, 0x19, 0x03, 0x0F,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
		                     0x00, 0x00, 0x00, 0x0F, 0x0A, 0x0F, 0x6E, 0x0F,
							 0x0A, 0x03, 0xE8, 0x07, 0x6C, 0x07, 0x08, 0x07,
		                     0xD0, 0x03, 0xE8, 0x02, 0x09, 0x02, 0x18, 0x02,
							 0x09, 0x03, 0xE8, 0x01, 0x8F, 0x01, 0x7E, 0x01,
		                     0x8F, 0x03, 0xE8, 0x6B, 0x6C, 0x69, 0x78, 0x03,
							 0xE8, 0x67, 0x20, 0x01, 0xF4, 0x7E, 0xF4, 0x80,
		                     0xE8, 0x03, 0xE8, 0x83, 0x40, 0x01, 0xF4, 0x00,
							 0x5F, 0x00, 0x69, 0x00, 0x64, 0x03, 0xE8, 0x00,
		                     0x1E, 0x00, 0x14, 0x00, 0x19, 0x03, 0xE8, 0x00,
							 0x69, 0x00, 0x6E, 0x00, 0x69, 0x03, 0xE8, 0x00,
		                     0x1E, 0x00, 0x14, 0x00, 0x19, 0x03, 0xE8, 0x01,
							 0xF4, 0x03, 0x20, 0x02, 0xBC, 0x03, 0xE8, 0x00,
		                     0x0A, 0x00, 0x0F, 0x00, 0x0A, 0x03, 0xE8, 0x00,
							 0x64, 0x00, 0x1E, 0x00, 0x96, 0x03, 0xE8, 0x00,
		                     0x82, 0x00, 0x8C, 0x00, 0x87, 0x03, 0xE8, 0x00,
							 0x82, 0x00, 0x8C, 0x00, 0x87, 0x03, 0xE8, 0x01,
		                     0xC2, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00,
							 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		                     0x00, 0x00, 0x00, 0x1F, 0x6D };


// Buffer local para montar o comando conforme os bytes saem da fila
uint8_t cmd_buffer[8] = {0};
uint8_t cmd_idx = 0;

extern lv_obj_t * Tela_Debug;
extern lv_obj_t * Tela_DAC;


void my_log_cb(lv_log_level_t level, const char * buf);

GT911_Config_t sampleConfig = {.X_Resolution = 320, .Y_Resolution = 480, .Number_Of_Touch_Support = 1, .ReverseY = true, .ReverseX = false, .SwithX2Y = true, .SoftwareNoiseReduction = false};

static uint8_t buf1[(480 * 10 * 3)] __attribute__((aligned(32)));
static uint8_t buf2[(480 * 10 * 3)] __attribute__((aligned(32)));
static lv_display_t * disp;

uint32_t timer_led = 0;
uint32_t timer_lvgl = 0;
volatile unsigned long ulHighFrequencyTimerTicks = 0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
LV_IMG_DECLARE(AUDIO);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for Task485 */
osThreadId_t Task485Handle;
const osThreadAttr_t Task485_attributes = {
  .name = "Task485",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};
/* Definitions for TaskLVGL */
osThreadId_t TaskLVGLHandle;
const osThreadAttr_t TaskLVGL_attributes = {
  .name = "TaskLVGL",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 2048 * 4
};
/* Definitions for MutexI2C */
osMutexId_t MutexI2CHandle;
const osMutexAttr_t MutexI2C_attributes = {
  .name = "MutexI2C"
};
/* Definitions for Mutex485 */
osMutexId_t Mutex485Handle;
const osMutexAttr_t Mutex485_attributes = {
  .name = "Mutex485"
};
/* Definitions for BinarySemI2C */
osSemaphoreId_t BinarySemI2CHandle;
const osSemaphoreAttr_t BinarySemI2C_attributes = {
  .name = "BinarySemI2C"
};
/* Definitions for BinarySemLVGL */
osSemaphoreId_t BinarySemLVGLHandle;
const osSemaphoreAttr_t BinarySemLVGL_attributes = {
  .name = "BinarySemLVGL"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
	ulHighFrequencyTimerTicks = 0;
}

__weak unsigned long getRunTimeCounterValue(void)
{
	return ulHighFrequencyTimerTicks;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* creation of MutexI2C */
  MutexI2CHandle = osMutexNew(&MutexI2C_attributes);

  /* creation of Mutex485 */
  Mutex485Handle = osMutexNew(&Mutex485_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */
  /* creation of BinarySemI2C */
  BinarySemI2CHandle = osSemaphoreNew(1, 1, &BinarySemI2C_attributes);

  /* creation of BinarySemLVGL */
  BinarySemLVGLHandle = osSemaphoreNew(1, 1, &BinarySemLVGL_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Task485 */
  Task485Handle = osThreadNew(StartTask485, NULL, &Task485_attributes);

  /* creation of TaskLVGL */
  TaskLVGLHandle = osThreadNew(StartTaskLVGL, NULL, &TaskLVGL_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */
  MX_USB_Device_Init();
  /* Infinite loop */

	for(;;)
	{
		if(HAL_GetTick() - timer_led > 250) {
			timer_led = HAL_GetTick();
			HAL_GPIO_TogglePin(LED_INT_GPIO_Port, LED_INT_Pin);
		}

		osDelay(10);
	}
  /* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_StartTask485 */
/**
* @brief Function implementing the Task485 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask485 */
void StartTask485(void *argument)
{
  /* USER CODE BEGIN Task485 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END Task485 */
}

/* USER CODE BEGIN Header_StartTaskLVGL */
/**
* @brief Function implementing the TaskLVGL thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskLVGL */
void StartTaskLVGL(void *argument)
{
  /* USER CODE BEGIN TaskLVGL */
	// Init GT911
	GT911_Init(sampleConfig);

	// Test Read SD-Card
	Mount_FATFS();

	lv_init();

	disp = lv_display_create(480, 320);
	lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB888);
	lv_display_set_buffers(disp, buf1, buf2, 480 * 10 * 3, LV_DISPLAY_RENDER_MODE_PARTIAL);
	lv_display_set_flush_cb(disp, ILI9488_Flush_DMA);
	lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB888);

	lv_indev_t * indev = lv_indev_create();
	lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
	lv_indev_set_read_cb(indev, touch_read_cb);

#if LV_USE_LOG
	// Log LVGL
	lv_log_register_print_cb(my_log_cb);
#endif

	// Tela Debug
	screen_boot();

  /* Infinite loop */
  for(;;)
  {
	  lv_timer_handler();

	  osDelay(5);
  }
  /* USER CODE END TaskLVGL */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI2) {
		ILI9488_Flush_End_DMA(disp);
	}
}

void my_log_cb(lv_log_level_t level, const char * buf)
{
	//logI(buf, strlen(buf));
}
/* USER CODE END Application */

