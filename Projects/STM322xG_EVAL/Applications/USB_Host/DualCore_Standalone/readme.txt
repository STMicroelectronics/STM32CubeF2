/**
  @page DualCore_Standalone USB Host Dual Core application
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    USB_Host/DualCore_Standalone/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB Host Dual Core application.
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

This application is a part of the USB Host Library package using STM32Cube firmware. It describes how to use
USB host application based on the STM32F2xx multi core support feature integrating Mass Storage (MSC) and
Human Interface (HID) in the same project.

This is a typical application on how to use the STM32F2xx USB OTG Host peripheral to operate with an USB MSC
device connected to the High Speed port and a HID device connected to the Full Speed port.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 120 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock, which is generated from an integrated PLL. In the High Speed (HS) mode the
USB clock (60 MHz) is driven by the ULPI.

When the application is started, the connected USB MSC device to HS port is detected in MSC mode and
gets initialized, also the connected USB HID device to FS port is detected in HID mode and gets 
initialized. The STM32 MCU behaves as a MSC/HID Host, it enumerates the devices and extracts VID, PID, 
manufacturer name, Serial no and product name information and displays it on the LCD screen. 

A menu is displayed and the user can select any operation from the menu using the Joystick buttons:
 - "Mass Storage demo" operation starts the Mass Storage application.
 - "Human Interface demo" operation starts the Human Interface application.
 - "Re-Enumerate MSC" operation performs a new Enumeration of the MSC device.
 - "Re-Enumerate HID" operation performs a new Enumeration of the HID device (keyboard/mouse).

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about the STM32Cube USB Host library, please refer to UM1720  
"STM32Cube USB Host library".


@par USB Library Configuration

To select the appropriate USB Core to work with, user must add the following macro defines within the
compiler preprocessor (already done in the preconfigured projects provided with this application):
      - "USE_USB_HS" and "USE_USB_FS" when using USB Dual Core Mode

It is possible to fine tune needed USB Host features by modifying defines values in USBH configuration
file �usbh_conf.h� available under the project includes directory, in a way to fit the application
requirements, such as:
- Level of debug: USBH_DEBUG_LEVEL
                  0: No debug messages
                  1: Only User messages are shown
                  2: User and Error messages are shown
                  3: All messages and internal debug messages are shown
   By default debug messages are displayed on the debugger IO terminal; to redirect the Library
   messages on the LCD screen, lcd_log.c driver need to be added to the application sources.

   
@par Directory contents

  - USB_Host/DualCore_Standalone/Src/main.c                  Main program
  - USB_Host/DualCore_Standalone/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file
  - USB_Host/DualCore_Standalone/Src/stm32f2xx_it.c          Interrupt handlers
  - USB_Host/DualCore_Standalone/Src/dual_menu.c             Main Menu State Machine
  - USB_Host/DualCore_Standalone/Src/usbh_conf.c             General low level driver configuration
  - USB_Host/DualCore_Standalone/Src/usbh_diskio.c           USB diskio interface for FatFs
  - USB_Host/DualCore_Standalone/Src/explorer.c              Explore the USB flash disk content
  - USB_Host/DualCore_Standalone/Src/file_operations.c       Write/read file on the disk 
  - USB_Host/DualCore_Standalone/Src/msc_menu.c              MSC State Machine
  - USB_Host/DualCore_Standalone/Src/hid_menu.c              HID State Machine
  - USB_Host/DualCore_Standalone/Src/mouse.c                 HID mouse functions  
  - USB_Host/DualCore_Standalone/Src/keyboard.c              HID keyboard functions
  - USB_Host/DualCore_Standalone/Inc/main.h                  Main program header file
  - USB_Host/DualCore_Standalone/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - USB_Host/DualCore_Standalone/Inc/lcd_log_conf.h          LCD log configuration file
  - USB_Host/DualCore_Standalone/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - USB_Host/DualCore_Standalone/Inc/usbh_conf.h             USB Host driver Configuration file
  - USB_Host/DualCore_Standalone/Inc/ffconf.h                FAT file system module configuration file
 

@par Hardware and Software environment

  - This application runs on STM32F207xx/STM32F217xx devices.
    
  - This application has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.

  - STM322xG-EVAL Set-up
    - Plug the USB key into the STM322xG-EVAL board through 'USB micro A-Male 
      to A-Female' cable to the connector:
      - CN9: to use USB High Speed (HS) 
    - Plug the HID device(Mouse/Keyboard) into the STM322xG-EVAL board through 'USB micro A-Male 
      to A-Female' cable to the connector:
      - CN8: to use USB Full Speed (FS) with embedded PHY(U2)
	- Please ensure that jumper JP31 is fitted.

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application
 

 */