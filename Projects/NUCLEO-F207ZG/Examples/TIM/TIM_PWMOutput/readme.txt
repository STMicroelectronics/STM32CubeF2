/**
  @page TIM_PWMOutput TIM PWM Output example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    TIM/TIM_PWMOutput/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWM signals generation using TIM3
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

Configuration of the TIM peripheral in PWM (pulse width modulation) mode.

SystemCoreClock is set to 120 MHz for STM32F2xx Devices.

    In this example TIM3 input clock (TIM3CLK) is set to APB1 clock x 2,
    since APB1 prescaler is equal to 2.
      TIM3CLK = APB1CLK*2
      APB1CLK = HCLK/4
      => TIM3CLK = HCLK/2 = SystemCoreClock/2

    To get TIM3 counter clock at 10 MHz, the prescaler is computed as follows:
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = ((SystemCoreClock / 2) /10 MHz) - 1

    To get TIM3 output clock at 15 KHz, the period (ARR)) is computed as follows:
       ARR = (TIM3 counter clock / TIM3 output clock) - 1
           = 665

    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR + 1)* 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR + 1)* 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR + 1)* 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR + 1)* 100 = 12.5%


The PWM waveforms can be displayed using an oscilloscope.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - TIM/TIM_PWMOutput/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - TIM/TIM_PWMOutput/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - TIM/TIM_PWMOutput/Inc/main.h                  Header for main.c module  
  - TIM/TIM_PWMOutput/Src/stm32f2xx_it.c          Interrupt handlers
  - TIM/TIM_PWMOutput/Src/main.c                  Main program
  - TIM/TIM_PWMOutput/Src/stm32f2xx_hal_msp.c     HAL MSP file
  - TIM/TIM_PWMOutput/Src/system_stm32f2xx.c      STM32F2xx system source file


@par Hardware and Software environment

  - This example runs on STM32F207xx devices.
  - In this example, the clock is set to 120 MHz.
    
  - This example has been tested with STMicroelectronics NUCLEO-207ZG Rev.B 
    board and can be easily tailored to any other supported device 
    and development board.      

  - NUCLEO-207ZG Set-up
   Connect the following pins to an oscilloscope to monitor the different waveforms:
        - TIM3_CH1 : PB.04 (pin 19 in CN7 connector)
        - TIM3_CH2 : PB.05 (pin 13 in CN7 connector)
        - TIM3_CH3 : PB.00 (pin 31 in CN10 connector)
        - TIM3_CH4 : PB.01 (pin 7 in CN10 connector)


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 */
