/**
  ******************************************************************************
  * @file    I2C/I2C_TwoBoards_AdvComIT/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use STM32F2xx I2C HAL API to transmit
  *          and receive data buffer with a communication process based on
  *          IT transfer.
  *          The communication is done using 2 Boards.
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

/** @addtogroup I2C_TwoBoards_AdvComIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Uncomment this line to use the board as master, if not it is used as slave */
#define MASTER_BOARD
#define I2C_ADDRESS        0x3E  /* Real 7 bits slave address value in Datasheet is: b0011111
                                    mean in uint8_t equivalent at 0x1F and this value can be
                                    seen in the OAR1 register in bits ADD[1:7] */
#define MASTER_REQ_READ    0x12
#define MASTER_REQ_WRITE   0x34

/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
I2C_HandleTypeDef I2CxHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****I2C_TwoBoards advanced communication based on IT****  ****I2C_TwoBoards advanced communication based on IT****  ****I2C_TwoBoards advanced communication based on IT**** ";

/* Buffer used for reception */
uint8_t aRxBuffer[RXBUFFERSIZE];
uint16_t hTxNumData = 0, hRxNumData = 0;
uint8_t bTransferRequest = 0;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength);
static void Flush_Buffer(uint8_t* pBuffer, uint16_t BufferLength);
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
  
  /* Configure LED1 and LED2 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  
  /* Configure the system clock to 120 MHz */
  SystemClock_Config();

  /*##-1- Configure the I2C peripheral #######################################*/
  I2CxHandle.Instance             = I2Cx;
  I2CxHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2CxHandle.Init.ClockSpeed      = 400000;
  I2CxHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2CxHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
  I2CxHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2CxHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  I2CxHandle.Init.OwnAddress1     = I2C_ADDRESS;
  I2CxHandle.Init.OwnAddress2     = 0;

  if(HAL_I2C_Init(&I2CxHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

#ifdef MASTER_BOARD
  /* Configure User Button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

  /* Wait for User Button press before starting the Communication */
  while (BSP_PB_GetState(BUTTON_KEY) != 1)
  {
  }

  /* Wait for User Button release before starting the Communication */
  while (BSP_PB_GetState(BUTTON_KEY) != 0)
  {
  }

  while(1)
  {
    /* Initialize number of data variables */
    hTxNumData = TXBUFFERSIZE;
    hRxNumData = RXBUFFERSIZE;

    /* Update bTransferRequest to send buffer write request for Slave */
    bTransferRequest = MASTER_REQ_WRITE;

    /*##-2- Master sends write request for slave #############################*/
    do
    {
      if(HAL_I2C_Master_Transmit_IT(&I2CxHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)&bTransferRequest, 1)!= HAL_OK)
      {
        /* Error_Handler() function is called in case of error. */
        Error_Handler();
      }

      /* Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /* When Acknowledge failure occurs (Slave don't acknowledge its address)
      Master restarts communication */
    }
    while(HAL_I2C_GetError(&I2CxHandle) == HAL_I2C_ERROR_AF); 

    /*##-3- Master sends number of data to be written ########################*/
    do
    {
      if(HAL_I2C_Master_Transmit_IT(&I2CxHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)&hTxNumData, 2)!= HAL_OK)
      {
        /* Error_Handler() function is called in case of error. */
        Error_Handler();
      }

      /* Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /* When Acknowledge failure occurs (Slave don't acknowledge its address)
      Master restarts communication */
    }
    while(HAL_I2C_GetError(&I2CxHandle) == HAL_I2C_ERROR_AF); 
    
    /*##-4- Master sends aTxBuffer to slave ##################################*/
    do
    {
      if(HAL_I2C_Master_Transmit_IT(&I2CxHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)aTxBuffer, TXBUFFERSIZE)!= HAL_OK)
      {
        /* Error_Handler() function is called in case of error. */
        Error_Handler();
      }

      /* Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /* When Acknowledge failure occurs (Slave don't acknowledge its address)
      Master restarts communication */
    }
    while(HAL_I2C_GetError(&I2CxHandle) == HAL_I2C_ERROR_AF); 

    /* Update bTransferRequest to send buffer read request for Slave */
    bTransferRequest = MASTER_REQ_READ;

    /*##-5- Master sends read request for slave ##############################*/
    do
    {
      if(HAL_I2C_Master_Transmit_IT(&I2CxHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)&bTransferRequest, 1)!= HAL_OK)
      {
        /* Error_Handler() function is called in case of error. */
        Error_Handler();
      }

      /* Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /* When Acknowledge failure occurs (Slave don't acknowledge its address)
      Master restarts communication */
    }
    while(HAL_I2C_GetError(&I2CxHandle) == HAL_I2C_ERROR_AF); 

    /*##-6- Master sends number of data to be read ###########################*/
    do
    {
      if(HAL_I2C_Master_Transmit_IT(&I2CxHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)&hRxNumData, 2)!= HAL_OK)
      {
        /* Error_Handler() function is called in case of error. */
        Error_Handler();
      }

      /* Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /* When Acknowledge failure occurs (Slave don't acknowledge its address)
      Master restarts communication */
    }
    while(HAL_I2C_GetError(&I2CxHandle) == HAL_I2C_ERROR_AF); 

    /*##-7- Master receives aRxBuffer from slave #############################*/
    do
    {
      if(HAL_I2C_Master_Receive_IT(&I2CxHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)aRxBuffer, RXBUFFERSIZE)!= HAL_OK)
      {
        /* Error_Handler() function is called in case of error. */
        Error_Handler();
      }

      /* Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /* When Acknowledge failure occurs (Slave don't acknowledge its address)
      Master restarts communication */
    }
    while(HAL_I2C_GetError(&I2CxHandle) == HAL_I2C_ERROR_AF);

    /* Check correctness of received buffer ##################################*/
    if(Buffercmp((uint8_t*)aTxBuffer,(uint8_t*)aRxBuffer,hRxNumData))
    {
      /* Processing Error */
      Error_Handler();
    }

    /* Flush Rx buffers */
    Flush_Buffer((uint8_t*)aRxBuffer,RXBUFFERSIZE);

    /* Toggle LED1 */
    BSP_LED_Toggle(LED1);

    /* This delay permit the user to see LED1 toggling */
    HAL_Delay(25);
  }
