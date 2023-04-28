/**
  @page TIM_Synchronization Timers Synchronization example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    TIM/TIM_Synchronization/Readme.txt 
  * @author  MCD Application Team
  * @brief   How to command 2 Timers as slaves (TIM3 & TIM4) using a Timer
  *          as master (TIM1)
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

Synchronization of TIM1 and TIM3/TIM4 timers in Parallel mode.

Timers synchronization in parallel mode:


                                                       ___________ 
                                                 ITR0 |  SLAVE 1  |
                                     _________________|    TIM3   |
   ___________                      |                 |___________|
  |   MASTER  |TRGO_Update          |                 
  |    TIM1   |---------------------|               
  |___________|                     |                  ___________ 
                                    |_________________|  SLAVE 2  |
                                                 ITR0 |    TIM4   |
                                                      |___________|
                         

1/ TIM1 is configured as Master Timer:
   - PWM Mode is used
   - The TIM1 Update event is used as Trigger Output 
 
2/ TIM3 and TIM4 are slaves for TIM1,
   - PWM Mode is used
   - The ITR0(TIM1) is used as input trigger for both slaves
   - Gated mode is used, so starts and stops of slaves counters
     are controlled by the Master trigger output signal(update event).

The TIM1 counter clock is 120 MHz.

  The Master Timer TIM1 is running at:
  TIM1 frequency = TIM1 counter clock / (TIM1_Period + 1) = 469 KHz
  and the duty cycle is equal to: TIM1_CCR1/(TIM1_ARR + 1) = 50%

  The TIM3 is running at: 
  (TIM1 frequency)/ ((TIM3 period +1)* (TIM1_Repetition_Counter+1)) = 31.25 KHz and
  a duty cycle equal to TIM3_CCR1/(TIM3_ARR + 1) = 33.3%

  The TIM4 is running at:
  (TIM1 frequency)/ ((TIM4 period +1)* (Repetition_Counter+1)) = 46.9 KHz and
  a duty cycle equal to TIM4_CCR1/(TIM4_ARR + 1) = 50%


The PWM waveform can be displayed using an oscilloscope.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - TIM/TIM_Synchronization/Inc/stm32f2xx_hal_conf.h      HAL configuration file
  - TIM/TIM_Synchronization/Inc/stm32f2xx_it.h            Interrupt handlers header file
  - TIM/TIM_Synchronization/Inc/main.h                    Main program header file
  - TIM/TIM_Synchronization/Src/stm32f2xx_it.c            Interrupt handlers
  - TIM/TIM_Synchronization/Src/main.c                    Main program
  - TIM/TIM_Synchronization/Src/stm32f2xx_hal_msp.c       HAL MSP module
  - TIM/TIM_Synchronization/Src/system_stm32f2xx.c        STM32F2xx system clock configuration file  


@par Hardware and Software environment

  - This example runs on STM32F207xx/217xx device.
    
  - This example has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device and development board

  - STM322xG-EVAL Set-up 
   Connect the following pins to an oscilloscope to monitor the different waveforms:
      - TIM1 CH1 (PA.08: Pin16 in CN3)
      - TIM3 CH1 (PC.06: Pin21 in CN3)
      - TIM4 CH1 (PB.06: Pin13 in CN4)


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
