/**
  ******************************************************************************
  * @file    Examples_LL/RNG/RNG_GenerateRandomNumbers_IT/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to use RNG peripheral for generating random
  *          numbers using the STM32F2xx RNG LL API.
  *          Peripheral initialization done using LL unitary services functions.
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

/** @addtogroup STM32F2xx_LL_Examples
  * @{
  */

/** @addtogroup RNG_GenerateRandomNumbers_IT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#if (USE_TIMEOUT == 1)
#define RNG_GENERATION_TIMEOUT   20
#endif /* USE_TIMEOUT */

#define    NB_OF_GENERATED_RANDOM_NUMBERS      8       /* Nb of Random numbers generated after the User button press */

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#if (USE_TIMEOUT == 1)
uint32_t Timeout = 0; /* Variable used for Timeout management */
#endif /* USE_TIMEOUT */
__IO uint8_t ubButtonPress = 0;
__IO uint8_t ubIndex = 0;
__IO uint8_t ubIsNbGenerated = 0;

/* Array used for storing generated Random 32bit Numbers */
__IO uint32_t aRandom32bit[NB_OF_GENERATED_RANDOM_NUMBERS];



/* Private function prototypes -----------------------------------------------*/
void     SystemClock_Config(void);
void     Configure_RNG(void);
void     RandomNumbersGenerationIT(void);
void     LED_Init(void);
void     LED_On(void);
void     LED_Blinking(uint32_t Period);
void     UserButton_Init(void);
void     WaitForUserButtonPress(void);
uint32_t SetSystemToHSI(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure the system clock to 120 MHz */
  SystemClock_Config();

  /* Initialize LED1 */
  LED_Init();

  /* Initialize Key push-button in EXTI mode */
  UserButton_Init();

  /* Configure RNG (RNG IP configuration : Clock enabling) */
  Configure_RNG();

  /* Wait for Key push-button press to trigger random numbers generation */
  WaitForUserButtonPress();

  /* Generate Random Numbers series */
  RandomNumbersGenerationIT();

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  This function configures RNG Instance.
  * @note   This function is used to :
  *         -1- Enable peripheral clock for RNG.
  *         -2- NVIC Configuration for RNG interrupts.
  * @param  None
  * @retval None
  */
void Configure_RNG(void)
{
  /* (1) Enable peripheral clock for RNG                   *********************/
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_RNG);
  
  /* Set system to HSI and disable PLL */
  while (SetSystemToHSI()!= 0)
  {
  };  

  /* Configure PLLSAI to enable 48M domain 
    - Keep same PLLSAI source (HSE) and PLLM factor (DIV8) used for main PLL 
    - Select PLL_N & PLL_Q to have a frequency of 48MHz
        * PLL_P output = (((HSE Freq / PLLM) * PLLSAI_N) / PLLSAI_P)
        *              = (((8000000  /   8 ) *    240    ) /    5     ) */
  LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 240, LL_RCC_PLLQ_DIV_5);
  
  /* set FLASH latency to 3 */  
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
   
  /* Enable PLL*/
  LL_RCC_PLL_Enable();
  
  /* Wait for PLL ready flag */
  while(LL_RCC_PLL_IsReady() != 1) 
  {
  };
  
  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };
  
  /* Set systick to 1ms */
  SysTick_Config(120000000 / 1000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  SystemCoreClock = 120000000;

  /* (2) NVIC Configuration for RNG interrupts */
  /*  - Set priority for RNG_IRQn */
  /*  - Enable RNG_IRQn */
  NVIC_SetPriority(RNG_IRQn, 0);  
  NVIC_EnableIRQ(RNG_IRQn);
}

/**
  * @brief  This function performs several random numbers generation.
  * @note   Generated random numbers are stored in global variable array, so that
  *         generated values could be observed by user by watching variable content
  *         in specific debugger window
  * @param  None
  * @retval None
  */
void RandomNumbersGenerationIT(void)
{
  /* Initialize random numbers generation */
  LL_RNG_Enable(RNG);

  /* Generate Random 32bit Numbers */
  for(ubIndex = 0; ubIndex < NB_OF_GENERATED_RANDOM_NUMBERS; ubIndex++)
  {
#if (USE_TIMEOUT == 1)
    Timeout = RNG_GENERATION_TIMEOUT;
#endif /* USE_TIMEOUT */

    ubIsNbGenerated = 0;

    /* Enable RNG generation interrupt */
    LL_RNG_EnableIT(RNG);

    /* Wait for Random Number generation completion */
    while (ubIsNbGenerated == 0)
    {
#if (USE_TIMEOUT == 1)
      /* Check Systick counter flag to decrement the time-out value */
      if (LL_SYSTICK_IsActiveCounterFlag()) 
      { 
        if(Timeout-- == 0)
        {
          /* Time-out occurred. Set LED to blinking mode */
          LED_Blinking(LED_BLINK_SLOW);
        }
      } 
#endif /* USE_TIMEOUT */
    }
  }

  /* Stop random numbers generation */
  LL_RNG_Disable(RNG);

  /* Values of Generated Random numbers are now available in aRandom32bit array.
     LED1 is turned on */
  LED_On();
}

