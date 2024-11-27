/**
 * @file cw32l010_vc.h
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

#ifndef __CW32L010_VC_H
#define __CW32L010_VC_H

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "system_cw32l010.h"
/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup VcGroup Voltage Comparator (VC)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
#define  VC_INT_PRIORITY              ((uint32_t)3)    /*VC interrupt priority (lowest by default)  */

/** @defgroup VC_interrupts_definition
  * @{
  */
#define VC_IT_HIGH                    ((uint16_t)0x0080)
#define VC_IT_RISE                    ((uint16_t)0x0040)
#define VC_IT_FALL                    ((uint16_t)0x0020)


#define IS_VC_IT(IT)                  ((((IT) & (uint16_t)0xFF00) == 0x00) && ((IT) != 0x00))
#define IS_VC_GET_IT(IT)              (((IT) == VC_IT_HIGH) || \
                                      ((IT) == VC_IT_RISE) || \
                                      ((IT) == VC_IT_FALL))


/** @defgroup VC_DivEn
  * @{
  */
#define VC_Div_Disable                ((uint32_t)0x00000000)
#define VC_Div_Enable                 ((uint32_t)0x00000010)

#define IS_VC_DIV_EN(DIV_EN)          (((DIV_EN) == VC_Div_Disable) || \
                                      ((DIV_EN) == VC_Div_Enable))

/** @defgroup VC_DivVref
  * @{
  */
#define VC_DivVref_VDDA               ((uint32_t)0x00000000)
#define VC_DivVref_VCAP               ((uint32_t)0x00000020)

#define IS_VC_DIV_VREF(DIV_VREF)      (((DIV_VREF) == VC_DivVref_VDDA) || \
                                      ((DIV_VREF) == VC_DivVref_VCAP))

/** @defgroup VC_InputP
  * @{
  * VC1              VC2
  * 输入通道0  PB05  输入通道0 PB06
  * 输入通道1  PA00  输入通道1 PA05
  * 输入通道2  PA03  输入通道2 PB02
  * 输入通道3  PB03  输入通道3 PB04

  */
#define VC_InputP_Ch0                 ((uint32_t)0x00000000)
#define VC_InputP_Ch1                 ((uint32_t)0x00000040)
#define VC_InputP_Ch2                 ((uint32_t)0x00000080)
#define VC_InputP_Ch3                 ((uint32_t)0x000000C0)


#define IS_VC_INPUT_P(INPUT_P)        (((INPUT_P) == VC_InputP_Ch0) || \
                                      ((INPUT_P) == VC_InputP_Ch1) || \
                                      ((INPUT_P) == VC_InputP_Ch2) || \
                                      ((INPUT_P) == VC_InputP_Ch3))

/** @defgroup VC_InputN
  * @{
  * VC1              VC2
  * 输入通道0  PB05  输入通道0 PB06
  * 输入通道1  PA00  输入通道1 PA05
  * VDDA分压         VDDA分压
  * BGR 1.2V         BGR 1.2V
  */
#define VC_InputN_Ch0                 ((uint32_t)0x00000000)
#define VC_InputN_Ch1                 ((uint32_t)0x00000100)
#define VC_InputN_Bgr1P2              ((uint32_t)0x00000200)
#define VC_InputN_DivOut              ((uint32_t)0x00000300)

#define IS_VC_INPUT_N(INPUT_N)        (((INPUT_N) == VC_InputN_Ch0) || \
                                      ((INPUT_N) == VC_InputN_Ch1) || \
                                      ((INPUT_N) == VC_InputN_Bgr1P2) || \
                                      ((INPUT_N) == VC_InputN_DivOut))

/** @defgroup VC_Hys
  * @{
  */
#define VC_Hys_Off                    ((uint32_t)0x00000000)
#define VC_Hys_25mV                   ((uint32_t)0x00000004)


#define IS_VC_HYS(HYS)                (((HYS) == VC_Hys_Off) || \
                                      ((HYS) == VC_Hys_25mV))

/** @defgroup VC_Resp
  * @{
  */
#define VC_Resp_Low                   ((uint32_t)0x00000000)
#define VC_Resp_High                  ((uint32_t)0x00000002)

#define IS_VC_RESP(RESP)              (((RESP) == VC_Resp_Low) || \
                                      ((RESP) == VC_Resp_High))

/** @defgroup VC_FilterClk
  * @{
  */
#define VC_FltClk_LSI                 ((uint32_t)0x00000000)
#define VC_FltClk_PCLK                ((uint32_t)0x00000010)

