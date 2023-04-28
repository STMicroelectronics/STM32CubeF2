/**
  ******************************************************************************
  * @file    stm322xg_eval_eeprom.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage an I2C M24C64 
  *          EEPROM memory.
  *          
  *          =================================================================== 
  *          Notes:
  *           - This driver is intended for STM32F2xx families devices only. 
  *           - The I2C EEPROM memory (M24C64) is available on STM322xG-EVAL
  *           - To use this driver you have to connect the eeprom jumper (JP24).
  *          ===================================================================
  *              
  *          It implements a high level communication layer for read and write 
  *          from/to this memory. The needed STM32F2xx hardware resources (I2C and 
  *          GPIO) are defined in stm32f2xg_eval.h file, and the initialization is 
  *          performed in EEPROM_IO_Init() function declared in stm32f2xg_eval.c 
  *          file.
  *          You can easily tailor this driver to any other development board, 
  *          by just adapting the defines for hardware resources and 
  *          EEPROM_IO_Init() function. 
  *        
  *          @note In this driver, basic read and write functions (BSP_EEPROM_ReadBuffer() 
  *                and EEPROM_WritePage()) use Polling mode to perform the data transfer 
  *                to/from EEPROM memory.
  *             
  *     +-----------------------------------------------------------------+
  *     |               Pin assignment for M24C64 EEPROM                 |
  *     +---------------------------------------+-----------+-------------+
  *     |  STM32F2xx I2C Pins                   |   EEPROM  |   Pin       |
  *     +---------------------------------------+-----------+-------------+
  *     | .                                     |   E0      |    1  (0V)  |
  *     | .                                     |   E1      |    2  (0V)  |
  *     | .                                     |   E2      |    3  (0V)  |
  *     | .                                     |   VSS(GND)|    4  (0V)  |
  *     | SDA                                   |   SDA     |    5        |
  *     | SCL                                   |   SCL     |    6        |
  *     | JP24                                  |   /WS     |    7        |
  *     | .                                     |   VDD     |    8 (3.3V) |
  *     +---------------------------------------+-----------+-------------+
  *
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
/* Includes ------------------------------------------------------------------*/
#include "stm322xg_eval_eeprom.h"
/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM322xG_EVAL
  * @{
  */ 
  
/** @addtogroup STM322xG_EVAL_EEPROM STM322xG EVAL EEPROM
  * @brief This file includes the I2C EEPROM driver of STM322xG-EVAL evaluation board.
  * @{
  */ 

/** @defgroup STM322xG_EVAL_EEPROM_Private_Variables STM322xG EVAL EEPROM Private Variables
  * @{
  */

__IO uint32_t  EEPROMTimeout = EEPROM_READ_TIMEOUT;
__IO uint16_t  EEPROMDataRead;
__IO uint8_t   EEPROMDataWrite;
/**
  * @}
  */ 

/** @defgroup STM322xG_EVAL_EEPROM_Private_Function_Prototypes STM322xG EVAL EEPROM Private Function Prototypes
  * @{
  */ 
static uint32_t EEPROM_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);
static uint32_t EEPROM_WaitEepromStandbyState(void);
/**
  * @}
  */ 

/** @defgroup STM322xG_EVAL_EEPROM_Private_Functions STM322xG EVAL EEPROM Private Functions
  * @{
  */ 

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0)
  */
uint32_t BSP_EEPROM_Init(void)
{ 
  /* I2C Initialization */
  EEPROM_IO_Init();
  
  /* Select the EEPROM address and check if OK */
  if(EEPROM_IO_IsDeviceReady(EEPROM_I2C_ADDRESS, EEPROM_MAX_TRIALS) != HAL_OK)
  {
    return EEPROM_FAIL;
  }
  return EEPROM_OK;
}

/**
  * @brief  Reads a block of data from the EEPROM.
  * @param  pBuffer: pointer to the buffer that receives the data read from 
  *         the EEPROM.
  * @param  ReadAddr: EEPROM's internal address to start reading from.
  * @param  NumByteToRead: pointer to the variable holding number of bytes to 
  *         be read from the EEPROM.
  * 
  *        @note The variable pointed by NumByteToRead is reset to 0 when all the 
  *              data are read from the EEPROM. Application should monitor this 
  *              variable in order know when the transfer is complete.
  * 
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0) or the timeout user callback.
  */
uint32_t BSP_EEPROM_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead)
{  
  uint32_t buffersize = *NumByteToRead;
  
  /* Set the pointer to the Number of data to be read */
  EEPROMDataRead = *NumByteToRead;
  
  if(EEPROM_IO_ReadData(EEPROM_I2C_ADDRESS, ReadAddr, pBuffer, buffersize) != HAL_OK)
  {
    BSP_EEPROM_TIMEOUT_UserCallback();
    return EEPROM_FAIL;
  }
  
  /* If all operations OK, return EEPROM_OK (0) */
  return EEPROM_OK;
}

/**
  * @brief  Writes buffer of data to the I2C EEPROM.
  * @param  pBuffer: pointer to the buffer  containing the data to be written 
  *         to the EEPROM.
  * @param  WriteAddr: EEPROM's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the EEPROM.
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0) or the timeout user callback.
  */