/**
  * @brief  Initialize LED1.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
  /* Enable the LED1 Clock */
  LED1_GPIO_CLK_ENABLE();

  /* Configure IO in output push-pull mode to drive external LED1 */
  LL_GPIO_SetPinMode(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_MODE_OUTPUT);
  /* Reset value is LL_GPIO_OUTPUT_PUSHPULL */
  //LL_GPIO_SetPinOutputType(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  /* Reset value is LL_GPIO_SPEED_FREQ_LOW */
  //LL_GPIO_SetPinSpeed(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_SPEED_FREQ_LOW);
  /* Reset value is LL_GPIO_PULL_NO */
  //LL_GPIO_SetPinPull(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  Turn-on LED1.
  * @param  None
  * @retval None
  */
void LED_On(void)
{
  /* Turn LED1 on */
  LL_GPIO_SetOutputPin(LED1_GPIO_PORT, LED1_PIN);
}

/**
  * @brief  Set LED1 to Blinking mode for an infinite loop (toggle period based on value provided as input parameter).
  * @param  Period : Period of time (in ms) between each toggling of LED
  *   This parameter can be user defined values. Pre-defined values used in that example are :
  *     @arg LED_BLINK_FAST : Fast Blinking
  *     @arg LED_BLINK_SLOW : Slow Blinking
  *     @arg LED_BLINK_ERROR : Error specific Blinking
  * @retval None
  */
void LED_Blinking(uint32_t Period)
{
  /* Toggle LED1 in an infinite loop */
  while (1)
  {
    LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);  
    LL_mDelay(Period);
  }
}

/**
  * @brief  Configures Key push-button in GPIO or EXTI Line Mode.
  * @param  None 
  * @retval None
  */
void UserButton_Init(void)
{
  /* Enable the BUTTON Clock */
  USER_BUTTON_GPIO_CLK_ENABLE();
  
  /* Configure GPIO for BUTTON */
  LL_GPIO_SetPinMode(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, LL_GPIO_PULL_NO);

  /* Connect External Line to the GPIO*/
  USER_BUTTON_SYSCFG_SET_EXTI();

  /* Enable a rising trigger EXTI Line13 Interrupt */
  USER_BUTTON_EXTI_LINE_ENABLE();
  USER_BUTTON_EXTI_FALLING_TRIG_ENABLE();

  /* Configure NVIC for USER_BUTTON_EXTI_IRQn */
  NVIC_SetPriority(USER_BUTTON_EXTI_IRQn, 0x03);  
  NVIC_EnableIRQ(USER_BUTTON_EXTI_IRQn); 
}

/**
  * @brief  Wait for Key push-button press to start transfer.
  * @param  None 
  * @retval None
  */
  /*  */
void WaitForUserButtonPress(void)
{
  while (ubButtonPress == 0)
  {
    LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
    LL_mDelay(LED_BLINK_FAST);
  }
  
  /* Turn LED1 off */
  LL_GPIO_ResetOutputPin(LED1_GPIO_PORT, LED1_PIN);
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
  *            HSI Frequency(Hz)              = 80000000
  *            PLL_M                          = 8
  *            PLL_N                          = 240
  *            PLL_P                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 3
  */
void SystemClock_Config(void)
{
  /* Enable HSE oscillator */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 240, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

  /* Set systick to 1ms */
  SysTick_Config(120000000 / 1000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  SystemCoreClock = 120000000;
}

uint32_t SetSystemToHSI(void)
{
  uint32_t timeout = 0;
  /* Enable HSI if not enabled */
  if (LL_RCC_HSI_IsReady() != 1)
  {
    LL_RCC_HSI_Enable();
    timeout = 1000;
    while ((LL_RCC_HSI_IsReady() != 1) && (timeout != 0))
    {
      if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) 
      {
        timeout --;
      }
      if (timeout == 0)
      {
        return 1;
      }  
    }
  }
  
  /* Set SYS clock source to HSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  SystemCoreClock = HSI_VALUE;
  
  /* Disable PLL if enabled */
  if (LL_RCC_PLL_IsReady() != 0)
  {
    LL_RCC_PLL_Disable();
    timeout = 1000;
    while ((LL_RCC_PLL_IsReady() != 0) && (timeout != 0))
    {
      if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) 
      {
        timeout --;
      }
      if (timeout == 0)
      {
        return 1;
      }  
    }
  }
  /* Test end */
  return 0;
}

/******************************************************************************/
/*   IRQ HANDLER TREATMENT Functions                                          */
/******************************************************************************/

/**
  * @brief  Function called when RNG IT is triggered with DRDY flag set
  * @param  None
  * @retval None
  */
void RNG_DataReady_Callback(void)
{
  /* Disable RNG IT generation */
  LL_RNG_DisableIT(RNG);

  /* Value of generated random number could be retrieved and stored in dedicated array */
  aRandom32bit[ubIndex] = LL_RNG_ReadRandData32(RNG);

  /* Set Flag indicated random Number generation is completed */
  ubIsNbGenerated = 1;
}

/**
  * @brief  Function called in case of error detected in RNG IT Handler
  * @param  None
  * @retval None
  */
void Error_Callback(void)
{
  /* Disable RNG_IRQn */
  NVIC_DisableIRQ(RNG_IRQn);
  
  /* Clock or Seed Error detected. Set LED to blinking mode (Error type)*/
  LED_Blinking(LED_BLINK_ERROR);
}

/**
  * @brief  Function to manage Key push-button
  * @param  None
  * @retval None
  */
void UserButton_Callback(void)
{
  /* Update Key push-button variable : to be checked in waiting loop in main program */
  ubButtonPress = 1;
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
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

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
