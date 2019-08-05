/**
  @page TIM_7PWMOutput TIM 7 PWM Output example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    TIM/TIM_7PWMOutput/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWM signals generation using Timer3 example.
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

Configuration of the TIM1 peripheral to generate seven PWM signals 
with four different duty cycles (50%, 37.5%, 25% and 12.5%).
  
TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
SystemCoreClock is set to 120 MHz.
  
The objective is to generate 7 PWM signal at 17.57 KHz:
  - TIM1_Period = (SystemCoreClock / 17570) - 1
The channel 1 and channel 1N duty cycle is set to 50%
The channel 2 and channel 2N duty cycle is set to 37.5%
The channel 3 and channel 3N duty cycle is set to 25%
The channel 4 duty cycle is set to 12.5%
The Timer pulse is calculated as follows:
  
  - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  
The TIM1 waveforms can be displayed using an oscilloscope.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - TIM/TIM_7PWMOutput/Inc/stm32f2xx_hal_conf.h     HAL configuration file
  - TIM/TIM_7PWMOutput/Inc/stm32f2xx_it.h           Interrupt handlers header file
  - TIM/TIM_7PWMOutput/Inc/main.h                   Main program header file  
  - TIM/TIM_7PWMOutput/Src/stm32f2xx_it.c           Interrupt handlers
  - TIM/TIM_7PWMOutput/Src/main.c                   Main program
  - TIM/TIM_7PWMOutput/Src/stm32f2xx_hal_msp.c      HAL MSP module
  - TIM/TIM_7PWMOutput/Src/system_stm32f2xx.c       STM32F2xx system clock configuration file

     
@par Hardware and Software environment 

  - This example runs on STM32F207xx/217xx device.
    
  - This example has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device and development board

  - STM322xG-EVAL Set-up 
    - Connect the TIM1 pins to an oscilloscope to monitor the different waveforms:
      - TIM1_CH1  pin (PA.08: Pin16 in CN3)
      - TIM1_CH1N pin (PB.13: Pin41 in CN3)
      - TIM1_CH2  pin (PE.11: Pin26 in CN2)
      - TIM1_CH2N pin (PB.14: Pin40 in CN3)
      - TIM1_CH3  pin (PA.10: Pin14 in CN3)
      - TIM1_CH3N pin (PB.15: Pin38 in CN3)
      - TIM1_CH4  pin (PE.14: Pin29 in CN2)


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