uint32_t BSP_EEPROM_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t  numofpage = 0, numofsingle = 0, count = 0;
  uint16_t addr = 0;
  uint8_t  dataindex = 0;
  uint32_t status = EEPROM_OK;
  
  addr = WriteAddr % EEPROM_PAGESIZE;
  count = EEPROM_PAGESIZE - addr;
  numofpage =  NumByteToWrite / EEPROM_PAGESIZE;
  numofsingle = NumByteToWrite % EEPROM_PAGESIZE;
  
  /* If WriteAddr is EEPROM_PAGESIZE aligned */
  if(addr == 0) 
  {
    /* If NumByteToWrite < EEPROM_PAGESIZE */
    if(numofpage == 0) 
    {
      /* Store the number of data to be written */
      dataindex = numofsingle;
      /* Start writing data */
      status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
      if(status != EEPROM_OK)
      {
        return status;
      }
    }
    /* If NumByteToWrite > EEPROM_PAGESIZE */
    else  
    {
      while(numofpage--)
      {
        /* Store the number of data to be written */
        dataindex = EEPROM_PAGESIZE;        
        status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
        
        WriteAddr +=  EEPROM_PAGESIZE;
        pBuffer += EEPROM_PAGESIZE;
      }
      
      if(numofsingle!=0)
      {
        /* Store the number of data to be written */
        dataindex = numofsingle;          
        status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
      }
    }
  }
  /* If WriteAddr is not EEPROM_PAGESIZE aligned */
  else 
  {
    /* If NumByteToWrite < EEPROM_PAGESIZE */
    if(numofpage == 0) 
    {
      /* If the number of data to be written is more than the remaining space 
      in the current page: */
      if(NumByteToWrite > count)
      {
        /* Store the number of data to be written */
        dataindex = count;        
        /* Write the data contained in same page */
        status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
        
        /* Store the number of data to be written */
        dataindex = (NumByteToWrite - count);          
        /* Write the remaining data in the following page */
        status = EEPROM_WritePage((uint8_t*)(pBuffer + count), (WriteAddr + count), (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
      }      
      else      
      {
        /* Store the number of data to be written */
        dataindex = numofsingle;         
        status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
      }     
    }
    /* If NumByteToWrite > EEPROM_PAGESIZE */
    else
    {
      NumByteToWrite -= count;
      numofpage =  NumByteToWrite / EEPROM_PAGESIZE;
      numofsingle = NumByteToWrite % EEPROM_PAGESIZE;
      
      if(count != 0)
      {  
        /* Store the number of data to be written */
        dataindex = count;         
        status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(numofpage--)
      {
        /* Store the number of data to be written */
        dataindex = EEPROM_PAGESIZE;          
        status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
        WriteAddr +=  EEPROM_PAGESIZE;
        pBuffer += EEPROM_PAGESIZE;  
      }
      if(numofsingle != 0)
      {
        /* Store the number of data to be written */
        dataindex = numofsingle; 
        status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
      }
    }
  }  
  
  /* If all operations OK, return EEPROM_OK (0) */
  return EEPROM_OK;
}

/**
  * @brief  Writes more than one byte to the EEPROM with a single WRITE cycle.
  *
  * @note   The number of bytes (combined to write start address) must not 
  *         cross the EEPROM page boundary. This function can only write into
  *         the boundaries of an EEPROM page.
  *         This function doesn't check on boundaries condition (in this driver 
  *         the function BSP_EEPROM_WriteBuffer() which calls EEPROM_WritePage() is 
  *         responsible of checking on Page boundaries).
  * 
  * @param  pBuffer: pointer to the buffer containing the data to be written to 
  *         the EEPROM.
  * @param  WriteAddr: EEPROM's internal address to write to.
  * @param  NumByteToWrite: pointer to the variable holding number of bytes to 
  *         be written into the EEPROM. 
  * 
  *        @note The variable pointed by NumByteToWrite is reset to 0 when all the 
  *              data are written to the EEPROM. Application should monitor this 
  *              variable in order know when the transfer is complete.
  * 
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0) or the timeout user callback.
  */
static uint32_t EEPROM_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite)
{ 
  uint32_t buffersize = *NumByteToWrite;
  uint32_t status = EEPROM_OK;
  
  /* Set the pointer to the Number of data to be written */
  EEPROMDataWrite = *NumByteToWrite;  
  if(EEPROM_IO_WriteData(EEPROM_I2C_ADDRESS, WriteAddr, pBuffer, buffersize) != HAL_OK)  
  {
    BSP_EEPROM_TIMEOUT_UserCallback();
    status = EEPROM_FAIL;
  }
  
  while(EEPROM_WaitEepromStandbyState() != EEPROM_OK)
  {
    return EEPROM_FAIL;
  }
  
  /* If all operations OK, return EEPROM_OK (0) */
  return status;
}

/**
  * @brief  Waits for EEPROM Standby state.
  * 
  * @note  This function allows to wait and check that EEPROM has finished the 
  *        last operation. It is mostly used after Write operation: after receiving
  *        the buffer to be written, the EEPROM may need additional time to actually
  *        perform the write operation. During this time, it doesn't answer to
  *        I2C packets addressed to it. Once the write operation is complete
  *        the EEPROM responds to its address.
  * 
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0) or the timeout user callback.
  */
static uint32_t EEPROM_WaitEepromStandbyState(void)      
{
  /* Check if the maximum allowed number of trials has bee reached */
  if(EEPROM_IO_IsDeviceReady(EEPROM_I2C_ADDRESS, EEPROM_MAX_TRIALS) != HAL_OK)
  {
    /* If the maximum number of trials has been reached, exit the function */
    BSP_EEPROM_TIMEOUT_UserCallback();
    return EEPROM_TIMEOUT;
  }
  return EEPROM_OK;
}

/**
  * @brief  Basic management of the timeout situation.
  */
__weak void BSP_EEPROM_TIMEOUT_UserCallback(void)
{
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

