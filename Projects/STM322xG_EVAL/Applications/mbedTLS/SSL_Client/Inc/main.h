/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @brief   main application header file. 
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

#ifndef __MAIN_H
#define __MAIN_H

#define USE_DHCP

#include "stm32f2xx_hal.h"
#include "stm322xg_eval.h"
#include "stm322xg_eval_lcd.h"
   
#include "cmsis_os.h"

#ifdef USE_LCD
#include "stm322xg_eval_lcd.h"
#include "stm322xg_eval_sram.h"
#include "lcd_log.h"
#endif

#define SERVER_PORT "4433"
#define SERVER_NAME "10.157.11.50"

#define GET_REQUEST "GET / HTTP/1.0\r\n\r\n"


#ifdef USE_DHCP

#define IP_ADDR0  0
#define IP_ADDR1  0
#define IP_ADDR2  0
#define IP_ADDR3  0

#define GW_ADDR0  0
#define GW_ADDR1  0
#define GW_ADDR2  0
#define GW_ADDR3  0

#define MASK_ADDR0  0
#define MASK_ADDR1  0
#define MASK_ADDR2  0
#define MASK_ADDR3  0

#else

#define IP_ADDR0  10
#define IP_ADDR1  157
#define IP_ADDR2  9
#define IP_ADDR3  133

#define GW_ADDR0  10
#define GW_ADDR1  157
#define GW_ADDR2  9
#define GW_ADDR3  254

#define MASK_ADDR0  255
#define MASK_ADDR1  255
#define MASK_ADDR2  254
#define MASK_ADDR3  0

#endif /* USE_DHCP */
#ifdef MBEDTLS_MEMORY_BUFFER_ALLOC_C
#define MAX_MEM_SIZE 35 * 1024
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

void SSL_Client(void const *argument);
void Error_Handler(void);
void Success_Handler(void);


#endif /*__MAIN_H */
