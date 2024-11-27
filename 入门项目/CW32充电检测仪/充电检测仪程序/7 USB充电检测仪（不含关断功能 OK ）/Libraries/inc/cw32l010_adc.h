/**
* @file cw32l010_adc.h
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

#ifndef __CW32L010_ADC_H
#define __CW32L010_ADC_H


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "system_cw32l010.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup AdcGroup AD Converter (ADC)
  **
 ******************************************************************************/
 
 
/******************************************************************************
 * Extern type definitions ('typedef')                                        *
 ******************************************************************************/

/**
 ******************************************************************************
 ** @brief  ADC配置
 *****************************************************************************/
typedef struct
{
    uint32_t                    ADC_SampTime;        /*单通道ADC采样保持时间*/ 
    uint32_t                    ADC_InputChannel;    /*通道选择 */       
}ADC_ChannelTypeDef;
typedef struct
{
    uint32_t                    ADC_ClkDiv;              /*ADC时钟分频选择*/ 
    
    uint32_t                    ADC_ConvertMode;         /*ADC转换模式选择*/ 

    uint32_t                    ADC_SQREns;    /*ADC转换通道配置*/
    
    ADC_ChannelTypeDef          ADC_IN0;         /*ADC 通道0配置*/
    
    ADC_ChannelTypeDef          ADC_IN1;         /*ADC 通道1配置*/
    
    ADC_ChannelTypeDef          ADC_IN2;         /*ADC 通道2配置*/
    
    ADC_ChannelTypeDef          ADC_IN3;         /*ADC 通道3配置*/
    
    ADC_ChannelTypeDef          ADC_IN4;         /*ADC 通道4配置*/
    
    ADC_ChannelTypeDef          ADC_IN5;         /*ADC 通道5配置*/
    
    ADC_ChannelTypeDef          ADC_IN6;         /*ADC 通道6配置*/
    
    ADC_ChannelTypeDef          ADC_IN7;         /*ADC 通道7配置*/
            
} ADC_InitTypeDef;

/**
 ******************************************************************************
 ** @brief  ADC模拟看门狗配置
 *****************************************************************************/
typedef struct
{
    ADC_InitTypeDef   ADC_InitStruct;    /*ADC通用初始化配置*/    
    
    uint32_t          ADC_WatchdogCHx;            /*ADC模拟看门狗通道*/   

    uint32_t          ADC_WatchdogVth;            /*ADC模拟看门狗上超出门限*/

    uint32_t          ADC_WatchdogVtl;            /*ADC模拟看门狗下超出门限*/
    
    uint32_t          ADC_WatchdogOverHighIrq;    /*ADC模拟看门狗上超出门限中断使能*/
    
    uint32_t          ADC_WatchdogUnderLowIrq;    /*ADC模拟看门狗下超出门限中断使能*/
} ADC_WatchdogTypeDef;


/**
 ******************************************************************************
 ** @brief  ADC中断配置
 *****************************************************************************/
typedef struct
{
    boolean_t  ADC_WdthIrq;   /*ADC模拟看门狗上阈值中断*/

    boolean_t  ADC_WdtlIrq;   /*ADC模拟看门狗下阈值中断*/

    boolean_t  ADC_EosIrq;    /*ADC序列转换完成中断*/

    boolean_t  ADC_EocIrq;    /*ADC单次转换完成中断*/
} ADC_IrqTypeDef;

//@{

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#ifndef ADC_WAIT_TIMEOUT
#define ADC_WAIT_TIMEOUT 5000U /* Define to zero means keep waiting until the flag is assert/deassert. */
#endif
 
#define  ADC_INT_PRIORITY                    ((uint32_t)3)    /*ADC interrupt priority (lowest by default)  */

#define COEFF_TS                             (0.095765f)

#define ADC_TS_T0_ADDRESS                    (0x001007CD)
#define ADC_TS_TRIM_ADDRESS                  (0x001007CE)

/**
  * @}
  */

/** @defgroup ADC_ConvertMode
  * @{
  */
#define ADC_ConvertMode_Once                     0
#define ADC_ConvertMode_Continuous               bv3

#define IS_ADC_CONV_MODE(MODE)              (((MODE) == ADC_ConvertMode_Single)         || \
                                             ((MODE) == ADC_ConvertMode_Continuous))                                            


/** @defgroup ADC_ClkDiv
  * @{
  */
