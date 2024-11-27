/**
 * @file cw32l010_btim.c
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

/* Includes ------------------------------------------------------------------*/
#include "cw32l010_btim.h"
#include "cw32l010_sysctrl.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/*******************************************************************************
// 说明：去初始化
// 参数：BTIMx x为1~3
// 返回值：无
*******************************************************************************/

void BTIM_DeInit(BTIM_TypeDef* BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));

    BTIMx->CR1 = 0UL;
    BTIMx->CR2 = 0UL;
    BTIMx->SMCR = 0UL;
    BTIMx->IER = 0UL;
    BTIMx->ICR = 0UL;    
    BTIMx->CNT = 0UL;
    BTIMx->PSC = 0UL;
    BTIMx->ARR = 0x0000FFFF;
}

/*******************************************************************************
// 说明：BTIM基本定时器初始化
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_TimeBaseInitStruct 指向BTIM_TimeBaseInitTypeDef类型结构体的指针
// 返回值：无
*******************************************************************************/
void BTIM_TimeBaseInit(BTIM_TypeDef* BTIMx, BTIM_TimeBaseInitTypeDef* BTIM_TimeBaseInitStruct)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_MODE(BTIM_TimeBaseInitStruct->BTIM_Mode));
    assert_param(IS_BTIM_PRS_DIV(BTIM_TimeBaseInitStruct->BTIM_Prescaler));
    assert_param(IS_BTIM_COUNT_MODE(BTIM_TimeBaseInitStruct->BTIM_CountMode));
   
    
    /* 使能BTIM的APB时钟 */
    CW_SYSCTRL->APBEN2 |= SYSCTRL_KEY | SYSCTRL_APBEN2_BTIM123_Msk;
    
    /* 配置BTIM的工作模式 */
    BTIMx->ARR = BTIM_TimeBaseInitStruct->BTIM_Period;
    BTIMx->PSC = BTIM_TimeBaseInitStruct->BTIM_Prescaler;
    REGBITS_MODIFY(BTIMx->CR1, BTIMx_CR1_ONESHOT_Msk, 
                   BTIM_TimeBaseInitStruct->BTIM_CountMode);
    REGBITS_MODIFY(BTIMx->SMCR, BTIMx_SMCR_SMS_Msk, BTIM_TimeBaseInitStruct->BTIM_Mode);  
}



/*******************************************************************************
// 说明：使能BTIMx定时器
// 参数：BTIM_TimeBaseInitStruct
// 返回值：无
*******************************************************************************/
void BTIM_Cmd(BTIM_TypeDef* BTIMx, FunctionalState NewState)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    NewState ? (BTIMx->CR1 |= BTIMx_CR1_EN_Msk) : (BTIMx->CR1 &= ~BTIMx_CR1_EN_Msk);
}


/*******************************************************************************
// 说明：配置BTIMx的中断
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_IT 中断事件类型
// 参数：NewState 中断事件类型的状态，ENABLE 或 DISABLE
// 返回值：无
*******************************************************************************/
void BTIM_ITConfig(BTIM_TypeDef* BTIMx, uint16_t BTIM_IT, FunctionalState NewState)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_BTIM_IT(BTIM_IT));

    NewState ? ( BTIMx->IER |= BTIM_IT) : (BTIMx->IER &= ~BTIM_IT);
}
/*******************************************************************************
// 说明： 检查BTIM的中断状态寄存器的各状态位是否置位
// 参数： BTIMx CW_BTIM1~3
// 参数： BTIM_FLAG 指定的状态位 ，参数范围： BTIM_IT_UPDATE
//                                           BTIM_IT_TI
//
// 返回值： 无
*******************************************************************************/
FlagStatus BTIM_GetITStatus(BTIM_TypeDef* BTIMx, uint16_t BTIM_FLAG)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_IT(BTIM_FLAG));

    return (REGBITS_GET(BTIMx->ISR, BTIM_FLAG) ? SET : RESET);
}

/*******************************************************************************
// 说明： 清除BTIM的状态寄存器的各状态位
// 参数： BTIMx CW_BTIM1~3
// 参数： BTIM_FLAG 指定的状态位 ，参数范围： BTIM_IT_UPDATE
//                                           BTIM_IT_TI
//
// 返回值： 无
*******************************************************************************/
void BTIM_ClearITPendingBit(BTIM_TypeDef* BTIMx, uint16_t BTIM_FLAG)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_IT(BTIM_FLAG));

    REGBITS_CLR(BTIMx->ICR, BTIM_FLAG);
}

/*******************************************************************************
// 说明： 软件产生事件
// 参数： BTIMx CW_BTIM1~3
// 参数： EventSource 事件源 BTIM_EVENTSOURCE_TRIG
//                           BTIM_EVENTSOURCE_UPDATE
//
// 返回值： 无
*******************************************************************************/
void BTIM_GenerateEvent(BTIM_TypeDef* BTIMx, uint16_t EventSource)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_EVENTSOURCE(EventSource));
    
    BTIMx->EGR |= EventSource;    
}

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
void BTIM_ModeConfig(BTIM_TypeDef* BTIMx, uint16_t BTIM_Mode)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_MODE(BTIM_Mode));

    REGBITS_MODIFY(BTIMx->SMCR , BTIMx_SMCR_SMS_Msk, BTIM_Mode);
}


