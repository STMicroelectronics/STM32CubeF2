/**
  @page I2C_OneBoard_Communication_PollingAndIT I2C example (Master Polling Mode)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/I2C/I2C_OneBoard_Communication_PollingAndIT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C_OneBoard_Communication_PollingAndIT I2C example (Master Polling Mode).
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

How to transmit data bytes from an I2C master device using polling mode 
to an I2C slave device using interrupt mode. The peripheral is initialized 
with LL unitary service functions to optimize for performance and size.

This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using only one NUCLEO-F207ZG.

I2C2 Peripheral is configured in Slave mode with EXTI (Clock 400Khz, Own address 7-bit enabled).
I2C1 Peripheral is configured in Master mode (Clock 400Khz).
GPIO associated to User push-button is linked with EXTI. 

LED1 blinks quickly to wait for user-button press. 

Example execution:
Press the Key push-button to initiate a Start condition by Master.
This action will generate an I2C start condition on the I2C bus.
When the I2C start condition is sent on I2C1, a SB flag is raised.
This will allow Master to send the Slave address with a write bit condition.
When address Slave match code is received on I2C2, the Slave acknowledge the address.
When this acknowledge is received on I2C1, an ADDR flag is raised.

When address Slave match code is received on I2C2, an ADDR interrupt occurs.
I2C2 IRQ Handler routine is then checking Address Match Code and direction at Read (mean write direction for Master).
This will allow Slave to enter in receiver mode and then acknowledge Master to send the bytes.
When acknowledge is received on I2C1, a TXE event occurs.
This will allow Master to transmit a byte to the Slave.
Each time a byte is received on I2C2 (Slave), an RXNE interrupt occurs until a STOP condition.
And so each time the Slave acknowledge the byte received a TXE event occurs on Master side.
Master generate a Stop condition when size of data to transmit is achieved.

The STOP condition generate a STOP interrupt and initiate the end of reception on Slave side.
I2C2 IRQ handler routine is then clearing the STOP flag.

LED1 is On if data are well received.

In case of errors, LED1 is blinking.

@par Directory contents 

  - I2C/I2C_OneBoard_Communication_PollingAndIT/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Inc/main.h                  Header for main.c module
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Src/stm32f2xx_it.c          Interrupt handlers
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Src/main.c                  Main program
  - I2C/I2C_OneBoard_Communication_PollingAndIT/Src/system_stm32f2xx.c      STM32F2xx system source file

@par Hardware and Software environment

  - This example runs on STM32F207ZG devices.
    
  - This example has been tested with NUCLEO-F207ZG board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-F207ZG Set-up
    - Connect GPIOs connected to I2C2 SCL/SDA (PB.10 and PB.11)
    to respectively SCL and SDA pins of I2C1 (PB.6 and PB.9).
      - I2C2_SCL  PB.10 (CN10, pin 32) : connected to I2C1_SCL PB.6 (CN10, pin 13) 
      - I2C2_SDA  PB.11 (CN10, pin 34) : connected to I2C1_SDA PB.9 (CN7, pin 4)

  - Launch the program. Press Key push-button to initiate a write request by Master 
      then Slave receive bytes.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 */