#define ADC_Clk_Div1                         ((uint32_t)0)
#define ADC_Clk_Div2                         ((uint32_t)(1U<<4))
#define ADC_Clk_Div4                         ((uint32_t)(2U<<4))
#define ADC_Clk_Div8                         ((uint32_t)(3U<<4))

#define IS_ADC_CLK_DIV(CLK_DIV)              (((CLK_DIV) == ADC_Clk_Div1)   || \
                                             ((CLK_DIV) == ADC_Clk_Div2)    || \
                                             ((CLK_DIV) == ADC_Clk_Div4)    || \
                                             ((CLK_DIV) == ADC_Clk_Div8))                                          

/** @defgroup ADC_InputCHx
  * @{
  * 通道0输入PA00
  * 通道1输入PA01
  * 通道2输入PA02
  * 通道3输入PA03
  * 通道4输入PA04
  * 通道5输入PA05
  * 通道6输入PA06
  * 通道7输入PB00
  * 通道8输入PB01
  * 通道9输入PB02
  * 通道10输入PB03
  * 通道11输入PB04
  * 通道12输入PB05
  * 通道13输入PB06
  * BGR_TS
  * Vref1P2
  */
#define ADC_InputCH0                       ((uint32_t)0x00000000)
#define ADC_InputCH1                       ((uint32_t)0x00000001)
#define ADC_InputCH2                       ((uint32_t)0x00000002)
#define ADC_InputCH3                       ((uint32_t)0x00000003)
#define ADC_InputCH4                       ((uint32_t)0x00000004)
#define ADC_InputCH5                       ((uint32_t)0x00000005)
#define ADC_InputCH6                       ((uint32_t)0x00000006)
#define ADC_InputCH7                       ((uint32_t)0x00000007)
#define ADC_InputCH8                       ((uint32_t)0x00000008)
#define ADC_InputCH9                       ((uint32_t)0x00000009)
#define ADC_InputCH10                      ((uint32_t)0x0000000A)
#define ADC_InputCH11                      ((uint32_t)0x0000000B)
#define ADC_InputCH12                      ((uint32_t)0x0000000C)
#define ADC_InputCH13                      ((uint32_t)0x0000000D)
#define ADC_InputTs                        ((uint32_t)0x0000000E)
#define ADC_InputVref1P2                   ((uint32_t)0x0000000F)

#define IS_ADC_CH_SEL(CH_SEL)                (((CH_SEL) == ADC_InputCH0)    || \
                                             ((CH_SEL) == ADC_InputCH1)     || \
                                             ((CH_SEL) == ADC_InputCH2)     || \
                                             ((CH_SEL) == ADC_InputCH3)     || \
                                             ((CH_SEL) == ADC_InputCH4)     || \
                                             ((CH_SEL) == ADC_InputCH5)     || \
                                             ((CH_SEL) == ADC_InputCH6)     || \
                                             ((CH_SEL) == ADC_InputCH7)     || \
                                             ((CH_SEL) == ADC_InputCH8)     || \
                                             ((CH_SEL) == ADC_InputCH9)     || \
                                             ((CH_SEL) == ADC_InputCH10)    || \
                                             ((CH_SEL) == ADC_InputCH11)    || \
                                             ((CH_SEL) == ADC_InputCH12)    || \
                                             ((CH_SEL) == ADC_InputCH13)  || \
                                             ((CH_SEL) == ADC_InputTs)        || \
                                             ((CH_SEL) == ADC_InputVref1P2))
                                            
                                             

/** @defgroup ADC_SampleTime
  * @{
  */
#define ADC_SampTime6Clk                     ((uint32_t)0x00000000)
#define ADC_SampTime7Clk                     ((uint32_t)0x00000001)
#define ADC_SampTime9Clk                     ((uint32_t)0x00000002)
#define ADC_SampTime12Clk                    ((uint32_t)0x00000003)
#define ADC_SampTime18Clk                    ((uint32_t)0x00000004)
#define ADC_SampTime24Clk                    ((uint32_t)0x00000005)
#define ADC_SampTime30Clk                    ((uint32_t)0x00000006)
#define ADC_SampTime42Clk                    ((uint32_t)0x00000007)
#define ADC_SampTime54Clk                    ((uint32_t)0x00000008)
#define ADC_SampTime70Clk                    ((uint32_t)0x00000009)
#define ADC_SampTime102Clk                   ((uint32_t)0x0000000A)
#define ADC_SampTime134Clk                   ((uint32_t)0x0000000B)
#define ADC_SampTime166Clk                   ((uint32_t)0x0000000C)
#define ADC_SampTime198Clk                   ((uint32_t)0x0000000D)
#define ADC_SampTime262Clk                   ((uint32_t)0x0000000E)
#define ADC_SampTime390Clk                   ((uint32_t)0x0000000F)


