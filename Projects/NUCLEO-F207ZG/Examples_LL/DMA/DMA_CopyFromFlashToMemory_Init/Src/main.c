/**
  ******************************************************************************
  * @file    Examples_LL/DMA/DMA_CopyFromFlashToMemory_Init/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to use a DMA channel to transfer
  *          a word data buffer from FLASH memory to embedded SRAM memory
  *          through the STM32F2xx DMA LL API.
  *          Peripheral initialization done using LL initialization function.
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

/** @addtogroup DMA_CopyFromFlashToMemory_Init
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE              32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static const uint32_t aSRC_Const_Buffer[BUFFER_SIZE] =
{
  0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
  0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
  0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
  0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
  0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
  0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
  0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
  0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80
};

static uint32_t aDST_Buffer[BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/
void     SystemClock_Config(void);
void     Configure_DMA(void);
uint8_t  Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint32_t BufferLength);
void     LED_Init(void);
void     LED_On(void);
void     LED_Blinking(uint32_t Period);

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

  /* Configure DMA2 Stream 0                                     */
  /* Enable DMA2 clock                                           */
  /* Configure the DMA functional parameters :                  */
  /*        - Transfer memory word to memory word in normal mode */
  /*        - Memory and Periph increment mode                   */
  /* Configure NVIC for DMA transfer complete/error interrupts   */
  Configure_DMA();

  /* Start the DMA transfer Flash to Memory */
  LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_0);
  
  /* Infinite loop */
  while (1)
  {
    /* Transfer completion and comparison is done on interrupt callback directly */
  }
}

/**
  * @brief  This function configures the DMA2 Stream 0 to copy data from
  *         Flash memory(aSRC_Const_Buffer) to Internal SRAM(aDST_Buffer).
  * @note   This function is used to :
  *         -1- Enable DMA2 clock
  *         -2- Configure the DMA functional parameters
  *         -3- Configure NVIC for DMA transfer complete/error interrupts
  * @param   None
  * @retval  None
  */
void Configure_DMA(void)
{  
  LL_DMA_InitTypeDef dma_initstruct;

  /* (1) Enable the clock of DMA2 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

  /* (2) Configure the DMA functional parameters */

  /* Reset DMA2 data registers */
  if (LL_DMA_DeInit(DMA2, LL_DMA_STREAM_0) != SUCCESS) 
  {
    /* Initialization Error */
    LED_Blinking(LED_BLINK_ERROR);
  }

  /* Set fields of initialization structure:
   *  - Source base address:        aSRC_Const_Buffer
   *  - Destination base address:   aDST_Buffer
   *  - Transfer direction :         Memory to memory
   *  - Source increment mode:      Increment mode Enable
   *  - Destination increment mode: Increment mode Enable
   *  - Source data alignment:      Word alignment
   *  - Destination data alignment: Word alignment
   *  - Number of data to transfer: BUFFER_SIZE
   *  - Transfer priority level:    High priority
  */
  dma_initstruct.PeriphOrM2MSrcAddress  = (uint32_t)&aSRC_Const_Buffer;
  dma_initstruct.MemoryOrM2MDstAddress  = (uint32_t)&aDST_Buffer;
  dma_initstruct.Direction              = LL_DMA_DIRECTION_MEMORY_TO_MEMORY;
  dma_initstruct.Mode                   = LL_DMA_MODE_NORMAL;
  dma_initstruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_INCREMENT;
  dma_initstruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
  dma_initstruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;
  dma_initstruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;
  dma_initstruct.NbData                 = BUFFER_SIZE;
  dma_initstruct.Priority               = LL_DMA_PRIORITY_HIGH;
  dma_initstruct.FIFOMode               = LL_DMA_FIFOMODE_DISABLE;
  dma_initstruct.Channel                = LL_DMA_CHANNEL_0;
  
  /* Initialize DMA instance according to parameters defined in initialization structure. */  
  if (LL_DMA_Init(DMA2, LL_DMA_STREAM_0, &dma_initstruct) != SUCCESS)
  {
    /* Initialization Error */
    LED_Blinking(LED_BLINK_ERROR);
  }

  /* (3) Configure NVIC for DMA transfer complete/error interrupts */
  LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_0);
  LL_DMA_EnableIT_TE(DMA2, LL_DMA_STREAM_0);
  NVIC_SetPriority(DMA2_Stream0_IRQn, 0);
  NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 0: pBuffer identical to pBuffer1
  *         1: pBuffer differs from pBuffer1
  */
uint8_t Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return 0;
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
  /* Turn LED1 on */
  LL_GPIO_SetOutputPin(LED1_GPIO_PORT, LED1_PIN);
  
  /* Toggle IO in an infinite loop */
  while (1)
  {
    LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);  
    LL_mDelay(Period);
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

/******************************************************************************/
/*   USER IRQ HANDLER TREATMENT                                               */
/******************************************************************************/
/**
  * @brief  DMA transfer complete callback
  * @note   This function is executed when the transfer complete interrupt
  *         is generated
  * @retval None
  */
void TransferComplete()
{
  /* DMA transfer completed */
  /* Verify the data transferred */
  if (Buffercmp((uint32_t*)aSRC_Const_Buffer, (uint32_t*)aDST_Buffer, BUFFER_SIZE) == 1)
  {
    /* DMA data transferred not consistency */
    LED_Blinking(LED_BLINK_ERROR);
  }
  
  /* DMA data transferred consistency */
  LED_On();
}

/**
  * @brief  DMA transfer error callback
  * @note   This function is executed when the transfer error interrupt
  *         is generated during DMA transfer
  * @retval None
  */
void TransferError()
{
  /* Error detected during DMA transfer */
  LED_Blinking(LED_BLINK_ERROR);
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
