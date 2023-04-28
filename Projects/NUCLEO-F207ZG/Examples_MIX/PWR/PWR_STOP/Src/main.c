/**
  ******************************************************************************
  * @file    Examples_MIX/PWR/PWR_STOP/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use STM32F2xx PWR HAL API to enter
  *          and exit the STOP with Low power regulator mode.
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

/** @addtogroup PWR_STOP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LED_TOGGLE_DELAY         100
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
/* Private function prototypes -----------------------------------------------*/
__STATIC_INLINE void SystemClock_Config(void);
__STATIC_INLINE void SYSCLKConfig_FromSTOP(void);
__STATIC_INLINE void SystemPower_Config(void);
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

  /* Configure LED1, LED2 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);

  /* Configure the system clock to 120 MHz */
  SystemClock_Config();

  /* Key push-button (EXTI Line13) will be used to wakeup the system from STOP mode */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

  /* Configure the system Power */
  SystemPower_Config();

  while (1)
  {
    /* Insert 5 second delay */
    HAL_Delay(5000);
    /* Turn OFF LED's */
    BSP_LED_Off(LED1);
    BSP_LED_Off(LED2);
    BSP_LED_Off(LED3);

    /* Enter STOP with Low power regulator mode */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    
    /* ... STOP with Low power regulator mode ... */

    /* Configure system clock after wake-up from STOP: enable and select PLL as system clock source 
       (PLL is disabled in STOP mode) */
    SYSCLKConfig_FromSTOP();  
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
/**
  * @brief  System Power Configuration
  *         The system Power is configured as follow : 
  *            + No IWDG
  *            + Wakeup using EXTI Line (Key push-button PC.13)
  * @param  None
  * @retval None
  */
static void SystemPower_Config(void)
{
  GPIO_InitTypeDef gpio_initstruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* Set all GPIO in analog state to reduce power consumption, except PC.13   */
  /* to keep user button interrupt enabled                                    */
  /* Note: Debug using ST-Link is not possible during the execution of this   */
  /*       example because communication between ST-link and the device       */
  /*       under test is done through UART. All GPIO pins are disabled (set   */
  /*       to analog input mode) including  UART I/O pins.                    */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA |
                           LL_AHB1_GRP1_PERIPH_GPIOB |
                           LL_AHB1_GRP1_PERIPH_GPIOC |
                           LL_AHB1_GRP1_PERIPH_GPIOD |
                           LL_AHB1_GRP1_PERIPH_GPIOE |
                           LL_AHB1_GRP1_PERIPH_GPIOF |
                           LL_AHB1_GRP1_PERIPH_GPIOG |
                           LL_AHB1_GRP1_PERIPH_GPIOH |
                           LL_AHB1_GRP1_PERIPH_GPIOI);

  /* In HAL, following codes can be called instead of LL:
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();*/

  gpio_initstruct.Mode  = GPIO_MODE_ANALOG;
  gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio_initstruct.Pull  = GPIO_NOPULL;
  gpio_initstruct.Pin   = GPIO_PIN_All;

  HAL_GPIO_Init(GPIOA, &gpio_initstruct);
  HAL_GPIO_Init(GPIOD, &gpio_initstruct);
  HAL_GPIO_Init(GPIOE, &gpio_initstruct);
  HAL_GPIO_Init(GPIOF, &gpio_initstruct);
  HAL_GPIO_Init(GPIOG, &gpio_initstruct);
  HAL_GPIO_Init(GPIOH, &gpio_initstruct);
  HAL_GPIO_Init(GPIOI, &gpio_initstruct);

  /* Set all the GPIOC pin to analog except PC.13 */
  gpio_initstruct.Pin   &= ~GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC, &gpio_initstruct);

  /* Set all the GPIOB pin to analog except PB.00, PB.07 and PB.14 (respectively LED1, LED2 and LED3) */
  gpio_initstruct.Pin   &= (GPIO_PIN_All & ~(GPIO_PIN_0 | GPIO_PIN_7 |GPIO_PIN_14));
  HAL_GPIO_Init(GPIOB, &gpio_initstruct);

}

/**
  * @brief  Configures system clock after wake-up from STOP: enable PLL
  *         and select PLL as system clock source.
  * @note   RCC LL API is used in this case to allow MCU to wake-up as quick
  *         as possible from STOP mode.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void SYSCLKConfig_FromSTOP(void)
{
  /* Customize process using LL interface to improve the performance 
     (wake-up time from STOP quicker in LL than HAL)*/  
  /* HSE configuration and activation */
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1) {};

  /* Main PLL activation */
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1) 
  {
  };
  
  /* SYSCLK activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) 
  {
  };
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* Suspend tick */
  HAL_SuspendTick();
  
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  while (1)
  {
  }
}

/**
  * @brief SYSTICK callback
  * @param None
  * @retval None
  */
void HAL_SYSTICK_Callback(void)
{
  HAL_IncTick();

  if (TimingDelay != 0)
  {
    TimingDelay--;
  }
  else
  {
    /* Toggle LED1 */
    BSP_LED_Toggle(LED1);
    TimingDelay = LED_TOGGLE_DELAY;
  }
}


/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == KEY_BUTTON_PIN)
  {
    /* Switch on LED1 */
    BSP_LED_On(LED1);
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
