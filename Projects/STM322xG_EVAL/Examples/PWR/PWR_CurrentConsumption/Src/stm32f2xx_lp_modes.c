/**
  ******************************************************************************
  * @file    PWR/PWR_CurrentConsumption/stm32f2xx_lp_modes.c 
  * @author  MCD Application Team
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the STM32F2xx Low Power Modes:
  *           - Sleep Mode
  *           - STOP mode with RTC
  *           - STANDBY mode without RTC and BKPSRAM
  *           - STANDBY mode with RTC
  *           - STANDBY mode with RTC and BKPSRAM
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

/** @addtogroup PWR_CurrentConsumption
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* RTC handler declaration */
RTC_HandleTypeDef RTCHandle;

/* Private function prototypes -----------------------------------------------*/
static void SYSCLKConfig_STOP(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the system to enter Sleep mode for
  *         current consumption measurement purpose.
  *         Sleep Mode
  *         ==========  
  *            - System Running at PLL (120MHz)
  *            - Flash 5 wait state
  *            - Instruction and Data caches ON
  *            - Prefetch ON   
  *            - Code running from Internal FLASH
  *            - All peripherals disabled.
  *            - Wakeup using EXTI Line (Key Button)
  * @param  None
  * @retval None
  */
void SleepMode_Measure(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Configure all GPIO as analog to reduce current consumption on non used IOs */
  /* Enable GPIOs clock */
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();
   __HAL_RCC_GPIOE_CLK_ENABLE();
   __HAL_RCC_GPIOF_CLK_ENABLE();
   __HAL_RCC_GPIOG_CLK_ENABLE();
   __HAL_RCC_GPIOH_CLK_ENABLE();
   __HAL_RCC_GPIOI_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Pin = GPIO_PIN_All;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct); 
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Disable GPIOs clock */
   __HAL_RCC_GPIOA_CLK_DISABLE();
   __HAL_RCC_GPIOB_CLK_DISABLE();
   __HAL_RCC_GPIOC_CLK_DISABLE();
   __HAL_RCC_GPIOD_CLK_DISABLE();
   __HAL_RCC_GPIOE_CLK_DISABLE();
   __HAL_RCC_GPIOF_CLK_DISABLE();
   __HAL_RCC_GPIOG_CLK_DISABLE();
   __HAL_RCC_GPIOH_CLK_DISABLE();
   __HAL_RCC_GPIOI_CLK_DISABLE();
   
  /* Configure Key Button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

  /* Suspend Tick increment to prevent wakeup by Systick interrupt. 
     Otherwise the Systick interrupt will wake up the device within 1ms (HAL time base) */
  HAL_SuspendTick();

  /* Request to enter SLEEP mode */
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
  
  /* Resume Tick interrupt if disabled prior to sleep mode entry */
  HAL_ResumeTick();

  /* Initialize LED4 */
  BSP_LED_Init(LED4);
  
  /* Turn LED4 On */
  BSP_LED_On(LED4);
  
  /* Inserted Delay: 2s */
  HAL_Delay(2000);  
}

/**
  * @brief  This function configures the system to enter Stop mode with RTC 
  *         clocked by LSE or LSI  for current consumption measurement purpose.
  *         STOP Mode with RTC clocked by LSE/LSI
  *         =====================================   
  *           - RTC Clocked by LSE or LSI
  *           - Regulator in LP mode
  *           - HSI, HSE OFF and LSI OFF if not used as RTC Clock source
  *           - No IWDG
  *           - FLASH in deep power down mode
  *           - Automatic Wakeup using RTC clocked by LSE/LSI (~20s)
  * @param  None
  * @retval None
  */
