/**
  @page ADC_RegularConversion_DMA conversion using DMA for Data transfer

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    ADC/ADC_RegularConversion_DMA/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the ADC RegularConversion DMA example.
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

How to use the ADC1 and DMA to transfer continuously converted data from 
ADC1 to memory.

The ADC1 is configured to convert continuously ADC_CHANNEL_10.

Each time an end of conversion occurs the DMA transfers, in circular mode, the
converted data from ADC1 DR register to the uhADCxConvertedValue variable.

The uhADCxConvertedValue read value is coded on 12 bits, the Vref+ reference voltage is connected 
on the board to VDD (+3.3V), the Vref- reference voltage is connected on the board to the ground.
To convert the read value in volts, here is the equation to apply :
Voltage = uhADCxConvertedValue * (Vref+ - Vref-) / (2^12) = uhADCxConvertedValue * 3.3 / 4096

In this example, the system clock is 120MHz, APB2 = 60MHz and ADC clock = APB2/2. 
Since ADC1 clock is 30 MHz and sampling time is set to 3 cycles, the conversion 
time to 12bit data is 12 cycles so the total conversion time is (12+3)/30= 0.5us(2Msps).

User can vary the ADC_CHANNEL_10 voltage by applying an input voltage on pin PC.00 (pin3 connector 9)
(e.g. using function generator).

STM32 board's LEDs can be used to monitor the transfer status:
  - LED1 is ON when the conversion is complete.
  - LED3 is ON when there is an error in ADC initialization, in ADC channel configuration 
    or during conversion process.

@par Directory contents 

  - ADC/ADC_RegularConversion_DMA/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - ADC/ADC_RegularConversion_DMA/Inc/stm32f2xx_it.h          DMA interrupt handlers header file
  - ADC/ADC_RegularConversion_DMA/Inc/main.h                  Header for main.c module  
  - ADC/ADC_RegularConversion_DMA/Src/stm32f2xx_it.c          DMA interrupt handlers
  - ADC/ADC_RegularConversion_DMA/Src/main.c                  Main program
  - ADC/ADC_RegularConversion_DMA/Src/stm32f2xx_hal_msp.c     HAL MSP file 
  - ADC/ADC_RegularConversion_DMA/Src/system_stm32f2xx.c      STM32F2xx system source file

@par Hardware and Software environment 

  - This example runs on STM32F207xx devices.
  
  - This example has been tested with NUCLEO-207ZG board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
