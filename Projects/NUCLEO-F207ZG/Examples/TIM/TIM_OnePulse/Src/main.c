/**
  ******************************************************************************
  * @file    TIM/TIM_OnePulse/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use TIM HAL API to generate
  *          a one pulse signal
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

/** @addtogroup TIM_OnePulse
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Timer handler declaration */
TIM_HandleTypeDef    TimHandle;

/* Prescaler value declaration*/
uint32_t uwPrescalerValue = 0;

/* Timer One Pulse Configuration Structure declaration */
TIM_OnePulse_InitTypeDef sConfig;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
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

  /*##1 Configure the system clock to 120 MHz */
  SystemClock_Config();

  /* Configure LED3 */
  BSP_LED_Init(LED3);

  /*##2 Compute the prescaler value, to have TIM3Freq = 20000000 Hz
   * TIM3 input clock is set to APB1 clock (PCLK1), 
   * if (APB1 prescaler = 1) x1 else x2
   * prescaler is 4.
   * TIM1CLK = (HCLK/4) x2 = HCLK / 2
   * TIM3CLK = SystemCoreClock / 2
   *
   * Prescaler = (TIM3CLK /TIM3 counter clock) - 1
   *
   * The prescaler value is computed in order to have TIM3 counter clock
   * set at 20000000 Hz.
   */

  uwPrescalerValue = (uint32_t)((SystemCoreClock / 2) / 20000000) - 1;

  /*##-3- Configure the TIM peripheral #######################################
   *
   *-The external signal is connected to TIM3_CH2 pin (PB.05),
   * and a rising edge on this input is used to trigger the Timer.
   *
   *-The One Pulse signal is output on TIM3_CH1 (PB.04).
   *
   * The delay value is fixed to:
   * - Delay =  CCR1/TIM3 counter clock
   *          = 16383 / 20000000 [sec]
   *
   * The pulse value is fixed to :
   * - Pulse value = (TIM_Period - TIM_Pulse)/TIM3 counter clock
   *               = (65535 - 16383) / 20000000 [sec]
   *
   * ------------------------------------------------------------------------ */


  TimHandle.Instance = TIMx;

  TimHandle.Init.Period            = 0xFFFF;
  TimHandle.Init.Prescaler         = uwPrescalerValue;
  TimHandle.Init.ClockDivision     = 0;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TimHandle.Init.RepetitionCounter = 0;
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  if (HAL_TIM_OnePulse_Init(&TimHandle, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Configure the Channel 1 in One Pulse mode ##########################*/
  sConfig.OCMode       = TIM_OCMODE_PWM2;
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
  sConfig.Pulse        = 16383;
  sConfig.ICPolarity   = TIM_ICPOLARITY_RISING;
  sConfig.ICSelection  = TIM_ICSELECTION_DIRECTTI;
  sConfig.ICFilter     = 0;
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;

  if (HAL_TIM_OnePulse_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }

  /*##-4- Start the One Pulse mode #######################################
   *
   * * The one pulse waveform can be displayed using an oscilloscope and it looks
   * like this.
   *
   *                              ____
   *                              |   |
   * CH2 _________________________|   |_________________________________________
   *
   *                                            ___________________________
   *                                           |                           |
   * CH1 ______________________________________|                           |____
   *                             <---Delay----><------Pulse--------------->
   *
   *
   *
   *
   *
   */

  if (HAL_TIM_OnePulse_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }

  while (1)
  {
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
  while (1)
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
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 240
  *            PLL_P                          = 2
  *            PLL_Q                          = 5
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3);
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
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
