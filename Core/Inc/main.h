/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_INPUT_Pin GPIO_PIN_13
#define KEY_INPUT_GPIO_Port GPIOC
#define TFT_RST_Pin GPIO_PIN_0
#define TFT_RST_GPIO_Port GPIOC
#define TP_RST_Pin GPIO_PIN_1
#define TP_RST_GPIO_Port GPIOC
#define LED_INT_Pin GPIO_PIN_2
#define LED_INT_GPIO_Port GPIOB
#define SPI2_NSS_Pin GPIO_PIN_12
#define SPI2_NSS_GPIO_Port GPIOB
#define TFT_DC_Pin GPIO_PIN_6
#define TFT_DC_GPIO_Port GPIOC
#define TFT_BACK_Pin GPIO_PIN_7
#define TFT_BACK_GPIO_Port GPIOC
#define SD_IN_Pin GPIO_PIN_8
#define SD_IN_GPIO_Port GPIOA
#define TP_IRQ_Pin GPIO_PIN_8
#define TP_IRQ_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define QSPI_ASSET  __attribute__((section(".qspi_data")))
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
