/**
  @page LibJPEG_Encoding LibJPEG encoding application
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    LibJPEG/LibJPEG_Encoding/Readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LibJPEG encoding application.
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

This application demonstrates how to read BMP file from micro SD, encode it, save the jpeg file
in uSD Card then decode the jpeg file and display the final BMP image on the LCD.

BMP image is read from the bottom to the top, in order to be encoded in JPG from the top to the bottom.
BMP image is in BGR format and JPG in RGB format. B and R values of the pixels are swapped by redefining
the order of pixel components.

The BMP image should be copied at the micro SD card root.The .bmp 
files available within the "BMP_320x240" folder under "Utilities/Media/Pictures"

The images must have the following properties:
 - named as "image.bmp"
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

    - LibJPEG/LibJPEG_Encoding/Inc/main.h                      Main program header file
    - LibJPEG/LibJPEG_Encoding/Inc/stm32f2xx_it.h              Interrupt handlers header file
    - LibJPEG/LibJPEG_Encoding/Inc/stm32f2xx_hal_conf.h        HAL Configuration file 
    - LibJPEG/LibJPEG_Encoding/Inc/ffconf.h                    FAT file system module configuration file
    - LibJPEG/LibJPEG_Encoding/Inc/encode.h                    Encoder header file
    - LibJPEG/LibJPEG_Encoding/Inc/decode.h                    Decoder header file
    - LibJPEG/LibJPEG_Encoding/Inc/jmorecfg.h                  Lib JPEG configuration file (advanced configuration).
    - LibJPEG/LibJPEG_Encoding/Inc/jconfig.h                   Lib JPEG configuration file.
    - LibJPEG/LibJPEG_Decoding/Inc/jdata_conf.h                Write/Read methods definition
    - LibJPEG/LibJPEG_Encoding/Src/main.c                      Main program  
    - LibJPEG/LibJPEG_Encoding/Src/stm32f2xx_it.c              Interrupt handlers
    - LibJPEG/LibJPEG_Encoding/Src/system_stm32f2xx.c          STM32F2xx system clock configuration file
    - LibJPEG/LibJPEG_Encoding/Src/encode.c                    Encoder file
    - LibJPEG/LibJPEG_Encoding/Src/decode.c                    Decoder file
    - LibJPEG/LibJPEG_Decoding/Src/jdata_conf.c                Write/Read methods definition



@par Hardware and Software environment

  - This application runs on STM32F207xx/217xx device.
    
  - This application has been tested with STMicroelectronics STM322xG-EVAL 
    evaluation boards and can be easily tailored to any other supported device 

  - STM322xG-EVAL Set-up
   - Connect a uSD Card to the MSD connector (CN6). 
   - Please ensure that jumpers JP16 and JP22 are in position 1-2.

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application


 */
                                   