/*******************************************************************************
// 说明：配置BTIMx的计数模式
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_CountMode  运行类型
//       BTIM_COUNT_MODE_SINGLE   单次运行
//       BTIM_COUNT_MODE_REPETITIVE 连续运行
// 返回值：无
*******************************************************************************/
void BTIM_SelectOnePulseMode(BTIM_TypeDef* BTIMx, uint16_t BTIM_CountMode)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_COUNT_MODE(BTIM_CountMode));

    REGBITS_MODIFY(BTIMx->CR1, BTIMx_CR1_ONESHOT_Msk, BTIM_CountMode);
}

/*******************************************************************************
// 说明：配置BTIMx的翻转输出功能
// 参数：BTIMx CW_BTIM1~3
// 参数：NewState ENABLE 或 DISABLE
// 返回值：无
*******************************************************************************/
void BTIM_OutputToggleCmd(BTIM_TypeDef* BTIMx, FunctionalState NewState)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    NewState ? (BTIMx->CR1 |= BTIMx_CR1_TOGEN_Msk) : (BTIMx->CR1 &= ~BTIMx_CR1_TOGEN_Msk);
}

/*******************************************************************************
// 说明：设置BTIM的计数初值
// 参数：BTIMx CW_BTIM1~3
// 参数：Counter 范围0x0000~0xFFFF
// 返回值：无
*******************************************************************************/
void BTIM_SetCounter(BTIM_TypeDef* BTIMx, uint16_t Counter)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));

    BTIMx->CNT = Counter;
}

/*******************************************************************************
// 说明：获取BTIM的当前计数值
// 参数：BTIMx CW_BTIM1~3
// 返回值：CNT寄存器的值
*******************************************************************************/
uint16_t BTIM_GetCounter(BTIM_TypeDef* BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));

    return BTIMx->CNT;
}

/*******************************************************************************
// 说明：设置BTIM的自动重载值
// 参数：BTIMx CW_BTIM1~3
// 参数：Autoreload 范围0x0000~0xFFFF
// 返回值：无
*******************************************************************************/
void BTIM_SetAutoreload(BTIM_TypeDef* BTIMx, uint16_t Autoreload)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));

    BTIMx->ARR = Autoreload;
}

/*******************************************************************************
// 说明：获取BTIM的当前自动重载值
// 参数：BTIMx CW_BTIM1~3
// 返回值：ARR寄存器的值
*******************************************************************************/
uint16_t BTIM_GetAutoreload(BTIM_TypeDef* BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));

    return BTIMx->ARR;
}

/*******************************************************************************
// 说明：配置BTIMx的预分配系数
// 参数：BTIMx CW_BTIM1~3
// 参数：Prescaler 预分配系数
// 返回值：无
*******************************************************************************/
void BTIM_SetPrescaler(BTIM_TypeDef* BTIMx, uint16_t Prescaler)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_PRS_DIV(Prescaler));

    BTIMx->PSC = Prescaler - 1;
}

/*******************************************************************************
// 说明：获取BTIM的当前预分配系数
// 参数：BTIMx CW_BTIM1~3
// 返回值：预分频器当前正在使用的分频系数,实际的分配值为预分配系数PSC+1
*******************************************************************************/
uint16_t BTIM_GetPrescaler(BTIM_TypeDef* BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));

    return BTIMx->PSC;
}

/*******************************************************************************
// 说明：UPDATE位重映射配置
// 参数：BTIMx CW_BTIM1~3
// 参数：State ENABLE 或 DISABLE
// 返回值： 无
*******************************************************************************/
void BTIM_ConfigUpdateRemap(BTIM_TypeDef* BTIMx, FunctionalState State)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_FUNCTIONAL_STATE(State));
    
    State ? (BTIMx->CR1 |= BTIM_UPDATE_REMAP_ENABLE) : (BTIMx->CR1 &= ~BTIM_UPDATE_REMAP_ENABLE);    
}

/*******************************************************************************
// 说明：配置BTIMx的外部输入ETR
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_ETRConfigStruct ETR滤波器参数
// 返回值：无
*******************************************************************************/
void BTIM_ETRConfig(BTIM_TypeDef* BTIMx, BTIM_ETRConfigTypeDef *BTIM_ETRConfigStruct)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));    
    assert_param(IS_BTIM_ETR_FILTER(BTIM_ETRConfigStruct->BTIM_ETR_Fliter));
    

   
    REGBITS_MODIFY(BTIMx->SMCR, BTIMx_SMCR_TRGIFLT_Msk, BTIM_ETRConfigStruct->BTIM_ETR_Fliter);
}


