/**
  @page DFU_Standalone USB Device Firmware Upgrade (DFU) application

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    USB_Device/DFU_Standalone/Readme.txt
  * @author  MCD Application Team
  * @brief   Description of the USB DFU application.
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

Compliant implementation of the Device Firmware Upgrade (DFU)
capability to program the embedded Flash memory through the USB peripheral.

This is a typical application on how to use the STM32F2xx USB OTG Device peripheral to implement the DFU
capability for programming the embedded Flash memory of the STM32F2xx devices.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 120 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock, which is generated from an integrated PLL. In the High Speed (HS) mode the
USB clock (60 MHz) is driven by the ULPI.

The DFU transactions are based on Endpoint 0 (control endpoint) transfer. All requests and status
control are sent/received through this endpoint.

The Internal Flash memory is split as follows:
 - DFU area located in [0x08000000 : USBD_DFU_APP_DEFAULT_ADD-1]: Only read access
 - Application area located in [USBD_DFU_APP_DEFAULT_ADD : Device's end address]: Read, Write, and Erase
   access

In this application, two operating modes are available:
 1. DFU operating mode:
    This mode is entered after an MCU reset in case:
     - The DFU mode is forced by the user: the user presses the key button.
     - No valid code found in the application area: a code is considered valid if the MSB of the initial
       Main Stack Pointer (MSP) value located in the first address of the application area is equal to
       0x2000

 2. Run-time application mode:
    This is the normal run-time activities. A binary which toggles LEDs on the evaluation board is
    provided in Binary directory.

@note After each device reset, hold down the Key button on the evaluation board to enter the DFU mode.

Traditionally, firmware is stored in Hex, S19 or Binary files, but these formats do not contain the
necessary information to perform the upgrade operation, they contain only the actual data of the program
to be downloaded. However, the DFU operation requires more information, such as the product identifier,
vendor identifier, Firmware version and the Alternate setting number (Target ID) of the target to be
used, this information makes the upgrade targeted and more secure. To add this information, DFU file
format is used. For more details refer to the "DfuSe File Format Specification" document (UM0391).

To generate a DFU image, download "DFUse Demonstration" tool and use DFU File Manager to convert a
binary image into a DFU image. This tool is for download from www.st.com
To download a *.dfu image, use "DfuSe Demo" available within "DFUse Demonstration" install directory.

Please refer to UM0412, DFuSe USB device firmware upgrade STMicroelectronics extension for more details
on the driver installation and PC host user interface.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about the STM32Cube USB Device library, please refer to UM1734
"STM32Cube USB Device library".


@par USB Library Configuration

To select the appropriate USB Core to work with, user must add the following macro defines within the
compiler preprocessor (already done in the preconfigured projects provided with this application):
      - "USE_USB_HS" when using USB High Speed (HS) Core
      - "USE_USB_FS" when using USB Full Speed (FS) Core

It is possible to fine tune needed USB Device features by modifying defines values in USBD configuration
file �usbd_conf.h� available under the project includes directory, in a way to fit the application
requirements, such as:
 - USBD_DFU_APP_DEFAULT_ADD, specifying the address from where user's application will be downloaded.

Device's end address is the end address of the Flash memory and it is dependent on the device in use.


@par Directory contents

  - USB_Device/DFU_Standalone/Src/main.c                  Main program
  - USB_Device/DFU_Standalone/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file
  - USB_Device/DFU_Standalone/Src/stm32f2xx_it.c          Interrupt handlers
  - USB_Device/DFU_Standalone/Src/usbd_conf.c             General low level driver configuration
  - USB_Device/DFU_Standalone/Src/usbd_desc.c             USB device descriptor
  - USB_Device/DFU_Standalone/Src/usbd_dfu_flash.c        Internal Flash memory management
  - USB_Device/DFU_Standalone/Inc/main.h                  Main program header file
  - USB_Device/DFU_Standalone/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - USB_Device/DFU_Standalone/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - USB_Device/DFU_Standalone/Inc/usbd_conf.h             USB device driver Configuration file
  - USB_Device/DFU_Standalone/Inc/usbd_desc.h             USB device descriptor header file
  - USB_Device/DFU_Standalone/Inc/usbd_dfu_flash.h        Internal Flash memory management header file


@par Hardware and Software environment

  - This application runs on STM32F207xx/STM32F217xx devices.

  - This application has been tested with STMicroelectronics STM322xG-EVAL
    evaluation boards and can be easily tailored to any other supported device
    and development board.

  - STM322xG-EVAL Set-up
    - Connect the STM322xG-EVAL board to the PC through 'USB micro A-Male
      to A-Male' cable to the connector:
      - CN9: to use USB High Speed (HS)
      - CN8: to use USB Full Speed (FS)
	- Please ensure that jumper JP31 is fitted.

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - In the workspace toolbar select the project configuration:
   - STM322xG-EVAL_USBH-HS: to configure the project for STM32F2xx devices using USB OTG HS peripheral
   - STM322xG-EVAL_USBH-FS: to configure the project for STM32F2xx devices using USB OTG FS peripheral
 - To run the application, proceed as follows:
   - Install "DfuSe Demonstrator"
   - Install the DFU driver available in "DfuSe Demonstrator" installation directory
   - For Windows 8.1 and later : Update STM32 DFU device driver manually from Windows Device Manager.
     The install of required device driver is available under "Program Files\STMicroelectronics\Software\DfuSe v3.0.5\Bin\Driver\Win8.1" directory.
   - Open "DfuSe Demo" and download the "STM322xG_EVAL_SysTick_0x0800C000.dfu" provided in Binary
     directory.
   - To run the downloaded application, execute the command "leave the DFU mode" or simply reset the
     board.


 */
