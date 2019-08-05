/**
  @page CAN_LoopBack CAN LoopBack example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    CAN/CAN_LoopBack/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the CAN LoopBack example.
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

How to set up a communication with the CAN in loopback mode.

The CAN cell first performs a transmission and a reception of a standard data
frame by polling at 1MB/s. The received frame is checked and some LEDs light
up to indicate whether the communication was successful.

STM32 Eval board's LEDs can be used to monitor the transfer status:
 - LED1 is ON when the transfer is complete.
 - LED2 is ON when there are an error of the transfer.
 - LED3 is ON when there are an error in initialisation.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - CAN/CAN_LoopBack/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - CAN/CAN_LoopBack/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - CAN/CAN_LoopBack/Inc/main.h                  Main program header file  
  - CAN/CAN_LoopBack/Src/stm32f2xx_it.c          Interrupt handlers
  - CAN/CAN_LoopBack/Src/main.c                  Main program
  - CAN/CAN_LoopBack/Src/stm32f2xx_hal_msp.c     HAL MSP module
  - CAN/CAN_LoopBack/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file


@par Hardware and Software environment

  - This example runs on STM32F207xx/217xx device.
    
  - This example has been tested with STM322xG-EVAL evaluation board and can be
    easily tailored to any other supported device and development board.

 
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
    
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
