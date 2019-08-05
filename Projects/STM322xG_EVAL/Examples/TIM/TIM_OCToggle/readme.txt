/**
  @page TIM_OCToggle TIM Output Compare Toggle example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    TIM/TIM_OCToggle/Readme.txt 
  * @author  MCD Application Team
  * @brief   This example shows how to configure the Timer to generate four 
  *          delayed signals.
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

Configuration of the TIM peripheral to generate four different 
signals at four different frequencies.

The TIM3CLK frequency is set to SystemCoreClock / 2 (Hz), and we want to get TIM3
counter clock at 30 MHz so the Prescaler is computed as following:
- Prescaler = (TIM3CLK / TIM3 counter clock) - 1

SystemCoreClock is set to 120 MHz for STM32F2xx devices

The TIM3 CCR1 register value is equal to 40961: 
CC1 update rate = TIM3 counter clock / CCR1_Val = 732.40 Hz,
so the TIM3 Channel 1 generates a periodic signal with a frequency equal to 365.5 Hz.

The TIM3 CCR2 register is equal to 20480:
CC2 update rate = TIM3 counter clock / CCR2_Val = 1464.84 Hz
so the TIM3 channel 2 generates a periodic signal with a frequency equal to 733 Hz.

The TIM3 CCR3 register is equal to 10240:
CC3 update rate = TIM3 counter clock / CCR3_Val = 2929.68 Hz
so the TIM3 channel 3 generates a periodic signal with a frequency equal to 1466 Hz.

The TIM3 CCR4 register is equal to 5120:
CC4 update rate = TIM3 counter clock / CCR4_Val =  5859.37 Hz
so the TIM3 channel 4 generates a periodic signal with a frequency equal to 2932 Hz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note LED4 is turned ON, because it's sharing the same GPIO pin with the TIM3 channel 2.


@par Directory contents 

  - TIM/TIM_OCToggle/Inc/stm32f2xx_hal_conf.h         HAL configuration file
  - TIM/TIM_OCToggle/Inc/stm32f2xx_it.h               Interrupt handlers header file
  - TIM/TIM_OCToggle/Inc/main.h                       Main program header file  
  - TIM/TIM_OCToggle/Src/stm32f2xx_it.c               Interrupt handlers
  - TIM/TIM_OCToggle/Src/main.c                       Main program
  - TIM/TIM_OCToggle/Src/stm32f2xx_hal_msp.c          HAL MSP module
  - TIM/TIM_OCToggle/Src/system_stm32f2xx.c           STM32F2xx system clock configuration file

                                                      
@par Hardware and Software environment 

  - This example runs on STM32F207xx/217xx device.
    
  - This example has been tested with STMicroelectronics STM322xG-EVAL  
    evaluation boards and can be easily tailored to any other supported device and development board

  - STM322xG-EVAL Set-up 
    - Connect the TIM3 pins to an oscilloscope to monitor the different waveforms:
       - PC.06(Pin21 in CN3) (TIM3_CH1)
       - PC.07(Pin20 in CN3) (TIM3_CH2)
       - PC.08(Pin18 in CN3) (TIM3_CH3)
       - PC.09(Pin17 in CN3) (TIM3_CH4) 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
