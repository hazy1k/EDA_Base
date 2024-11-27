/**
 * @file cw32l010_atim.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2022-7-12
 *
 * @copyright Copyright (c) 2021
 *
 */
/* Includes ------------------------------------------------------------------*/
#include "cw32l010_atim.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/
/**
 * @brief ATIM复位，寄存器恢复为默认值
 */
void ATIM_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.ATIM = 0;
    CW_SYSCTRL->APBRST1_f.ATIM = 1;
}

/**
 * @brief ATIM 初始化
 * @param ATIM_InitStruct  详见ATIM_InitTypeDef的定义
 */
void ATIM_Init(ATIM_InitTypeDef *ATIM_InitStruct)
{
    assert_param(IS_ATIM_COUNTING_DIRECTION(ATIM_InitStruct->CounterDirection));
    assert_param(IS_ATIM_OP_MODE(ATIM_InitStruct->CounterOPMode));
    assert_param(IS_ATIM_COUNT_MODE(ATIM_InitStruct->CounterAlignedMode));
    assert_param(IS_ATIM_PRESCALER(ATIM_InitStruct->Prescaler));   
    
    CW_SYSCTRL->APBEN1 |= SYSCTRL_APBEN1_ATIM_Msk;  

    REGBITS_MODIFY(CW_ATIM->CR1, ATIM_CR1_DIR_Msk | ATIM_CR1_OPM_Msk |\
                   ATIM_CR1_ARPE_Msk | ATIM_CR1_CMS_Msk,
                   ATIM_InitStruct->CounterDirection | ATIM_InitStruct->CounterOPMode |\
                   (ATIM_InitStruct->BufferState ? ATIM_BUFFER_ENABLE : ATIM_BUFFER_DISABLE)|\
                   ATIM_InitStruct->CounterAlignedMode);
    
    CW_ATIM->PSC = ATIM_InitStruct->Prescaler;

    CW_ATIM->ARR = ATIM_InitStruct->ReloadValue;

    CW_ATIM->RCR = ATIM_InitStruct->RepetitionCounter;
}

/**
 * @brief ATIM 启动
 *
 * @param NewState ENABLE or DISABLE
 */
void ATIM_Cmd(FunctionalState NewState)
{
    CW_ATIM->CR1_f.CEN = NewState;
}

/**
 * @brief ATIM中断设置
 * @param ATIM_IT 中断源
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_ITConfig(uint32_t ATIM_IT, FunctionalState NewState)
{
    assert_param(IS_ATIM_IT(ATIM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        CW_ATIM->IER |= ATIM_IT;
    }
    else
    {
        CW_ATIM->IER &= ~ATIM_IT;
    }
}

/**
 * @brief 获取ATIM中断标志位
 * @param ATIM_IT 中断源
 * @return ITStatus
 */
ITStatus ATIM_GetITStatus(uint32_t ATIM_STATE)
{
    assert_param(IS_ATIM_STATE(ATIM_STATE));
    return  (CW_ATIM->ISR & ATIM_STATE) ? SET : RESET;
}

/**
 * @brief 清除ATIM中断标志位
 */
void ATIM_ClearITPendingBit(uint32_t ATIM_STATE)
{
    assert_param(IS_ATIM_IT(ATIM_STATE));
    CW_ATIM->ICR = ~ATIM_STATE;
}

/**
 * @brief 设置ATIM重载值
 * @param Value
 */
void ATIM_SetReloadValue(uint32_t Value)
{
    CW_ATIM->ARR = Value;
}

/**
 * @brief 设置ATIM的计数器值
 * @param Value
 */
void ATIM_SetCounterValue(uint32_t value)
{
    CW_ATIM->CNT = value;
}

/**
 * @brief 设置ATIM主模式下，TRGO1的输出配置
 * @param Value
 */

void ATIM_MasterModeTrgo1Config(uint8_t ATIM_MasterOutput)
{
    assert_param(IS_ATIM_MASTER_OUTPUT(ATIM_MasterOutput));

    CW_ATIM->CR2_f.MMS = (ATIM_MasterOutput & 0x07);
    CW_ATIM->CR2_f.MMSH = (ATIM_MasterOutput >> 3);
}

