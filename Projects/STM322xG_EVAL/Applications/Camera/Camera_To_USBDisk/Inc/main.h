/**
  ******************************************************************************
  * @file    Camera/Camera_To_USBDisk/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
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
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm322xg_eval.h"
#include "stm322xg_eval_lcd.h"
#include "stm322xg_eval_camera.h"
#include "fatfs_storage.h"
#include "stm322xg_eval_ts.h"
#include "stm322xg_eval_sram.h"

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "usbh_diskio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* LCD Frame Buffer address */
#define CAMERA_FRAME_BUFFER               0x64000000

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Touchscreen_Calibration (void);
uint16_t Calibration_GetX(uint16_t x);
uint16_t Calibration_GetY(uint16_t y);
uint8_t IsCalibrationDone(void);

#endif /* __MAIN_H */
