/**
  @page SMARTCARD_T0 Smart Card T0 protocol example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    SMARTCARD/T0/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Smart Card T0 protocol example.
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

Firmware smartcard interface based on USART. The main purpose
of this firmware example is to provide resources that ease the development of applications
using the USART in Smartcard mode.

The firmware interface is composed of library source files developed in order to
support ISO7816-3/4 specification, an application example is also provided.

This example is based on the AN2598 "Smartcard interface with the STM32F101xx 
and STM32F103xx" application note. For more details, please refer to AN2598 
available on www.st.com


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - SMARTCARD/SMARTCARD_T0/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - SMARTCARD/SMARTCARD_T0/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - SMARTCARD/SMARTCARD_T0/Inc/main.h                  Main program header file
  - SMARTCARD/SMARTCARD_T0/Inc/smartcard.h             Header for smartcard.c module
  - SMARTCARD/SMARTCARD_T0/Src/stm32f2xx_it.c          Interrupt handlers
  - SMARTCARD/SMARTCARD_T0/Src/main.c                  Main program
  - SMARTCARD/SMARTCARD_T0/Inc/smartcard.c             smartcard module
  - SMARTCARD/SMARTCARD_T0/Src/stm32f2xx_hal_msp.c     HAL MSP module
  - SMARTCARD/SMARTCARD_T0/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file


@par Hardware and Software environment

  - This example runs on STM32F207xx/217xx device.
  
  - This example has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board. 
      
  - STM322xG-EVAL Set-up
    - Use LED1, LED2, LED3 and LED4 connected respectively to PG.06, PG.08, PI.09
      and PC.07 pins.
    - Please ensure that jumper JP21 is fitted.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