#define IS_VC_FLT_CLK(FLT_CLK)        (((FLT_CLK) == VC_FltClk_LSI) || \
                                      ((FLT_CLK) == VC_FltClk_PCLK))

/** @defgroup VC_FilterTime
  * @{
  */
#define VC_FilterTime_1N2     ((uint32_t)0x00000001)
#define VC_FilterTime_1N4     ((uint32_t)0x00000002)
#define VC_FilterTime_1N8     ((uint32_t)0x00000003)
#define VC_FilterTime_2N6     ((uint32_t)0x00000004)
#define VC_FilterTime_2N8     ((uint32_t)0x00000005)
#define VC_FilterTime_4N6     ((uint32_t)0x00000006)
#define VC_FilterTime_4N8     ((uint32_t)0x00000007)
#define VC_FilterTime_8N6     ((uint32_t)0x00000008)
#define VC_FilterTime_8N8     ((uint32_t)0x00000009)
#define VC_FilterTime_16N5    ((uint32_t)0x0000000A)
#define VC_FilterTime_16N6    ((uint32_t)0x0000000B)
#define VC_FilterTime_16N8    ((uint32_t)0x0000000C)
#define VC_FilterTime_32N5    ((uint32_t)0x0000000D)
#define VC_FilterTime_32N6    ((uint32_t)0x0000000E)
#define VC_FilterTime_32N8    ((uint32_t)0x0000000F)


#define IS_VC_FLT_TIME(FILTER_TIME)      (((FILTER_TIME) ==  VC_FilterTime_1N2)   || \
          ((FILTER_TIME) == VC_FilterTime_1N4) || \
          ((FILTER_TIME) == VC_FilterTime_1N8) || \
          ((FILTER_TIME) == VC_FilterTime_2N6) || \
          ((FILTER_TIME) == VC_FilterTime_2N8) || \
          ((FILTER_TIME) == VC_FilterTime_4N6) || \
          ((FILTER_TIME) == VC_FilterTime_4N8) || \
					((FILTER_TIME) == VC_FilterTime_8N6) || \
					((FILTER_TIME) == VC_FilterTime_8N8) || \
					((FILTER_TIME) == VC_FilterTime_16N5)|| \
					((FILTER_TIME) == VC_FilterTime_16N6)|| \
					((FILTER_TIME) == VC_FilterTime_16N8)|| \
					((FILTER_TIME) == VC_FilterTime_32N5)|| \
					((FILTER_TIME) == VC_FilterTime_32N6)|| \
          ((FILTER_TIME) == VC_FilterTime_32N8))

/** @defgroup VC_WindowEn
  * @{
  */
#define VC_Window_Disable             ((uint32_t)0x00000000)
#define VC_Window_Enable              ((uint32_t)0x00000020)

#define IS_VC_WINDOW(WINDOW)          (((WINDOW) == VC_Window_Disable) || \
                                      ((WINDOW) == VC_Window_Enable))

/** @defgroup VC_Polarity
  * @{
  */
#define VC_Polarity_Low               ((uint32_t)0x00000010)
#define VC_Polarity_High              ((uint32_t)0x00000000)

#define IS_VC_POLARITY(POLARITY)      (((POLARITY) == VC_Polarity_Low) || \
                                      ((POLARITY) == VC_Polarity_High))

/** @defgroup VC_BlankFlt
  * @{
  */
#define VC_BlankTime_4Clk              ((uint32_t)0x00000000)
#define VC_BlankTime_8Clk              ((uint32_t)0x00004000)
#define VC_BlankTime_16Clk             ((uint32_t)0x00008000)
#define VC_BlankTime_32Clk             ((uint32_t)0x0000C000)
#define VC_BlankTime_64Clk             ((uint32_t)0x00010000)
#define VC_BlankTime_128Clk            ((uint32_t)0x00014000)
#define VC_BlankTime_256Clk            ((uint32_t)0x00018000)
#define VC_BlankTime_512Clk            ((uint32_t)0x0001C000)

#define IS_VC_BLANK_TIME(BLANK_TIME)  (((BLANK_TIME) == VC_BlankTime_4Clk)   || \
                                      ((BLANK_TIME) == VC_BlankTime_8Clk)    || \
                                      ((BLANK_TIME) == VC_BlankTime_16Clk)   || \
                                      ((BLANK_TIME) == VC_BlankTime_32Clk)   || \
                                      ((BLANK_TIME) == VC_BlankTime_64Clk)   || \
                                      ((BLANK_TIME) == VC_BlankTime_128Clk)  || \
                                      ((BLANK_TIME) == VC_BlankTime_256Clk)  || \
                                      ((BLANK_TIME) == VC_BlankTime_512Clk))
																																						
