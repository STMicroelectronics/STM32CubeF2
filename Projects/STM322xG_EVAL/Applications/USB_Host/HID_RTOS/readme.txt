/**
  @page HID_RTOS USB Host Human Interface (HID) RTOS application
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    USB_Host/HID_RTOS/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB Host HID RTOS application.
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

Use of the USB host application based on the HID class.

This is a typical application on how to use the STM32F2xx USB OTG Host peripheral to interact with an USB 
HID Device such as a Mouse or a Keyboard.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 120 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock, which is generated from an integrated PLL. In the High Speed (HS) mode the
USB clock (60 MHz) is driven by the ULPI. 

When the application is started, the connected HID device (Mouse/Keyboard) is detected in HID mode and 
gets initialized. The STM32 MCU behaves as a HID Host, it enumerates the device and extracts VID, PID, 
manufacturer name, Serial no and product name information and displays it on the LCD screen. 
This application is based on interacting with a HID device (Mouse/Keyboard). It creates a normal 
priority thread, that executes a HID routine.

A menu is displayed and the user can select any operation from the menu using the Joystick buttons:
 - "Start HID" operation starts the appropriate HID application to the attached HID Device.
   - "Start Mouse / Re-Initialize" operation starts Mouse HID application. Moving the mouse will move
    the pointer in the display rectangle and if a button is pressed, the corresponding rectangle will be
    highlighted in Blue.
   - "Start Keyboard / Clear" operation starts Keyboard HID application. Taped Keyboard characters are 
   displayed on the LCD screen.
 - "Re-Enumerate" operation performs a new Enumeration of the device.

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

For more details about the STM32Cube USB Host library, please refer to UM1720  
"STM32Cube USB Host library".


@par USB Library Configuration

To select the appropriate USB Core to work with, user must add the following macro defines within the
compiler preprocessor (already done in the preconfigured projects provided with this application):
      - "USE_USB_HS" when using USB High Speed (HS) Core
      - "USE_USB_FS" when using USB Full Speed (FS) Core 

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

Since this is an RTOS based application, built around FreeRTOS and CMSIS-OS wrapping layer common APIs,
the RTOS is enabled by setting, #define USBH_USE_OS      1


@par Directory contents

  - USB_Host/HID_RTOS/Src/main.c                  Main program
  - USB_Host/HID_RTOS/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file
  - USB_Host/HID_RTOS/Src/stm32f2xx_it.c          Interrupt handlers
  - USB_Host/HID_RTOS/Src/menu.c                  HID State Machine
  - USB_Host/HID_RTOS/Src/usbh_conf.c             General low level driver configuration
  - USB_Host/HID_RTOS/Src/mouse.c                 HID mouse functions file
  - USB_Host/HID_RTOS/Src/keyboard.c              HID keyboard functions file
  - USB_Host/HID_RTOS/Inc/main.h                  Main program header file
  - USB_Host/HID_RTOS/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - USB_Host/HID_RTOS/Inc/lcd_log_conf.h          LCD log configuration file
  - USB_Host/HID_RTOS/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - USB_Host/HID_RTOS/Inc/FreeRTOSConfig.h        FreeRTOS Module Configuration file
  - USB_Host/HID_RTOS/Inc/usbh_conf.h             USB Host driver Configuration file
 

@par Hardware and Software environment

  - This application runs on STM32F207xx/STM32F217xx devices.
    
  - This application has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.

  - STM322xG-EVAL Set-up
    - Plug the USB key into the STM322xG-EVAL board through 'USB micro A-Male 
      to A-Female' cable to the connector:
      - CN9: to use USB High Speed (HS) 
      - CN8: to use USB Full Speed (FS) with embedded PHY(U2)
	- Please ensure that jumper JP31 is fitted.

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - In the workspace toolbar select the project configuration:
   - STM322xG-EVAL_USBH-HS: to configure the project for STM32F2xx devices using USB OTG HS peripheral
   - STM322xG-EVAL_USBH-FS: to configure the project for STM32F2xx devices using USB OTG FS peripheral
 - Run the application
 

 */
