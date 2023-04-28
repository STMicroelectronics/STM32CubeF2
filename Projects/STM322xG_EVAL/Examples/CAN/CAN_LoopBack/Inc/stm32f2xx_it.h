/**
  ******************************************************************************
  * @file    CAN/CAN_LoopBack/Inc/stm32f2xx_it.h 
  * @author  MCD Application Team
  * @brief   This file contains the headers of the interrupt handlers.
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
#ifndef __STM32F2xx_IT_H
#define __STM32F2xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
void CAN1_RX0_IRQHandler(void);
void CAN2_RX0_IRQHandler(void);
void CAN1_RX1_IRQHandler(void);
void CAN2_RX1_IRQHandler(void);
void CAN1_TX_IRQHandler(void);
void CAN2_TX_IRQHandler(void);
#ifdef __cplusplus
}
#endif

#endif /* __STM32F2xx_IT_H */
