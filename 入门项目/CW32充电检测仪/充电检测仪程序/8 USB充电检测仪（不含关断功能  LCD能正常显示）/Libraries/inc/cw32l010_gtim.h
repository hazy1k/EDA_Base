/**
 * @file cw32l010_gtim.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2022-7-12
 *
 * @copyright Copyright (c) 2021
 *
 */
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
#ifndef __CW32L010_GTIM_H
#define __CW32L010_GTIM_H


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "system_cw32l010.h"


/******************************************************************************
 * type definitions ('typedef')
 ******************************************************************************/

/**
 * @brief GTIM 基础初始化参数
 */
typedef struct
{
    uint32_t ARRBuffState;                  /*!< GTIM ARR 缓存是能控制 */
    uint32_t AlignMode;                     /*!< GTIM的模式选择。 */
    uint32_t Direction;                     /*!< GTIM的计数方向，中心对其模式下无效 */
    uint32_t PulseMode;                     /*!< GTIM的单次/连续计数模式选择。 */
    uint32_t EventOption;                   /*!< GTIM的事件源选择 */
    uint32_t UpdateOption;                  /*!< GTIM更新使能选择 */   
    uint32_t Prescaler;                     /*!< GTIM的预分频系数。 */
    uint32_t ReloadValue;                   /*!< GTIM的重载值。 */    
} GTIM_InitTypeDef;


typedef struct
{
    uint32_t SlaverMode;                       /*!< 从模式选择 */
    uint32_t TrigInput;                        /*!< 触发信号源选择 */
    uint32_t PreloadSource;                    /*!< 预加载源选择 */
    uint32_t PreloadState;                     /*!< 预加载使能  */
}GTIM_SlaverCfgTypeDef;

typedef struct
{
    FunctionalState FastMode;                       /* 输出比较快速模式使能 */
    FunctionalState PreloadState;                   /* 输出比较预装载使能 */
    uint32_t OCMode;                         /* 输出比较模式 */
    uint32_t OCPolarity;                     /* 比较输出极性 */  
}GTIM_OCModeCfgTypeDef;


typedef struct
{
    uint32_t ICMap;                /* IC映射 */
    
    uint32_t ICPrescaler;          /* 输入捕获预分配 */
    
    uint32_t ICFilter;             /*!< 输入滤波配置 */
    
    uint32_t ICPolarity;           /*!< 输入捕获极性：上升、下降、双沿 */    
}GTIM_ICModeCfgTypeDef;

/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_GTIM_DEFINE(GTIMx)              ((GTIMx) == CW_GTIM1) 
                                          
#define GTIM_ARR_BUFF_EN                   (1UL << GTIMx_CR1_ARPE_Pos)
#define GTIM_ARR_BUFF_DIS                  (0UL)
#define IS_GTIM_ARR_BUFF(STATE)            (((STATE) == GTIM_ARR_BUFF_EN) ||\
                                            ((STATE) == GTIM_ARR_BUFF_DIS))

#define GTIM_ALIGN_MODE_EDGE               (0UL)
#define GTIM_ALIGN_MODE_CENTER_DOWN        (1UL << GTIMx_CR1_CMS_Pos)
#define GTIM_ALIGN_MODE_CENTER_UP          (2UL << GTIMx_CR1_CMS_Pos)
#define GTIM_ALIGN_MODE_CENTER_BOTH        (3UL << GTIMx_CR1_CMS_Pos)
#define IS_GTIM_ALIGN_MODE(MODE)           (((MODE) == GTIM_ALIGN_MODE_EDGE) ||\
                                            ((MODE) == GTIM_ALIGN_MODE_CENTER_DOWN) ||\
                                            ((MODE) == GTIM_ALIGN_MODE_CENTER_UP) ||\
                                            ((MODE) == GTIM_ALIGN_MODE_CENTER_BOTH))

#define GTIM_DIRECTION_UP                  (0U)
#define GTIM_DIRECTION_DOWN                (1UL << GTIMx_CR1_DIR_Pos)
#define IS_GTIM_DIRECTION(DIR)             (((DIR) == GTIM_DIRECTION_UP) ||\
                                            ((DIR) == GTIM_DIRECTION_DOWN))
                                            