void StopMode_Measure(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Configure all GPIO as analog to reduce current consumption on non used IOs */
  /* Enable GPIOs clock */
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();
   __HAL_RCC_GPIOE_CLK_ENABLE();
   __HAL_RCC_GPIOF_CLK_ENABLE();
   __HAL_RCC_GPIOG_CLK_ENABLE();
   __HAL_RCC_GPIOH_CLK_ENABLE();
   __HAL_RCC_GPIOI_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Pin = GPIO_PIN_All;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct); 
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Disable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();
  __HAL_RCC_GPIOD_CLK_DISABLE();
  __HAL_RCC_GPIOE_CLK_DISABLE();
  __HAL_RCC_GPIOF_CLK_DISABLE();
  __HAL_RCC_GPIOG_CLK_DISABLE();
  __HAL_RCC_GPIOH_CLK_DISABLE();
  __HAL_RCC_GPIOI_CLK_DISABLE();
 
  RTCHandle.Instance = RTC;
    
  /* Configure RTC prescaler and RTC data registers as follow:
  - Hour Format = Format 24
  - Asynch Prediv = Value according to source clock
  - Synch Prediv = Value according to source clock
  - OutPut = Output Disable
  - OutPutPolarity = High Polarity
  - OutPutType = Open Drain */ 
  RTCHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RTCHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
  RTCHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
  RTCHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RTCHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RTCHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  
  if(HAL_RTC_Init(&RTCHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }

  /*## Configure the Wake up timer ###########################################*/
  /*  RTC Wakeup Interrupt Generation:
      Wakeup Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE or LSI))
      Wakeup Time = Wakeup Time Base * WakeUpCounter 
                  = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE or LSI)) * WakeUpCounter
      ==> WakeUpCounter = Wakeup Time / Wakeup Time Base

      To configure the wake up timer to 20s the WakeUpCounter is set to 0xA017:
        RTC_WAKEUPCLOCK_RTCCLK_DIV = RTCCLK_Div16 = 16 
        Wakeup Time Base = 16 /(~32.768KHz) = ~0,488 ms
        Wakeup Time = ~20s = 0,488ms  * WakeUpCounter
        ==> WakeUpCounter = ~20s/0,488ms = 40983 = 0xA017 */
  /* Disable Wake-up timer */
  HAL_RTCEx_DeactivateWakeUpTimer(&RTCHandle);

  HAL_RTCEx_SetWakeUpTimer_IT(&RTCHandle, 0xA017, RTC_WAKEUPCLOCK_RTCCLK_DIV16);

  /* FLASH Deep Power Down Mode enabled */
  HAL_PWREx_EnableFlashPowerDown();

  /* Enter Stop Mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

  /* Configures system clock after wake-up from STOP: enable HSE, PLL and select 
  PLL as system clock source (HSE and PLL are disabled in STOP mode) */
  SYSCLKConfig_STOP();
  
  /* Disable Wake-up timer */
  HAL_RTCEx_DeactivateWakeUpTimer(&RTCHandle);

  /* Initialize LED4 */
  BSP_LED_Init(LED4);

  /* Turn LED4 On */
  BSP_LED_On(LED4);
}

/**
  * @brief  This function configures the system to enter Standby mode for
  *         current consumption measurement purpose.
  *         STANDBY Mode
  *         ============
  *           - Backup SRAM and RTC OFF
  *           - IWDG and LSI OFF
  *           - Wakeup using WakeUp Pin (PA.00)
  * @param  None
  * @retval None
  */
void StandbyMode_Measure(void)
{
  /* Enable Power Clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* Allow access to Backup */
  HAL_PWR_EnableBkUpAccess();

  /* Reset RTC Domain */
  __HAL_RCC_BACKUPRESET_FORCE();
  __HAL_RCC_BACKUPRESET_RELEASE();
  
  /* Disable all used wakeup sources: Pin1(PA.0) */
  HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
  
  /* Clear all related wakeup flags */
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  
  /* Re-enable all used wakeup sources: Pin1(PA.0) */
  HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Request to enter STANDBY mode  */
  HAL_PWR_EnterSTANDBYMode();
}

/**
  * @brief  This function configures the system to enter Standby mode with RTC 
  *         clocked by LSE or LSI for current consumption measurement purpose.
  *         STANDBY Mode with RTC clocked by LSE/LSI
  *         ========================================
  *           - RTC Clocked by LSE/LSI
  *           - IWDG OFF
  *           - Backup SRAM OFF
  *           - Automatic Wakeup using RTC clocked by LSE/LSI (after ~20s)
  * @param  None
  * @retval None
  */
