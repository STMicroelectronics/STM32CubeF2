/**
  @page ADC_RegularConversion_DMA ADC3 conversion using DMA for Data transfer example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    ADC/ADC_RegularConversion_DMA/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the ADC Regular Conversion DMA example.
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

How to use the ADC3 and DMA to transfer continuously converted data from 
ADC3 to memory.

The ADC3 is configured to convert continuously channel7(for STM322xG-EVAL).

Each time an end of conversion occurs the DMA transfers, in circular mode, the
converted data from ADC3 DR register to the uhADCxConvertedValue variable.

The user can use the debugger's watch to evaluate uhADCxConvertedValue.

In this example, the system clock is 120MHz, APB2 = 60MHz and ADC clock = APB2/2. 
Since ADC3 clock is 30 MHz and sampling time is set to 3 cycles, the conversion 
time to 12bit data is 12 cycles so the total conversion time is (12+3)/30= 0.5us(2Msps).

User can vary the ADC3 channel7(for STM322xG-EVAL) voltage using the Eval Board potentiometer.

STM32 Eval board's LEDs can be used to monitor the transfer status:
 - LED1 is ON when the conversion is complete.
 - LED3 is ON when there are an error in initialization.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - ADC/ADC_RegularConversion_DMA/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - ADC/ADC_RegularConversion_DMA/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - ADC/ADC_RegularConversion_DMA/Inc/main.h                  Main program header file  
  - ADC/ADC_RegularConversion_DMA/Src/stm32f2xx_it.c          Interrupt handlers
  - ADC/ADC_RegularConversion_DMA/Src/main.c                  Main program
  - ADC/ADC_RegularConversion_DMA/Src/stm32f2xx_hal_msp.c     HAL MSP module
  - ADC/ADC_RegularConversion_DMA/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file


@par Hardware and Software environment 

  - This example runs on STM32F207xx/217xx device.
    
  - This example has been tested with STM322xG-EVAL evaluation board and can be
    easily tailored to any other supported device and development board.
  
  - STM322xG-EVAL Set-up
    - Use the Potentiometer (RV1) of the Eval board (connected to PF.09).


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
