/**
 * @file cw32l010_btim.h
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
#ifndef __CW32L010_BTIM_H
#define __CW32L010_BTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "system_cw32l010.h"

typedef struct
{
    uint16_t BTIM_Prescaler;         /* 预分配系数，取值范围2的n次幂，n=0,1,2,...,65535 */

    uint16_t BTIM_Mode;              /* 工作模式，00：定时器模式
                                         01：触发计数模式
                                         10：门控计数模式
                                         11：计数器模式  */

    uint16_t BTIM_Period;            /* 计数重载周期，取值范围0x0000 到 0xFFFF.  */

    uint16_t BTIM_CountMode;            /* 单次和连续模式控制 */    

} BTIM_TimeBaseInitTypeDef;


typedef struct
{
    uint32_t BTIM_ETR_PCLKDivider;     /* 配置ETR滤波时钟与PCLK的分频比 */
    uint32_t BTIM_ETR_Fliter;          /* 配置ETR滤波器的采样点和采样时钟 */
}BTIM_ETRConfigTypeDef;


#define IS_BTIM_ALL_PERIPH(PERIPH)                  (((PERIPH) == CW_BTIM1) || \
                                                    ((PERIPH) == CW_BTIM2) || \
                                                    ((PERIPH) == CW_BTIM3))


#define BTIM_COUNT_MODE_SINGLE                       ((uint16_t)0x0008)
#define BTIM_COUNT_MODE_REPETITIVE                   ((uint16_t)0x0000)
#define IS_BTIM_COUNT_MODE(MODE)                    (((MODE) == BTIM_COUNT_MODE_SINGLE) || \
                                                    ((MODE) == BTIM_COUNT_MODE_REPETITIVE))

#define IS_BTIM_PRS_DIV(DIV)                        (((DIV) <= 0xFFFF) && ((DIV) >= 1))


/*  BTIM_Mode  */
#define BTIM_MODE_TIMER                             ((uint16_t)0x0000)
#define BTIM_MODE_COUNTER                           ((uint16_t)0x0003)
#define BTIM_MODE_TRIGGER                           ((uint16_t)0x0001)
#define BTIM_MODE_GATE                              ((uint16_t)0x0002)
#define IS_BTIM_MODE(MODE)                          (((MODE) == BTIM_MODE_TIMER) ||  \
                                                    ((MODE) == BTIM_MODE_COUNTER) || \
                                                    ((MODE) == BTIM_MODE_TRIGGER) || \
                                                    ((MODE) == BTIM_MODE_GATE))
/* BTIM TOG */
#define BTIM_TOGGLE_ENABLE                          (0x8000)
#define BTIM_TOGGLE_DISABLE                         (0x0000)

/* BTIM UPDATE REMAP */
#define BTIM_UPDATE_REMAP_ENABLE                    (0x0800)
#define BTIM_UPDATE_REMAP_DISABLE                   (0x0000)

/* BTIM ETR 滤波时钟分频系数 */
#define BTIM_ETR_FLITER_PCLK_DIV1                        (0x0000)
#define BTIM_ETR_FLITER_PCLK_DIV2                        (0x0100)
#define BTIM_ETR_FLITER_PCLK_DIV4                        (0x0200)
#define IS_BTIM_ETR_FILTER_DIV(DIV)               (((DIV) == BTIM_ETR_FLITER_PCLK_DIV1) || \
                                                    ((DIV) == BTIM_ETR_FLITER_PCLK_DIV2) || \
                                                    ((DIV) == BTIM_ETR_FLITER_PCLK_DIV4))