#define GTIM_PULSE_MODE_EN                 (1UL << GTIMx_CR1_OPM_Pos)
#define GTIM_PULSE_MODE_DIS                (0UL)
#define IS_GTIM_PULSE_MODE(MODE)           (((MODE) == GTIM_PULSE_MODE_EN) ||\
                                            ((MODE) == GTIM_PULSE_MODE_DIS))

#define GTIM_EVENT_EXTENSION               (0U)
#define GTIM_EVENT_NORMAL                  (1UL << GTIMx_CR1_URS_Pos)
#define IS_GTIM_EVENT_OPT(OPT)             (((OPT) == GTIM_EVENT_NORMAL) ||\
                                            ((OPT) == GTIM_EVENT_EXTENSION))

#define GTIM_UPDATE_EN                     (0U)
#define GTIM_UPDATE_DIS                    (1UL << GTIMx_CR1_UDIS_Pos)
#define IS_GTIM_UPDATE_OPT(OPT)            (((OPT) == GTIM_UPDATE_EN) ||\
                                            ((OPT) == GTIM_UPDATE_DIS))
                      
#define GTIM_MASTER_TRGO_RESET             (0UL)
#define GTIM_MASTER_TRGO_EN                (1UL)
#define GTIM_MASTER_TRGO_UPDATE            (2UL)
#define GTIM_MASTER_TRGO_CCH1              (3UL)
#define GTIM_MASTER_TRGO_CCH2              (4UL)
#define GTIM_MASTER_TRGO_CCH3              (5UL)
#define GTIM_MASTER_TRGO_CCH4              (6UL)
#define GTIM_MASTER_TRGO_OC1REF            (7UL)
#define GTIM_MASTER_TRGO_OC2REF            (8UL)
#define GTIM_MASTER_TRGO_OC3REF            (9UL)
#define GTIM_MASTER_TRGO_OC4REF            (10UL)
#define GTIM_MASTER_TRGO_OC1REFC           (11UL)
#define GTIM_MASTER_TRGO_OC2REFC           (12UL)
#define GTIM_MASTER_TRGO_OC3REFC           (13UL)
#define GTIM_MASTER_TRGO_OC4REFC           (14UL)
#define GTIM_MASTER_TRGO_ENCODE            (15UL)

#define GTIM_SLAVER_MODE_RESET             (4UL)
#define GTIM_SLAVER_MODE_GATE              (5UL)
#define GTIM_SLAVER_MODE_TRIGGER           (6UL)
#define GTIM_SLAVER_MODE_EXTENAL           (7UL)
#define GTIM_SLAVER_MODE_GROUP_RST_TRIG    (8UL)
#define GTIM_SLAVER_MODE_GROUP_GATE_RST    (9UL)
#define IS_GTIM_SLAVER_MODE(MODE)          (((MODE) == GTIM_SLAVER_MODE_RESET) ||\
                                            ((MODE) == GTIM_SLAVER_MODE_GATE) ||\
                                            ((MODE) == GTIM_SLAVER_MODE_TRIGGER) ||\
                                            ((MODE) == GTIM_SLAVER_MODE_EXTENAL) ||\
                                            ((MODE) == GTIM_SLAVER_MODE_GROUP_RST_TRIG) ||\
                                            ((MODE) == GTIM_SLAVER_MODE_GROUP_GATE_RST))
                                            
#define GTIM_TRIG_INPUT_ITR0               (0U)
#define GTIM_TRIG_INPUT_ITR1               (1U)
#define GTIM_TRIG_INPUT_ITR2               (2U)
#define GTIM_TRIG_INPUT_ITR3               (3U)
#define GTIM_TRIG_INPUT_TI1F_ED            (4U)
#define GTIM_TRIG_INPUT_TI1FP1             (5U)
#define GTIM_TRIG_INPUT_TI1FP2             (6U)
#define GTIM_TRIG_INPUT_ETRF               (7U)
#define GTIM_TRIG_INPUT_ITR4               (8U)
#define GTIM_TRIG_INPUT_ITR5               (9U)
#define GTIM_TRIG_INPUT_ITR6               (10U)
#define GTIM_TRIG_INPUT_ITR7               (11U)
#define GTIM_TRIG_INPUT_ITR8               (12U)
#define GTIM_TRIG_INPUT_ITR9               (13U)
#define GTIM_TRIG_INPUT_ITR10              (14U)
#define GTIM_TRIG_INPUT_ITR11              (15U)
#define GTIM_TRIG_INPUT_ITR12              (16U)
#define IS_GTIM_TRIG_INPUT(INPUT)          (INPUT <= 16)


