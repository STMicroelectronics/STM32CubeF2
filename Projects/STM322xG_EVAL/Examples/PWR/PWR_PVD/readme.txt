/**
  @page PWR_PVD PWR Programmable Voltage Detector (PVD) example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    PWR/PWR_PVD/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWR Programmable Voltage Detector (PVD) example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

How to configure the programmable voltage detector by using an external interrupt 
line. External DC supply must be used to supply Vdd.

In this example, EXTI line 16 is configured to generate 
an interrupt on each rising or falling edge of the PVD output signal (which 
indicates that the Vdd voltage is below the PVD threshold).
In the interrupt routine a LED connected to a specific GPIO pin is toggled every 
time the voltage drops below or above the target threshold.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - PWR/PWR_PVD/Inc/stm32f2xx_hal_conf.h     HAL configuration file
  - PWR/PWR_PVD/Inc/stm32f2xx_it.h           Interrupt handlers header file
  - PWR/PWR_PVD/Inc/main.h                   header file for main.c
  - PWR/PWR_PVD/Src/system_stm32f2xx.c       STM32F2xx system clock configuration file
  - PWR/PWR_PVD/Src/stm32f2xx_it.c           Interrupt handlers
  - PWR/PWR_PVD/Src/main.c                   Main program
  - PWR/PWR_PVD/Src/stm32f2xx_hal_msp.c      HAL MSP module
  

@par Hardware and Software environment

  - This example runs on STM32F207xx/217xx device.  
    
  - This example has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.

  - STM322xG-EVAL Set-up
    - Use LED1, LED2 and LED3 connected respectively to PG.06, PG.08 and PI.09 pins
    @note This example can't run on the STM322xG-EVAL board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