#define IS_ADC_SAMPLE_TIME(SAMPLE_TIME)      ((SAMPLE_TIME) <= 0x0000000F)  

/** @defgroup ADC_WatchdogVth
  * @{
  */
#define IS_ADC_WATCHDOG_VTH(VTH)             ((VTH) < 0x1000)

/** @defgroup ADC_WatchdogVtl
  * @{
  */
#define IS_ADC_WATCHDOG_VTL(VTL)             ((VTL) < 0x1000)



/** @defgroup ADC_SqrEns1
  * @{
  */
#define ADC_SqrEns0to0                         0
#define ADC_SqrEns0to1                         (((uint32_t)1u) << 6)
#define ADC_SqrEns0to2                         (((uint32_t)2u) << 6)
#define ADC_SqrEns0to3                         (((uint32_t)3u) << 6)
#define ADC_SqrEns0to4                         (((uint32_t)4u) << 6)
#define ADC_SqrEns0to5                         (((uint32_t)5u) << 6)
#define ADC_SqrEns0to6                         (((uint32_t)6u) << 6)
#define ADC_SqrEns0to7                         (((uint32_t)7u) << 6)
    
#define IS_ADC_SQR_ENS1(SQR_ENS)              (((SQR_ENS) == ADC_SqrEns0to0)   || \
                                             ((SQR_ENS) == ADC_SqrEns0to1)   || \
                                             ((SQR_ENS) == ADC_SqrEns0to2)   || \
                                             ((SQR_ENS) == ADC_SqrEns0to3)   || \
                                             ((SQR_ENS) == ADC_SqrEns0to4)   || \
                                             ((SQR_ENS) == ADC_SqrEns0to5)   || \
                                             ((SQR_ENS) == ADC_SqrEns0to6)   || \
                                             ((SQR_ENS) == ADC_SqrEns0to7))

#define ADC_RESULT_0                          0x00
#define ADC_RESULT_1                          0x01
#define ADC_RESULT_2                          0x02
#define ADC_RESULT_3                          0x03
#define ADC_RESULT_4                          0x04
#define ADC_RESULT_5                          0x05
#define ADC_RESULT_6                          0x06
#define ADC_RESULT_7                          0x07

#define IS_ADC_RESULT_X(CHx)                  ((CHx) < 0x08)



/** @defgroup ADC_interrupts_definition
  * @{
  */

#define ADC_IT_AWDH                          ((uint16_t)0x0008)
#define ADC_IT_AWDL                          ((uint16_t)0x0004)
#define ADC_IT_EOS                           ((uint16_t)0x0002)
#define ADC_IT_EOC                           ((uint16_t)0x0001)

#define IS_ADC_IT(IT)                        ((((IT) & (uint16_t)0xFFF0) == 0x00) && ((IT) != 0x00))
#define IS_ADC_GET_IT(IT)                    (((IT) == ADC_IT_AWDH)  || \
                                             ((IT) == ADC_IT_AWDL)   || \
                                             ((IT) == ADC_IT_EOS)    || \
                                             ((IT) == ADC_IT_EOC))


/** @defgroup ADC external interrupts_definition
  * @{
  */

#define ADC_TRIG_UART2                       bv18
#define ADC_TRIG_UART1                       bv17
#define ADC_TRIG_SPI1                        bv16
#define ADC_TRIG_BTIM3TRGO                   bv15
#define ADC_TRIG_BTIM2TRGO                   bv14
#define ADC_TRIG_BTIM1TRGO                   bv13
#define ADC_TRIG_GTIM1CC4                    bv12
#define ADC_TRIG_GTIM1CC3                    bv11
#define ADC_TRIG_GTIM1CC2                    bv10
#define ADC_TRIG_GTIM1CC1                    bv9
#define ADC_TRIG_GTIM1TRGO                   bv8
#define ADC_TRIG_ATIMCC6                     bv7
#define ADC_TRIG_ATIMCC5                     bv6
#define ADC_TRIG_ATIMCC4                     bv5
#define ADC_TRIG_ATIMCC3                     bv4
#define ADC_TRIG_ATIMCC2                     bv3
#define ADC_TRIG_ATIMCC1                     bv2
#define ADC_TRIG_ATIMTRGO2                   bv1
#define ADC_TRIG_ATIMTRGO                    bv0