#define GTIM_PRELOAD_SOURCE_EVENT          0
#define GTIM_PRELOAD_SOURCE_INDEX          1
#define IS_GTIM_PRELOAD_SOURCE(SOURCE)     (((SOURCE) == GTIM_PRELOAD_SOURCE_EVENT) ||\
                                            ((SOURCE) == GTIM_PRELOAD_SOURCE_INDEX))
                                            
#define GTIM_PRELOAD_EN                    1
#define GTIM_PRELOAD_DIS                   0


#define GTIM_OC_MODE_FROZEN                0u
#define GTIM_OC_MODE_ACTIVE                1u
#define GTIM_OC_MODE_INACTIVE              2u
#define GTIM_OC_MODE_TOGGLE                3u
#define GTIM_OC_MODE_FORCE_LOW             4u
#define GTIM_OC_MODE_FORCE_HIGH            5u
#define GTIM_OC_MODE_PWM1                  6u
#define GTIM_OC_MODE_PWM2                  7u
#define GTIM_OC_MODE_OPM1                  8u
#define GTIM_OC_MODE_OPM2                  9u
#define GTIM_OC_MODE_DIRECTION             11u
#define GTIM_OC_MODE_GROUP_PWM1_OCREF      12u
#define GTIM_OC_MODE_GROUP_PWM2_OCREF      13u
#define GTIM_OC_MODE_PWM_ASYM1             14u
#define GTIM_OC_MODE_PWM_ASYM2             15u
#define IS_GTIM_OC_MODE(MODE)             (((MODE) <= 15) && ((MODE) != 10))

#define GTIM_OC_POLAR_INVERT               1
#define GTIM_OC_POLAR_NONINVERT            0
#define IS_GTIM_OC_POLAR(POLAR)            (((POLAR) == GTIM_OC_POLAR_INVERT) ||\
                                            ((POLAR) == GTIM_OC_POLAR_NONINVERT))
                                            
#define GTIM_IC1_MAP_TI1                       (0x01U)
#define GTIM_IC1_MAP_TI2                       (0x02U)
#define GTIM_IC2_MAP_TI2                       (0x01U)
#define GTIM_IC2_MAP_TI1                       (0x02U)
#define GTIM_IC_MAP_TRC                        (0x03U)
#define IS_GTIM_IC_MAP(INSTANCE)               (((INSTANCE) <= 3) && ((INSTANCE) != 0))

#define GTIM_IC_PRESCALER_DIV1             0u
#define GTIM_IC_PRESCALER_DIV2             1u
#define GTIM_IC_PRESCALER_DIV4             2u
#define GTIM_IC_PRESCALER_DIV8             3u
#define IS_GTIM_IC_PRESCALER(SCALER)       ((SCALER) < 4)

#define GTIM_IC_FILTER_PCLK_NONE           (0u)
#define GTIM_IC_FILTER_PCLK_N2             (1u)
#define GTIM_IC_FILTER_PCLK_N4             (2u)
#define GTIM_IC_FILTER_PCLK_N8             (3u)
#define GTIM_IC_FILTER_FDTS_DIV2_N6        (4u)
#define GTIM_IC_FILTER_FDTS_DIV2_N8        (5u)
#define GTIM_IC_FILTER_FDTS_DIV4_N6        (6u)
#define GTIM_IC_FILTER_FDTS_DIV4_N8        (7u)
#define GTIM_IC_FILTER_FDTS_DIV8_N6        (8u)
#define GTIM_IC_FILTER_FDTS_DIV8_N8        (9u)
#define GTIM_IC_FILTER_FDTS_DIV16_N5       (10u)
#define GTIM_IC_FILTER_FDTS_DIV16_N6       (11u)
#define GTIM_IC_FILTER_FDTS_DIV16_N8       (12u)
#define GTIM_IC_FILTER_FDTS_DIV32_N5       (13u)
#define GTIM_IC_FILTER_FDTS_DIV32_N6       (14u)
#define GTIM_IC_FILTER_FDTS_DIV32_N8       (15u)
#define IS_GTIM_IC_FILTER(FILTER)          (FILTER <=15)