/** @defgroup VC_BlankLevel
  * @{
  */
#define VC_BlankLevel_low             ((uint32_t)0x00000000)
#define VC_BlankLevel_high           ((uint32_t)0x00020000)

#define IS_VC_BLANK_LEVEL(BLANK_LEVEL)  (((BLANK_LEVEL) == VC_BlankLevel_low) || \
                                      ((BLANK_LEVEL) == VC_BlankLevel_high))
																																				
/** @defgroup VC_BlankCh6
  * @{
  */
#define VC_BlankCh6_Disable          ((uint32_t)0x00000000)
#define VC_BlankCh6_Enable           ((uint32_t)0x00002000)

#define IS_VC_BLANK_CH6(BLANK_CH6)  (((BLANK_CH6) == VC_BlankCh6_Disable) || \
                                      ((BLANK_CH6) == VC_BlankCh6_Enable))
																																						
/** @defgroup VC_BlankCh5
  * @{
  */
#define VC_BlankCh5_Disable          ((uint32_t)0x00000000)
#define VC_BlankCh5_Enable           ((uint32_t)0x00001000)

#define IS_VC_BLANK_CH5(BLANK_CH5)  (((BLANK_CH5) == VC_BlankCh5_Disable) || \
                                      ((BLANK_CH5) == VC_BlankCh5_Enable))

/** @defgroup VC_BlankCh4
  * @{
  */
#define VC_BlankCh4_Disable          ((uint32_t)0x00000000)
#define VC_BlankCh4_Enable           ((uint32_t)0x00000800)

#define IS_VC_BLANK_CH4(BLANK_CH4)  (((BLANK_CH4) == VC_BlankCh4_Disable) || \
                                      ((BLANK_CH4) == VC_BlankCh4_Enable))

/** @defgroup VC_BlankCh3
  * @{
  */
#define VC_BlankCh3_Disable          ((uint32_t)0x00000000)
#define VC_BlankCh3_Enable           ((uint32_t)0x00000400)

#define IS_VC_BLANK_CH3(BLANK_CH3)  (((BLANK_CH3) == VC_BlankCh3_Disable) || \
                                      ((BLANK_CH3) == VC_BlankCh3_Enable))
/** @defgroup VC_BlankCh2
  * @{
  */
#define VC_BlankCh2_Disable          ((uint32_t)0x00000000)
#define VC_BlankCh2_Enable           ((uint32_t)0x00000200)

#define IS_VC_BLANK_CH2(BLANK_CH2)  (((BLANK_CH2) == VC_BlankCh2_Disable) || \
                                      ((BLANK_CH2) == VC_BlankCh2_Enable))
/** @defgroup VC_BlankCh1
  * @{
  */
#define VC_BlankCh1_Disable          ((uint32_t)0x00000000)
#define VC_BlankCh1_Enable           ((uint32_t)0x00000100)

#define IS_VC_BLANK_CH1(BLANK_CH1)  (((BLANK_CH1) == VC_BlankCh1_Disable) || \
                                      ((BLANK_CH1) == VC_BlankCh1_Enable))



/**
 ******************************************************************************
 ** @brief VC模块配置
 *****************************************************************************/
typedef struct
{
    uint32_t  VC_DivVref;       // 6-bit VDDA divider输入参考电压选择
    uint32_t  VC_DivEn;         // 使能6-bit VDDA divider
    uint8_t   VC_DivValue;      // 6-bit VDDA divider设置值
} VC_DivTypeDef;

/**
 ******************************************************************************
 ** @brief VC通道配置
 *****************************************************************************/
typedef struct
{
    uint32_t VC_InputP;         // P端输入
    uint32_t VC_InputN;         // N端输入
    uint32_t VC_Hys;            // VC迟滞
    uint32_t VC_Resp;           // VC响应速度
    uint32_t VC_FilterClk;      // 滤波时钟源
    uint32_t VC_FilterTime;     // 输出滤波时间
    uint32_t VC_Window;         // VC窗口比较功能使能
    uint32_t VC_Polarity;       // VC输出信号极性设置
} VC_InitTypeDef;

/**
 ******************************************************************************
 ** @brief  VC模拟Blank窗口配置
 *****************************************************************************/
