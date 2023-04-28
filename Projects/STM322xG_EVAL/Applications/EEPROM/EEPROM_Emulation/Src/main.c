/**
  ******************************************************************************
  * @file    EEPROM/EEPROM_Emulation/src/main.c 
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
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
/** @addtogroup EEPROM_Emulation
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Virtual address defined by the user: 0xFFFF value is prohibited */
uint16_t VirtAddVarTab[NB_OF_VAR] = {0x5555, 0x6666, 0x7777};
uint16_t VarDataTab[NB_OF_VAR] = {0, 0, 0};
uint16_t VarValue,VarDataTmp = 0;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  
  /* Configure the system clock to 120 MHz */
  SystemClock_Config();
  
   /* Unlock the Flash Program Erase controller */
  HAL_FLASH_Unlock();
  
  /* Configure LED1 */
  BSP_LED_Init(LED1);

  /* EEPROM Init */
  if( EE_Init() != EE_OK)
  {
    Error_Handler();
  }
  
  /* --- Store successively many values of the three variables in the EEPROM ---*/
  /* Store 0x1000 values of Variable1 in EEPROM */
  for (VarValue = 1; VarValue <= 0x1000; VarValue++)
  {
    /* Sequence 1 */
    if((EE_WriteVariable(VirtAddVarTab[0],  VarValue)) != HAL_OK)
    {
      Error_Handler();
    }
    if((EE_ReadVariable(VirtAddVarTab[0],  &VarDataTab[0])) != HAL_OK)
    {
      Error_Handler();
    }
    if (VarValue != VarDataTab[0])
    {
      Error_Handler();
    }
    
    /* Sequence 2 */
    if(EE_WriteVariable(VirtAddVarTab[1], ~VarValue) != HAL_OK)
    {
      Error_Handler();
    }  
    if(EE_ReadVariable(VirtAddVarTab[1], &VarDataTab[1]) != HAL_OK)
    {
      Error_Handler();
    } 
    if(((uint16_t)~VarValue) != VarDataTab[1])
    {
      Error_Handler();
    }

    /* Sequence 3 */
    if(EE_WriteVariable(VirtAddVarTab[2],  VarValue << 1) != HAL_OK)
    {
      Error_Handler();
    }
    if(EE_ReadVariable(VirtAddVarTab[2],  &VarDataTab[2]) != HAL_OK)
    {
      Error_Handler();
    } 
    if ((VarValue << 1) != VarDataTab[2])
    {
      Error_Handler();
    }
  }

  /* Store 0x2000 values of Variable2 in EEPROM */
  for (VarValue = 1; VarValue <= 0x2000; VarValue++)
  {
    if(EE_WriteVariable(VirtAddVarTab[1], VarValue) != HAL_OK)
    {
      Error_Handler();
    }      
    if(EE_ReadVariable(VirtAddVarTab[1], &VarDataTab[1]) != HAL_OK)
    {
      Error_Handler();
    }    
    if(VarValue != VarDataTab[1])
    {
      Error_Handler();
    }
  }

  /* read the last stored variables data*/
  if(EE_ReadVariable(VirtAddVarTab[0], &VarDataTmp) != HAL_OK)
  {
    Error_Handler();
  }   
  if (VarDataTmp != VarDataTab[0])
  {
    Error_Handler();
  }

  if(EE_ReadVariable(VirtAddVarTab[1], &VarDataTmp) != HAL_OK)
  {
    Error_Handler();
  }    
  if (VarDataTmp != VarDataTab[1])
  {
    Error_Handler();
  }

  if(EE_ReadVariable(VirtAddVarTab[2], &VarDataTmp) != HAL_OK)
  {
    Error_Handler();
  }    
  if (VarDataTmp != VarDataTab[2])
  {
    Error_Handler();
  }
  
  /* Store 0x3000 values of Variable3 in EEPROM */
  for (VarValue = 1; VarValue <= 0x3000; VarValue++)
  {
    if(EE_WriteVariable(VirtAddVarTab[2], VarValue) != HAL_OK)
    {
      Error_Handler();
    }      
    if(EE_ReadVariable(VirtAddVarTab[2], &VarDataTab[2]) != HAL_OK)
    {
      Error_Handler();
    }    
    if(VarValue != VarDataTab[2])
    {
      Error_Handler();
    }
  }

  /* read the last stored variables data*/
  if(EE_ReadVariable(VirtAddVarTab[0], &VarDataTmp) != HAL_OK)
  {
    Error_Handler();
  }    
  if (VarDataTmp != VarDataTab[0])
  {
    Error_Handler();
  }

  if(EE_ReadVariable(VirtAddVarTab[1], &VarDataTmp) != HAL_OK)
  {
    Error_Handler();
  }
  if (VarDataTmp != VarDataTab[1])
  {
    Error_Handler();
  }

  if(EE_ReadVariable(VirtAddVarTab[2], &VarDataTmp) != HAL_OK)
  {
    Error_Handler();
  }  
  if (VarDataTmp != VarDataTab[2])
  {
    Error_Handler();
  }

  while (1)
  {
    /* Turn LED1 On */
    BSP_LED_On(LED1);
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
  while(1)
  {
    /* Toggle LED1 fast */
    BSP_LED_Toggle(LED1);
    HAL_Delay(40);
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
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