#define GTIM_ICPolarity_Rising             (1UL)
#define GTIM_ICPolarity_Falling            (2UL)
#define GTIM_ICPolarity_BothEdge           (3UL)
#define IS_GTIM_ICPolarity(MODE)           (((MODE) == GTIM_ICPolarity_Rising)     || \
                                           ((MODE) == GTIM_ICPolarity_Falling)     || \
                                           ((MODE) == GTIM_ICPolarity_BothEdge))





#define GTIM_PRESCALER_DIV1                (0UL)
#define GTIM_PRESCALER_DIV2                (1UL)
#define GTIM_PRESCALER_DIV4                (3UL)
#define GTIM_PRESCALER_DIV8                (7UL)
#define GTIM_PRESCALER_DIV16               (15UL)
#define GTIM_PRESCALER_DIV32               (31UL)
#define GTIM_PRESCALER_DIV64               (63UL)
#define GTIM_PRESCALER_DIV128              (127UL)
#define GTIM_PRESCALER_DIV256              (255UL)
#define GTIM_PRESCALER_DIV512              (511UL)
#define GTIM_PRESCALER_DIV1024             (1023UL)
#define GTIM_PRESCALER_DIV2048             (2047UL)
#define GTIM_PRESCALER_DIV4096             (4095UL)
#define GTIM_PRESCALER_DIV8192             (8191UL)
#define GTIM_PRESCALER_DIV16384            (16383UL)
#define GTIM_PRESCALER_DIV32768            (32767UL)

#define IS_GTIM_PRESCALER(DIV)             ((DIV) <= 0xFFFF)                                          

#define GTIM_IT_UPDATA                     (1UL << GTIMx_IER_UIE_Pos)
#define GTIM_IT_CC1                        (1UL << GTIMx_IER_CC1IE_Pos)
#define GTIM_IT_CC2                        (1UL << GTIMx_IER_CC2IE_Pos)
#define GTIM_IT_CC3                        (1UL << GTIMx_IER_CC3IE_Pos)
#define GTIM_IT_CC4                        (1UL << GTIMx_IER_CC4IE_Pos)
#define GTIM_IT_TI                         (1UL << GTIMx_IER_TIE_Pos)
#define GTIM_IT_IDX                        (1UL << GTIMx_IER_IDXIE_Pos)
#define GTIM_IT_DIR                        (1UL << GTIMx_IER_DIRIE_Pos)
#define GTIM_IT_IERR                       (1UL << GTIMx_IER_IERRIE_Pos)
#define GTIM_IT_TERR                       (1UL << GTIMx_IER_TERRIE_Pos)
#define IS_GTIM_IT(IT)                     ((((IT) & 0xFF0FFFA0) == 0x0UL) && ((IT) != 0x0UL))
#define IS_GTIM_GET_IT(IT)                 (((IT) == GTIM_IT_UPDATA) ||\
                                            ((IT) == GTIM_IT_CC1) ||\
                                            ((IT) == GTIM_IT_CC2) ||\
                                            ((IT) == GTIM_IT_CC3) ||\
                                            ((IT) == GTIM_IT_CC4) ||\
                                            ((IT) == GTIM_IT_TI) ||\
                                            ((IT) == GTIM_IT_IDX) ||\
                                            ((IT) == GTIM_IT_DIR) ||\
                                            ((IT) == GTIM_IT_IERR) ||\
                                            ((IT) == GTIM_IT_TERR))

/******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/


/******************************************************************************
* Global function prototypes
******************************************************************************/
void GTIM1_DeInit(void);
void GTIM_TimeBaseInit(GTIM_TypeDef* GTIMx, GTIM_InitTypeDef *GTIM_InitStruct);

