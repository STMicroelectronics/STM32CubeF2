/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_Queues/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body
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
#include "cmsis_os.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define blckqSTACK_SIZE   configMINIMAL_STACK_SIZE
#define QUEUE_SIZE        (uint32_t) 1

/* Private variables ---------------------------------------------------------*/
osMessageQId osQueue;
uint32_t ProducerValue = 0, ConsumerValue = 0;

/* Private function prototypes -----------------------------------------------*/

/* Thread function that creates an incrementing number and posts it on a queue. */
static void MessageQueueProducer(const void *argument);

/* Thread function that removes the incrementing number from a queue and checks that
   it is the expected number. */
static void MessageQueueConsumer(const void *argument);
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
  
  /* Configure LED1 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED3);
  
  /* Create the queue used by the two tasks to pass the incrementing number.
  Pass a pointer to the queue in the parameter structure. */
  osMessageQDef(osqueue, QUEUE_SIZE, uint16_t);
  osQueue = osMessageCreate(osMessageQ(osqueue), NULL);
  
  /* Note the producer has a lower priority than the consumer when the tasks are
     spawned. */
  osThreadDef(QCons, MessageQueueConsumer, osPriorityBelowNormal, 0, blckqSTACK_SIZE);
  osThreadCreate(osThread(QCons), NULL);
  
  osThreadDef(QProd, MessageQueueProducer, osPriorityBelowNormal, 0, blckqSTACK_SIZE);
  osThreadCreate(osThread(QProd), NULL);
  
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  for(;;);
}

/**
  * @brief  Message Queue Producer Thread.
  * @param  argument: Not used
  * @retval None
  */
static void MessageQueueProducer(const void *argument)
{
  for(;;)
  {		
    if(osMessagePut(osQueue, ProducerValue, 100) != osOK)  
    {      
      /* Toggle LED3 to indicate error */
      BSP_LED_Toggle(LED3);
    }
    else
    {
      /* Increment the variable we are going to post next time round.  The
      consumer will expect the numbers to follow in numerical order. */
      ++ProducerValue;
      
      /* Toggle LED1 to indicate a correct number received */
      BSP_LED_Toggle(LED1);

      osDelay(250);
    }
  }
}

/**
  * @brief  Message Queue Consumer Thread.
  * @param  argument: Not used
  * @retval None
  */
static void MessageQueueConsumer(const void *argument)
{
  osEvent event;
  
  for(;;)
  {
    /* Get the message from the queue */
    event = osMessageGet(osQueue, 100);
    
    if(event.status == osEventMessage)
    {
      if(event.value.v != ConsumerValue)
      {
        /* Catch-up. */
        ConsumerValue = event.value.v;
        
        /* Toggle LED3 to indicate error */
        BSP_LED_Toggle(LED3);
      }
      else
      {  
        /* Increment the value we expect to remove from the queue next time
        round. */
        ++ConsumerValue;
      }
    }
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
  /* User may add here some code to deal with this error */
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