#define IS_ADC_TRIG(TRIG)                    ((((TRIG) & (uint32_t)0x00000000) == 0x00) && ((TRIG) != 0x00))

/** @defgroup ADC_Watchdog
  * @{
  */
#define ADC_WATCHDOG_IN0                     bv0
#define ADC_WATCHDOG_IN1                     bv1
#define ADC_WATCHDOG_IN2                     bv2
#define ADC_WATCHDOG_IN3                     bv3
#define ADC_WATCHDOG_IN4                     bv4
#define ADC_WATCHDOG_IN5                     bv5
#define ADC_WATCHDOG_IN6                     bv6
#define ADC_WATCHDOG_IN7                     bv7
#define ADC_WATCHDOG_IN8                     bv8
#define ADC_WATCHDOG_IN9                     bv9
#define ADC_WATCHDOG_IN10                    bv10
#define ADC_WATCHDOG_IN11                    bv11
#define ADC_WATCHDOG_IN12                    bv12
#define ADC_WATCHDOG_IN13                    bv13
#define ADC_WATCHDOG_IN14                    bv14
#define ADC_WATCHDOG_IN15                    bv15


/** @defgroup ADC_TsEn
  * @{
  */
#define ADC_TsDisable                        0u
#define ADC_TsEnable                         bv2

#define IS_ADC_TS_ENABLE(TS_ENABLE)          (((TS_ENABLE) == ADC_TsDisable) || \
                                             ((TS_ENABLE) == ADC_TsEnable))


/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC去初始化
void ADC_DeInit(void);
//ADC初始化
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct);
//ADC使能
ErrorStatus ADC_Enable(void);
//ADC禁用
void ADC_Disable(void);
  
//ADC模拟看门狗初始化
void ADC_WatchdogInit(ADC_WatchdogTypeDef* ADC_WatchdogStruct);


//ADC中断配置
void ADC_ITConfig(uint16_t ADC_IT, FunctionalState NewState);
//获取ADC所有中断状态
void ADC_GetITStatusAll(volatile uint8_t* pFlagAdcIrq);
//获取ADC指定的中断状态
ITStatus ADC_GetITStatus(uint16_t ADC_IT);
//清除ADC所有中断状态
void ADC_ClearITPendingAll(void);
//清除ADC指定的中断状态
void ADC_ClearITPendingBit(uint16_t ADC_IT);

//ADC转换软件启动命令
void ADC_SoftwareStartConvCmd(FunctionalState NewState);

//ADC外部中断触发源配置
void ADC_ExtTrigCfg(uint16_t ADC_TRIG, FunctionalState NewState);


//获取转换采样值
uint16_t ADC_GetConversionValue(uint32_t SqrCHx);
//获取SQR0通道采样值
void ADC_GetSqr0Result(uint16_t* pAdcResult);
//获取SQR1通道采样值
void ADC_GetSqr1Result(uint16_t* pAdcResult);
//获取SQR2通道采样值
void ADC_GetSqr2Result(uint16_t* pAdcResult);
//获取SQR3通道采样值
void ADC_GetSqr3Result(uint16_t* pAdcResult);
//获取SQR4通道采样值
void ADC_GetSqr4Result(uint16_t* pAdcResult);
//获取SQR5通道采样值
void ADC_GetSqr5Result(uint16_t* pAdcResult);
//获取SQR6通道采样值
void ADC_GetSqr6Result(uint16_t* pAdcResult);
//获取SQR7通道采样值
void ADC_GetSqr7Result(uint16_t* pAdcResult);
//获取SQR8通道采样值
void ADC_GetSqr8Result(uint16_t* pAdcResult);
//获取SQR9通道采样值
void ADC_GetSqr9Result(uint16_t* pAdcResult);
//获取SQR10通道采样值
void ADC_GetSqr10Result(uint16_t* pAdcResult);
//获取SQR11通道采样值
void ADC_GetSqr11Result(uint16_t* pAdcResult);



//设置内置温度传感器使能控制
void ADC_SetTs(uint32_t enTs);
// 获取内置温度传感器的值
float ADC_GetTs(float RefVoltage, uint32_t AdcValue);


//@}
#ifdef __cplusplus
}
#endif

#endif /* __CW32L010_ADC_H */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
