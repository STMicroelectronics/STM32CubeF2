/**
  @page STemWin_HelloWorld Readme file
 
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    STemWin/STemWin_HelloWorld/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of STemWin Hello World application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
   @endverbatim

@par Description

Simple "Hello World" example based on STemWin.

The application allows also to run the different Segger samples that can be
downloaded from here:
http://www.segger.com/emwin-samples.html
To do this, user has only to replace the file "Basic_HelloWorld.c" into the
project workspace by the downloaded one.
As application, two sample source files are provided (but not linked to the project):
	STemWin/HelloWorld/Src/MEMDEV_WM_Ticker.c
	STemWin/HelloWorld/Src/MOVIE_ShowFeatures.c

Note that the following user files may need to be updated:
  LCDConf_stm322xg_eval.c
  GUIConf_stm322xg_eval.c
(if for example more GUI allocated memory is needed)

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - STemWin/STemWin_HelloWorld/Inc/GUIConf.h                Header for GUIConf_stm322xg_eval.c
  - STemWin/STemWin_HelloWorld/Inc/LCDConf_stm322xg_eval.h  Header for LCDConf_stm322xg_eval.c
  - STemWin/STemWin_HelloWorld/Inc/main.h                   Main program header file
  - STemWin/STemWin_HelloWorld/Inc/stm32f2xx_hal_conf.h     Library Configuration file
  - STemWin/STemWin_HelloWorld/Inc/stm32f2xx_it.h           Interrupt handlers header file
  - STemWin/STemWin_HelloWorld/Src/BASIC_HelloWorld.c       Simple demo drawing "Hello world"
  - STemWin/STemWin_HelloWorld/Src/GUIConf_stm322xg_eval.c  Display controller initialization
  - STemWin/STemWin_HelloWorld/Src/LCDConf_stm322xg_eval.c  Configuration file for the GUI library
  - STemWin/STemWin_HelloWorld/Src/main.c                   Main program file
  - STemWin/STemWin_HelloWorld/Src/stm32f2xx_it.c           STM32F2xx Interrupt handlers
  - STemWin/STemWin_HelloWorld/Src/system_stm32f2xx.c       STM32F2xx system file
 
@par Hardware and Software environment 

  - This application runs on STM32F2xx devices.
    
  - This application has been tested with STM322xG-EVAL evaluation board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the application
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
