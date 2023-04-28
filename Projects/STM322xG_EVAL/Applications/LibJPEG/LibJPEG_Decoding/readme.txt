/**
  @page LibJPEG_Decoding LibJPEG decoding application
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    LibJPEG/LibJPEG_Decoding/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LibJPEG decoding application.
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

This application demonstrates how to read jpeg file from SDCard memory, decode it 
and display the final BMP image on the LCD.

The JPEG images should be copied at the micro SD card root.The .jpg 
file available within the "JPG" folder under "Utilities/Media/Pictures"

The images must have the following properties:
 - named as "image.jpg"
 - 320*240 size

The image size can be modified by changing IMAGE_WIDTH and IMAGE_HEIGHT defines 
in "main.h" file to decode other resolution than 320x240.
  
@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents

    - LibJPEG/LibJPEG_Decoding/Inc/main.h                      Main program header file
    - LibJPEG/LibJPEG_Decoding/Inc/stm32f2xx_it.h              Interrupt handlers header file
    - LibJPEG/LibJPEG_Decoding/Inc/stm32f2xx_hal_conf.h        HAL Configuration file 
    - LibJPEG/LibJPEG_Decoding/Inc/ffconf.h                    FAT file system module configuration file
    - LibJPEG/LibJPEG_Decoding/Inc/decode.h                    Decoder header file
    - LibJPEG/LibJPEG_Decoding/Inc/jmorecfg.h                  Lib JPEG configuration file (advanced configuration)
    - LibJPEG/LibJPEG_Decoding/Inc/jconfig.h                   Lib JPEG configuration file
    - LibJPEG/LibJPEG_Decoding/Inc/jdata_conf.h                Write/Read methods definition
	- LibJPEG/LibJPEG_Decoding/Src/main.c                      Main program  
    - LibJPEG/LibJPEG_Decoding/Src/stm32f2xx_it.c              Interrupt handlers
    - LibJPEG/LibJPEG_Decoding/Src/system_stm32f2xx.c          STM32F2xx system clock configuration file
    - LibJPEG/LibJPEG_Decoding/Src/decode.c                    Decoder file
    - LibJPEG/LibJPEG_Decoding/Src/jdata_conf.c                Write/Read methods definition



@par Hardware and Software environment

  - This application runs on STM32F207xx/217xx device.
    
  - This application has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.  

  - STM322xG-EVAL Set-up
   - Connect a uSD Card to the MSD connector (CN6). 
   - Please ensure that jumpers JP16 and JP22 are in position 1-2.

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application


 */
                                   
