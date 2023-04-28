/**
  @page LwIP_UDP_Echo_Client LwIP UDP Echo Client application
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    LwIP/LwIP_UDP_Echo_Client/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LwIP UDP Echo Client application.
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

This application guides STM32Cube HAL API users to run a UDP Echo Client application 
based on Raw API of LwIP TCP/IP stack

To run this application, On the remote PC, open a command prompt window.
(In Windows, select Start > All Programs > Accessories > Command Prompt.)
At the command prompt, enter:
    C:\>echotool /p udp /s
where:
    � /p transport layer protocol used for communication (UDP)
    � /s is the actual mode of connection (Server mode)

Each time the user pushes the KEY button of the STM322xG-EVAL board, an echo 
request is sent to the server

If the LCD is used (#define USE_LCD in main.h), log messages will be displayed 
to inform user about ethernet cable status and the IP address value, else this 
will be ensured by LEDs:
  + LED1: ethernet cable is connected.
  + LED2: ethernet cable is not connected.

If a DHCP server is available, a dynamic IP address can be allocated by enabling 
the DHCP process (#define USE_DHCP in main.h)

If DHCP is used, user should define its PC Host IP address ( DEST_IP_ADDR0 [0..3] in main.h file.

Note: In this application the Ethernet Link ISR need the HAL time base to configure 
the Ethernet MAC, so the Ethernet Link interrupt priority must be set lower (numerically greater) 
than the HAL tick interrupt priority to ensure that the System tick increments while executing 
the Ethernet Link ISR.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
For more details about this application, refer to UM1713 "STM32Cube interfacing with LwIP and applications"


@par Directory contents

  - LwIP/LwIP_UDP_Echo_Client/Inc/app_ethernet.h          header of app_ethernet.c file
  - LwIP/LwIP_UDP_Echo_Client/Inc/ethernetif.h            header for ethernetif.c file
  - LwIP/LwIP_UDP_Echo_Client/Inc/lcd_log_conf.h          LCD Log configuration file
  - LwIP/LwIP_UDP_Echo_Client/Inc/stm32f2xx_hal_conf.h    HAL configuration file
  - LwIP/LwIP_UDP_Echo_Client/Inc/stm32f2xx_it.h          STM32 interrupt handlers header file
  - LwIP/LwIP_UDP_Echo_Client/Inc/main.h                  Main program header file
  - LwIP/LwIP_UDP_Echo_Client/Inc/lwipopts.h              LwIP stack configuration options
  - LwIP/LwIP_UDP_Echo_Client/Inc/udp_echoclient.h        Header for UDP echoclient application
  - LwIP/LwIP_UDP_Echo_Client/Src/app_ethernet.c          Ethernet specific module
  - LwIP/LwIP_UDP_Echo_Client/Src/stm32f2xx_it.c          STM32 interrupt handlers
  - LwIP/LwIP_UDP_Echo_Client/Src/main.c                  Main program
  - LwIP/LwIP_UDP_Echo_Client/Src/system_stm32f2xx.c      STM32F2xx system clock configuration file
  - LwIP/LwIP_UDP_Echo_Client/Src/ethernetif.c            Interfacing LwIP to ETH driver
  - LwIP/LwIP_UDP_Echo_Client/Src/udp_echoclient.c        UDP echoclient application


@par Hardware and Software environment

  - This application runs on STM32F207xx/STM32F217xx Devices.
    
  - This application has been tested with the following environments:
     - STM322xG-EVAL board   
     - echotool: (http://bansky.net/echotool/) is used as echo server that sends
       back every incoming data.   
      
  - STM322xG-EVAL Set-up
    - Connect the eval board to remote PC (through a crossover ethernet cable)
      or to your local network (through a straight ethernet cable)
    - JP5 and JP6 jumpers should be fitted in 2-3 position
    
  - Remote PC Set-up
    - Configure a static IP address for your remote PC 
      this address must be 192.168.0.11 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application


 */
