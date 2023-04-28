/**
  @page FatFs_USBDisk_RTOS   FatFs with USB disk drive in RTOS mode application
 
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    FatFs/FatFs_USBDisk_RTOS/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the FatFs with USB disk drive in RTOS mode application
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

@par Application Description

How to use STM32Cube firmware with FatFs middleware component as a generic FAT
file system module, FreeRTOS as an RTOS module based on using CMSIS-OS wrapping
layer common APIs, and STM32 USB On-The-Go (OTG) host library, in both Full
Speed (FS) and High Speed (HS) modes. This example develops an application
exploiting FatFs features, with a USB disk drive in RTOS mode configuration.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock
(SYSCLK) to run at 120 MHz.
           
The application is based on writing a text file to a drive, it creates a normal 
priority thread, that executes a Mass Storage Class routine and it's performed 
using FatFs APIs to access the FAT volume as described in the following steps:  

 - Link the USB Host disk I/O driver;
 - Register the file system object (mount) to the FatFs module for the USB drive;
 - Create and Open new text file object with write access;
 - Write data to the text file;
 - Close the open text file;
 - Open text file object with read access;
 - Read back data from the text file;
 - Close the open text file;
 - Check on read data from text file;
 - Unlink the USB Host disk I/O driver.
 
It is worth noting that the application manages any error occurred during the 
access to FAT volume, when using FatFs APIs. Otherwise, user can check if the
written text file is available on the USB disk.

It is possible to fine tune needed FatFs features by modifying defines values 
in FatFs configuration file �ffconf.h� available under the project includes 
directory, in a way to fit the application requirements. 

STM32 Eval board's LEDs can be used to monitor the application status:
  - LED1 is ON when the application runs successfully.
  - LED3 is ON when any error occurs.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in HAL time base ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the HAL time base interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the HAL time base is always set to 1 millisecond to have correct 
      HAL operation.

@note The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set 
      according to the OS resources memory requirements of the application with +10% margin and 
      rounded to the upper Kbyte boundary.

For more details about FatFs implementation on STM32Cube, please refer to UM1721 "Developing Applications 
on STM32Cube with FatFs".


@par Directory contents
 
  - FatFs/FatFs_USBDisk_RTOS/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - FatFs/FatFs_USBDisk_RTOS/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - FatFs/FatFs_USBDisk_RTOS/Inc/main.h                  Main program header file
  - FatFs/FatFs_USBDisk_RTOS/Inc/ffconf.h                FAT file system module configuration file   
  - FatFs/FatFs_USBDisk_RTOS/Src/stm32f2xx_it.c          Interrupt handlers
  - FatFs/FatFs_USBDisk_RTOS/Src/main.c                  Main program
  - FatFs/FatFs_USBDisk_RTOS/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file


@par Hardware and Software environment

  - This application runs on STM32F207xx/217xx device.
    
  - This application has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.

  - STM322xG-EVAL Set-up
    - Plug the USB key into the STM322xG-EVAL board through 'USB micro A-Male 
      to A-Female' cable to the connector:
      - CN9: to use USB High Speed (HS) 
      - CN8: to use USB Full Speed (FS) with embedded PHY(U2)


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - In the workspace toolbar select the project configuration:
   - STM322xG-EVAL_USBH-HS: to configure the project for STM32F2xx devices using USB OTG HS peripheral
   - STM322xG-EVAL_USBH-FS: to configure the project for STM32F2xx devices using USB OTG FS peripheral
 - Run the application


 */