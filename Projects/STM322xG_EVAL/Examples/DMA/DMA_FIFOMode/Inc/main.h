/**
  ******************************************************************************
  * @file    DMA/DMA_FIFOMode/Inc/main.h 
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
/* DMA Stream parameters definitions. You can modify these parameters to select
   a different DMA Stream and/or channel.
   But note that only DMA2 Streams are capable of Memory to Memory transfers. */
#define DMA_STREAM               DMA2_Stream0
#define DMA_CHANNEL              DMA_CHANNEL_0 
#define DMA_STREAM_IRQ           DMA2_Stream0_IRQn
#define DMA_STREAM_IRQHANDLER    DMA2_Stream0_IRQHandler

#define BUFFER_SIZE              32

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */
