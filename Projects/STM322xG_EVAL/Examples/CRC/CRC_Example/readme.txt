/**
  @page CRC_Example Cyclic Redundancy Check example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    CRC/CRC_Example/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of Cyclic Redundancy Check example.
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

How to configure the CRC using the HAL API. The CRC (cyclic
redundancy check) calculation unit computes the CRC code of a given buffer of
32-bit data words, using a fixed generator polynomial (0x4C11DB7).

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 120 MHz.

The CRC peripheral configuration is ensured by the HAL_CRC_Init() function.
This later is calling the HAL_CRC_MspInit()function which core is implementing
the configuration of the needed CRC resources according to the used hardware (CLOCK, 
GPIO, DMA and NVIC). You may update this function to change CRC configuration.

The calculated CRC code is compared to displayed on the debugger in uwCRCValue variable.
Once calculated, the CRC value is compared to the CRC expected value.

STM32 Eval board's LEDs can be used to monitor the example status:
  - LED1 is ON when Right CRC calculated value
  - LED3 is ON when Wrong CRC calculated value there are an error in initialization.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 
  
  - CRC/CRC_Example/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - CRC/CRC_Example/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - CRC/CRC_Example/Inc/main.h                  Main program header file
  - CRC/CRC_Example/Src/stm32f2xx_it.c          Interrupt handlers
  - CRC/CRC_Example/Src/main.c                  Main program
  - CRC/CRC_Example/Src/stm32f2xx_hal_msp.c     HAL MSP module 
  - CRC/CRC_Example/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file

     
@par Hardware and Software environment

  - This example runs on STM32F207xx/217xx device.  
    
  - This example has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.
      

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 

 */
 