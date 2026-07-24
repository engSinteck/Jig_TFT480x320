/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
#include "string.h"
#include "../App/src/ILI9488.h"
#include "../App/src/GT911.h"
#include "../App/src/log_cdc.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void my_log_cb(lv_log_level_t level, const char * buf);
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);

GT911_Config_t sampleConfig = {.X_Resolution = 320, .Y_Resolution = 480, .Number_Of_Touch_Support = 1, .ReverseY = true, .ReverseX = false, .SwithX2Y = true, .SoftwareNoiseReduction = false};

static uint8_t buf1[(480 * 10 * 3)] /*__attribute__((section(".tftram")))*/ __attribute__((aligned(32)));
static uint8_t buf2[(480 * 10 * 3)] /*__attribute__((section(".tftram")))*/ __attribute__((aligned(32)));
static lv_display_t * disp;

uint32_t timer_led = 0;
uint32_t timer_lvgl = 0;
static lv_obj_t * Tela_Debug;
static lv_obj_t * img_fundo;
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
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskLVGL */
osThreadId_t TaskLVGLHandle;
const osThreadAttr_t TaskLVGL_attributes = {
  .name = "TaskLVGL",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for MutexLVGL */
osMutexId_t MutexLVGLHandle;
const osMutexAttr_t MutexLVGL_attributes = {
  .name = "MutexLVGL"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTaskLVGL(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

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

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    HAL_GPIO_WritePin(LED_INT_GPIO_Port, LED_INT_Pin, GPIO_PIN_SET); // ou um breakpoint aqui
    while(1);
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
  /* Create the mutex(es) */
  /* creation of MutexLVGL */
  MutexLVGLHandle = osMutexNew(&MutexLVGL_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

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
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	  if(HAL_GetTick() - timer_led > 250) {
		  timer_led = HAL_GetTick();
		  HAL_GPIO_TogglePin(LED_INT_GPIO_Port, LED_INT_Pin);
	  }
	  osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
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
  /* USER CODE BEGIN StartTaskLVGL */
  ILI9488_Init();
  ILI9488_Set_Address(0, 0, ILI9488_SCREEN_WIDTH-1, ILI9488_SCREEN_HEIGHT-1);
  ILI9488_Fill_Screen(0x0000);

  // Init GT911
  GT911_Init(sampleConfig);

  lv_init();

  disp = lv_display_create(480, 320);
  lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB888);
  lv_display_set_buffers(disp, buf1, buf2, 480 * 10 * 3, LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_flush_cb(disp, ILI9488_Flush_DMA);

  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touch_read_cb);
  
#if LV_USE_LOG
  // Log LVGL
  lv_log_register_print_cb(my_log_cb);
#endif

  // Teste Imagem
	Tela_Debug = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Debug, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Debug, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Debug, lv_color_hex(0x000000), 0);

    /* Default size driven by label content */
    //lv_obj_t * button_1 = lv_button_create(Tela_Debug);
    //lv_obj_set_align(button_1, LV_ALIGN_CENTER);

    //lv_obj_t * label_1 = lv_label_create(button_1);
    //lv_obj_set_align(label_1, LV_ALIGN_CENTER);
    //lv_label_set_text(label_1, "Click me");

		img_fundo = lv_img_create(Tela_Debug);
		lv_img_set_src(img_fundo, &AUDIO);
		//  lv_obj_set_width(img_fundo, 480);
		//  lv_obj_set_height(img_fundo, 128);
		  //lv_obj_set_protect(img_fundo, LV_PROTECT_POS);
		  lv_obj_set_pos(img_fundo, 0, 0);
		  //lv_obj_align(img_fundo, LV_ALIGN_CENTER, 0, 0);

	lv_scr_load(Tela_Debug);

  /* Infinite loop */
  for(;;)
  {
	  lv_timer_handler();

	  if(HAL_GetTick() - timer_lvgl > 1000) {
		  timer_lvgl = HAL_GetTick();

		  UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL); 				// dentro da própria TaskLVGL
		  LV_LOG_USER("Stack HWM: %lu words livres", (unsigned long)hwm);
	  }

      osDelay(5);
  }
  /* USER CODE END StartTaskLVGL */
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
	logI(buf, strlen(buf));
}
/* USER CODE END Application */

