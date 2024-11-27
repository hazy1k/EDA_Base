/**
 * @file cw32l052_lptim.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2022-02-18
 *
 * @copyright Copyright (c) 2022
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "cw32l010_lptim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief LPTIM复位
 *
 */
void LPTIM_DeInit(void)
{
    CW_SYSCTRL->APBRST2_f.LPTIM = 0;
    CW_SYSCTRL->APBRST2_f.LPTIM = 1;
}

/**
 * @brief LPTIM 初始化函数
 *
 * @param LPTIM_InitStruct
 */
void LPTIM_Init(LPTIM_InitTypeDef* LPTIM_InitStruct)
{
    assert_param(IS_LPTIM_CLOCK_SOURCE(LPTIM_InitStruct->LPTIM_ClockSource));
    assert_param(IS_LPTIM_COUNTER_MODE(LPTIM_InitStruct->LPTIM_CounterMode));
    assert_param(IS_LPTIM_PRS(LPTIM_InitStruct->LPTIM_Prescaler));

    CW_LPTIM->ARR = LPTIM_InitStruct->LPTIM_Period;
    CW_LPTIM->CFGR = LPTIM_InitStruct->LPTIM_Prescaler | LPTIM_InitStruct->LPTIM_ClockSource | LPTIM_InitStruct->LPTIM_CounterMode;
}

/**
 * @brief 设置预分配系数
 *
 * @param Prescaler LPTIM_PRS_DIV1 LPTIM_PRS_DIV2 LPTIM_PRS_DIV4 LPTIM_PRS_DIV8
 *                  LPTIM_PRS_DIV16 LPTIM_PRS_DIV32 LPTIM_PRS_DIV64 LPTIM_PRS_DIV128
 */
void LPTIM_PrescalerConfig(uint32_t Prescaler)
{
    assert_param(IS_LPTIM_PRS(Prescaler));

    REGBITS_MODIFY(CW_LPTIM->CFGR, LPTIM_CFGR_PRS_Msk, Prescaler);
}

/**
 * @brief 设置LPTIM的计数模式为定时模式或计数模式
 *
 * @param LPTIM_CounterMode LPTIM_COUNTER_MODE_TIME LPTIM_COUNTER_MODE_COUNT
 *
 */
void LPTIM_CounterModeConfig(uint32_t LPTIM_CounterMode)
{
    assert_param(IS_LPTIM_COUNTER_MODE(LPTIM_CounterMode));
    REGBITS_MODIFY(CW_LPTIM->CFGR, LPTIM_CFGR_COUNTMD_Msk, LPTIM_CounterMode);
}

/**
 * @brief 设置LPTIM的ARR值与更新方式
 *
 * @param Autoreload 0x0000~0xFFFF
 * @param ReloadMode LPTIM_RELOAD_MODE_UPDATE LPTIM_RELOAD_MODE_IMMEDIATE
 */
void LPTIM_SetAutoreload(uint16_t Autoreload, uint32_t ReloadMode)
{
    assert_param(IS_LPTIM_RELOAD_MODE(ReloadMode));

    CW_LPTIM->ARR = Autoreload;
    REGBITS_MODIFY(CW_LPTIM->CFGR, LPTIM_CFGR_PRELOAD_Msk, ReloadMode);
}

/**
 * @brief 获取LPTIM的CNT值, 连续两次读到相同值才认为读出数据
 *
 */
uint32_t LPTIM_GetCounter(void)
{
    uint32_t TmpCNT = 0;
    do
    {
        TmpCNT = CW_LPTIM->CNT;
    }
    while (TmpCNT != CW_LPTIM->CNT);

    return TmpCNT;
}

/**
 * @brief 获取LPTIM的分频值
 *
 * @return uint8_t
 */
uint8_t TIM_GetPrescaler(void)
{
    return CW_LPTIM->CFGR_f.PRS;
}

/**
 * @brief 设置LPTIM工作模式为单脉冲模式或连续运行模式
 *
 * @param LPTIM_OPMode LPTIM_OPERATION_SINGLE LPTIM_OPERATION_REPETITIVE
 */
void LPTIM_SelectOnePulseMode(uint16_t LPTIM_OPMode)
{
    assert_param(IS_LPTIM_OPERATION_MODE(LPTIM_OPMode));
    REGBITS_MODIFY(CW_LPTIM->CR, LPTIM_CR_CNTSTART_Msk | LPTIM_CR_SNGSTART_Msk, LPTIM_OPMode);

}

/**
 * @brief 打开或关闭LPTIM
 *
 * @param NewState
 */
void LPTIM_Cmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    CW_LPTIM->CR_f.EN = NewState;
}

/**
 * @brief 配置内部时钟源
 *
 * @param LPTIM_ICLK_Source LPTIM_ICLK_PCLK LPTIM_ICLK_LSE LPTIM_ICLK_LSI
 */