typedef struct
{
    uint32_t  VC_BlankTime;   /*Blank窗口持续时间*/
	
	  uint32_t  VC_BlankLevel;  /*Blank窗口期间输出电平配置*/
	
    uint32_t  VC_BlankCh6;  /*ATIM的CH6触发VCx启动Blank窗口*/	
    
    uint32_t  VC_BlankCh5;  /*ATIM的CH5触发VCx启动Blank窗口*/
    
    uint32_t  VC_BlankCh4;  /*ATIM的CH4触发VCx启动Blank窗口*/

    uint32_t  VC_BlankCh3;  /*ATIM的CH3触发VCx启动Blank窗口*/

    uint32_t  VC_BlankCh2;  /*ATIM的CH2触发VCx启动Blank窗口*/

    uint32_t  VC_BlankCh1;  /*ATIM的CH1触发VCx启动Blank窗口*/
} VC_BlankTypeDef;



/******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//VC1/VC2模块VCx负端输入信号初始化
void VC1VC2_INNInit(VC_InitTypeDef* VC_InitStruct);

//VC通道1初始化
void VC1_ChannelInit(VC_InitTypeDef* VC_InitStruct);
//VC通道2初始化
void VC2_ChannelInit(VC_InitTypeDef* VC_InitStruct);
//VC通道1去初始化
void VC1_ChannelDeInit(void);
//VC通道2去初始化
void VC2_ChannelDeInit(void);
//VC模块去初始化
void VC_DeInit(void);

//VC1/VC2模块DIV参考电压初始化
void VC1VC2_DIVInit(VC_DivTypeDef* VC_DivStruct);
//VC1/VC2模块DIV参考电压去初始化
void VC1VC2_DIVDeInit(void);

//VC1通道使能
void VC1_EnableChannel(void);
//VC2通道使能
void VC2_EnableChannel(void);
//VC1通道禁用
void VC1_DisableChannel(void);
//VC2通道禁用
void VC2_DisableChannel(void);

//VC1输出滤波使能
void VC1_EnableFilter(void);
//VC2输出滤波使能
void VC2_EnableFilter(void);
//VC1输出滤波禁用
void VC1_DisableFilter(void);
//VC2输出滤波禁用
void VC2_DisableFilter(void);


//VC通道1/2 BlanK窗口默认值初始化
void VC1VC2_BlankInit(VC_BlankTypeDef* VC_BlankStruct);
//VC通道1 BlanK窗口配置
void VC1_BlankCfg(VC_BlankTypeDef* VC_BlankStruct);
//VC通道2 BlanK窗口配置
void VC2_BlankCfg(VC_BlankTypeDef* VC_BlankStruct);

//VC通道1窗口比较功能配置
void VC1_WindowEnable(boolean_t bWindow);
//VC通道2窗口比较功能配置
void VC2_WindowEnable(boolean_t bWindow);

//VC通道1输出信号极性设置
void VC1_PolarityCfg(boolean_t bPolarity);
//VC通道2输出信号极性设置
void VC2_PolarityCfg(boolean_t bPolarity);

//使能NVIC中VCx中断
void VC_EnableNvic(IRQn_Type enIrqn, uint8_t intPriority);
//禁止NVIC中VC中断
void VC_DisableNvic(IRQn_Type enIrqn);
//VC通道1中断禁用
void VC1_DisableIrq(void);
//VC通道2中断禁用
void VC2_DisableIrq(void);
//VC通道1中断使能
void VC1_EnableIrq(uint8_t intPriority);
//VC通道2中断使能
void VC2_EnableIrq(uint8_t intPriority);
//配置VC1中断触发方式
void VC1_ITConfig(uint16_t VC_IT, FunctionalState NewState);
//配置VC2中断触发方式
void VC2_ITConfig(uint16_t VC_IT, FunctionalState NewState);

//清除VC1中断标志
void VC1_ClearIrq(void);
//清除VC2中断标志
void VC2_ClearIrq(void);

//获取VC1状态
FlagStatus VC1_GetFlagStatus(uint16_t VC_FLAG);
//获取VC2状态
FlagStatus VC2_GetFlagStatus(uint16_t VC_FLAG);

//获取VC1的使能控制状态
FlagStatus VC1_GetEnableStatus(void);
//获取VC2的使能控制状态
FlagStatus VC2_GetEnableStatus(void);
//@} // VcGroup

#ifdef __cplusplus
}
#endif

#endif /* __CW32L010_VC_H */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

