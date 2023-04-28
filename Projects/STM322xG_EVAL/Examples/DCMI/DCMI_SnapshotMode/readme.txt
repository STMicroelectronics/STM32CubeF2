/**
  @page DCMI_SnapShotMode DCMI Snapshot Mode example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    DCMI/DCMI_SnapShotMode/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the DCMI SnapShotMode example.
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

How to use the DCMI to interface with camera module and display in snapshot mode the picture on LCD.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 120 MHz.

The Digital camera interface is configured to receive the capture from
the camera module mounted on STM322xG-EVAL evaluation board.
DMA2 Stream1 channel1 is configured to transfer the picture from DCMI peripheral
to an external RAM.   
When the frame event callback is raised the picture is transferred to the LCD frame buffer.

The camera module is configured to generate QVGA (320x240) image resolution
and the LCD is configured to display QVGA image resolution

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents
    - DCMI/DCMI_SnapShotMode/Inc/stm32f2xx_hal_conf.h        HAL configuration file
    - DCMI/DCMI_SnapShotMode/Inc/main.h                      Main program header file
    - DCMI/DCMI_SnapShotMode/Inc/stm32f2xx_it.h              Interrupt handlers header file
    - DCMI/DCMI_SnapShotMode/Inc/stm32f2xx_hal_conf.h        HAL Configuration file 
    - DCMI/DCMI_SnapShotMode/Src/main.c                      Main program  
    - DCMI/DCMI_SnapShotMode/Src/stm32f2xx_it.c              Interrupt handlers   
    - DCMI/DCMI_SnapShotMode/Src/system_stm32f2xx.c          STM32F2xx system clock configuration file


@par Hardware and Software environment  

  - This example runs on STM32F207xx/217xx device. 
     
  - This example has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.
  
  - STM322xG-EVAL Set-up
    - Please ensure that jumper JP5 is fitted in position 1-2


@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
  

 */
                                   