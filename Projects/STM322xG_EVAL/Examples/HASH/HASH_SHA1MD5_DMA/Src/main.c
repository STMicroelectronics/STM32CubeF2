/**
  ******************************************************************************
  * @file    HASH/HASH_SHA1MD5_DMA/Src/main.c 
  * @author  MCD Application Team
  * @brief   This example provides a short description of HASH digest calculation
  *          using SHA1 and MD5 example.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F2xx_HAL_Examples
  * @{
  */

/** @addtogroup HASH_SHA1MD5_DMA
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* HASH handler declaration */
HASH_HandleTypeDef     HashHandle;

__ALIGN_BEGIN const uint8_t aInput[] __ALIGN_END = "The STM32 F2 series is the result of a perfect symbiosis of the real-time control capabilities of an MCU and the signal processing performance of a DSP, and thus complements the STM32 portfolio with a new class of devices, digital signal controllers (DSC).";

__ALIGN_BEGIN static uint8_t aMD5Digest[16] __ALIGN_END;
__ALIGN_BEGIN static uint8_t aExpectMD5Digest[16] __ALIGN_END = {0x54, 0x80, 0xba, 0xcb, 0xd4, 0x03, 0x22, 0xa7,
                                                                 0xf4, 0xb2, 0xac, 0xac, 0x8a, 0xb5, 0x54, 0xb8};
__ALIGN_BEGIN static uint8_t aSHA1Digest[20] __ALIGN_END;
__ALIGN_BEGIN static uint8_t aExpectSHA1Digest[20] __ALIGN_END = {0x66, 0x1a, 0x32, 0xbb, 0x48, 0xa3, 0xda, 0x46,
                                                                  0x80, 0xee, 0x2d, 0x58, 0xf3, 0xd2, 0x82, 0x5b,
                                                                  0x25, 0xb4, 0x3c, 0x5f};

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F2xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();
  
  /* Configure the system clock to 120 MHz */
  SystemClock_Config();
  
  /* Configure LED1, LED3 and LED4 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  
  /****************************************************************************/
  /******************************** SHA1 **************************************/
  /****************************************************************************/
  HAL_HASH_DeInit(&HashHandle);
  HashHandle.Init.DataType = HASH_DATATYPE_8B;
  
  if(HAL_HASH_Init(&HashHandle) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Start HASH computation using DMA transfer */
  if (HAL_HASH_SHA1_Start_DMA(&HashHandle, (uint8_t*)aInput, strlen((char const*)aInput)) != HAL_OK)
  {
    Error_Handler();
  }

  /* Get the computed digest value */
  if (HAL_HASH_SHA1_Finish(&HashHandle, aSHA1Digest, 0xFF) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Compare computed digest with expected one */
  if(memcmp(aSHA1Digest, aExpectSHA1Digest, sizeof(aExpectSHA1Digest)/sizeof(aExpectSHA1Digest[0])) != 0)
  {
    Error_Handler();
  }
  else
  {
    BSP_LED_On(LED1);
  }
  
  /****************************************************************************/
  /******************************** MD5 ***************************************/
  /****************************************************************************/
  HAL_HASH_DeInit(&HashHandle);
  HashHandle.Init.DataType = HASH_DATATYPE_8B;
  
  if(HAL_HASH_Init(&HashHandle) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Start HASH computation using DMA transfer */
  if (HAL_HASH_MD5_Start_DMA(&HashHandle, (uint8_t*)aInput, strlen((char const*)aInput)) != HAL_OK)
  {
    Error_Handler();
  }

  /* Get the computed digest value */
  if (HAL_HASH_MD5_Finish(&HashHandle, aMD5Digest, 0xFF) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Compare computed digest with expected one */
  if(memcmp(aMD5Digest, aExpectMD5Digest, sizeof(aExpectMD5Digest)/sizeof(aExpectMD5Digest[0])) != 0)
  {
    Error_Handler();
  }
  else
  {
    BSP_LED_On(LED4);
  }
  while(1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 120000000
  *            HCLK(Hz)                       = 120000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 240
  *            PLL_P                          = 2
  *            PLL_Q                          = 5
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
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

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 