/*  BTIM_External_Trigger_Filter  */
#define BTIM_ETR_FILTER_NONE                        (0U)
#define BTIM_ETR_FILTER_DIV1_N2                     (1U<<12)
#define BTIM_ETR_FILTER_DIV1_N4                     (2U<<12)
#define BTIM_ETR_FILTER_DIV1_N6                     (3U<<12)
#define BTIM_ETR_FILTER_DIV4_N4                     (4U<<12)
#define BTIM_ETR_FILTER_DIV4_N6                     (5U<<12)
#define BTIM_ETR_FILTER_DIV16_N4                    (6U<<12)
#define BTIM_ETR_FILTER_DIV16_N6                    (7U<<12)
#define IS_BTIM_ETR_FILTER(EXTFILTER)               (((EXTFILTER) == BTIM_ETR_FILTER_NONE) || \
                                                    ((EXTFILTER) == BTIM_ETR_FILTER_DIV1_N2) || \
                                                    ((EXTFILTER) == BTIM_ETR_FILTER_DIV1_N4) || \
                                                    ((EXTFILTER) == BTIM_ETR_FILTER_DIV1_N6) || \
                                                    ((EXTFILTER) == BTIM_ETR_FILTER_DIV4_N4) || \
                                                    ((EXTFILTER) == BTIM_ETR_FILTER_DIV4_N6) || \
                                                    ((EXTFILTER) == BTIM_ETR_FILTER_DIV16_N4) || \
                                                    ((EXTFILTER) == BTIM_ETR_FILTER_DIV16_N6))

/* BTIM ARR 缓存 */
#define BTIM_ARR_PRELOAD_ENABLE                        (0x0080)
#define BTIM_ARR_PRELOAD_DISABLE                       (0x0000)
#define IS_BTIM_AUTORELOAD_PRELOAD(PRELOAD)         (((PRELOAD) == BTIM_ARR_PRELOAD_ENABLE) || ((PRELOAD) == BTIM_ARR_PRELOAD_DISABLE))

/* BTIM 更新源 */
#define BTIM_UPDATE_REQUEST_SOURCE_OVERFLOW        (0x0004)
#define BTIM_UPDATE_REQUEST_SOURCE_FLEXIBLE        (0x0000)
#define IS_BTIM_UPDATE_REQUEST(SOURCE)              (((SOURCE) == BTIM_UPDATE_REQUEST_SOURCE_OVERFLOW) || ((SOURCE) == BTIM_UPDATE_REQUEST_SOURCE_FLEXIBLE))

/*  BTIM_interrupt_sources  */
#define BTIM_IT_UPDATE                              ((uint16_t)0x0001)
#define BTIM_IT_TI                                  ((uint16_t)0x0040)
#define IS_BTIM_IT(IT)                              (((IT) == BTIM_IT_UPDATE) || ((IT) == BTIM_IT_TI))

#define IS_BTIM_GET_IT(IT)                          (((IT) == BTIM_IT_UPDATE) || ((IT) == BTIM_IT_TI))

/* BTIM event source */
#define BTIM_EVENTSOURCE_TRIG                        (0x00000040)
#define BTIM_EVENTSOURCE_UPDATE                      (0x00000001)
#define IS_BTIM_EVENTSOURCE(SOURCE)                  (((SOURCE) == BTIM_EVENTSOURCE_TRIG) || ((SOURCE) == BTIM_EVENTSOURCE_UPDATE))