void StandbyRTCMode_Measure(void)
{
  RTCHandle.Instance = RTC;  
  /* Configure RTC prescaler and RTC data registers as follow:
  - Hour Format = Format 24
  - Asynch Prediv = Value according to source clock
  - Synch Prediv = Value according to source clock
  - OutPut = Output Disable
  - OutPutPolarity = High Polarity
  - OutPutType = Open Drain */ 
  RTCHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RTCHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
  RTCHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
  RTCHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RTCHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RTCHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  
  if(HAL_RTC_Init(&RTCHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /*## Configure the Wake up timer ###########################################*/
  /*  RTC Wakeup Interrupt Generation:
      Wakeup Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE or LSI))
      Wakeup Time = Wakeup Time Base * WakeUpCounter 
                  = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE or LSI)) * WakeUpCounter
      ==> WakeUpCounter = Wakeup Time / Wakeup Time Base

      To configure the wake up timer to 20s the WakeUpCounter is set to 0xA017:
  RTC_WAKEUPCLOCK_RTCCLK_DIV = RTCCLK_Div16 = 16 
  Wakeup Time Base = 16 /(~32.768KHz) = ~0,488 ms
  Wakeup Time = ~20s = 0,488ms  * WakeUpCounter
  ==> WakeUpCounter = ~20s/0,488ms = 40983 = 0xA017 */
  /* Disable Wake-up timer */
  HAL_RTCEx_DeactivateWakeUpTimer(&RTCHandle);

  /*## Clear all related wakeup flags ########################################*/
  /* Clear PWR wake up Flag */
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  
  /* Clear RTC Wake Up timer Flag */
  __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&RTCHandle, RTC_FLAG_WUTF);
  
  /*## Setting the Wake up time ##############################################*/
  HAL_RTCEx_SetWakeUpTimer_IT(&RTCHandle, 0xA017, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
  
  /*## Enter the Standby mode ################################################*/
  /* Request to enter STANDBY mode  */
  HAL_PWR_EnterSTANDBYMode(); 
}

/**
  * @brief  This function configures the system to enter Standby mode with RTC 
  *         clocked by LSE or LSI and with Backup SRAM ON for current consumption 
  *         measurement purpose.
  *         STANDBY Mode with RTC clocked by LSE/LSI and BKPSRAM
  *         ====================================================
  *           - RTC Clocked by LSE or LSI
  *           - Backup SRAM ON
  *           - IWDG OFF
  *           - Automatic Wakeup using RTC clocked by LSE/LSI (after ~20s)
  * @param  None
  * @retval None
  */
void StandbyRTCBKPSRAMMode_Measure(void)
{
  /* Configure RTC prescaler and RTC data registers as follow:
  - Hour Format = Format 24
  - Asynch Prediv = Value according to source clock
  - Synch Prediv = Value according to source clock
  - OutPut = Output Disable
  - OutPutPolarity = High Polarity
  - OutPutType = Open Drain */ 
  RTCHandle.Instance = RTC;
  RTCHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RTCHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
  RTCHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
  RTCHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RTCHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RTCHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

  if(HAL_RTC_Init(&RTCHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }

  /*## Configure the Wake up timer ###########################################*/
  /*  RTC Wakeup Interrupt Generation:
      Wakeup Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE or LSI))
      Wakeup Time = Wakeup Time Base * WakeUpCounter 
                  = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE or LSI)) * WakeUpCounter
      ==> WakeUpCounter = Wakeup Time / Wakeup Time Base

      To configure the wake up timer to 20s the WakeUpCounter is set to 0xA017:
        RTC_WAKEUPCLOCK_RTCCLK_DIV = RTCCLK_Div16 = 16 
        Wakeup Time Base = 16 /(~32.768KHz) = ~0,488 ms
        Wakeup Time = ~20s = 0,488ms  * WakeUpCounter
        ==> WakeUpCounter = ~20s/0,488ms = 40983 = 0xA017 */
  /* Disable Wake-up timer */
  HAL_RTCEx_DeactivateWakeUpTimer(&RTCHandle);
  
  /*## Clear all related wakeup flags ########################################*/
  /* Clear PWR wake up Flag */
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  
  /* Clear RTC Wake Up timer Flag */
  __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&RTCHandle, RTC_FLAG_WUTF);
  
  /*## Setting the Wake up time ##############################################*/
  HAL_RTCEx_SetWakeUpTimer_IT(&RTCHandle, 0xA017, RTC_WAKEUPCLOCK_RTCCLK_DIV16);

  /* Enable BKPRAM Clock */
  __HAL_RCC_BKPSRAM_CLK_ENABLE();

  /* Enable the Backup SRAM low power Regulator */
  HAL_PWREx_EnableBkUpReg();

  /*## Enter the Standby mode ################################################*/
  /* Request to enter STANDBY mode  */
  HAL_PWR_EnterSTANDBYMode();
}

/**
  * @brief  Configures system clock after wake-up from STOP: enable HSE, PLL
  *         and select PLL as system clock source.
  * @param  None
  * @retval None
  */
static void SYSCLKConfig_STOP(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  uint32_t pFLatency = 0;

  /* Get the Oscillators configuration according to the internal RCC registers */
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  /* After wake-up from STOP reconfigure the system clock: Enable HSE and PLL */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Get the Clocks configuration according to the internal RCC registers */
  HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &pFLatency);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, pFLatency) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @}
  */ 

/**
  * @}
  */ 
