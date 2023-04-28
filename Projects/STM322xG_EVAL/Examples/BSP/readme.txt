/**
  @page BSP  Example on how to use the BSP drivers
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    BSP/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the BSP example.
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

This example provides a description of how to use the different BSP drivers. 

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 120 MHz.

This example shows how to use the different functionalities of LCD, SD card, 
touchscreen and joystick by switching between all tests using key button. 

Firstly, use the joystick button to move a pointer inside a rectangle 
(up/down/right/left) and change the pointer color(select).

Secondly, and after the touchscreen calibration, use the touchscreen 
functionality to select or activate colored circle inside a rectangle.

Thirdly, this example shows how to use the different LCD features to display string
with different fonts, to display different shapes and to draw a bitmap.

Fourthly, this example shows how to erase, write and read the SD card and also 
how to detect the presence of the card.

Fifthly, this example shows how to use the LCD log features.

Sixthly, this example shows how to read and write data in EEPROM. The I2C EEPROM
memory (M24C64) is available on STM322xG-EVAL board.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - BSP/Src/main.c                     Main program
  - BSP/Src/system_stm32f2xx.c         STM32F2xx system clock configuration file
  - BSP/Src/stm32f2xx_it.c             Interrupt handlers 
  - BSP/Src/joystick.c                 Joystick feature
  - BSP/Src/lcd.c                      LCD drawing features
  - BSP/Src/log.c                      LCD Log firmware functions
  - BSP/Src/sd.c                       SD features
  - BSP/Src/touchscreen.c              Touchscreen feature
  - BSP/Src/ts_calibration.c           Touchscreen calibration
  - BSP/Src/eeprom.c                   EEPROM features
  - BSP/Inc/main.h                     Main program header file  
  - BSP/Inc/stm32f2xx_hal_conf.h       HAL configuration file
  - BSP/Inc/stm32f2xx_it.h             Interrupt handlers header file
  - BSP/Inc/lcd_log_conf.h             lcd_log configuration template file
  - BSP/Inc/stlogo.h                   Image used for BSP example
        
        
@par Hardware and Software environment  

  - This example runs on STM32F207xx/217xx device.    
  
  - This example has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.

  - STM322xG-EVAL Set-up
    - Please ensure that jumper JP24 (EEPROM WP) is fitted.
    - For uSD card operation, please ensure that jumpers JP16 and JP22 are in position 1-2.
  
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
