/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BspQspiBoot.h"
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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC


#define QSPI_CLK_ENABLE()               __HAL_RCC_QSPI_CLK_ENABLE()
#define QSPI_CLK_DISABLE()              __HAL_RCC_QSPI_CLK_DISABLE()
#define QSPI_CS_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_CLK_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_BK1_D0_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()
#define QSPI_BK1_D1_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()
#define QSPI_BK1_D2_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()
#define QSPI_BK1_D3_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()

#define QSPI_MDMA_CLK_ENABLE()          __HAL_RCC_MDMA_CLK_ENABLE()
#define QSPI_FORCE_RESET()              __HAL_RCC_QSPI_FORCE_RESET()
#define QSPI_RELEASE_RESET()            __HAL_RCC_QSPI_RELEASE_RESET()

#define QSPI_CS_PIN                     GPIO_PIN_6
#define QSPI_CS_GPIO_PORT               GPIOB
#define QSPI_CS_GPIO_AF                 GPIO_AF10_QUADSPI

#define QSPI_CLK_PIN                    GPIO_PIN_2
#define QSPI_CLK_GPIO_PORT              GPIOB
#define QSPI_CLK_GPIO_AF                GPIO_AF9_QUADSPI

#define QSPI_BK1_D0_PIN                 GPIO_PIN_8
#define QSPI_BK1_D0_GPIO_PORT           GPIOF
#define QSPI_BK1_D0_GPIO_AF             GPIO_AF10_QUADSPI

#define QSPI_BK1_D1_PIN                 GPIO_PIN_9
#define QSPI_BK1_D1_GPIO_PORT           GPIOF
#define QSPI_BK1_D1_GPIO_AF             GPIO_AF10_QUADSPI

#define QSPI_BK1_D2_PIN                 GPIO_PIN_7
#define QSPI_BK1_D2_GPIO_PORT           GPIOF
#define QSPI_BK1_D2_GPIO_AF             GPIO_AF9_QUADSPI

#define QSPI_BK1_D3_PIN                 GPIO_PIN_6
#define QSPI_BK1_D3_GPIO_PORT           GPIOF
#define QSPI_BK1_D3_GPIO_AF             GPIO_AF9_QUADSPI

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