void ATIM_MasterModeTrgo2Config(uint8_t ATIM_MasterOutput)
{
    assert_param(IS_ATIM_MASTER_OUTPUT(ATIM_MasterOutput));

    CW_ATIM->CR2_f.MMS2 = ATIM_MasterOutput;
}


void ATIM_SlaverModeConfig(uint8_t ATIM_SlaverType)
{
    assert_param(IS_ATIM_SLAVER_TYPE(ATIM_SlaverType));

    CW_ATIM->SMCR_f.SMS = ATIM_SlaverType & 0x07;
    CW_ATIM->SMCR_f.SMSH = ATIM_SlaverType >> 3;
}

void ATIM_SetTriggerInput(uint32_t TriggerInput)
{
     assert_param(IS_ATIM_TRIGGER_INPUT(TriggerInput));
    REGBITS_MODIFY(CW_ATIM->SMCR, ATIM_SMCR_TSH_Msk | ATIM_SMCR_TS_Msk, TriggerInput);
}

void ATIM_IC1Init(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    assert_param(IS_ATIMC_IC_PRESCALER(ATIM_ICInitStruct->ICPrescaler));
    
    CW_ATIM->CCMR1CAP_f.CC1S = ATIM_ICInitStruct->ICMap;
    CW_ATIM->CCMR1CAP_f.IC1PSC = ATIM_ICInitStruct->ICPrescaler;
    CW_ATIM->CCMR1CAP_f.IC1F = ATIM_ICInitStruct->ICFilter;
    
    CW_ATIM->CCER_f.CC1P = ATIM_ICInitStruct->ICPolarity;
    CW_ATIM->CCER_f.CC1E = 1;                     
}

void ATIM_IC2Init(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    
    CW_ATIM->CCMR1CAP_f.CC2S = ATIM_ICInitStruct->ICMap;
    CW_ATIM->CCMR1CAP_f.IC2PSC = ATIM_ICInitStruct->ICPrescaler;
    CW_ATIM->CCMR1CAP_f.IC2F = ATIM_ICInitStruct->ICFilter;
    
    CW_ATIM->CCER_f.CC2P = ATIM_ICInitStruct->ICPolarity;
    CW_ATIM->CCER_f.CC2E = 1;                     
}

void ATIM_IC3Init(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    
    CW_ATIM->CCMR2CAP_f.CC3S = ATIM_ICInitStruct->ICMap;
    CW_ATIM->CCMR2CAP_f.IC3PSC = ATIM_ICInitStruct->ICPrescaler;
    CW_ATIM->CCMR2CAP_f.IC3F = ATIM_ICInitStruct->ICFilter;
    
    CW_ATIM->CCER_f.CC3P = ATIM_ICInitStruct->ICPolarity;
    CW_ATIM->CCER_f.CC3E = 1;                     
}

void ATIM_IC4Init(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    
    CW_ATIM->CCMR2CAP_f.CC4S = ATIM_ICInitStruct->ICMap;
    CW_ATIM->CCMR2CAP_f.IC4PSC = ATIM_ICInitStruct->ICPrescaler;
    CW_ATIM->CCMR2CAP_f.IC4F = ATIM_ICInitStruct->ICFilter;
    
    CW_ATIM->CCER_f.CC4P = ATIM_ICInitStruct->ICPolarity;
    CW_ATIM->CCER_f.CC4E = 1;                     
}

void ATIM_IC5Init(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    
    CW_ATIM->CCMR3CAP_f.CC5S = ATIM_ICInitStruct->ICMap;
    CW_ATIM->CCMR3CAP_f.IC5PSC = ATIM_ICInitStruct->ICPrescaler;
    CW_ATIM->CCMR3CAP_f.IC5F = ATIM_ICInitStruct->ICFilter;
    
    CW_ATIM->CCER_f.CC5P = ATIM_ICInitStruct->ICPolarity;
    CW_ATIM->CCER_f.CC5E = 1;                     
}

