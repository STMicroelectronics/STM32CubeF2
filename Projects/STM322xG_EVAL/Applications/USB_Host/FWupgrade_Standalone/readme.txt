/**
  @page FWupgrade_Standalone USB Host Firmware Upgrade application
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    USB_Host/FWupgrade_Standalone/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB Host Firmware Upgrade application
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
USB host application based on the In-Application programming (IAP) on the STM32F2xx devices.

This is a typical application on how to use the STM32F2xx USB OTG Host peripheral for firmware upgrade 
application or IAP, allowing user to erase and write to on-chip Flash memory.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 120 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock, which is generated from an integrated PLL. In the High Speed (HS) mode the
USB clock (60 MHz) is driven by the ULPI.

This application uses the USB Host to:
 - DOWNLOAD: Reads the defined image (.bin) file �DOWNLOAD_FILENAME� from the thumb drive and writes it
             to the embedded Flash memory.
 - UPLOAD:   Reads the entire embedded Flash memory and saves the contents to the defined file name 
             �UPLOAD_FILENAME� in the thumb drive.
 - JUMP:     Executes the user code at the defined user application start address �APPLICATION_ADDRESS�.
             Image which must be defined from this flash address: 0x0800C000
  
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
      - "USE_USB_HS" when using USB High Speed (HS) Core
      - "USE_USB_FS" when using USB Full Speed (FS) Core 

The user application (binary file) to be loaded into the Flash memory using the firmware upgrade 
application is built by the following configuration settings:
	- Set the program load address to APPLICATION_ADDRESS in the toolchain linker file.
	- Relocate the vector table to address APPLICATION_ADDRESS using the VECT_TAB_OFFSET definition  
	  inside the system_stm32f2xx.c file.


@par Directory contents 

  - USB_Host/FWupgrade_Standalone/Src/main.c                  Main program
  - USB_Host/FWupgrade_Standalone/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file
  - USB_Host/FWupgrade_Standalone/Src/stm32f2xx_it.c          Interrupt handlers
  - USB_Host/FWupgrade_Standalone/Src/iap_menu.c              IAP State Machine   
  - USB_Host/FWupgrade_Standalone/Src/usbh_conf.c             General low level driver configuration
  - USB_Host/FWupgrade_Standalone/Src/command.c               IAP command functions
  - USB_Host/FWupgrade_Standalone/Src/flash_if.c              Flash layer functions
  - USB_Host/FWupgrade_Standalone/Src/usbh_diskio.c           USB diskio interface for FatFs
  - USB_Host/FWupgrade_Standalone/Inc/main.h                  Main program header file
  - USB_Host/FWupgrade_Standalone/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - USB_Host/FWupgrade_Standalone/Inc/command.h               IAP command functions header file
  - USB_Host/FWupgrade_Standalone/Inc/flash_if.h              Flash layer functions header file
  - USB_Host/FWupgrade_Standalone/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - USB_Host/FWupgrade_Standalone/Inc/usbh_conf.h             USB Host driver Configuration file
  - USB_Host/FWupgrade_Standalone/Inc/ffconf.h                FatFs Module Configuration file
  
  - USB_Host/FWupgrade_Standalone/Binary/
    This folder contains images that can be loaded and executed by the FW upgrade application:
    - STM322xG_EVAL_SysTick.bin
    - STM322xG_EVAL_USBH_MSC_FS.bin
    - STM322xG_EVAL_USBH_MSC_HS.bin
    

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
 - To run the application, proceed as follows:

1. Load the binary image of the user program to the root directory of a USB key. You can use the 
   provided binary images under the USB_Host/FWupgrade_Standalone/Binary folder. 
   The binary should be renamed to �image.bin�.

2. Program the firmware upgrade application into the internal Flash memory.
   a. Open the project (under USB_Host/FWupgrade_Standalone) with your preferred toolchain.
   b. Compile and load the project into the target memory and run the project.

After the board reset and depending on the Key button state:
   1. Key button pressed: The firmware upgrade application is executed.
   2. Key button not pressed: A test on the user application start address will be performed and one of
      the below processes is executed:
      � User vector table available: User application is executed.
      � User vector table not available: firmware upgrade application is executed.

During the firmware upgrade application execution, there is a continuous check on the Key button pressed
state time. Depending on the state time of the Key button, one of the following processes is executed:
 - If Key Button is pressed for more than > 3 seconds at firmware startup:
   UPLOAD command will be executed immediately after completed execution of the DOWNLOAD command
 - If Key Button is pressed for less than< 3 seconds at firmware startup:
   Only the DOWNLOAD command is executed.

STM32 Eval board's LEDs can be used to monitor the application status:
 - Red LED blinks in infinite loop 
	 �> Error: USB key disconnected.

 - Red LED blinks in infinite loop and Orange/Blue LEDs are ON 
	 �> Error: Flash programming error.
	
 - Red LED blinks in infinite loop and Green LED is ON 
	 �> Error: Download done and USB key disconnected.

 - Red LED blinks in infinite loop and Blue/Orange/Green LEDs are ON
	 �> Error: Binary file not available

 - Red/Blue/Orange LEDs blink in infinite loop
	 �> Error: Buffer size limit, Exceed 32Kbyte
	
 - Red LED blinks in infinite loop and Blue LED is ON
	 �> Error: No available Flash memory size to load the binary file.
	
 - Red/Orange LEDs blink in infinite loop
	 �> Error: Flash erase error.

 - Red/Blue LEDs are ON
	 �> UPLOAD condition verified and the user should release the Key button.
	
 - Blue LED is ON
	 �> DOWNLOAD ongoing.
	
 - Orange/Red LEDs are ON
	 �> DOWNLOAD done and UPLOAD is ongoing.

 - Orange/Blue LEDs are ON
	 �> UPLOAD is ongoing.
	
 - Red LED blinks in infinite loop and Orange LED is ON
	 �> USB key read out protection ON.
	
 - Green LED is ON
	 �> DOWNLOAD and UPLOAD done with success; and the MCU waiting until you press the Key button before
      executing the JUMP command.
  

 */
