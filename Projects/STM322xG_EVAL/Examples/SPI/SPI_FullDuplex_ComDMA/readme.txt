    /**
  @page SPI_FullDuplex_ComDMA SPI Full Duplex DMA example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    SPI/SPI_FullDuplex_ComDMA/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the SPI Full Duplex DMA example.
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

Data buffer transmission/reception between two boards via SPI using DMA.

The communication is done with 2 boards through SPI.

   _________________________                        _________________________
  |           ______________|                      |______________           |
  |          |SPI3          |                      |          SPI3|          |
  |          |              |                      |              |          |
  |          |     CLK(PC10)|______________________|(PC10)CLK     |          |
  |          |              |                      |              |          |
  |          |    MISO(PC11)|______________________|(PC11)MISO    |          |
  |          |              |                      |              |          |
  |          |    MOSI(PC12)|______________________|(PC12)MOSI    |          |
  |          |              |                      |              |          |
  |          |______________|                      |______________|          |
  |      __                 |                      |      __                 |
  |     |__|                |                      |     |__|                |
  |    TAMPER               |                      |    TAMPER               |
  |                      GND|______________________|GND                      |
  |                         |                      |                         |
  |_STM322xG________________|                      |_STM322xG________________|

This example guides you through the different configuration steps by mean of HAL API 
to ensure SPI Data buffer transmission and reception with DMA.
The communication is done with 2 boards through SPI.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 120 MHz.

The SPI peripheral configuration is ensured by the HAL_SPI_Init() function.
This later is calling the HAL_SPI_MspInit()function which core is implementing
the configuration of the needed SPI resources according to the used hardware (CLOCK, 
GPIO, DMA and NVIC). You may update this function to change SPI configuration.

The SPI communication is then initiated.
The HAL_SPI_TransmitReceive_DMA() function allows the reception and the 
transmission of a predefined data buffer at the same time (Full Duplex Mode). 
The user can choose between Master and Slave through "#define MASTER_BOARD"
in the "main.c" file.
If the Master board is used, the "#define MASTER_BOARD" must be uncommented.
If the Slave board is used the "#define MASTER_BOARD" must be commented.

For this example the aTxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step after the user press the Tamper Key, SPI Master starts the 
communication by sending aTxBuffer and receiving aRxBuffer through 
HAL_SPI_TransmitReceive_DMA(), at the same time SPI Slave transmits aTxBuffer 
and receives aRxBuffer through HAL_SPI_TransmitReceive_DMA(). 
The end of this step is monitored through the HAL_SPI_GetState() function
result.
Finally, aRxBuffer and aTxBuffer are compared through Buffercmp() in order to 
check buffers correctness.  

STM32 Eval boards' LEDs can be used to monitor the transfer status:
 - LED1 turns ON when the transmission process is complete.
 - LED2 turns ON when the reception process is complete.
 - LED3 turns ON when there is an error in transmission/reception process.
 - LED4 toggles on master board waiting tamper button to be pressed.    

 @note SPIx instance used and associated resources can be updated in "main.h"
       file depending hardware configuration used.
       
 @note You need to perform a reset on Slave board, then perform it on Master board
       to have the correct behaviour of this example.
 

@par Directory contents 

  - SPI/SPI_FullDuplex_ComDMA/Inc/stm32f2xx_hal_conf.h   HAL configuration file
  - SPI/SPI_FullDuplex_ComDMA/Inc/stm32f2xx_it.h         Interrupt handlers header file
  - SPI/SPI_FullDuplex_ComDMA/Inc/main.h                 Header for main.c module  
  - SPI/SPI_FullDuplex_ComDMA/Src/stm32f2xx_it.c         Interrupt handlers
  - SPI/SPI_FullDuplex_ComDMA/Src/main.c                 Main program
  - SPI/SPI_FullDuplex_ComDMA/Src/system_stm32f2xx.c     stm32f2xx system source file

@par Hardware and Software environment 

  - This example runs on STM32F2xxxx devices.
    
  - This example has been tested with STM322xG-EVAL RevC evaluation board and can be
    easily tailored to any other supported device and development board. 

  - STM322xG-EVAL Set-up
    - Connect Master board PC10 to Slave Board PC10 (Pin36 in CN4)
    - Connect Master board PC11 to Slave Board PC11 (Pin35 in CN4)
    - Connect Master board PC12 to Slave Board PC12 (Pin34 in CN4)
    - Connect Master board GND  to Slave Board GND

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
    o Uncomment "#define MASTER_BOARD" and load the project in Master Board
    o Comment "#define MASTER_BOARD" and load the project in Slave Board
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