/*  BTIM Trigger source  */
#define BTIM_TS_AWT_OV                              (0U<<7)
#define BTIM_TS_LVD_OUT                             (1U<<7)
#define BTIM_TS_VCx_OUT                             (2U<<7)
#define BTIM_TS_SPI_NCS                             (3U<<7)
#define BTIM_TS_I2C_SCL                             (4U<<7)
#define BTIM_TS_UARTx_RXD                           (5U<<7)
#define BTIM_TS_RTC_OUT                             (6U<<7)
#define BTIM_TS_ATIM1_TRGO                          (7U<<7)
#define BTIM_TS_BTIM1_TRGO                          (8U<<7)
#define BTIM_TS_BTIM2_TRGO                          (9U<<7)
#define BTIM_TS_BTIM3_TRGO                          (10U<<7)
#define BTIM_TS_GTIM1_TRGO                          (11U<<7)
#define BTIM_TS_GTIM2_TRGO                          (12U<<7)
#define BTIM_TS_BTIMx_ETR                           (15U<<7)
#define IS_BTIM_TRIGGER_SELECTION(SELECTION)        (((SELECTION) == BTIM_TS_AWT_OV) || \
                                                     ((SELECTION) == BTIM_TS_LVD_OUT) || \
                                                     ((SELECTION) == BTIM_TS_VCx_OUT) || \
                                                     ((SELECTION) == BTIM_TS_SPI_NCS) || \
                                                     ((SELECTION) == BTIM_TS_I2C_SCL) || \
                                                     ((SELECTION) == BTIM_TS_UARTx_RXD) || \
                                                     ((SELECTION) == BTIM_TS_RTC_OUT) || \
                                                     ((SELECTION) == BTIM_TS_ATIM1_TRGO) || \
                                                     ((SELECTION) == BTIM_TS_BTIM1_TRGO) || \
                                                     ((SELECTION) == BTIM_TS_BTIM2_TRGO) || \
                                                     ((SELECTION) == BTIM_TS_BTIM3_TRGO) || \
                                                     ((SELECTION) == BTIM_TS_GTIM1_TRGO) || \
                                                     ((SELECTION) == BTIM_TS_GTIM2_TRGO) || \
                                                     ((SELECTION) == BTIM_TS_BTIMx_ETR))

/* BTIM Trigger input polarity */
#define BTIM_TRIGGER_POLARITY_POSITIVE              (0x00000000)
#define BTIM_TRIGGER_POLARITY_NEGATIVE              (1U << 17)
#define IS_BTIM_TRIGGER_POLARITY(POLARITY)          (((POLARITY) == BTIM_TRIGGER_POLARITY_POSITIVE) || ((POLARITY) == BTIM_TRIGGER_POLARITY_NEGATIVE))

/*  BTIM Reset source  */
#define BTIM_RESET_AWT_OV                              (0U<<3)
#define BTIM_RESET_LVD_OUT                             (1U<<3)
#define BTIM_RESET_VCx_OUT                             (2U<<3)
#define BTIM_RESET_SPI_NCS                             (3U<<3)
#define BTIM_RESET_I2C_SCL                             (4U<<3)
#define BTIM_RESET_UARTx_RXD                           (5U<<3)
#define BTIM_RESET_RTC_OUT                             (6U<<3)
#define BTIM_RESET_ATIM1_TRGO                          (7U<<3)
#define BTIM_RESET_BTIM1_TRGO                          (8U<<3)
#define BTIM_RESET_BTIM2_TRGO                          (9U<<3)
#define BTIM_RESET_BTIM3_TRGO                          (10U<<3)
#define BTIM_RESET_GTIM1_TRGO                          (11U<<3)
#define BTIM_RESET_GTIM2_TRGO                          (12U<<3)
#define BTIM_RESET_BTIMx_ETR                           (15U<<3)
#define IS_BTIM_RESET_SELECTION(SELECTION)          (((SELECTION) == BTIM_RESET_AWT_OV) || \
                                                     ((SELECTION) == BTIM_RESET_LVD_OUT) || \
                                                     ((SELECTION) == BTIM_RESET_VCx_OUT) || \
                                                     ((SELECTION) == BTIM_RESET_SPI_NCS) || \
                                                     ((SELECTION) == BTIM_RESET_I2C_SCL) || \
                                                     ((SELECTION) == BTIM_RESET_UARTx_RXD) || \
                                                     ((SELECTION) == BTIM_RESET_RTC_OUT) || \
                                                     ((SELECTION) == BTIM_RESET_ATIM1_TRGO) || \
                                                     ((SELECTION) == BTIM_RESET_BTIM1_TRGO) || \
                                                     ((SELECTION) == BTIM_RESET_BTIM2_TRGO) || \
                                                     ((SELECTION) == BTIM_RESET_BTIM3_TRGO) || \
                                                     ((SELECTION) == BTIM_RESET_GTIM1_TRGO) || \
                                                     ((SELECTION) == BTIM_RESET_GTIM2_TRGO) || \
                                                     ((SELECTION) == BTIM_RESET_BTIMx_ETR))

/* BTIM Trigger input polarity */
#define BTIM_RESET_POLARITY_POSITIVE              (0x00000000)
#define BTIM_RESET_POLARITY_NEGATIVE              (1U << 16)
#define IS_BTIM_RESET_POLARITY(POLARITY)          (((POLARITY) == BTIM_RESET_POLARITY_POSITIVE) || ((POLARITY) == BTIM_RESET_POLARITY_NEGATIVE))

/*  BTIM_DMA_sources  */
#define BTIM_DMA_TRIGGER                            (1U<<14)
#define BTIM_DMA_UPDATE                             (1U<<8)
#define IS_BTIM_DMA_SOURCE(SOURCE)                  (((SOURCE) == BTIM_DMA_TRIGGER) ||\
                                                    ((SOURCE) == BTIM_DMA_UPDATE))
/* BTIM Master output trigger */
#define BTIM_MASTER_OUTPUT_TRIGGER_RESET           (0U)
#define BTIM_MASTER_OUTPUT_TRIGGER_EN              (1U << 4)
#define BTIM_MASTER_OUTPUT_TRIGGER_UPDATE          (2U << 4)
#define BTIM_MASTER_OUTPUT_TRIGGER_OVERFLOW        (3U << 4)
#define IS_BTIM_MASTER_OUTPUT_TRIGGER(SOURCE)       (((SOURCE) == BTIM_MASTER_OUTPUT_TRIGGER_RESET) ||\
                                                     ((SOURCE) == BTIM_MASTER_OUTPUT_TRIGGER_EN) ||\
                                                     ((SOURCE) == BTIM_MASTER_OUTPUT_TRIGGER_UPDATE) ||\
                                                     ((SOURCE) == BTIM_MASTER_OUTPUT_TRIGGER_OVERFLOW))

/*   BTIM_Exported_Functions  */
/*******************************************************************************
// 说明：去初始化
// 参数：BTIMx x为1~3
// 返回值：无
*******************************************************************************/
void BTIM_DeInit(BTIM_TypeDef* BTIMx);

/*******************************************************************************
// 说明：BTIM基本定时器初始化
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_TimeBaseInitStruct 指向BTIM_TimeBaseInitTypeDef类型结构体的指针
// 返回值：无
*******************************************************************************/
void BTIM_TimeBaseInit(BTIM_TypeDef* BTIMx, BTIM_TimeBaseInitTypeDef* BTIM_TimeBaseInitStruct);

/*******************************************************************************
// 说明：使能BTIMx定时器
// 参数：BTIM_TimeBaseInitStruct
// 返回值：无
*******************************************************************************/
void BTIM_Cmd(BTIM_TypeDef* BTIMx, FunctionalState NewState);

/*******************************************************************************
// 说明：配置BTIMx的中断
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_IT 中断事件类型
// 参数：NewState 中断事件类型的状态，ENABLE 或 DISABLE
// 返回值：无
*******************************************************************************/
void BTIM_ITConfig(BTIM_TypeDef* BTIMx, uint16_t BTIM_IT, FunctionalState NewState);

/*******************************************************************************
// 说明： 检查BTIM的中断状态寄存器的各状态位是否置位
// 参数： BTIMx CW_BTIM1~3
// 参数： BTIM_FLAG 指定的状态位 ，参数范围： BTIM_IT_UPDATE
//                                           BTIM_IT_TI
//
// 返回值： 无
*******************************************************************************/
FlagStatus BTIM_GetITStatus(BTIM_TypeDef* BTIMx, uint16_t BTIM_FLAG);

/*******************************************************************************
// 说明： 清除BTIM的状态寄存器的各状态位
// 参数： BTIMx CW_BTIM1~3
// 参数： BTIM_FLAG 指定的状态位 ，参数范围： BTIM_IT_UPDATE
//                                           BTIM_IT_TI
//
// 返回值： 无
*******************************************************************************/
void BTIM_ClearITPendingBit(BTIM_TypeDef* BTIMx, uint16_t BTIM_FLAG);

/*******************************************************************************
// 说明： 软件产生事件
// 参数： BTIMx CW_BTIM1~3
// 参数： EventSource 事件源 BTIM_EVENTSOURCE_TRIG
//                           BTIM_EVENTSOURCE_UPDATE
//
// 返回值： 无
*******************************************************************************/
void BTIM_GenerateEvent(BTIM_TypeDef* BTIMx, uint16_t EventSource);

/*******************************************************************************
// 说明：配置BTIMx的工作模式
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_Mode 模式类型
//       BTIM_MODE_TIMER   定时器模式
//       BTIM_MODE_COUNTER 计数器模式
//       BTIM_MODE_TRIGGER 触发启动模式
//       BTIM_MODE_GATE    门控模式
// 返回值：无
*******************************************************************************/
void BTIM_ModeConfig(BTIM_TypeDef* BTIMx, uint16_t BTIM_Mode);

/*******************************************************************************
// 说明：配置BTIMx的计数模式
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_CountMode  运行类型
//       BTIM_COUNT_MODE_SINGLE   单次运行
//       BTIM_COUNT_MODE_REPETITIVE 连续运行
// 返回值：无
*******************************************************************************/
void BTIM_SelectOnePulseMode(BTIM_TypeDef* BTIMx, uint16_t BTIM_CountMode);

/*******************************************************************************
// 说明：配置BTIMx的翻转输出功能
// 参数：BTIMx CW_BTIM1~3
// 参数：NewState ENABLE 或 DISABLE
// 返回值：无
*******************************************************************************/
void BTIM_OutputToggleCmd(BTIM_TypeDef* BTIMx, FunctionalState NewState);

/*******************************************************************************
// 说明：设置BTIM的计数初值
// 参数：BTIMx CW_BTIM1~3
// 参数：Counter 范围0x0000~0xFFFF
// 返回值：无
*******************************************************************************/
void BTIM_SetCounter(BTIM_TypeDef* BTIMx, uint16_t Counter);

/*******************************************************************************
// 说明：获取BTIM的当前计数值
// 参数：BTIMx CW_BTIM1~3
// 返回值：CNT寄存器的值
*******************************************************************************/
uint16_t BTIM_GetCounter(BTIM_TypeDef* BTIMx);

/*******************************************************************************
// 说明：设置BTIM的自动重载值
// 参数：BTIMx CW_BTIM1~3
// 参数：Autoreload 范围0x0000~0xFFFF
// 返回值：无
*******************************************************************************/
void BTIM_SetAutoreload(BTIM_TypeDef* BTIMx, uint16_t Autoreload);

/*******************************************************************************
// 说明：获取BTIM的当前自动重载值
// 参数：BTIMx CW_BTIM1~3
// 返回值：ARR寄存器的值
*******************************************************************************/
uint16_t BTIM_GetAutoreload(BTIM_TypeDef* BTIMx);

/*******************************************************************************
// 说明：配置BTIMx的预分配系数
// 参数：BTIMx CW_BTIM1~3
// 参数：Prescaler 预分配系数
// 返回值：无
*******************************************************************************/
void BTIM_SetPrescaler(BTIM_TypeDef* BTIMx, uint16_t Prescaler);

/*******************************************************************************
// 说明：获取BTIM的当前预分配系数
// 参数：BTIMx CW_BTIM1~3
// 返回值：预分频器当前正在使用的分频系数,实际的分配值为预分配系数PSC+1
*******************************************************************************/
uint16_t BTIM_GetPrescaler(BTIM_TypeDef* BTIMx);