void GTIM_MasterTRGOCfg(GTIM_TypeDef *GTIMx,uint32_t MasterTRGO);
void GTIM_SlaverModeCfg(GTIM_TypeDef *GTIMx, GTIM_SlaverCfgTypeDef *GTIM_SlaverCfgStruct);

void GTIM_OC1ModeCfg(GTIM_TypeDef *GTIMx, GTIM_OCModeCfgTypeDef *GTIM_OCModeCfgStruct);
void GTIM_OC2ModeCfg(GTIM_TypeDef *GTIMx, GTIM_OCModeCfgTypeDef *GTIM_OCModeCfgStruct);
void GTIM_OC3ModeCfg(GTIM_TypeDef *GTIMx, GTIM_OCModeCfgTypeDef *GTIM_OCModeCfgStruct);
void GTIM_OC4ModeCfg(GTIM_TypeDef *GTIMx, GTIM_OCModeCfgTypeDef *GTIM_OCModeCfgStruct);

void GTIM_OC1Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);
void GTIM_OC2Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);
void GTIM_OC3Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);
void GTIM_OC4Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);

void GTIM_IC1ModeCfg(GTIM_TypeDef* GTIMx, GTIM_ICModeCfgTypeDef *GTIM_ICInitStruct);
void GTIM_IC2ModeCfg(GTIM_TypeDef* GTIMx, GTIM_ICModeCfgTypeDef *GTIM_ICInitStruct);
void GTIM_IC3ModeCfg(GTIM_TypeDef* GTIMx, GTIM_ICModeCfgTypeDef *GTIM_ICInitStruct);
void GTIM_IC4ModeCfg(GTIM_TypeDef* GTIMx, GTIM_ICModeCfgTypeDef *GTIM_ICInitStruct);

void GTIM_IC1Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);
void GTIM_IC2Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);
void GTIM_IC3Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);
void GTIM_IC4Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);

void GTIM_Cmd(GTIM_TypeDef* GTIMx, FunctionalState NewState);

void GTIM_RemapUpdateFlag(GTIM_TypeDef *GTIMx,FunctionalState NewState);
void GTIM_SetPrescaler(GTIM_TypeDef* GTIMx, uint16_t GTIMPrescaler);
void GTIM_SetReloadValue(GTIM_TypeDef* GTIMx, uint16_t ReloadValue);
void GTIM_SetCounterValue(GTIM_TypeDef* GTIMx, uint16_t Value);

void GTIM_SetCompare1(GTIM_TypeDef* GTIMx, uint16_t Value);
void GTIM_SetCompare2(GTIM_TypeDef* GTIMx, uint16_t Value);
void GTIM_SetCompare3(GTIM_TypeDef* GTIMx, uint16_t Value);
void GTIM_SetCompare4(GTIM_TypeDef* GTIMx, uint16_t Value);
uint16_t GTIM_GetCapture1(GTIM_TypeDef* GTIMx);
uint16_t GTIM_GetCapture2(GTIM_TypeDef* GTIMx);
uint16_t GTIM_GetCapture3(GTIM_TypeDef* GTIMx);
uint16_t GTIM_GetCapture4(GTIM_TypeDef* GTIMx);

void GTIM_ITConfig(GTIM_TypeDef* GTIMx, uint32_t GTIM_IT, FunctionalState NewState);
ITStatus GTIM_GetITStatus(GTIM_TypeDef* GTIMx, uint32_t GTIM_IT);
void GTIM_ClearITPendingBit(GTIM_TypeDef* GTIMx, uint32_t GTIM_IT);



void GTIM_ETRConfig(GTIM_TypeDef* GTIMx, uint32_t ETRPolarity, uint32_t ETRFilter);
void GTIM_ICChannelConfig(GTIM_TypeDef* GTIMx, uint32_t CHx, uint32_t CHxFilter,uint32_t CHxInvert);


void GTIM1_ITRConfig(uint32_t ITRSouce);

#ifdef __cplusplus
}
#endif

#endif /*__CW32L010_GTIM_H */
