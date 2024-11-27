/*******************************************************************************
*
* 代码许可和免责信息
* 武汉芯源半导体有限公司授予您使用所有编程代码示例的非专属的版权许可，您可以由此
* 生成根据您的特定需要而定制的相似功能。根据不能被排除的任何法定保证，武汉芯源半
* 导体有限公司及其程序开发商和供应商对程序或技术支持（如果有）不提供任何明示或暗
* 含的保证或条件，包括但不限于暗含的有关适销性、适用于某种特定用途和非侵权的保证
* 或条件。
* 无论何种情形，武汉芯源半导体有限公司及其程序开发商或供应商均不对下列各项负责，
* 即使被告知其发生的可能性时，也是如此：数据的丢失或损坏；直接的、特别的、附带的
* 或间接的损害，或任何后果性经济损害；或利润、业务、收入、商誉或预期可节省金额的
* 损失。
* 某些司法辖区不允许对直接的、附带的或后果性的损害有任何的排除或限制，因此某些或
* 全部上述排除或限制可能并不适用于您。
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32L052_LPTIM_H
#define __CW32L052_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32l010.h"
#include "base_types.h"


/* Exported types ------------------------------------------------------------*/

typedef enum {DOWN_STOP = 0,  UP_STOP, DOWN_RUN, UP_RUN} ENCStatus;



/**
 * @brief  LPTIM Init structure definition
 */

typedef struct
{
    uint32_t LPTIM_ClockSource;
    uint32_t LPTIM_CounterMode;
    uint32_t LPTIM_Period;
    uint32_t LPTIM_Prescaler;
} LPTIM_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
#define LPTIM_CLOCK_SOURCE_MCLK          ((uint32_t)0x00000000)
#define LPTIM_CLOCK_SOURCE_CH1           ((uint32_t)0x00000001)
#define IS_LPTIM_CLOCK_SOURCE(SOURCE)    (((SOURCE) == LPTIM_CLOCK_SOURCE_MCLK)  ||\
                                         ((SOURCE) == LPTIM_CLOCK_SOURCE_CH1))

#define LPTIM_COUNTER_MODE_TIME          ((uint32_t)0x00000000)
#define LPTIM_COUNTER_MODE_COUNT         (((uint32_t)0x00000001) << 23)
#define IS_LPTIM_COUNTER_MODE(MODE)      (((MODE) == LPTIM_COUNTER_MODE_TIME)    ||\
                                         ((MODE) == LPTIM_COUNTER_MODE_COUNT))

#define LPTIM_PRS_DIV1                   (((uint32_t)0x00000000))
#define LPTIM_PRS_DIV2                   (((uint32_t)0x00000001) << 9)
#define LPTIM_PRS_DIV4                   (((uint32_t)0x00000002) << 9)
#define LPTIM_PRS_DIV8                   (((uint32_t)0x00000003) << 9)
#define LPTIM_PRS_DIV16                  (((uint32_t)0x00000004) << 9)
#define LPTIM_PRS_DIV32                  (((uint32_t)0x00000005) << 9)
#define LPTIM_PRS_DIV64                  (((uint32_t)0x00000006) << 9)
#define LPTIM_PRS_DIV128                 (((uint32_t)0x00000007) << 9)
#define IS_LPTIM_PRS(PRS)                (((PRS) == LPTIM_PRS_DIV1)              || \
                                         ((PRS) == LPTIM_PRS_DIV2)               || \
                                         ((PRS) == LPTIM_PRS_DIV4)               || \
                                         ((PRS) == LPTIM_PRS_DIV8)               || \
                                         ((PRS) == LPTIM_PRS_DIV16)              || \
                                         ((PRS) == LPTIM_PRS_DIV32)              || \
                                         ((PRS) == LPTIM_PRS_DIV64)              || \
                                         ((PRS) == LPTIM_PRS_DIV128))

#define LPTIM_OPERATION_SINGLE           ((uint32_t)0x00000002)
#define LPTIM_OPERATION_REPETITIVE       ((uint32_t)0x00000004)
#define IS_LPTIM_OPERATION_MODE(MODE)    (((MODE) == LPTIM_OPERATION_SINGLE)     ||\
                                         ((MODE) == LPTIM_OPERATION_REPETITIVE))

#define LPTIM_RELOAD_MODE_UPDATE         (((uint32_t)0x00000001) << 22)
#define LPTIM_RELOAD_MODE_IMMEDIATE      (((uint32_t)0x00000000))
#define IS_LPTIM_RELOAD_MODE(RELOAD)     (((RELOAD) == LPTIM_RELOAD_MODE_UPDATE) ||\
                                         ((RELOAD) == LPTIM_RELOAD_MODE_IMMEDIATE))



