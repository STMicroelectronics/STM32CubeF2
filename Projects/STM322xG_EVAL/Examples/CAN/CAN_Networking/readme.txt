/**
  @page CAN_Networking CAN Networking example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    CAN/CAN_Networking/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the CAN Networking example.
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

How to configure the CAN peripheral to send and receive CAN frames in 
normal mode. 

The sent frames are used to control LEDs by pressing  key push button.

The CAN serial communication link is a bus to which a number of units may be
connected. This number has no theoretical limit. Practically the total number
of units will be limited by delay times and/or electrical loads on the bus line.

This program behaves as follows:
  - After reset, all LEDs are OFF on the N eval boards
  - By Pressing on KEY Button : LED1 turns ON and all other LEDs are OFF, on the N
    eval boards connected to the bus. 
  - Press on KEY Button again to send CAN Frame to command LEDn+1 ON, all other LEDs 
    are OFF on the N eval boards.
    
@note This example is tested with a bus of 3 units. The same program example is 
      loaded in all units to send and receive frames.
@note Any unit in the CAN bus may play the role of sender (by pressing KEY button)
      or receiver.
	
	The CAN is configured as follows:
		- ID Filter  = All identifiers are allowed
		- RTR = Data
		- DLC = 1 byte
		- Data: LED number that should be turned ON

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - CAN/CAN_Networking/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - CAN/CAN_Networking/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - CAN/CAN_Networking/Inc/main.h                  Main program header file  
  - CAN/CAN_Networking/Src/stm32f2xx_it.c          Interrupt handlers
  - CAN/CAN_Networking/Src/main.c                  Main program
  - CAN/CAN_Networking/Src/stm32f2xx_hal_msp.c     HAL MSP module
  - CAN/CAN_Networking/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file
  

@par Hardware and Software environment 

  - This example runs on STM32F207xx/217xx device.
    
  - This example has been tested with STM322xG-EVAL evaluation board and can be
    easily tailored to any other supported device and development board.

  - STM322xG-EVAL Set-up 
    - Use LED1, LED2, LED3 and LED4 connected respectively to PG.06, PG.08, PI.09
      and PC.07 pins
    - Use KEY Push Button connected to PG15
    - Connect a female/female CAN cable between at least 2 EVAL CAN connectors (CN10)
    - You have to configure the jumpers as follows:

  @verbatim    
       +-------------------------------+
       |   Jumper    |       CAN1      |
       +-------------------------------+
       |   JP3       |       2-3       |
       |   JP10      |       2-3       |
       |   JP7       |       1-2       |
       |   JP9       |      fitted     |
       +-------------------------------+

  @endverbatim
  
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */