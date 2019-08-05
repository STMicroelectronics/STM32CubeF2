/**
  @page SPI_OneBoard_HalfDuplex_IT SPI example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/SPI/SPI_OneBoard_HalfDuplex_IT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the SPI_OneBoard_HalfDuplex_IT example.
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

Configuration of GPIO and SPI peripherals to transmit bytes 
from an SPI Master device to an SPI Slave device in Interrupt mode. This example
is based on the STM32F2xx SPI LL API. The peripheral initialization uses 
LL unitary service functions for optimization purposes (performance and size).

This example works with only one NUCLEO-F207ZG.

SPI1 Peripheral is configured in Master mode Half-Duplex Tx.
SPI3 Peripheral is configured in Slave mode Half-Duplex Rx.
GPIO associated to User push-button is linked with EXTI. 

Example execution:

LED1 is blinking Fast (200ms) and wait Key push-button action.
Press Key push-button on BOARD start a Half-Duplex communication through IT.
On MASTER side (SPI1), Clock will be generated on SCK line, Transmission done on MOSI Line.
On SLAVE side (SPI3) reception is done through the MISO Line.

LED1 is On if data is well received.

In case of errors, LED1 is blinking Slowly (1s).

@par Directory contents 

  - SPI/SPI_OneBoard_HalfDuplex_IT/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - SPI/SPI_OneBoard_HalfDuplex_IT/Inc/main.h                  Header for main.c module
  - SPI/SPI_OneBoard_HalfDuplex_IT/Inc/stm32_assert.h          Template file to include assert_failed function
  - SPI/SPI_OneBoard_HalfDuplex_IT/Src/stm32f2xx_it.c          Interrupt handlers
  - SPI/SPI_OneBoard_HalfDuplex_IT/Src/main.c                  Main program
  - SPI/SPI_OneBoard_HalfDuplex_IT/Src/system_stm32f2xx.c      STM32F2xx system source file

@par Hardware and Software environment

  - This example runs on STM32F207ZG devices.

  - This example has been tested with NUCLEO-F207ZG board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-F207ZG Set-up
    - Connect Master SCK  PA5 to Slave SCK  PB3
    - Connect Master MOSI PA7 to Slave MISO PB4

Relation with Board connector:
  PA5  is connected to pin 10 of CN7 connector
  PA7  is connected to pin 14 of CN7 connector
  PB3 is connected to pin 15 of CN7 connector
  PB4 is connected to pin 19 of CN7 connector

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
