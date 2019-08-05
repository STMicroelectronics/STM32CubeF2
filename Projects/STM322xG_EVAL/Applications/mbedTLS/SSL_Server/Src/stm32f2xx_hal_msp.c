/**
  ******************************************************************************
  * @file    stm32f2xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  *         
  @verbatim
  ===============================================================================
  ##### How to use this driver #####
  ===============================================================================
  [..]
  This file is generated automatically by STM32CubeMX and eventually modified 
  by the user
  
  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f2xx_hal.h"

/** @addtogroup STM32F2xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
  modified by the user
  */
  /* Enable UART 4 clock  */
  __HAL_RCC_UART4_CLK_ENABLE();
  
  /* RNG Periph clock enable */
  __HAL_RCC_RNG_CLK_ENABLE();
  
#ifdef USE_STM32F2XX_HW_CRYPTO   
  /* Enable CRYP clock */
  __HAL_RCC_CRYP_CLK_ENABLE();
    
  /* Enable Hash clock */
  __HAL_RCC_HASH_CLK_ENABLE();

#endif  /* USE_STM32F2XX_HW_CRYPTO */
  
}

#ifdef USE_STM32F2XX_HW_CRYPTO  
/**
  * @brief  DeInitializes the HASH MSP.
  * @param  None  
  * @retval None
  */
void HAL_HASH_MspDeInit(HASH_HandleTypeDef *hhash)
{
  /* Force the HASH Periheral Clock Reset */  
  __HAL_RCC_HASH_FORCE_RESET(); 
  
  /* Release the HASH Periheral Clock Reset */  
  __HAL_RCC_HASH_RELEASE_RESET();
}

/**
  * @brief  DeInitializes the CRYP MSP.
  * @param  None  
  * @retval None
  */
void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef *hcryp)
{
  /* Force the CRYP Periheral Clock Reset */  
  __HAL_RCC_CRYP_FORCE_RESET(); 
  
  /* Release the CRYP Periheral Clock Reset */  
  __HAL_RCC_CRYP_RELEASE_RESET();
}
#endif  /* USE_STM32F2XX_HW_CRYPTO */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
