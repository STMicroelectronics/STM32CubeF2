/**
  @page CRC_CalculateAndCheck CRC : CRC calculation and computed CRC value checking (HAL/LL mixed usage example)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    CRC/CRC_CalculateAndCheck/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the CRC_CalculateAndCheck example.
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

How to use a CRC peripheral through the STM32F2xx CRC HAL & LL API 
(an LL API is used for performance improvement). A fixed CRC-32 (Ethernet)
generator polynomial: 0x4C11DB7 is used in the CRC peripheral.
The CRC (cyclic redundancy check) calculation unit first computes the CRC code
of a given buffer of 32-bit data words, using HAL APIs
In a second step, the CRC calculation unit is reset for a new CRC calculation
and the second calculation is started using the CRC LL API. Both calculated CRC
codes are checked against the expected value.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK).

The CRC peripheral configuration is ensured by HAL_CRC_Init() function.
The latter is calling HAL_CRC_MspInit() function which core is implementing
the configuration of the needed CRC resources according to the used hardware (CLOCK). 

For each computation, calculated CRC code is stored in uwCRCValue variable.
Once calculated, CRC value (uwCRCValue) is compared to the CRC expected value (uwExpectedCRCValue),
and if both checks are successful, LED is turned On. 
In case of errors, LED is blinking (1sec period).

STM32 Eval board's LEDs are used to monitor the example status:
  - LED1 is ON when correct CRC values are calculated
  - LED3 is ON when there is an error in initialization or if an incorrect CRC value is calculated.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 
  
  - CRC/CRC_CalculateAndCheck/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - CRC/CRC_CalculateAndCheck/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - CRC/CRC_CalculateAndCheck/Inc/main.h                  Header for main.c module
  - CRC/CRC_CalculateAndCheck/Src/stm32f2xx_it.c          Interrupt handlers
  - CRC/CRC_CalculateAndCheck/Src/main.c                  Main program
  - CRC/CRC_CalculateAndCheck/Src/stm32f2xx_hal_msp.c     HAL MSP module 
  - CRC/CRC_CalculateAndCheck/Src/system_stm32f2xx.c      STM32F2xx system source file

     
@par Hardware and Software environment

  - This example runs on STM32F207xx devices.
    
  - This example has been tested with NUCLEO-F207ZG board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 */
 