void ATIM_IC6Init(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    
    CW_ATIM->CCMR3CAP_f.CC6S = ATIM_ICInitStruct->ICMap;
    CW_ATIM->CCMR3CAP_f.IC6PSC = ATIM_ICInitStruct->ICPrescaler;
    CW_ATIM->CCMR3CAP_f.IC6F = ATIM_ICInitStruct->ICFilter;
    
    CW_ATIM->CCER_f.CC6P = ATIM_ICInitStruct->ICPolarity;
    CW_ATIM->CCER_f.CC6E = 1;                     
}

void ATIM_OC1Init(ATIM_OCInitTypeDef *TIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_POLARITY(TIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_MODE(TIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_FAST_MODE(TIM_OCInitStruct->OCFastMode));
    assert_param(IS_FUNCTIONAL_STATE(TIM_OCInitStruct->BufferState));
    
    CW_ATIM->CCMR1CMP_f.CC1S = 0;
    CW_ATIM->CCMR1CMP_f.OC1FE = TIM_OCInitStruct->OCFastMode;
    CW_ATIM->CCMR1CMP_f.OC1PE = TIM_OCInitStruct->BufferState;
    CW_ATIM->CCMR1CMP_f.OC1M = TIM_OCInitStruct->OCMode & 0x07;
    CW_ATIM->CCMR1CMP_f.OC1MH = TIM_OCInitStruct->OCMode >> 3;
    
    CW_ATIM->CCER_f.CC1NE = TIM_OCInitStruct->OCComplement;
    
}

void ATIM_OC2Init(ATIM_OCInitTypeDef *TIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_POLARITY(TIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_MODE(TIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_FAST_MODE(TIM_OCInitStruct->OCFastMode));
    assert_param(IS_FUNCTIONAL_STATE(TIM_OCInitStruct->BufferState));
    
    CW_ATIM->CCMR1CMP_f.CC2S = 0;
    CW_ATIM->CCMR1CMP_f.OC2FE = TIM_OCInitStruct->OCFastMode;
    CW_ATIM->CCMR1CMP_f.OC2PE = TIM_OCInitStruct->BufferState;
    CW_ATIM->CCMR1CMP_f.OC2M = TIM_OCInitStruct->OCMode & 0x07;
    CW_ATIM->CCMR1CMP_f.OC2MH = TIM_OCInitStruct->OCMode >> 3;
    
    CW_ATIM->CCER_f.CC2NE = TIM_OCInitStruct->OCComplement;
}

void ATIM_OC3Init(ATIM_OCInitTypeDef *TIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_POLARITY(TIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_MODE(TIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_FAST_MODE(TIM_OCInitStruct->OCFastMode));
    assert_param(IS_FUNCTIONAL_STATE(TIM_OCInitStruct->BufferState));
    
    CW_ATIM->CCMR2CMP_f.CC3S = 0;
    CW_ATIM->CCMR2CMP_f.OC3FE = TIM_OCInitStruct->OCFastMode;
    CW_ATIM->CCMR2CMP_f.OC3PE = TIM_OCInitStruct->BufferState;
    CW_ATIM->CCMR2CMP_f.OC3M = TIM_OCInitStruct->OCMode & 0x07;
    CW_ATIM->CCMR2CMP_f.OC3MH = TIM_OCInitStruct->OCMode >> 3;
    
    CW_ATIM->CCER_f.CC3NE = TIM_OCInitStruct->OCComplement;
}

void ATIM_OC4Init(ATIM_OCInitTypeDef *TIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_POLARITY(TIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_MODE(TIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_FAST_MODE(TIM_OCInitStruct->OCFastMode));
    assert_param(IS_FUNCTIONAL_STATE(TIM_OCInitStruct->BufferState));
    
    CW_ATIM->CCMR2CMP_f.CC4S = 0;
    CW_ATIM->CCMR2CMP_f.OC4FE = TIM_OCInitStruct->OCFastMode;
    CW_ATIM->CCMR2CMP_f.OC4PE = TIM_OCInitStruct->BufferState;
    CW_ATIM->CCMR2CMP_f.OC4M = TIM_OCInitStruct->OCMode & 0x07;
    CW_ATIM->CCMR2CMP_f.OC4MH = TIM_OCInitStruct->OCMode >> 3;    
    
    CW_ATIM->CCER_f.CC4NE = TIM_OCInitStruct->OCComplement;
}

void ATIM_OC5Init(ATIM_OCInitTypeDef *TIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_POLARITY(TIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_MODE(TIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_FAST_MODE(TIM_OCInitStruct->OCFastMode));
    assert_param(IS_FUNCTIONAL_STATE(TIM_OCInitStruct->BufferState));
    
    CW_ATIM->CCMR3CMP_f.CC5S = 0;
    CW_ATIM->CCMR3CMP_f.OC5FE = TIM_OCInitStruct->OCFastMode;
    CW_ATIM->CCMR3CMP_f.OC5PE = TIM_OCInitStruct->BufferState;
    CW_ATIM->CCMR3CMP_f.OC5M = TIM_OCInitStruct->OCMode & 0x07;
    CW_ATIM->CCMR3CMP_f.OC5MH = TIM_OCInitStruct->OCMode >> 3;
    
    CW_ATIM->CCER_f.CC5NE = TIM_OCInitStruct->OCComplement;
}

void ATIM_OC6Init(ATIM_OCInitTypeDef *TIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_POLARITY(TIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_MODE(TIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_FAST_MODE(TIM_OCInitStruct->OCFastMode));
    assert_param(IS_FUNCTIONAL_STATE(TIM_OCInitStruct->BufferState));
    
    CW_ATIM->CCMR3CMP_f.CC6S = 0;
    CW_ATIM->CCMR3CMP_f.OC6FE = TIM_OCInitStruct->OCFastMode;
    CW_ATIM->CCMR3CMP_f.OC6PE = TIM_OCInitStruct->BufferState;
    CW_ATIM->CCMR3CMP_f.OC6M = TIM_OCInitStruct->OCMode & 0x07;
    CW_ATIM->CCMR3CMP_f.OC6MH = TIM_OCInitStruct->OCMode >> 3;
    
    CW_ATIM->CCER_f.CC6NE = TIM_OCInitStruct->OCComplement;
}

/**
 * @brief 设置通道1的功能
 *
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH1Config(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    CW_ATIM->CCER_f.CC1E = NewState;
}

/**
 * @brief 设置通道2的功能
 *
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH2Config(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    CW_ATIM->CCER_f.CC2E = NewState;
}

/**
 * @brief 设置通道3的功能
 *
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH3Config(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    CW_ATIM->CCER_f.CC3E = NewState;
}

/**
 * @brief 设置通道4的功能
 *
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH4Config(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    CW_ATIM->CCER_f.CC4E = NewState;
}

/**
 * @brief 设置通道5的功能
 *
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH5Config(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    CW_ATIM->CCER_f.CC5E = NewState;
}

/**
 * @brief 设置通道6的功能
 *
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH6Config(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    CW_ATIM->CCER_f.CC6E = NewState;
}

uint16_t ATIM_GetCapture1(void)
{
    return CW_ATIM->CCR1;
}

uint16_t ATIM_GetCapture2(void)
{
    return CW_ATIM->CCR2;
}

uint16_t ATIM_GetCapture3(void)
{
    return CW_ATIM->CCR3;
}

uint16_t ATIM_GetCapture4(void)
{
    return CW_ATIM->CCR4;
}

uint16_t ATIM_GetCapture5(void)
{
    return CW_ATIM->CCR5;
}

uint16_t ATIM_GetCapture6(void)
{
    return CW_ATIM->CCR6;
}

void ATIM_SetCompare1(uint16_t Compare)
{
    CW_ATIM->CCR1 = Compare;
}

void ATIM_SetCompare2(uint16_t Compare)
{
    CW_ATIM->CCR2 = Compare;
}
void ATIM_SetCompare3(uint16_t Compare)
{
    CW_ATIM->CCR3 = Compare;
}
void ATIM_SetCompare4(uint16_t Compare)
{
    CW_ATIM->CCR4 = Compare;
}
void ATIM_SetCompare5(uint16_t Compare)
{
    CW_ATIM->CCR5 = Compare;
}
void ATIM_SetCompare6(uint16_t Compare)
{
    CW_ATIM->CCR6 = Compare;
}

void ATIM_CtrlPWMOutputs(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    CW_ATIM->BDTR_f.MOE = NewState;
}

/**
 * @brief 设置PWM输出的死区
 *
 * @param RiseDeadtime 上升沿死区 死区时间，单位为定时器的计数时隙，范围：0~0xFF
 * @param FallDeadtime 上升沿死区 死区时间，单位为定时器的计数时隙，范围：0~0xFF
 * @param BuffState 死区缓存使能 
 *                 
 */
void ATIM_SetPWMDeadtime(int16_t RiseDeadtime, int16_t FallDeadtime, FunctionalState BuffState)
{
    if (RiseDeadtime == FallDeadtime)
    {
        CW_ATIM->DTR2_f.DTAE = 0;
        CW_ATIM->BDTR_f.DTG = RiseDeadtime;
    }
    else
    {
        CW_ATIM->DTR2_f.DTAE = 1;
        CW_ATIM->BDTR_f.DTG = RiseDeadtime;
        CW_ATIM->DTR2_f.DTGF = FallDeadtime;        
    }
    
    CW_ATIM->DTR2_f.DTPE = BuffState;    
}

/**
 * @brief 设置Brake输入信号的参数
 * @param ATIM_BrakePolarity 信号极性，参数为下列参数之一：
 *        @arg ATIM_BRAKE_POLARITY_LOW
 *        @arg ATIM_BRAKE_POLARITY_HIGH
 * @param ATIM_BrakeFilter
 */
void ATIM_Brake1Config(uint32_t ATIM_BrakePolarity, uint32_t ATIM_BrakeFilter)
{
    assert_param(IS_ATIM_BRAKE_POLARITY(ATIM_BrakePolarity));
    assert_param(IS_ATIM_BRAKE_FILTER(ATIM_BrakeFilter));
    
    CW_ATIM->BDTR_f.BKP = ATIM_BrakePolarity;
    CW_ATIM->BDTR_f.BKF = ATIM_BrakeFilter;
    
    CW_ATIM->BDTR_f.BKE = 1; 
}

void ATIM_Brake2Config(uint32_t ATIM_BrakePolarity, uint32_t ATIM_BrakeFilter)
{
    assert_param(IS_ATIM_BRAKE_POLARITY(ATIM_BrakePolarity));
    assert_param(IS_ATIM_BRAKE_FILTER(ATIM_BrakeFilter));
    
    CW_ATIM->BDTR_f.BK2P = ATIM_BrakePolarity;
    CW_ATIM->BDTR_f.BK2F = ATIM_BrakeFilter;
    
    CW_ATIM->BDTR_f.BK2E = 1; 
}

/**
 * @brief 设置ATIM更新事件类型
 *
 * @param ATIM_UpdateEvent 
 *        @arg ATIM_UPDATE_EVENT_NORMAL 上溢出/下溢出
 *        @arg ATIM_UPDATE_EVENT_EXTENSION 上溢出/下溢出/软件更新/从模式复位
 *                 
 */

void ATIM_UpdateEventSelect(uint8_t ATIM_UpdateEvent)
{
    assert_param(IS_ATIM_UPDATE_EVENT(ATIM_UpdateEvent));

    CW_ATIM->CR1_f.URS = ATIM_UpdateEvent;
}

void ATIM_RemapTimerInput(uint32_t ChannelX, uint32_t Remap)
{
    switch (ChannelX)
    {
        case ATIM_CH1:
            CW_ATIM->TISEL1_f.TI1SEL = Remap;
            break;
        case ATIM_CH2:
            CW_ATIM->TISEL1_f.TI2SEL = Remap;
            break;
        case ATIM_CH3:
            CW_ATIM->TISEL1_f.TI3SEL = Remap;
            break;
        case ATIM_CH4:
            CW_ATIM->TISEL1_f.TI4SEL = Remap;
            break;
        case ATIM_CH5:
            CW_ATIM->TISEL2_f.TI5SEL = Remap;
            break;
        case ATIM_CH6:
            CW_ATIM->TISEL2_f.TI6SEL = Remap;
            break;
        default:
            break;        
    }
}

