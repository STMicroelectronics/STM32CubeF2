/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @brief   Main program 
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

#include <string.h>
#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"

/* FreeRTOS buffer for static allocation */

#if (configAPPLICATION_ALLOCATED_HEAP == 1)
uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
#endif

static void SystemClock_Config(void);
static void RNG_Init(void);
static void MainThread(void const * argument);

RNG_HandleTypeDef RngHandle;

int main()
{
#ifdef USE_LCD
  uint8_t  sram_status = SRAM_OK;
#endif

  HAL_Init();

  /* Configure the system clock to 178 MHz */
  SystemClock_Config();

  /* Initialize BSP Led for LED1 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED3);

  RNG_Init();

#ifdef USE_LCD

  /* Initialize the LCD */
 /* Initialize the SDRAM */
  sram_status = BSP_SRAM_Init();
  if(sram_status != SRAM_OK)
  {
          Error_Handler();
  }

  /* Initialize LCD in landscape mode in DSI mode video burst */
  /* Initialize and start the LCD display in mode 'lcd_mode'
   *  Using LCD_FB_START_ADDRESS as frame buffer displayed contents.
   *  This buffer is modified by the BSP (draw fonts, objects depending on BSP calls).
   */

  /* Set Portrait orientation if needed, by default orientation is set to
     Landscape */

  /* Initialize DSI LCD */
  BSP_LCD_Init();

  LCD_LOG_Init();
  LCD_LOG_SetHeader((uint8_t *)("SSL Client Application"));

#endif /* USE_LCD */

   /* Init thread */
  osThreadDef(Start, MainThread, osPriorityAboveNormal, 0, configMINIMAL_STACK_SIZE * 2);
  osThreadCreate (osThread(Start), NULL);
  
  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */
  Error_Handler();

  
}

/**
  * @brief  Start Thread 
  * @param  argument not used
  * @retval None
  */
static void MainThread(void const * argument)
{ 
  UNUSED(argument);
#ifdef USE_LCD
  LCD_UsrLog("\r\n Starting Main Thread...\n");
#endif

  /* Start SSL Client task : Connect to SSL server and provide the SSL handshake protocol */
  osThreadDef(Client, SSL_Client, osPriorityHigh, 0, configMINIMAL_STACK_SIZE * 20);
  osThreadCreate (osThread(Client), NULL);

  for( ;; )
  {
    /* Delete the start Thread */ 
    osThreadTerminate(NULL);
  }
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

           
/* RNG init function */
static void RNG_Init(void)
{
  RngHandle.Instance = RNG;
 /* DeInitialize the RNG peripheral */
  if (HAL_RNG_DeInit(&RngHandle) != HAL_OK)
  {
    /* DeInitialization Error */
    Error_Handler();
  }    

  /* Initialize the RNG peripheral */
  if (HAL_RNG_Init(&RngHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

void Error_Handler(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED3);
    osDelay(100);
  }
}

void Success_Handler(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED1);
    osDelay(200);
  }
}
