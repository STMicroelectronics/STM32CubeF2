/**
  @page I2C_TwoBoards_MasterTx_SlaveRx I2C example (Polling Mode)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/I2C/I2C_TwoBoards_MasterTx_SlaveRx/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C_TwoBoards_MasterTx_SlaveRx I2C example (Polling Mode).
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
to configure GPIO and I2C peripherals using two NUCLEO-F207ZG.

Boards: NUCLEO-F207ZG (embeds a STM32F207ZG device)
SCL Pin: PB.10 (CN10, pin 32)
SDA Pin: PB.11 (CN10, pin 34)

   ______BOARD SLAVE_____                       _____BOARD MASTER_____
  |        ______________|                     |______________        |
  |       |I2C2          |                     |          I2C1|       |
  |       |              |                     |              |       |
  |       |          SCL |_____________________| SCL          |       |
  |       |              |                     |              |       |
  |       |              |                     |              |       |
  |       |          SDA |_____________________| SDA          |       |
  |       |______________|                     |______________|       |
  |         __           |                     |             __       |
  |        |__|          |                     |            |__|      |
  |        USER       GND|_____________________|GND         USER      |
  |___STM32F2xx_Nucleo_144___|                     |___STM32F2xx_Nucleo_144___|

The project is split in two parts the Master Board and the Slave Board
- Master Board
  I2C1 Peripheral is configured in Master mode (Clock 400Khz).
  And GPIO associated to Key push-button is linked with EXTI. 
- Slave Board
  I2C2 Peripheral is configured in Slave mode (Clock 400Khz, Own address 7-bit enabled).

The user can choose between Master and Slave through "#define SLAVE_BOARD"
in the "main.h" file:
- Comment "#define SLAVE_BOARD" to select Master board.
- Uncomment "#define SLAVE_BOARD" to select Slave board.

A first program launch, BOARD SLAVE waiting Address Match code through Handle_I2C_Slave() routine.
LED1 blinks quickly on both BOARD to wait for user-button press. 

Example execution:
To perform this example, two steps are necessary to prevent a wrong start/stop detection due to the initialization of the opposite GPIO board.

So at first step, press the Key push-button on BOARD SLAVE to activate Slave peripheral and then prepare acknowledge for Slave address reception.
At second step, press the Key push-button on BOARD MASTER to activate Master peripheral and then to initiate a write request by Master.
This action will generate an I2C start condition with the Slave address and a write bit condition.
When address Slave match code is received on I2C2 of BOARD SLAVE, an ADDR event occurs.
Handle_I2C_Slave() routine is then checking the direction Read (mean write direction for Master).
This will allow Slave to enter in receiver mode and then acknowledge Master to send the bytes.
When acknowledge is received on I2C1 (Master), a TXE event occurs.
This will allow Master to transmit a byte to the Slave.
Each time a byte is received on I2C2 (Slave), an RXNE or BTF event occurs until a STOP condition.
And so each time the Slave acknowledge the byte received a TXE event occurs on Master side.
Master generate a Stop condition when size of data to transmit is achieved.

The STOP condition generate a STOP event and initiate the end of reception on Slave side.
Handle_I2C_Slave() routine is then clearing the STOP flag.

LED1 turn OFF on BOARD SLAVE when pressing the Key push-button.

LED1 is On :
- Slave side if data are well received.
- Master side if transfer sequence is completed.

- LED1 blinks quickly on both boards waiting for user button to be pressed on Slave board
- Once user button is pressed to activate Slave peripheral, LED1 turns ON on slave board and still blinking on master board
- When user button isn pressed on master board, LED1 turns ON on both boards to indicate that : 
   - Data are well received on slave side
   - Transfer sequence is completed on master side
   
In case of errors, LED1 is blinking.


@par Directory contents 

  - I2C/I2C_TwoBoards_MasterTx_SlaveRx/Inc/stm32f2xx_it.h          Interrupt handlers header file
  - I2C/I2C_TwoBoards_MasterTx_SlaveRx/Inc/main.h                  Header for main.c module
  - I2C/I2C_TwoBoards_MasterTx_SlaveRx/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_TwoBoards_MasterTx_SlaveRx/Src/stm32f2xx_it.c          Interrupt handlers
  - I2C/I2C_TwoBoards_MasterTx_SlaveRx/Src/main.c                  Main program
  - I2C/I2C_TwoBoards_MasterTx_SlaveRx/Src/system_stm32f2xx.c      STM32F2xx system source file

@par Hardware and Software environment

  - This example runs on STM32F207ZG devices.
    
  - This example has been tested with NUCLEO-F207ZG board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-F207ZG Set-up
    - Connect GPIOs connected to Board Slave I2C2 SCL/SDA (PB.10 and PB.11)
    to respectively Board Master SCL and SDA pins of I2C1 (PB.6 and PB.9).
      - I2C2_SCL  PB.10 (CN10, pin 32) : connected to I2C1_SCL PB.6 (CN10, pin 13) 
      - I2C2_SDA  PB.11 (CN10, pin 34) : connected to I2C1_SDA PB.9 (CN7, pin 4)
    - Connect Master board GND to Slave Board GND

  - Launch the program. Press Key push-button on Slave BOARD then on Master BOARD
      to initiate a write request by Master then Slave receive bytes.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory (The user can choose between Master 
   and Slave target through "#define SLAVE_BOARD" in the "main.h" file)
    o Comment "#define SLAVE_BOARD" and load the project in Master Board
    o Uncomment "#define SLAVE_BOARD" and load the project in Slave Board
 - Run the example


 */
