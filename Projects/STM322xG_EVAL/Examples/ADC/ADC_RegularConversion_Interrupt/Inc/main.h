/**
  ******************************************************************************
  * @file    ADC/ADC_RegularConversion_Interrupt/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"
#include "stm322xg_eval.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor ADCx instance used and associated 
   resources */
/* Definition for ADCx clock resources */
#define ADCx_INSTANCE                     ADC3
#define ADCx_CLOCK_ENABLE()               __HAL_RCC_ADC3_CLK_ENABLE();
#define ADCx_CHANNEL_GPIO_CLOCK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE()
     
#define ADCx_FORCE_RESET()                __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()              __HAL_RCC_ADC_RELEASE_RESET()

/* Definition for ADCx Channel Pin */
#define ADCx_CHANNEL_PIN                  GPIO_PIN_9
#define ADCx_CHANNEL_GPIO_PORT            GPIOF 

/* Definition for ADCx's Channel */
#define ADCx_CHANNEL                      ADC_CHANNEL_7

/* Definition for ADCx's NVIC */
#define ADCx_IRQn                         ADC_IRQn

/* Exported macro ------------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */


#endif /* __MAIN_H */
