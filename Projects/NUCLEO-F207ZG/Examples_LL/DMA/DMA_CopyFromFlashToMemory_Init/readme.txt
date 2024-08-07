/**
  @page DMA_CopyFromFlashToMemory_Init DMA example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/DMA/DMA_CopyFromFlashToMemory_Init/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the DMA example.
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

This example describes how to use a DMA to transfer a word data buffer
from Flash memory to embedded SRAM. Peripheral initialization done
using LL initialization function to demonstrate LL init usage.

At the beginning of the main program the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 120 MHz.

Then the LED_Init() function is used to initialize the LED1.

Then the Configure_DMA() function is used to configure the DMA2_Stream0 to transfer the contents of a 32-word data
buffer stored in Flash memory to the reception buffer declared in RAM.

The start of transfer is triggered by software(LL_DMA_EnableStream()). DMA2_Stream0 memory-to-memory
transfer is enabled. Source and destination addresses incrementing is also enabled.
The transfer is started by setting the channel enable bit for DMA2_Stream0.
At the end of the transfer a Transfer Complete interrupt is generated since it
is enabled and the callback function (customized by user) is called.

Finally, aSRC_Const_Buffer and aDST_Buffer are compared through Buffercmp() in order to 
check buffers correctness.  

NUCLEO-F207ZG's LED1 can be used to monitor the transfer status:
- LED1 is turn on if DMA data transferred consistency.
- LED1 is blinking every 1 sec in case of error.

@par Directory contents 

  - DMA/DMA_CopyFromFlashToMemory_Init/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - DMA/DMA_CopyFromFlashToMemory_Init/Inc/main.h                  Header for main.c module  
  - DMA/DMA_CopyFromFlashToMemory_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - DMA/DMA_CopyFromFlashToMemory_Init/Src/stm32f2xx_it.c          Interrupt handlers
  - DMA/DMA_CopyFromFlashToMemory_Init/Src/main.c                  Main program
  - DMA/DMA_CopyFromFlashToMemory_Init/Src/system_stm32f2xx.c      STM32F2xx system source file

@par Hardware and Software environment

  - This example runs on STM32F207xx devices.
    
  - This example has been tested with NUCLEO-F207ZG board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
