/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PE1   ------> FMC_NBL1
     PE0   ------> FMC_NBL0
     PG15   ------> FMC_SDNCAS
     PG12   ------> LTDC_B4
     PG10   ------> LTDC_G3
     PD0   ------> FMC_D2_DA2
     PI7   ------> LTDC_B7
     PI6   ------> LTDC_B6
     PI5   ------> LTDC_B5
     PD1   ------> FMC_D3_DA3
     PI2   ------> LTDC_G7
     PI9   ------> LTDC_VSYNC
     PH15   ------> LTDC_G4
     PI1   ------> LTDC_G6
     PC14-OSC32_IN (OSC32_IN)   ------> RCC_OSC32_IN
     PF0   ------> FMC_A0
     PI10   ------> LTDC_HSYNC
     PH13   ------> LTDC_G2
     PI0   ------> LTDC_G5
     PC15-OSC32_OUT (OSC32_OUT)   ------> RCC_OSC32_OUT
     PH2   ------> FMC_SDCKE0
     PA8   ------> LTDC_B3
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
     PH3   ------> FMC_SDNE0
     PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
     PF2   ------> FMC_A2
     PF1   ------> FMC_A1
     PG8   ------> FMC_SDCLK
     PF3   ------> FMC_A3
     PF4   ------> FMC_A4
     PH5   ------> FMC_SDNWE
     PG7   ------> LTDC_CLK
     PG6   ------> LTDC_R7
     PF5   ------> FMC_A5
     PH12   ------> LTDC_R6
     PG5   ------> FMC_A15_BA1
     PG4   ------> FMC_A14_BA0
     PF10   ------> LTDC_DE
     PH11   ------> LTDC_R5
     PH10   ------> LTDC_R4
     PD15   ------> FMC_D1_DA1
     PG2   ------> FMC_A12
     PG1   ------> FMC_A11
     PH9   ------> LTDC_R3
     PD14   ------> FMC_D0_DA0
     PD13   ------> I2C4_SDA
     PF13   ------> FMC_A7
     PG0   ------> FMC_A10
     PE13   ------> FMC_D10_DA10
     PD12   ------> I2C4_SCL
     PD10   ------> FMC_D15_DA15
     PF12   ------> FMC_A6
     PF15   ------> FMC_A9
     PE8   ------> FMC_D5_DA5
     PE9   ------> FMC_D6_DA6
     PE11   ------> FMC_D8_DA8
     PE14   ------> FMC_D11_DA11
     PD9   ------> FMC_D14_DA14
     PD8   ------> FMC_D13_DA13
     PF11   ------> FMC_SDNRAS
     PF14   ------> FMC_A8
     PE7   ------> FMC_D4_DA4
     PE10   ------> FMC_D7_DA7
     PE12   ------> FMC_D9_DA9
     PE15   ------> FMC_D12_DA12
*/
void MX_GPIO_Init(void)
{

 GPIO_InitTypeDef GPIO_InitStruct = {0};

 /* GPIO Ports Clock Enable */
 __HAL_RCC_GPIOE_CLK_ENABLE();
 __HAL_RCC_GPIOB_CLK_ENABLE();
 __HAL_RCC_GPIOG_CLK_ENABLE();
 __HAL_RCC_GPIOD_CLK_ENABLE();
 __HAL_RCC_GPIOI_CLK_ENABLE();
 __HAL_RCC_GPIOC_CLK_ENABLE();
 __HAL_RCC_GPIOH_CLK_ENABLE();
 __HAL_RCC_GPIOA_CLK_ENABLE();
 __HAL_RCC_GPIOF_CLK_ENABLE();
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(LCD_DISP_GPIO_Port, LCD_DISP_Pin, GPIO_PIN_SET);
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_SET);
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
//
//  /*Configure GPIO pins : PE1 PE0 PE13 PE8
//                           PE9 PE11 PE14 PE7
//                           PE10 PE12 PE15 */
//  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_13|GPIO_PIN_8
//                          |GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_7
//                          |GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_15;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
//  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PG15 PG8 PG5 PG4
//                           PG2 PG1 PG0 */
//  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_5|GPIO_PIN_4
//                          |GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
//  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PG12 PG10 */
//  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_10;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
//  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PD0 PD1 PD15 PD14
//                           PD10 PD9 PD8 */
//  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_15|GPIO_PIN_14
//                          |GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
//  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PI7 PI6 PI5 PI2
//                           PI9 PI1 PI10 PI0 */
//  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_2
//                          |GPIO_PIN_9|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_0;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
//  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = LED_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PH15 PH13 PH12 PH11
//                           PH10 PH9 */
//  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_11
//                          |GPIO_PIN_10|GPIO_PIN_9;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
//  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PF0 PF2 PF1 PF3
//                           PF4 PF5 PF13 PF12
//                           PF15 PF11 PF14 */
//  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_3
//                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_12
//                          |GPIO_PIN_15|GPIO_PIN_11|GPIO_PIN_14;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
//  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PH2 PH3 PH5 */
//  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
//  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : PA8 */
//  GPIO_InitStruct.Pin = GPIO_PIN_8;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF13_LTDC;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PG7 PG6 */
//  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
//  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = LCD_DISP_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(LCD_DISP_GPIO_Port, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : PF10 */
//  GPIO_InitStruct.Pin = GPIO_PIN_10;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
//  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = TP_INT_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  HAL_GPIO_Init(TP_INT_GPIO_Port, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = TP_RST_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(TP_RST_GPIO_Port, &GPIO_InitStruct);
//
 /*Configure GPIO pin : PtPin */
 GPIO_InitStruct.Pin = LCD_BL_Pin;
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
 GPIO_InitStruct.Pull = GPIO_PULLUP;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
 HAL_GPIO_Init(LCD_BL_GPIO_Port, &GPIO_InitStruct);
//
//  /*Configure GPIO pins : PD13 PD12 */
//  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_12;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF4_I2C4;
//  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = TP_INTH7_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(TP_INTH7_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
