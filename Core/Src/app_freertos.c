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
#include "tim.h"
#include "usart.h"
#include "lvgl.h"

#include "string.h"
#include "../App/src/ILI9488.h"
#include "../App/src/GT911.h"
#include "../App/src/stm32_qspi.h"
#include "../App/src/file_handle.h"
#include "../App/src/log_cdc.h"
#include "../App/src/Teste_FATFS.h"


#include "../App/UI/screen_dac.h"
#include "../App/UI/screen_debug.h"
#include "../App/UI/screen_gpio.h"
#include "../App/UI/screen_mp3.h"
#include "../App/UI/screen_tuner.h"
//
#include "../App/UI/Screen_Main.h"
#include "../App/UI/Screen_Splash.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern void MX_USB_Device_Init(void);

extern volatile uint8_t rx_buffer[1024];
extern volatile uint8_t rx_flag;
extern uint8_t rx_byte;
extern volatile uint16_t head;
extern uint16_t tail;

// Definicao dos comandos esperados
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
void print_runtime_stats(void);

GT911_Config_t sampleConfig = {.X_Resolution = 320, .Y_Resolution = 480, .Number_Of_Touch_Support = 1, .ReverseY = true, .ReverseX = false, .SwithX2Y = true, .SoftwareNoiseReduction = false};

uint32_t timer_led = 0;
uint32_t timer_lvgl = 0;
uint32_t timer_stat = 0;

volatile unsigned long ulHighFrequencyTimerTicks = 0;

static uint8_t buf1[DRAW_BUF_SIZE_BYTES] __attribute__((aligned(32)));
static uint8_t buf2[DRAW_BUF_SIZE_BYTES] __attribute__((aligned(32)));
static lv_display_t * disp;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

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
  .stack_size = 8192 * 4
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
/* Definitions for MutexLog */
osMutexId_t MutexLogHandle;
const osMutexAttr_t MutexLog_attributes = {
  .name = "MutexLog"
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
void configureTimerForRunTimeStats(void)
{
	ulHighFrequencyTimerTicks = 0;
	__HAL_TIM_SET_COUNTER(&htim12, 0);
	HAL_TIM_Base_Start_IT(&htim12);
}

unsigned long getRunTimeCounterValue(void)
{
	/* Retorna (Voltas * Período) + Passos Atuais do Timer */
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

  /* creation of MutexLog */
  MutexLogHandle = osMutexNew(&MutexLog_attributes);

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

		if(HAL_GetTick() - timer_stat > 5000) {
			timer_stat = HAL_GetTick();
			print_runtime_stats();
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
	  if (rx_flag) {
		  rx_flag = 0; // Limpa a flag de aviso de novos dados

		  // Processa os bytes enquanto a fila circular não estiver vazia
		  while (tail != head) {
			  // Retira o byte atual da fila circular
			  uint8_t byte_atual = rx_buffer[tail];
			  tail = (tail + 1) % 1024;

			  // Alinha o início do frame: se o buffer local estiver vazio, o byte DEVE ser 0x81
			  if (cmd_idx == 0 && byte_atual != 0x81) {
				  continue; // Ignora lixo na linha de comunicação
			  }

			  // Adiciona o byte ao buffer de comando local
			  cmd_buffer[cmd_idx] = byte_atual;
			  cmd_idx++;

			  // Se completou os 8 bytes do comando, realiza a validação
			  if (cmd_idx == 8) {

				  // Compara com o Comando 1
				  if (memcmp(cmd_buffer, CMD1, 8) == 0) {
					  // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0); // Toggle no LED 1 (ex: PA0)
					  HAL_UART_Transmit(&huart2, RESP1, sizeof(RESP1), 1000);
				  }
				  // Compara com o Comando 2
				  else if (memcmp(cmd_buffer, CMD2, 8) == 0) {
					  //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1); // Toggle no LED 2 (ex: PA1)
					  HAL_UART_Transmit(&huart2, RESP2, sizeof(RESP2), 1000);
				  }
				  // Reseta o índice para aguardar o próximo comando de 8 bytes
				  cmd_idx = 0;
			  }
		  }
	  }
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

	// Test Speed FATFS
	//Test_FATFS();

	lv_init();

#if LV_USE_LOG
	// Log LVGL
//	lv_log_register_print_cb(my_log_cb);
#endif

	disp = lv_display_create(480, 320);
	lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB888);
	lv_display_set_buffers(disp, buf1, buf2, DRAW_BUF_SIZE_BYTES, LV_DISPLAY_RENDER_MODE_PARTIAL);
	lv_display_set_flush_cb(disp, ILI9488_Flush_DMA);

	lv_indev_t * indev = lv_indev_create();
	lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
	lv_indev_set_read_cb(indev, touch_read_cb);

	// Tela Splash
	Screen_Create_Splash();
	//Screen_Create_Main();

  /* Infinite loop */
  for(;;)
  {
	  // Testar codigo abaixo
      uint32_t time_till_next = lv_timer_handler();
      if(time_till_next == 0) time_till_next = 1; // Evita travar
      vTaskDelay(pdMS_TO_TICKS(time_till_next));
  }
  /* USER CODE END TaskLVGL */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART2) {	// COMM. UART1
		// Salva Byte Recebido
		rx_buffer[head] = rx_byte;

		// Avança o head de forma circular (volta para 0 se estourar o tamanho)
		head = (head + 1) % 1024;

		// Sinaliza ao loop principal que existem dados novos
		rx_flag = 1;

		HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
	}
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI2) {
		ILI9488_Flush_End_DMA(disp);
	}
}

void my_log_cb(lv_log_level_t level, const char * buf)
{
	//logI(buf, strlen(buf));
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, strlen(buf), HAL_MAX_DELAY);
}

void print_runtime_stats(void)
{
    TaskStatus_t *pxArr;
    UBaseType_t n = uxTaskGetNumberOfTasks();
    uint32_t total;

    pxArr = pvPortMalloc(n * sizeof(TaskStatus_t));
    if (pxArr == NULL) return;

    n = uxTaskGetSystemState(pxArr, n, &total);
    uint32_t div = total / 100U;          /* 1% em ticks */

    printf("\n%-16s %10s  %5s\r\n", "Task", "Ticks", "CPU%");
    for (UBaseType_t i = 0; i < n; i++) {
        uint32_t pct = (div > 0) ? (pxArr[i].ulRunTimeCounter / div) : 0;
        printf("%-16s %10lu  %4lu%%\r\n",
               pxArr[i].pcTaskName,
               (unsigned long)pxArr[i].ulRunTimeCounter,
               (unsigned long)pct);
    }
    vPortFree(pxArr);
}
/* USER CODE END Application */