void LPTIM_InternalClockConfig(uint32_t LPTIM_ICLK_Source)
{
    assert_param(IS_LPTIM_ICLK(LPTIM_ICLK_Source));

    REGBITS_MODIFY(CW_LPTIM->CFGR, LPTIM_CFGR_ICLKSRC_Msk, LPTIM_ICLK_Source);
}

/**
 * @brief 设置PWM输出
 *
 * @param Period 周期
 * @param Pulse  脉宽
 * @param Polarity  波形极性
 */
void LPTIM_PWMStart(uint32_t Period, uint32_t Pulse, uint32_t Polarity)
{
    assert_param(IS_LPTIM_PWM_POL(Polarity));

    CW_LPTIM->ARR = Period;
    CW_LPTIM->CMP = Pulse;

    REGBITS_MODIFY(CW_LPTIM->CFGR, LPTIM_CFGR_WAVPOL_Msk, Polarity);
    CW_LPTIM->CFGR_f.WAVE = 0;
    LPTIM_Cmd(ENABLE);
    LPTIM_SelectOnePulseMode(LPTIM_OPERATION_REPETITIVE);
}


/**
 * @brief 设置LPTIM的中断使能或禁能，可同时设置多个中断使能位，用“|”连接
 *
 * @param LPTIM_IT LPTIM_IT_CMPM LPTIM_IT_ARRM LPTIM_IT_EXTTRIG LPTIM_IT_CMPOK
 *                 LPTIM_IT_ARROK LPTIM_IT_UP LPTIM_IT_DOWN
 * @param NewState ENABLE DISABLE
 */
void LPTIM_ITConfig(uint32_t LPTIM_IT, FunctionalState NewState)
{
    assert_param(IS_LPTIM_IT(LPTIM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        CW_LPTIM->IER |= LPTIM_IT;
    }
    else
    {
        CW_LPTIM->IER &= ~LPTIM_IT;
    }
}

/**
 * @brief 获得LPTIM的状态位
 *
 * @param LPTIM_FLAG LPTIM_FLAG_CMPM LPTIM_FLAG_ARRM LPTIM_FLAG_EXTTRIG
 *                   LPTIM_FLAG_CMPOK LPTIM_FLAG_ARROK LPTIM_FLAG_UP LPTIM_FLAG_DOWN
 * @return FlagStatus SET RESET
 */
FlagStatus LPTIM_GetFlagStatus(uint32_t LPTIM_FLAG)
{
    assert_param(IS_LPTIM_GET_FLAG(LPTIM_FLAG));

    return (FlagStatus)(!!(CW_LPTIM->ISR & LPTIM_FLAG));
}

/**
 * @brief 清除LPTIM的标志位
 *
 * @param LPTIM_FLAG LPTIM_FLAG_CMPM LPTIM_FLAG_ARRM LPTIM_FLAG_EXTTRIG
 *                   LPTIM_FLAG_CMPOK LPTIM_FLAG_ARROK LPTIM_FLAG_UP LPTIM_FLAG_DOWN
 */
void LPTIM_ClearFlag(uint32_t LPTIM_FLAG)
{
    assert_param(IS_LPTIM_GET_FLAG(LPTIM_FLAG));
    CW_LPTIM->ICR = ~LPTIM_FLAG;

}

/**
 * @brief 获取LPTIM的中断标志位
 *
 * @param LPTIM_IT LPTIM_IT_CMPM LPTIM_IT_ARRM LPTIM_IT_EXTTRIG LPTIM_IT_CMPOK
 *                 LPTIM_IT_ARROK LPTIM_IT_UP LPTIM_IT_DOWN
 * @return ITStatus SET RESET
 */
ITStatus LPTIM_GetITStatus(uint32_t LPTIM_IT)
{
    assert_param(IS_LPTIM_GET_FLAG(LPTIM_IT));

    return (ITStatus)!!(CW_LPTIM->ISR & LPTIM_IT);
}

/**
 * @brief 清除LPTIM的中断标志位
 *
 * @param LPTIM_IT LPTIM_IT_CMPM LPTIM_IT_ARRM LPTIM_IT_EXTTRIG LPTIM_IT_CMPOK
 *                 LPTIM_IT_ARROK LPTIM_IT_UP LPTIM_IT_DOWN
 */
void LPTIM_ClearITPendingBit(uint32_t LPTIM_IT)
{
    assert_param(IS_LPTIM_GET_FLAG(LPTIM_IT));
    CW_LPTIM->ICR = ~LPTIM_IT;
}

/**
 * @brief 获取LPTIM在编码器模式下的状态
 *
 * @return ENCStatus DOWN_STOP UP_STOP DOWN_RUN UP_RUN
 */
ENCStatus LPTIM_GetENCStatus(void)
{
    return (ENCStatus)((CW_LPTIM->ISR & 0x00000180) >> 7);
}






/************************ END OF FILE************************/
