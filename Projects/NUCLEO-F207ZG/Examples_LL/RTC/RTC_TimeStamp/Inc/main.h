/**
  ******************************************************************************
  * @file    Examples_LL/RTC/RTC_TimeStamp/Inc/main.h
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
#include "stm32f2xx_ll_bus.h"
#include "stm32f2xx_ll_rcc.h"
#include "stm32f2xx_ll_system.h"
#include "stm32f2xx_ll_utils.h"
#include "stm32f2xx_ll_gpio.h"
#include "stm32f2xx_ll_pwr.h"
#include "stm32f2xx_ll_exti.h"
#include "stm32f2xx_ll_rtc.h"
#include "stm32f2xx_ll_cortex.h"
#include <stdio.h>
#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Define used to enable time-out management*/
#define USE_TIMEOUT       0

#define RTC_ERROR_NONE    0
#define RTC_ERROR_TIMEOUT 1

/**
  * @brief LED1 
  */

#define LED1_PIN                           LL_GPIO_PIN_0
#define LED1_GPIO_PORT                     GPIOB
#define LED1_GPIO_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)

/**
  * @brief Toggle periods for various blinking modes
  */

#define LED_BLINK_FAST  200
#define LED_BLINK_SLOW 500
#define LED_BLINK_ERROR 1000


/**
  * @brief Key push-button
  */
#define USER_BUTTON_PIN                         LL_GPIO_PIN_13
#define USER_BUTTON_GPIO_PORT                   GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC)   

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
/* IRQ Handler treatment.  */
void TimeStampEvent_Callback(void);

#endif /* __MAIN_H */
