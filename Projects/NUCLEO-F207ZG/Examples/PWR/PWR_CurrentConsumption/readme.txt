/**
  @page PWR_CurrentConsumption PWR Current Consumption example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    PWR/PWR_CurrentConsumption/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWR Current Consumption example.
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
  @endverbatim

@par Example Description 

How to configure the system to measure the current consumption in different 
low-power modes.

The Low Power modes are:
  - Sleep Mode
  - STOP mode with RTC
  - STANDBY mode without RTC and BKPSRAM
  - STANDBY mode with RTC
  - STANDBY mode with RTC and BKPSRAM
  
To run this example, user has to follow these steps:
 1. Select the Low power modes to be measured by uncommenting the corresponding
    line inside the stm32f2xx_lp_modes.h file.
    @code
       /* #define SLEEP_MODE               */
       /* #define STOP_MODE                */
       /* #define STANDBY_MODE             */
       /* #define STANDBY_RTC_MODE         */
       /* #define STANDBY_RTC_BKPSRAM_MODE */
    @endcode       

 2. Use an external amperemeter to measure the IDD current. 

 3. This example can not be used in DEBUG mode, this is due to the fact that the 
    Cortex-M3 core is no longer clocked during low power mode so debugging 
    features are disabled.

Here below a detailed description of the example code:

  @verbatim

 1. After reset, the program waits for User button connected to the PC.13 to be 
    pressed - green LED (LED1) is blinking slowly (1 sec.)- to enter the selected low power mode.
     - When the RTC is not used in the low power mode configuration, press
       again the User button (PC.13) to exit the low power mode except STANDBY mode
       which is waked up by connecting wakeup pin (PA.00) to 3.3v.
       Green LED (LED1) toggles while entering in User button press IT callback.
     - When the RTC is used, the wakeup from low power mode is automatically 
       generated by the RTC (after 20s)
       Green LED (LED1) toggles while entering in RTC IT callback.

--> In anyway, wrong end of test is showing red LED (LED2) stay ON

 2. Low power modes description:

    - Sleep Mode
    ============  
            - System Running at PLL (120MHz)
            - Flash 3 wait state
            - Instruction and Data caches ON
            - Prefetch OFF       
            - Code running from Internal FLASH
            - All peripherals disabled
            - Wakeup using EXTI Line (User Button PC.13)

    - STOP Mode
    ===========
            - RTC Clocked by LSI
            - Regulator in LP mode
            - HSI, HSE OFF and LSI if not used as RTC Clock source
            - No IWDG
            - FLASH in deep power down mode
            - Automatic Wakeup using RTC clocked by LSI (after ~20s)

    - STANDBY Mode
    ==============
            - Backup SRAM and RTC OFF
            - IWDG and LSI OFF
            - Wakeup using WakeUp Pin (PA.00) by connecting PA0 (pin 29 in CN10  
              connector) to 3.3V (pin 7 in CN8 connector)
                        
    - STANDBY Mode with RTC clocked by LSI 
    ==========================================
            - RTC Clocked by LSI
            - IWDG OFF and LSI OFF  if not used as RTC Clock source
            - Backup SRAM OFF
            - Automatic Wakeup using RTC clocked by LSI (after ~20s)

    - STANDBY Mode with RTC clocked by LSI and BKPSRAM
    ======================================================
            - RTC Clocked by LSI
            - Backup SRAM ON
            - IWDG OFF
            - Automatic Wakeup using RTC clocked by LSI (after ~20s)

   @endverbatim


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
	  
@note On the NUCLEO-207ZG board, an extra current consumption(~4µA) is added due to the Ethernet PHY. 
      So, to reach the correct current consumption values, this example configures the Ethernet
      PHYs in Low power mode.


@par Directory contents 

  - PWR/PWR_CurrentConsumption/Inc/stm32f2xx_hal_conf.h     HAL configuration file
  - PWR/PWR_CurrentConsumption/Inc/stm32f2xx_it.h           Interrupt handlers header file
  - PWR/PWR_CurrentConsumption/Inc/main.h                   Main program header file 
  - PWR/PWR_CurrentConsumption/Inc/stm32f2xx_lp_modes.h     STM32F2xx Low Power Modes header file
  - PWR/PWR_CurrentConsumption/Src/stm32f2xx_it.c           Interrupt handlers
  - PWR/PWR_CurrentConsumption/Src/main.c                   Main program
  - PWR/PWR_CurrentConsumption/Src/stm32f2xx_hal_msp.c      HAL MSP module
  - PWR/PWR_CurrentConsumption/Src/stm32f2xx_lp_modes.c     STM32F2xx Low Power Modes source file
  - PWR/PWR_CurrentConsumption/Src/system_stm32f2xx.c       STM32F2xx system clock configuration file


@par Hardware and Software environment

  - This example runs on STM32F207xG devices.
    
  - This example has been tested with NUCLEO-207ZG Rev.B
    board and can be easily tailored to any other supported device 
    and development board.

  - NUCLEO-207ZG Set-up
    - Use LED2 connected to PB.07 pin.
      * LED2 (RED) will stay ON if initialization fails.
    - Use LED1 connected to PB.00 pin.
      * LED1 (GREEN) will slowly toggle (1sec.) waiting for user to launch test, then will turn OFF
      * LED1 (GREEN) will toggle fast (100ms) while returning from STANDBY mode (PWR flag check callback) 
      * LED1 (GREEN) will toggle fast (100ms) at the end of test in case of success.
    - Use User Button connected to PC.13 pin.
    - Connect (PA.00) to 3.3v to wake up from STANDBY mode.
    - Connect an amperemeter to jumper JP5 to measure the IDD current
	

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