/*******************************************************************************
// 说明：配置BTIMx的ARR预装载功能
// 参数：BTIMx CW_BTIM1~3
// 参数：NewState Enable or Disable
// 返回值：无
*******************************************************************************/
void BTIM_AutoReloadPreloadConfig(BTIM_TypeDef* BTIMx, FunctionalState NewState)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    (NewState) ? (BTIMx->CR1 |= BTIM_ARR_PRELOAD_ENABLE) : (BTIMx->CR1 &= ~BTIM_ARR_PRELOAD_ENABLE);    
}

/*******************************************************************************
// 说明：配置BTIMx的更新请求
// 参数：BTIMx CW_BTIM1~3
// 参数：Source BTIM_UPDATE_REQUEST_SOURCE_OVERFLOW  BTIM_UPDATE_REQUEST_SOURCE_FLEXIBLE
// 返回值：无
*******************************************************************************/
void BTIM_UpdateRequestSourceConfig(BTIM_TypeDef* BTIMx, uint16_t Source)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx)); 
    assert_param(IS_BTIM_UPDATE_REQUEST(Source));
    REGBITS_MODIFY(BTIMx->CR1, BTIMx_CR1_URS_Msk, Source);
}

/*******************************************************************************
// 说明：使能BTIMx的事件更新请求
// 参数：BTIMx CW_BTIM1~3
// 返回值：无
*******************************************************************************/
void BTIM_EnableUpdateEvent(BTIM_TypeDef* BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx)); 
    
    REGBITS_CLR(BTIMx->CR1, BTIMx_CR1_UDIS_Msk);
}

/*******************************************************************************
// 说明：禁止BTIMx的事件更新请求
// 参数：BTIMx CW_BTIM1~3
// 返回值：无
*******************************************************************************/
void BTIM_DisableUpdateEvent(BTIM_TypeDef* BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx)); 
    
    REGBITS_SET(BTIMx->CR1, BTIMx_CR1_UDIS_Msk);
}

/*******************************************************************************
// 说明：配置BTIMx的触发输入信号来源
// 参数：BTIMx CW_BTIM1~3
// 参数：Source 触发源
// 参数：Polarity 极性    BTIM_TRIGGER_POLARITY_POSITIVE， BTIM_TRIGGER_POLARITY_NEGATIVE
// 返回值：无
*******************************************************************************/
void BTIM_TriggerInputConfig(BTIM_TypeDef* BTIMx, uint16_t Source, uint32_t Polarity)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx)); 
    assert_param(IS_BTIM_TRIGGER_SELECTION(Source)); 
    assert_param(IS_BTIM_TRIGGER_POLARITY(Polarity));
    
    REGBITS_MODIFY(BTIMx->SMCR, BTIMx_SMCR_TRGIPOL_Msk |BTIMx_SMCR_TRGISRC_Msk, (Source) |(Polarity));    
}

/*******************************************************************************
// 说明：配置BTIMx的复位输入信号来源
// 参数：BTIMx CW_BTIM1~3
// 参数：Source 复位源
// 参数：Polarity 极性    BTIM_RESET_POLARITY_POSITIVE， BTIM_RESET_POLARITY_NEGATIVE
// 返回值：无
*******************************************************************************/
void BTIM_ResetInputConfig(BTIM_TypeDef* BTIMx, uint16_t Source, uint32_t Polarity)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx)); 
    assert_param(IS_BTIM_RESET_SELECTION(Source)); 
    assert_param(IS_BTIM_RESET_POLARITY(Polarity));
    
    REGBITS_MODIFY(BTIMx->SMCR, BTIMx_SMCR_RSTIPOL_Msk |BTIMx_SMCR_RSTISRC_Msk, (Source) |(Polarity));    
}

/*******************************************************************************
// 说明：配置BTIMx在主模式下的输出
// 参数：BTIMx CW_BTIM1~3
// 参数：Source TRGO信号生成的来源
// 返回值：无
*******************************************************************************/
void BTIM_MasterOutputTriggerConfig(BTIM_TypeDef* BTIMx, uint16_t source)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_MASTER_OUTPUT_TRIGGER(source));
    
    BTIMx->CR2 = source;
}

/*******************************************************************************
// 说明：配置BTIMx在从模式下同步使能
// 参数：BTIMx CW_BTIM1~3
// 返回值：无
*******************************************************************************/
void BTIM_SlaveSynchronEnable(BTIM_TypeDef* BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    REGBITS_SET(BTIMx->SMCR, BTIMx_SMCR_MSM_Msk);    
}

/*******************************************************************************
// 说明：配置BTIMx在从模式下同步使能
// 参数：BTIMx CW_BTIM1~3
// 返回值：无
*******************************************************************************/
void BTIM_SlaveSynchronDisable(BTIM_TypeDef* BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    REGBITS_CLR(BTIMx->SMCR, BTIMx_SMCR_MSM_Msk);    
}


