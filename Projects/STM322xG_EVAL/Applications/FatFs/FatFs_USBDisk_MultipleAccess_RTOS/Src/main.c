/**
  ******************************************************************************
  * @file    FatFs/FatFs_USBDisk_MultipleAccess_RTOS/Src/main.c 
  * @author  MCD Application Team
  * @brief   Main program body
  *          This sample code shows how to use FatFs with USB disk drive with 
  *          multiple access in RTOS mode.
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
FIL MyFile1, MyFile2;         /* File objects */
char USBDISKPath[4];          /* USB Host logical drive path */
USBH_HandleTypeDef hUSB_Host; /* USB Host handle */
uint8_t disk_op = 0;

typedef enum {
  DISCONNECTION_EVENT = 1,  
  CONNECTION_EVENT,    
}MSC_ApplicationTypeDef;

typedef enum {
  DISK_READY_EVENT = 1,  
  DISK_REMOVE_EVENT,    
}FatFs_DiskTypeDef;

osMessageQId AppliEvent;
osMessageQId DiskEvent;

/* Private function prototypes -----------------------------------------------*/ 
static void SystemClock_Config(void);
static void Error_Handler(void);
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);
static void MSC_Application(void);
static void StartThread(void const *argument);
static void ConcurrentThread(void const *argument);

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
  
  /*##-1- Start task #########################################################*/
  osThreadDef(USER_Thread, StartThread, osPriorityNormal, 0, 8 * configMINIMAL_STACK_SIZE);
  osThreadCreate (osThread(USER_Thread), NULL);
  
  osThreadDef(USER_ConcurrentThread, ConcurrentThread, osPriorityHigh, 0, 8 * configMINIMAL_STACK_SIZE);
  osThreadCreate (osThread(USER_ConcurrentThread), NULL);  
  
  /*##-2- Create Application Queue ###########################################*/
  osMessageQDef(app_queue, 1, uint16_t);
  AppliEvent = osMessageCreate (osMessageQ(app_queue), NULL);
  
  /*##-3- Create Disk Queue ##################################################*/
  osMessageQDef(disk_queue, 1, uint16_t);
  DiskEvent = osMessageCreate (osMessageQ(disk_queue), NULL);
  
  /*##-4- Start scheduler ####################################################*/
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  for( ;; );
}

/**
  * @brief  Start task
  * @param  pvParameters not used
  * @retval None
  */
static void StartThread(void const *argument)
{
  osEvent event;
  
  /* Link the USB Host disk I/O driver */
  if(FATFS_LinkDriver(&USBH_Driver, USBDISKPath) == 0)
  {
    /* Init Host Library */
    USBH_Init(&hUSB_Host, USBH_UserProcess, 0);
    
    /* Add Supported Class */
    USBH_RegisterClass(&hUSB_Host, USBH_MSC_CLASS);
    
    /* Start Host Process */
    USBH_Start(&hUSB_Host);
    
    for( ;; )
    {
      event = osMessageGet(AppliEvent, osWaitForever);
      
      if(event.status == osEventMessage)
      {
        switch(event.value.v)
        {
        case CONNECTION_EVENT:
          MSC_Application();
          break;
          
        case DISCONNECTION_EVENT:
          f_mount(NULL, (TCHAR const*)"", 0);
          break;
          
        default:
          break;   
        }
      }
    }
  }
}

/**
  * @brief  Concurrent task
  * @param  pvParameters not used
  * @retval None
  */
static void ConcurrentThread(void const *argument)
{
  osEvent event;
  FRESULT res;                                          /* FatFs function common result code */
  uint16_t byteswritten;                                /* File write count */
  uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
  
  for( ;; )
  {
    event = osMessageGet(DiskEvent, osWaitForever);
    
    if(event.status == osEventMessage)
    {
      switch(event.value.v)
      {
      case DISK_READY_EVENT:
        /* Create and Open a new text file object with write access */
        if(f_open(&MyFile2, "STM32_2.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) 
        {
          /* 'STM32_2.TXT' file Open for write Error */
          Error_Handler();
        }
        else
        {
          /* Write data to the text file */
          res = f_write(&MyFile2, wtext, sizeof(wtext), (void *)&byteswritten);
          
          if((byteswritten == 0) || (res != FR_OK))
          {
            /* 'STM32_2.TXT' file Write or EOF Error */
            Error_Handler();
          }
          else
          {
            /* Close the open text file */
            f_close(&MyFile2);
            
            /* If last access to Disk, unlink drive */
            if(disk_op == 1)
            {
              osMessagePut(DiskEvent, DISK_REMOVE_EVENT, 0);
            }
            
            disk_op = 2;
            
            /* Success of the demo: no error occurrence */
            BSP_LED_On(LED4); 
          }
        }
        break;
        
      case DISK_REMOVE_EVENT:
        /* Unlink the USB disk I/O driver */
        FATFS_UnLinkDriver(USBDISKPath);       
        break;
        
      default:
        break; 
      }
    }
  }
}

/**
  * @brief  Main routine for Mass Storage Class
  * @param  None
  * @retval None
  */
static void MSC_Application(void)
{
  FRESULT res;                                          /* FatFs function common result code */
  uint32_t byteswritten;                                /* File write count */
  uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
  
  /* Register the file system object to the FatFs module */
  if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK)
  {
    /* FatFs Initialization Error */
    Error_Handler();
  }
  else
  {
    /* Create and Open a new text file object with write access */
    if(f_open(&MyFile1, "STM32_1.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) 
    {
      /* 'STM32_1.TXT' file Open for write Error */
      Error_Handler();
    }
    else
    {
      /* Allow Second task to have access to FatFs */
      osMessagePut(DiskEvent, DISK_READY_EVENT, 0);
      
      /* Write data to the text file */
      res = f_write(&MyFile1, wtext, sizeof(wtext), (void *)&byteswritten);
      
      if((byteswritten == 0) || (res != FR_OK))
      {
        /* 'STM32_1.TXT' file Write or EOF Error */
        Error_Handler();
      }
      else
      {
        /* Close the open text file */
        f_close(&MyFile1);
        
        /* If last access to Disk, unlink drive */
        if(disk_op == 2)
        {
          osMessagePut(DiskEvent, DISK_REMOVE_EVENT, 0);
        }
        
        disk_op = 1;
        
        /* Success of the demo: no error occurrence */
        BSP_LED_On(LED1);        
      }
    }
  }
}

/**
  * @brief  User Process
  * @param  phost: Host handle
  * @param  id: Host Library user message ID
  * @retval None
  */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{  
  switch (id)
  { 
  case HOST_USER_SELECT_CONFIGURATION:
    break;
    
  case HOST_USER_DISCONNECTION:
    BSP_LED_Off(LED1);
    BSP_LED_Off(LED3);  
    BSP_LED_Off(LED4); 
    osMessagePut(AppliEvent, DISCONNECTION_EVENT, 0);
    break;
    
  case HOST_USER_CLASS_ACTIVE:
    osMessagePut(AppliEvent, CONNECTION_EVENT, 0);
    break;
    
  default:
    break; 
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