/*******************************************************************************
// 说明：UPDATE位重映射配置
// 参数：BTIMx CW_BTIM1~3
// 参数：State ENABLE 或 DISABLE
// 返回值： 无
*******************************************************************************/
void BTIM_ConfigUpdateRemap(BTIM_TypeDef* BTIMx, FunctionalState State);

/*******************************************************************************
// 说明：配置BTIMx的外部输入ETR
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_ETRConfigStruct ETR滤波器参数
// 返回值：无
*******************************************************************************/
void BTIM_ETRConfig(BTIM_TypeDef* BTIMx, BTIM_ETRConfigTypeDef *BTIM_ETRConfigStruct);

/*******************************************************************************
// 说明：配置BTIMx的ARR预装载功能
// 参数：BTIMx CW_BTIM1~3
// 参数：NewState Enable or Disable
// 返回值：无
*******************************************************************************/
void BTIM_AutoReloadPreloadConfig(BTIM_TypeDef* BTIMx, FunctionalState NewState);

/*******************************************************************************
// 说明：配置BTIMx的更新请求
// 参数：BTIMx CW_BTIM1~3
// 参数：Source BTIM_UPDATE_REQUEST_SOURCE_OVERFLOW  BTIM_UPDATE_REQUEST_SOURCE_FLEXIBLE
// 返回值：无
*******************************************************************************/
void BTIM_UpdateRequestSourceConfig(BTIM_TypeDef* BTIMx, uint16_t Source);

/*******************************************************************************
// 说明：使能BTIMx的事件更新请求
// 参数：BTIMx CW_BTIM1~3
// 返回值：无
*******************************************************************************/
void BTIM_EnableUpdateEvent(BTIM_TypeDef* BTIMx);

/*******************************************************************************
// 说明：禁止BTIMx的事件更新请求
// 参数：BTIMx CW_BTIM1~3
// 返回值：无
*******************************************************************************/
void BTIM_DisableUpdateEvent(BTIM_TypeDef* BTIMx);

/*******************************************************************************
// 说明：配置BTIMx的触发输入信号来源
// 参数：BTIMx CW_BTIM1~3
// 参数：Source 触发源
// 参数：Polarity 极性    BTIM_TRIGGER_POLARITY_POSITIVE， BTIM_TRIGGER_POLARITY_NEGATIVE
// 返回值：无
*******************************************************************************/
void BTIM_TriggerInputConfig(BTIM_TypeDef* BTIMx, uint16_t Source, uint32_t Polarity);

/*******************************************************************************
// 说明：配置BTIMx的复位输入信号来源
// 参数：BTIMx CW_BTIM1~3
// 参数：Source 复位源
// 参数：Polarity 极性    BTIM_RESET_POLARITY_POSITIVE， BTIM_RESET_POLARITY_NEGATIVE
// 返回值：无
*******************************************************************************/
void BTIM_ResetInputConfig(BTIM_TypeDef* BTIMx, uint16_t Source, uint32_t Polarity);


/*******************************************************************************
// 说明：配置BTIMx在主模式下的输出
// 参数：BTIMx CW_BTIM1~3
// 参数：Source TRGO信号生成的来源
// 返回值：无
*******************************************************************************/
void BTIM_MasterOutputTriggerConfig(BTIM_TypeDef* BTIMx, uint16_t source);

/*******************************************************************************
// 说明：配置BTIMx在从模式下同步使能
// 参数：BTIMx CW_BTIM1~3
// 返回值：无
*******************************************************************************/
void BTIM_SlaveSynchronEnable(BTIM_TypeDef* BTIMx);

/*******************************************************************************
// 说明：配置BTIMx在从模式下同步使能
// 参数：BTIMx CW_BTIM1~3
// 返回值：无
*******************************************************************************/
void BTIM_SlaveSynchronDisable(BTIM_TypeDef* BTIMx);


#ifdef __cplusplus
}
#endif

#endif 

