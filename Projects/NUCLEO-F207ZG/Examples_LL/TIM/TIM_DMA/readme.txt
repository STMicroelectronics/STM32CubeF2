/**
  @page TIM_DMA TIM example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/TIM/TIM_DMA/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the TIM_DMA example.
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

Use of the DMA with a timer update request 
to transfer data from memory to Timer Capture Compare Register 3 (TIMx_CCR3). This 
example is based on the STM32F2xx TIM LL API. The peripheral initialization 
uses LL unitary service functions for optimization purposes (performance and size).

The following configuration values are used in this example:
  - TIM3CLK = SystemClock
  - Counter repetition = 3 
  - Prescaler = 0 
  - TIM3 counter clock = SystemClock
  - SystemCoreClock is set to 120 MHz for STM32F2xx Devices.

The objective is to configure TIM3 channel 3 to generate PWM edge aligned 
signal with a frequency equal to 17.57 KHz, and a variable duty cycle that
is changed by the DMA after a specific number of Update DMA request.

The number of this repetitive requests is defined by the TIM3 Repetition counter,
each 4 Update Requests, the TIM3 Channel 3 Duty Cycle changes to the next new 
value defined by the aCCValue_Buffer.

The PWM waveform can be displayed using an oscilloscope.

Whenever a DMA transfer fails LED2 flashes with a frequency of 1 Hz.
 
@note PWM signal frequency value mentioned above is theoretical (obtained when
      the system clock frequency is exactly 120 MHz). Since the generated system
      clock frequency may vary from one board to another observed PWM signal
      frequency might be slightly different.

@note LED1 is always ON since it shares the same pin as TM3_CH3.

@par Directory contents 

  - TIM/TIM_DMA/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - TIM/TIM_DMA/Inc/main.h                  Header for main.c module
  - TIM/TIM_DMA/Inc/stm32_assert.h          Template file to include assert_failed function
  - TIM/TIM_DMA/Src/stm32f2xx_it.c          Interrupt handlers
  - TIM/TIM_DMA/Src/main.c                  Main program
  - TIM/TIM_DMA/Src/system_stm32f2xx.c      STM32F2xx system source file


@par Hardware and Software environment

  - This example runs on STM32F207xx devices.
    
  - This example has been tested with NUCLEO-F207ZG board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-F207ZG Set-up
    - Connect TIM3 pin to the oscilloscope to monitor the generated waveform:
      - TIM3_CH3  PB.00: connected to pin 31 of CN10 connector 

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 */
