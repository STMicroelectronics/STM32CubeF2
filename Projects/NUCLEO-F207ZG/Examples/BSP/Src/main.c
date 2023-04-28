/**
  ******************************************************************************
  * @file    main.c 
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
#include "stlogo.h"

/** @addtogroup STM32F2xx-Nucleo_Demo
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum 
{
  SHIELD_NOT_DETECTED = 0, 
  SHIELD_DETECTED
}ShieldStatus;

/* Private define -------------------------------------------------------------*/
/* tmp */
#define BUTTON_USER BUTTON_KEY
/* Private macro -------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/
uint8_t DemoIndex = 0;
uint8_t UserButtonPressed = 0x00;
uint32_t LedToggleDelay = 0x00;

/* Private function prototypes --------------------------------------------------*/
static void SystemClock_Config(void);
static ShieldStatus TFT_ShieldDetect(void);
#ifdef ADAFRUIT_TFT_JOY_SD_ID802
static void Display_DemoDescription(void);
#endif /* ADAFRUIT_TFT_JOY_SD_ID802 */

BSP_DemoTypedef  BSP_examples[]=
{
  {Joystick_demo, "JOYSTICK", 0},
  {LCD_demo, "LCD", 0}, 
  {SD_demo, "mSD", 0},
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint8_t count = 0;

  /* Init HAL */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();
  
  /* Retrieve System Core Clock */
  SystemCoreClock = HAL_RCC_GetHCLKFreq();
  
  /* Initialize User_Button on STM32F2xx-Nucleo ------------------*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI); 

  /* Check the availability of adafruit 1.8" TFT shield on top of STM32NUCLEO
     board. This is done by reading the state of IO NUCLEO_ADCx_GPIO_PIN pin (mapped to JoyStick
     available on adafruit 1.8" TFT shield). If the state of NUCLEO_ADCx_GPIO_PIN is high then
     the adafruit 1.8" TFT shield is available. */  
  if(TFT_ShieldDetect() == SHIELD_DETECTED)
  {
#ifdef ADAFRUIT_TFT_JOY_SD_ID802
    BSP_LED_Init(LED2);

    /* Initialize the LCD */
    BSP_LCD_Init();

    Display_DemoDescription();

    while (1)
    {
      BSP_LED_Toggle(LED2);
      HAL_Delay(100);
      if(BSP_PB_GetState(BUTTON_USER) != RESET)
      {
        HAL_Delay(10);
        while (BSP_PB_GetState(BUTTON_USER) != RESET);
      
        BSP_examples[DemoIndex++].DemoFunc();
      
        if(DemoIndex >= COUNT_OF_EXAMPLE(BSP_examples))
        {
          DemoIndex = 0;
        }
        Display_DemoDescription();
      }
    }
#endif /* ADAFRUIT_TFT_JOY_SD_ID802 */
  }  
  else /* there is no AdaFruit shield 802 connected */
  {
    /* Initialize Led1 on STM32F2xx-Nucleo ------------------*/
    BSP_LED_Init(LED1);  /* this is in conflict with Adafruit shield */
    BSP_LED_Init(LED2);

    /* 0. Wait for User button to be pressed -------------------------------------*/
    while (BSP_PB_GetState(BUTTON_USER) != KEY_PRESSED)
    {
      /* Toggle LED2 */
      BSP_LED_Toggle(LED2);
      HAL_Delay(200);
    }
    /* Wait for User button is released */
    while (BSP_PB_GetState(BUTTON_USER) != KEY_NOT_PRESSED)
    {}

    /* Infinite loop */
    while (1)
    {
      if(UserButtonPressed==0x01)
      {
        count++;
        LedToggleDelay += 20*count;
        UserButtonPressed = 0x00;
        if(LedToggleDelay>500)
        {
          LedToggleDelay = 20;
          count = 0;
        }
      }
      /* Toggle LED1 & LED2 */
      BSP_LED_Toggle(LED1);
      HAL_Delay(LedToggleDelay);
      BSP_LED_Toggle(LED2);
      HAL_Delay(LedToggleDelay);
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
static void SystemClock_Config(void)
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
  * @brief  Display main demo messages.
  * @param  None
  * @retval None
  */
#ifdef ADAFRUIT_TFT_JOY_SD_ID802

static void Display_DemoDescription(void)
{
  uint8_t desc[50];
  
  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
  
  /* Clear the LCD */ 
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE); 
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  
  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);  
  
  /* Display LCD messages */
  BSP_LCD_DisplayStringAt(0, 10, (uint8_t *)"STM32F207ZG BSP", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"Drivers examples", CENTER_MODE);
  
  /* Draw Bitmap */
  BSP_LCD_DrawBitmap((BSP_LCD_GetXSize() - 80)/2, 35, (uint8_t *)stlogo);
  
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 15, (uint8_t *)"Copyright (c) STM 2015", CENTER_MODE);
  
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, BSP_LCD_GetYSize()/2 + 15, BSP_LCD_GetXSize(), 40);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE); 
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 25, (uint8_t *)"Use User Button to start", CENTER_MODE);
  sprintf((char *)desc,"%s example", BSP_examples[DemoIndex].DemoName);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 40, (uint8_t *)desc, CENTER_MODE);   
}
#endif /* ADAFRUIT_TFT_JOY_SD_ID802 */

/**
  * @brief  Check for user input.
  * @param  None
  * @retval Input state (1 : active / 0 : Inactive)
  */
uint8_t CheckForUserInput(void)
{
  if(BSP_PB_GetState(BUTTON_USER) != RESET)
  {
    HAL_Delay(10);
    while (BSP_PB_GetState(BUTTON_USER) != RESET);
    return 1 ;
  }
  return 0;
}

/**
  * @brief  Check the availability of adafruit 1.8" TFT shield on top of STM32NUCLEO
  *         board. This is done by reading the state of IO NUCLEO_ADCx_GPIO_PIN (mapped to 
  *         JoyStick available on adafruit 1.8" TFT shield). If the state of NUCLEO_ADCx_GPIO_PIN 
  *         is high then the adafruit 1.8" TFT shield is available.
  * @param  None
  * @retval SHIELD_DETECTED: 1.8" TFT shield is available
  *         SHIELD_NOT_DETECTED: 1.8" TFT shield is not available
  */
static ShieldStatus TFT_ShieldDetect(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct; 

  /* Enable GPIO clock */
  NUCLEO_ADCx_GPIO_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = NUCLEO_ADCx_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(NUCLEO_ADCx_GPIO_PORT, &GPIO_InitStruct);
  
  if(HAL_GPIO_ReadPin(NUCLEO_ADCx_GPIO_PORT, NUCLEO_ADCx_GPIO_PIN) != 0)
  {
    return SHIELD_DETECTED;
  }
  else
  {
    return SHIELD_NOT_DETECTED;
  }
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==USER_BUTTON_PIN)
  {
    UserButtonPressed = 0x01;
  }
}


/**
  * @brief  This function handles the test program fail.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  while(1)
  {
    /* red LED stays ON*/
    BSP_LED_On(LED2);
  }
}

#ifdef USE_FULL_ASSERT

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
#endif /* USE_FULL_ASSERT */ 

/**
  * @}
  */
