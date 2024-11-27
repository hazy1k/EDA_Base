/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 CW.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "base_types.h"
#include "cw32l010.h"
#include "system_cw32l010.h"
#include "interrupts_cw32l010.h"
#include "cw32l010_btim.h"
#include "cw32l010_sysctrl.h"
#include "cw32l010_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */
////每个编号对应的引脚
//#define SEGMENT_1 GPIO_PIN_1
//#define SEGMENT_2 GPIO_PIN_2
//#define SEGMENT_3 GPIO_PIN_5
//#define SEGMENT_4 GPIO_PIN_6
//#define SEGMENT_5 GPIO_PIN_2
//#define SEGMENT_6 GPIO_PIN_3
//#define SEGMENT_7 GPIO_PIN_6
//#define SEGMENT_8 GPIO_PIN_5
//#define SEGMENT_9 GPIO_PIN_4

////数码管的位数
//#define DIG1 1
//#define DIG2 2
//#define DIG3 3
//#define DIG4 4
//#define DIG5 5
//#define DIG6 6


/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/* USER CODE END ET */
void Seg_Dis(uint8_t SEGBIT,uint8_t Num);

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* USER CODE END EC */


/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
/* USER CODE END EM */


/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
/* USER CODE END EFP */


/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT CW *****END OF FILE****/
