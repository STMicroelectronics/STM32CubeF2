/**
  @page TIM_ExtTriggerSynchro TIM External Trigger Synchro example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    TIM/TIM_ExtTriggerSynchro/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the TIM External Trigger Synchro example.        
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

Synchronization of TIM peripherals in Cascade mode with an external trigger.
Three timers are used in this example:

  1/TIM1 is configured as Master Timer:
      - Toggle Mode is used
      - The TIM1 Enable event is used as Trigger Output 

  2/TIM1 is configured as Slave Timer for an external Trigger connected to TIM1 
    TI2 pin (TIM1 CH2 configured as input pin):
      - The TIM1 TI2FP2 is used as Trigger Input
      - Rising edge is used to start and stop the TIM1: Gated Mode.

  3/TIM3 is slave for TIM1 and Master for TIM4,
      - Toggle Mode is used
      - The ITR1(TIM1) is used as input trigger 
      - Gated mode is used, so start and stop of slave counter
        are controlled by the Master trigger output signal(TIM1 enable event).
      - The TIM3 enable event is used as Trigger Output. 

  4/TIM4 is slave for TIM3,
      - Toggle Mode is used
      - The ITR2(TIM3) is used as input trigger
      - Gated mode is used, so start and stop of slave counter
        are controlled by the Master trigger output signal(TIM3 enable event).

   The TIM1CLK is fixed to 120 MHZ, the Prescaler is equal to 5 so the TIMx clock 
   counter is equal to 20 MHz.
   The TIM3CLK  and TIM4CLK are fixed to 60 MHZ, the Prescaler is equal to 5 
   so the TIMx clock counter is equal to 10 MHz. 
   The Three Timers are running at: 
   TIMx frequency = TIMx clock counter/ 2*(TIMx_Period + 1) = 66.7 KHz.
   
  The starts and stops of the TIM1 counters are controlled by the external trigger.
  The TIM3 starts and stops are controlled by the TIM1, and the TIM4 starts and 
  stops are controlled by the TIM3.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - TIM/TIM_ExtTriggerSynchro/Inc/stm32f2xx_hal_conf.h      HAL configuration file
  - TIM/TIM_ExtTriggerSynchro/Inc/stm32f2xx_it.h            Interrupt handlers header file
  - TIM/TIM_ExtTriggerSynchro/Inc/main.h                    Main program header file
  - TIM/TIM_ExtTriggerSynchro/Src/stm32f2xx_it.c            Interrupt handlers
  - TIM/TIM_ExtTriggerSynchro/Src/main.c                    Main program
  - TIM/TIM_ExtTriggerSynchro/Src/stm32f2xx_hal_msp.c       HAL MSP module
  - TIM/TIM_ExtTriggerSynchro/Src/system_stm32f2xx.c        STM32F2xx system clock configuration file  


@par Hardware and Software environment

  - This example runs on STM32F207xx/217xx device.
    
  - This example has been tested with STMicroelectronics STM322xG-EVAL  
    evaluation boards and can be easily tailored to any other supported device and development board

  - STM322xG-EVAL Set-up 
    - Connect an external trigger to the TIM1 CH2 (PE.11: Pin 26 in CN2).

    - Connect the following pins to an oscilloscope to monitor the different waveforms:
      - TIM1 CH1 (PA.08: Pin16 in CN3)
      - TIM3 CH1 (PC.06: Pin21 in CN3)
      - TIM4 CH1 (PB.06: Pin13 in CN4) 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
