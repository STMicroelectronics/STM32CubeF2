/**
  @page TIM_PWMOutput TIM PWM Output example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    TIM/TIM_PWMOutput/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWM signals generation using Timer3 example.
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

The TIM3CLK frequency is set to SystemCoreClock / 2 (Hz), to get TIM3 counter
clock at 21 MHz the Prescaler is computed as following:
   - Prescaler = (TIM3CLK / TIM3 counter clock) - 1

SystemCoreClock is set to 120 MHz for STM32F2xx Devices.

The TIM3 generates 4 PWM signals at 45.045 KHz:

    TIM3_Output Frequency = TIM3 counter clock/(ARR + 1)
                          = 30 MHz / 666
                          = 45.045 KHz
                        
The TIM3 CCR1 register value is equal to 333, so the TIM3 Channel 1 generates a 
PWM signal with a frequency equal to 45 KHz and a duty cycle equal to 50%:
TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR + 1)* 100 = 50%

The TIM3 CCR2 register value is equal to 249, so the TIM3 Channel 2 generates a 
PWM signal with a frequency equal to 45.045 KHz and a duty cycle equal to 37.5%:
TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR + 1)* 100 = 37.5%

The TIM3 CCR3 register value is equal to 166, so the TIM3 Channel 3 generates a 
PWM signal with a frequency equal to 45.045 KHz and a duty cycle equal to 25%:
TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR + 1)* 100 = 25%

The TIM3 CCR4 register value is equal to 83, so the TIM3 Channel 4 generates a 
PWM signal with a frequency equal to 45.045 KHz and a duty cycle equal to 12.5%:
TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR + 1)* 100 = 12.5%

The PWM waveforms can be displayed using an oscilloscope.

                             
@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note LED4 is turned ON, because it's sharing the same GPIO pin with the TIM3 channel 2.


@par Directory contents 

  - TIM/TIM_PWMOutput/Inc/stm32f2xx_hal_conf.h     HAL configuration file
  - TIM/TIM_PWMOutput/Inc/stm32f2xx_it.h           Interrupt handlers header file
  - TIM/TIM_PWMOutput/Inc/main.h                   Main program header file  
  - TIM/TIM_PWMOutput/Src/stm32f2xx_it.c           Interrupt handlers
  - TIM/TIM_PWMOutput/Src/main.c                   Main program
  - TIM/TIM_PWMOutput/Src/stm32f2xx_hal_msp.c      HAL MSP module
  - TIM/TIM_PWMOutput/Src/system_stm32f2xx.c       STM32F2xx system clock configuration file

                                     
@par Hardware and Software environment 

  - This example runs on STM32F207xx/217xx device.
    
  - This example has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device and development board

  - STM322xG-EVAL Set-up 
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
        - PC.06(Pin21 in CN3): (TIM3_CH1)
        - PC.07(Pin20 in CN3): (TIM3_CH2)
        - PC.08(Pin18 in CN3): (TIM3_CH3)
        - PC.09(Pin17 in CN3): (TIM3_CH4)  


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