#else
  while(1)
  {
    /* Initialize number of data variables */
    hTxNumData = 0;
    hRxNumData = 0;

    /*##-2- Slave receive request from master ################################*/
    while(HAL_I2C_Slave_Receive_IT(&I2CxHandle, (uint8_t*)&bTransferRequest, 1)!= HAL_OK)
    {
    }

    /*  Before starting a new communication transfer, you need to check the current
    state of the peripheral; if it�s busy you need to wait for the end of current
    transfer before starting a new one.
    For simplicity reasons, this example is just waiting till the end of the
    transfer, but application may perform other tasks while transfer operation
    is ongoing. */
    while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
    {
    }

    /* If master request write operation #####################################*/
    if(bTransferRequest == MASTER_REQ_WRITE)
    {
      /*##-3- Slave receive number of data to be read ########################*/
      while(HAL_I2C_Slave_Receive_IT(&I2CxHandle, (uint8_t*)&hRxNumData, 2)!= HAL_OK);

      /*  Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /*##-4- Slave receives aRxBuffer from master ###########################*/
      while(HAL_I2C_Slave_Receive_IT(&I2CxHandle, (uint8_t*)aRxBuffer, hRxNumData)!= HAL_OK);

      /*  Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /* Check correctness of received buffer ################################*/
      if(Buffercmp((uint8_t*)aTxBuffer,(uint8_t*)aRxBuffer,hRxNumData))
      {
        /* Processing Error */
        Error_Handler();
      }

      /* Flush Rx buffers */
      Flush_Buffer((uint8_t*)aRxBuffer,RXBUFFERSIZE);

      /* Toggle LED1 */
      BSP_LED_Toggle(LED1);
    }
    /* If master request write operation #####################################*/
    else
    {
      /*##-3- Slave receive number of data to be written #####################*/
      while(HAL_I2C_Slave_Receive_IT(&I2CxHandle, (uint8_t*)&hTxNumData, 2)!= HAL_OK);

      /*  Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }

      /*##-4- Slave transmit aTxBuffer to master #############################*/
      while(HAL_I2C_Slave_Transmit_IT(&I2CxHandle, (uint8_t*)aTxBuffer, RXBUFFERSIZE)!= HAL_OK);

      /*  Before starting a new communication transfer, you need to check the current
      state of the peripheral; if it�s busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */
      while (HAL_I2C_GetState(&I2CxHandle) != HAL_I2C_STATE_READY)
      {
      }
    }
  }
#endif /* MASTER_BOARD */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn Off LED1 */
  BSP_LED_Off(LED1);
  /* Turn On LED2 */
  BSP_LED_On(LED2);
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
  * @brief  I2C error callbacks
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  /** Error_Handler() function is called when error occurs.
  * 1- When Slave don't acknowledge it's address, Master restarts communication.
  * 2- When Master don't acknowledge the last data transferred, Slave don't care in this example.
  */
  if (HAL_I2C_GetError(I2cHandle) != HAL_I2C_ERROR_AF)
  {
    Error_Handler();
  }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 0  : pBuffer1 identical to pBuffer2
  *         >0 : pBuffer1 differs from pBuffer2
  */
static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if ((*pBuffer1) != *pBuffer2)
    {
      return BufferLength;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

/**
  * @brief  Flushes the buffer
  * @param  pBuffer: buffers to be flushed.
  * @param  BufferLength: buffer's length
  * @retval None
  */
static void Flush_Buffer(uint8_t* pBuffer, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    *pBuffer = 0;

    pBuffer++;
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
