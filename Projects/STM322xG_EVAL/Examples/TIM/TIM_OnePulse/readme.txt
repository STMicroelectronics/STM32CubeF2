/**
  @page TIM_OnePulse TIM One Pulse example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    TIM/TIM_OnePulse/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the TIM One Pulse example.      
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

Use of the TIM peripheral to generate a single pulse when 
an external signal rising edge is received on the timer input pin.

  TIM2CLK = SystemCoreClock/2, we want to get TIM2 counter clock at 30 MHz:
             - Prescaler = (TIM2CLK / TIM2 counter clock) - 1

  SystemCoreClock is set to 120 MHz.

  The Autoreload value is 65535 (TIM4->ARR), so the maximum frequency value to 
  trigger the TIM4 input is 30000000/65535 = 458 Hz.

  The TIM4 is configured as follows: 
  The One Pulse mode is used, the external signal is connected to TIM4 CH2 pin (PB.07), 
  the rising edge is used as active edge, the One Pulse signal is output 
  on TIM4_CH1 (PB.06).

  The TIM_Pulse defines the delay value, the delay value is fixed to:
  delay =  CCR1/TIM4 counter clock = 16383 / 30000000 = 546  us. 
  The (TIM_Period - TIM_Pulse) defines the One Pulse value, the pulse value is fixed to:
  One Pulse value = (TIM_Period - TIM_Pulse)/TIM4 counter clock 
                  = (65535 - 16383) / 30000000 = 1.638 ms.

The one pulse waveform can be displayed using an oscilloscope.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - TIM/TIM_OnePulse/system_stm32f2xx.c             STM32F2xx system clock configuration file
  - TIM/TIM_OnePulse/stm32f2xx_hal_conf.h           HAL configuration file
  - TIM/TIM_OnePulse/stm32f2xx_it.h                 Interrupt handlers header file
  - TIM/TIM_OnePulse/stm32f2xx_it.c                 Interrupt handlers
  - TIM/TIM_OnePulse/main.c                         Main program
  - TIM/TIM_OnePulse/main.h                         Main program header file


@par Hardware and Software environment

  - This example runs on STM32F207xx/217xx Devices.
    
  - This example has been tested with STM322xG-EVAL evaluation board and can be
    easily tailored to any other supported device and development board. 

   - STM322xG-EVAL Set-up 
    - Connect the external signal to the TIM4_CH2 pin (PB.07: Pin12 in CN4)
    - Connect the TIM4_CH1 (PB.06: Pin13 in CN4) pin to an oscilloscope to monitor the waveform.  


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