#define LPTIM_FLAG_CMPM                  (((uint32_t)0x00000001))
#define LPTIM_FLAG_ARRM                  (((uint32_t)0x00000001) << 1)
#define LPTIM_FLAG_EXTTRIG               (((uint32_t)0x00000001) << 2)
#define LPTIM_FLAG_CMPOK                 (((uint32_t)0x00000001) << 3)
#define LPTIM_FLAG_ARROK                 (((uint32_t)0x00000001) << 4)
#define LPTIM_FLAG_UP                    (((uint32_t)0x00000001) << 5)
#define LPTIM_FLAG_DOWN                  (((uint32_t)0x00000001) << 6)
//#define LPTIM_FLAG_DIR                 (((uint32_t)0x00000003) << 7)
#define IS_LPTIM_GET_FLAG(FLAG)          (((FLAG) == LPTIM_FLAG_CMPM)            || \
                                         ((FLAG) == LPTIM_FLAG_ARRM)             || \
                                         ((FLAG) == LPTIM_FLAG_EXTTRIG)          || \
                                         ((FLAG) == LPTIM_FLAG_CMPOK)            || \
                                         ((FLAG) == LPTIM_FLAG_ARROK)            || \
                                         ((FLAG) == LPTIM_FLAG_UP)               || \
                                         ((FLAG) == LPTIM_FLAG_DOWN))
//                                       ((FLAG) == LPTIM_FLAG_DIR))

#define IS_LPTIM_CLEAR_FLAG(FLAG)        ((((FLAG) & 0xFFFFFE00) == 0x00000000) && ((FLAG) != 0x00000000))

#define LPTIM_IT_CMPM                    (((uint32_t)0x00000000))
#define LPTIM_IT_ARRM                    (((uint32_t)0x00000001) << 1)
#define LPTIM_IT_EXTTRIG                 (((uint32_t)0x00000001) << 2)
#define LPTIM_IT_CMPOK                   (((uint32_t)0x00000001) << 3)
#define LPTIM_IT_ARROK                   (((uint32_t)0x00000001) << 4)
#define LPTIM_IT_UP                      (((uint32_t)0x00000001) << 5)
#define LPTIM_IT_DOWN                    (((uint32_t)0x00000001) << 6)

#define IS_LPTIM_IT(IT)                  (((IT) == LPTIM_IT_CMPM)                || \
                                         ((IT) == LPTIM_IT_ARRM)                 || \
                                         ((IT) == LPTIM_IT_EXTTRIG)              || \
                                         ((IT) == LPTIM_IT_CMPOK)                || \
                                         ((IT) == LPTIM_IT_ARROK)                || \
                                         ((IT) == LPTIM_IT_UP)                   || \
                                         ((IT) == LPTIM_IT_DOWN))

#define IS_LPTIM_CLEAR_IT(IT)            ((((IT) & 0xFFFFFF80) == 0x00000000) && ((IT) != 0x00000000))

#define LPTIM_ICLK_PCLK                  ((uint32_t)0x00000000)
#define LPTIM_ICLK_LSE                   (((uint32_t)0x00000002) << 25)
#define LPTIM_ICLK_LSI                   (((uint32_t)0x00000003) << 25)
#define IS_LPTIM_ICLK(SRC)               (((SRC) == LPTIM_ICLK_PCLK)             ||\
                                         ((SRC) == LPTIM_ICLK_LSE)               ||\
                                         ((SRC) == LPTIM_ICLK_LSI))

#define LPTIM_PWM_POL_POS                (((uint32_t)0x00000000))
#define LPTIM_PWM_POL_NEG                (((uint32_t)0x00000001) << 21)
#define IS_LPTIM_PWM_POL(POL)            (((POL) == LPTIM_PWM_POL_POS) || ((POL) == LPTIM_PWM_POL_NEG))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void LPTIM_DeInit(void);
void LPTIM_Init(LPTIM_InitTypeDef* LPTIM_InitStruct);
void LPTIM_PrescalerConfig(uint32_t Prescaler);
void LPTIM_CounterModeConfig(uint32_t LPTIM_CounterMode);
void LPTIM_SetAutoreload(uint16_t Autoreload, uint32_t ReloadMode);
uint32_t LPTIM_GetCounter(void);
uint8_t LPTIM_GetPrescaler(void);
void LPTIM_SelectOnePulseMode(uint16_t LPTIM_OPMode);
void LPTIM_Cmd(FunctionalState NewState);

void LPTIM_InternalClockConfig(uint32_t LPTIM_ICLK_Source);
void LPTIM_PWMStart(uint32_t Period, uint32_t Pulse, uint32_t Polarity);



void LPTIM_ITConfig(uint32_t LPTIM_IT, FunctionalState NewState);
FlagStatus LPTIM_GetFlagStatus(uint32_t LPTIM_FLAG);
void LPTIM_ClearFlag(uint32_t LPTIM_FLAG);
ITStatus LPTIM_GetITStatus(uint32_t LPTIM_IT);
void LPTIM_ClearITPendingBit(uint32_t LPTIM_IT);

ENCStatus LPTIM_GetENCStatus(void);




#ifdef __cplusplus
}
#endif

#endif /*__CW32L052_LPTIM_H */
/**
  * @}
  */
