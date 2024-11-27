/**
 * @file cw32l010_vc.c
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


/******************************************************************************
 * Include files
 ******************************************************************************/
#include "cw32l010.h"
#include "cw32l010_vc.h"
#include "cw32l010_adc.h"

/**
 ******************************************************************************
 ** \addtogroup VcGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_CHANNEL(x)     ( VcChannel1==(x) || VcChannel2 == (x))
#define IS_VALID_STAT(x)        ( VcCmpResult==(x) || VcIntrResult == (x))
#define IS_VALID_DIV(x)         ( (x) <= 64u )

#define IS_VALID_INPUT_P(x)     ( (x) <= VcInPCh7 )

#define IS_VALID_INPUT_N(x)     ( (x) <= AiAdcVref )

#define IS_VALID_DLY(x)         ( (VcDelay30mv == (x)) ||\
                                  (VcDelay20mv == (x)) ||\
                                  (VcDelay10mv == (x)) ||\
                                  (VcDelayoff == (x)) )

#define IS_VALID_BIAS(x)        ( (VcRespExtraLow == (x)) ||\
                                  (VcRespLow == (x)) ||\
                                  (VcRespMedium == (x)) ||\
                                  (VcRespHigh == (x)) )

#define IS_VALID_CLK(x)         ( (x) <= VcFilterPclk )

#define IS_VALID_FILTER(x)      ( (x) <= VcFilter4095Clk )

#define IS_VALID_BLANK(x)       ( (x) <= VcBlankAtimCh3 )

#define IS_VALID_OUTPUT(x)      ( (x) <= VcOutAtimClr )

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/


/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/


/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/


/**
 * @brief
 *          使能NVIC中VCx中断
 *
 * @param   enIrqn:
 *          @arg VC1_IRQn
 *          @arg VC2_IRQn
 * @param   intPriority:
 *          @arg 0 ~ 3
 */
void VC_EnableNvic(IRQn_Type enIrqn, uint8_t intPriority)
{
    if (intPriority < (1UL << __NVIC_PRIO_BITS))
    {
        NVIC_ClearPendingIRQ(enIrqn);
        NVIC_EnableIRQ(enIrqn);
        NVIC_SetPriority(enIrqn, intPriority);
    }
}

/**
 * @brief
 *          VC通道1中断使能
 *
 * @param   intPriority:
 *          @arg 0 ~ 3
 *
 *          @return
 */
void VC1_EnableIrq(uint8_t intPriority)
{
    VC_EnableNvic(VC1_IRQn, intPriority);
    REGBITS_SET(CW_VC1->CR0, VCx_CR0_IE_Msk);
}

/**
 * @brief
 *          VC通道2中断使能
 *
 * @param   intPriority:
 *          @arg 0 ~ 3
 *
 *          @return
 */
void VC2_EnableIrq(uint8_t intPriority)
{
    VC_EnableNvic(VC2_IRQn, intPriority);
    REGBITS_SET(CW_VC2->CR0, VCx_CR0_IE_Msk);
}

/**
 * @brief
 *          VC通道1中断禁用
 *
 * @return
 */
void VC1_DisableIrq(void)
{
    REGBITS_CLR(CW_VC1->CR0, VCx_CR0_IE_Msk);
    VC_DisableNvic(VC1_IRQn);
}

/**
 * @brief
 *          VC通道2中断禁用
 *
 * @return
 */
void VC2_DisableIrq(void)
{
    REGBITS_CLR(CW_VC2->CR0, VCx_CR0_IE_Msk);
    VC_DisableNvic(VC2_IRQn);
}

/**
 * @brief
 *          禁止NVIC中VC中断
 *
 * @param   enIrqn:
 *          @arg VC1_IRQn
 *          @arg VC2_IRQn
 *
 * @return
 */
void VC_DisableNvic(IRQn_Type enIrqn)
{
    NVIC_ClearPendingIRQ(enIrqn);
    NVIC_DisableIRQ(enIrqn);
}



/**
 * @brief
 *          清除VC1中断标志
 *
 * @param
 *
 * @return
 */
void VC1_ClearIrq(void)
{
    REGBITS_CLR(CW_VC1->SR, VCx_SR_INTF_Msk);
}

/**
 * @brief
 *          清除VC2中断标志
 *
 * @param
 *
 * @return
 */
void VC2_ClearIrq(void)
{
    REGBITS_CLR(CW_VC2->SR, VCx_SR_INTF_Msk);
}

/**
 * @brief
 *          VC1/VC2模块DIV参考电压初始化
 *
 * @param   VC_DivStruct
 *
 * @return
 */
void VC1VC2_DIVInit(VC_DivTypeDef* VC_DivStruct)
{
    ASSERT(NULL != VC_DivStruct)
    assert_param(IS_VC_DIV_EN(VC_DivStruct->VC_DivEn));
    assert_param(IS_VC_DIV_VREF(VC_DivStruct->VC_DivVref));

    REGBITS_MODIFY(CW_VCREF->CR, VCREF_CR_EN_Msk | VCREF_CR_VIN_Msk, \
                   VC_DivStruct->VC_DivEn | VC_DivStruct->VC_DivVref);
	
    if (VC_DivStruct->VC_DivValue < 0x08)
    {
        CW_VCREF->CR_f.DIV = VC_DivStruct->VC_DivValue;
    }
    else
    {
    }
}

/**
 * @brief
 *          VC1/VC2模块DIV参考电压去初始化
 *
 * @param
 *
 * @return
 */
void VC1VC2_DIVDeInit(void)
{
    CW_VCREF->CR= 0x0u;
    CW_VCREF->CR = 0x0u;
}

/**
 * @brief
 *          VC1/VC2模块VCx负端输入信号初始化
 *
 * @param   VC_InitStruct
 *
 * @return
 */
void VC1VC2_INNInit(VC_InitTypeDef* VC_InitStruct)
{
    ASSERT(NULL != VC_InitStruct)
    assert_param(IS_VC_INPUT_N(VC_InitStruct->VC_InputN));
								 if(VC_InitStruct->VC_InputN==VC_InputN_Bgr1P2)
									{     
										//VCx负端输入信号为BGR 1.2V
            //打开ADC时钟
            REGBITS_SET( CW_SYSCTRL->APBEN1, SYSCTRL_APBEN1_ADC_Msk );
            REGBITS_SET(CW_ADC->CR, ADC_CR_BGREN_Msk);
									}
}

/**
 * @brief
 *          VC通道1初始化
 *
 * @param   VC_InitStruct
 *
 * @return
 */
void VC1_ChannelInit(VC_InitTypeDef* VC_InitStruct)
{
    ASSERT(NULL != VC_InitStruct)
    assert_param(IS_VC_INPUT_P(VC_InitStruct->VC_InputP));
    assert_param(IS_VC_INPUT_N(VC_InitStruct->VC_InputN));
    assert_param(IS_VC_HYS(VC_InitStruct->VC_Hys));
    assert_param(IS_VC_RESP(VC_InitStruct->VC_Resp));  
    assert_param(IS_VC_FLT_CLK(VC_InitStruct->VC_FilterClk));
    assert_param(IS_VC_FLT_TIME(VC_InitStruct->VC_FilterTime));
    assert_param(IS_VC_WINDOW(VC_InitStruct->VC_Window));
    assert_param(IS_VC_POLARITY(VC_InitStruct->VC_Polarity));

    REGBITS_MODIFY(CW_VC1->CR0, \
                   VCx_CR0_INN_Msk  |VCx_CR0_INP_Msk  | \
                   VCx_CR0_WINDOW_Msk | VCx_CR0_POL_Msk | \
                   VCx_CR0_HYS_Msk | VCx_CR0_RESP_Msk, \
                   VC_InitStruct->VC_InputN | \
                   VC_InitStruct->VC_InputP | \
                   VC_InitStruct->VC_Window | \
                   VC_InitStruct->VC_Polarity | \
                   VC_InitStruct->VC_Hys | \
                   VC_InitStruct->VC_Resp);

    REGBITS_MODIFY(CW_VC1->CR1, \
                   VCx_CR1_FLTCLK_Msk | VCx_CR1_FLTTIME_Msk , \
                   VC_InitStruct->VC_FilterClk | \
                   VC_InitStruct->VC_FilterTime );

    //VCx负端输入信号初始化
    VC1VC2_INNInit(VC_InitStruct);
}

/**
 * @brief
 *          VC通道2初始化
 *
 * @param   VC_InitStruct
 *
 * @return
 */
void VC2_ChannelInit(VC_InitTypeDef* VC_InitStruct)
{
    ASSERT(NULL != VC_InitStruct)
    assert_param(IS_VC_INPUT_P(VC_InitStruct->VC_InputP));
    assert_param(IS_VC_INPUT_N(VC_InitStruct->VC_InputN));
    assert_param(IS_VC_HYS(VC_InitStruct->VC_Hys));
    assert_param(IS_VC_RESP(VC_InitStruct->VC_Resp));
    assert_param(IS_VC_FLT_CLK(VC_InitStruct->VC_FilterClk));
    assert_param(IS_VC_FLT_TIME(VC_InitStruct->VC_FilterTime));
    assert_param(IS_VC_WINDOW(VC_InitStruct->VC_Window));
    assert_param(IS_VC_POLARITY(VC_InitStruct->VC_Polarity));

    REGBITS_MODIFY(CW_VC2->CR0, \
                   VCx_CR0_INN_Msk  |VCx_CR0_INP_Msk  | \
                   VCx_CR0_WINDOW_Msk | VCx_CR0_POL_Msk | \
                   VCx_CR0_HYS_Msk | VCx_CR0_RESP_Msk, \
                   VC_InitStruct->VC_InputN | \
                   VC_InitStruct->VC_InputP | \
                   VC_InitStruct->VC_Window | \
                   VC_InitStruct->VC_Polarity | \
                   VC_InitStruct->VC_Hys | \
                   VC_InitStruct->VC_Resp);

    REGBITS_MODIFY(CW_VC2->CR1, \
                   VCx_CR1_FLTCLK_Msk | VCx_CR1_FLTTIME_Msk , \
                   VC_InitStruct->VC_FilterClk | \
                   VC_InitStruct->VC_FilterTime );

    //VCx负端输入信号初始化
    VC1VC2_INNInit(VC_InitStruct);
}

/**
 * @brief
 *          VC模块去初始化
 *
 * @return
 */
void VC_DeInit(void)
{
    // Enable VC reset state
    REGBITS_CLR(CW_SYSCTRL->APBRST2, 0x5A5A0000U|SYSCTRL_APBRST1_VC_Msk);
    // Release VC from reset state
    REGBITS_SET(CW_SYSCTRL->APBRST2, 0x5A5A0000U|SYSCTRL_APBRST1_VC_Msk);

    VC1_ChannelDeInit();
    VC2_ChannelDeInit();
}

/**
 * @brief
 *          VC通道1去初始化
 *
 * @return
 */
void VC1_ChannelDeInit(void)
{
    CW_VC1->CR0 = 0u;
    CW_VC1->CR1 = 0u;
    VC_DisableNvic(VC1_IRQn);
}

/**
 * @brief
 *          VC通道2去初始化
 *
 * @return
 */
void VC2_ChannelDeInit(void)
{
    CW_VC2->CR0 = 0u;
    CW_VC2->CR1 = 0u;
    VC_DisableNvic(VC2_IRQn);
}

/**
 * @brief
 *          VC1通道使能
 *
 * @return
 */
void VC1_EnableChannel(void)
{
    REGBITS_SET(CW_VC1->CR0, VCx_CR0_EN_Msk);
}

/**
 * @brief
 *          VC2通道使能
 *
 * @return
 */
void VC2_EnableChannel(void)
{
    REGBITS_SET(CW_VC2->CR0, VCx_CR0_EN_Msk);
	   FirmwareDelay(50);
}

/**
 * @brief
 *          VC1通道禁用
 *
 * @return
 */
void VC1_DisableChannel(void)
{
    REGBITS_CLR(CW_VC1->CR0, VCx_CR0_EN_Msk);
}

/**
 * @brief
 *          VC2通道禁用
 *
 * @return
 */
void VC2_DisableChannel(void)
{
    REGBITS_CLR(CW_VC2->CR0, VCx_CR0_EN_Msk);
}




/**
 * @brief
 *          VC通道1/2 BlanK窗口默认值初始化
 * @param   VC_BlankStruct
 *
 * @return
 */
void VC1VC2_BlankInit(VC_BlankTypeDef* VC_BlankStruct)
{
    VC_BlankStruct->VC_BlankTime = 0u;
				VC_BlankStruct->VC_BlankLevel = 0u;
				VC_BlankStruct->VC_BlankCh6 = 0u;
    VC_BlankStruct->VC_BlankCh5 = 0u;
    VC_BlankStruct->VC_BlankCh4 = 0u;
    VC_BlankStruct->VC_BlankCh3 = 0u;
    VC_BlankStruct->VC_BlankCh2 = 0u;
    VC_BlankStruct->VC_BlankCh1 = 0u;
}

/**
 * @brief
 *          VC通道1 BlanK窗口配置
 * @param   VC_BlankStruct
 *
 * @return
 */
void VC1_BlankCfg(VC_BlankTypeDef* VC_BlankStruct)
{
    ASSERT(NULL != VC_BlankStruct)
    assert_param(IS_VC_BLANK_TIME(VC_BlankStruct->VC_BlankTime));
	   assert_param(IS_VC_BLANK_CH6(VC_BlankStruct->VC_BlankCh6));
	   assert_param(IS_VC_BLANK_CH6(VC_BlankStruct->VC_BlankCh6));
    assert_param(IS_VC_BLANK_CH5(VC_BlankStruct->VC_BlankCh5));
    assert_param(IS_VC_BLANK_CH4(VC_BlankStruct->VC_BlankCh4));
    assert_param(IS_VC_BLANK_CH3(VC_BlankStruct->VC_BlankCh3));
    assert_param(IS_VC_BLANK_CH2(VC_BlankStruct->VC_BlankCh2));
    assert_param(IS_VC_BLANK_CH1(VC_BlankStruct->VC_BlankCh1));

    REGBITS_MODIFY(CW_VC1->CR1, \
                   VCx_CR1_BLANKTIME_Msk  | VCx_CR1_BLANKLVL_Msk | VCx_CR1_BLANKATCH6_Msk |\
                   VCx_CR1_BLANKATCH5_Msk | VCx_CR1_BLANKATCH4_Msk |VCx_CR1_BLANKATCH3_Msk| \
                   VCx_CR1_BLANKATCH2_Msk | VCx_CR1_BLANKATCH1_Msk,
                   VC_BlankStruct->VC_BlankTime | \
				               VC_BlankStruct->VC_BlankLevel | \
				               VC_BlankStruct->VC_BlankCh6 | \
                   VC_BlankStruct->VC_BlankCh5 | \
                   VC_BlankStruct->VC_BlankCh4 | \
                   VC_BlankStruct->VC_BlankCh3 | \
                   VC_BlankStruct->VC_BlankCh2 | \
                   VC_BlankStruct->VC_BlankCh1);
}

/**
 * @brief
 *          VC通道2 BlanK窗口配置
 * @param   VC_BlankStruct
 *
 * @return
 */
void VC2_BlankCfg(VC_BlankTypeDef* VC_BlankStruct)
{
    ASSERT(NULL != VC_BlankStruct)
    assert_param(IS_VC_BLANK_TIME(VC_BlankStruct->VC_BlankTime));
   	assert_param(IS_VC_BLANK_CH6(VC_BlankStruct->VC_BlankCh6));
   	assert_param(IS_VC_BLANK_CH6(VC_BlankStruct->VC_BlankCh6));
    assert_param(IS_VC_BLANK_CH5(VC_BlankStruct->VC_BlankCh5));
    assert_param(IS_VC_BLANK_CH4(VC_BlankStruct->VC_BlankCh4));
    assert_param(IS_VC_BLANK_CH3(VC_BlankStruct->VC_BlankCh3));
    assert_param(IS_VC_BLANK_CH2(VC_BlankStruct->VC_BlankCh2));
    assert_param(IS_VC_BLANK_CH1(VC_BlankStruct->VC_BlankCh1));

    REGBITS_MODIFY(CW_VC2->CR1, \
                   VCx_CR1_BLANKTIME_Msk  | VCx_CR1_BLANKLVL_Msk | VCx_CR1_BLANKATCH6_Msk |\
                   VCx_CR1_BLANKATCH5_Msk | VCx_CR1_BLANKATCH4_Msk |VCx_CR1_BLANKATCH3_Msk| \
                   VCx_CR1_BLANKATCH2_Msk | VCx_CR1_BLANKATCH1_Msk,
                   VC_BlankStruct->VC_BlankTime | \
				               VC_BlankStruct->VC_BlankLevel | \
				               VC_BlankStruct->VC_BlankCh6 | \
                   VC_BlankStruct->VC_BlankCh5 | \
                   VC_BlankStruct->VC_BlankCh4 | \
                   VC_BlankStruct->VC_BlankCh3 | \
                   VC_BlankStruct->VC_BlankCh2 | \
                   VC_BlankStruct->VC_BlankCh1);
}

/**
 * @brief
 *          VC通道1窗口比较功能配置
 *
 * @param   bWindow: TRUE or FALSE
 *
 * @return
 */
void VC1_WindowEnable(boolean_t bWindow)
{
    if (bWindow)
    {
        REGBITS_SET(CW_VC1->CR0, VCx_CR0_WINDOW_Msk);
    }
    else
    {
        REGBITS_CLR(CW_VC1->CR0, VCx_CR0_WINDOW_Msk);
    }
}

/**
 * @brief
 *          VC通道2窗口比较功能配置
 *
 * @param   bWindow: TRUE or FALSE
 *
 * @return
 */
void VC2_WindowEnable(boolean_t bWindow)
{
    if (bWindow)
    {
        REGBITS_SET(CW_VC2->CR0, VCx_CR0_WINDOW_Msk);
    }
    else
    {
        REGBITS_CLR(CW_VC2->CR0, VCx_CR0_WINDOW_Msk);
    }
}

/**
 * @brief
 *          VC通道1输出信号极性设置
 *
 * @param   bPolarity: TRUE or FALSE
 *
 * @return
 */
void VC1_PolarityCfg(boolean_t bPolarity)
{
    if (bPolarity)
    {
        REGBITS_SET(CW_VC1->CR0, VCx_CR0_POL_Msk);
    }
    else
    {
        REGBITS_CLR(CW_VC1->CR0, VCx_CR0_POL_Msk);
    }
}

/**
 * @brief
 *          VC通道2输出信号极性设置
 *
 * @param   bPolarity: TRUE or FALSE
 *
 * @return
 */
void VC2_PolarityCfg(boolean_t bPolarity)
{
    if (bPolarity)
    {
        REGBITS_SET(CW_VC2->CR0, VCx_CR0_POL_Msk);
    }
    else
    {
        REGBITS_CLR(CW_VC2->CR0, VCx_CR0_POL_Msk);
    }
}

/**
 * @brief
 *          VC1中断配置
 *
 * @param   VC_IT:
 *          @arg VC_IT_HIGH
 *          @arg VC_IT_RISE
 *          @arg VC_IT_FALL
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void VC1_ITConfig(uint16_t VC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_VC_IT(VC_IT));
    if (NewState != DISABLE)
    {
        /* Enable the selected VC interrupts */
        CW_VC1->CR1 |= VC_IT;
    }
    else
    {
        /* Disable the selected VC interrupts */
        CW_VC1->CR1 &= (~(uint32_t) VC_IT);
    }
}

/**
 * @brief
 *          VC2中断配置
 *
 * @param   VC_IT:
 *          @arg VC_IT_READY
 *          @arg VC_IT_OVW
 *          @arg VC_IT_WDTR
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void VC2_ITConfig(uint16_t VC_IT, FunctionalState NewState)
{
    uint8_t itMask = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_VC_IT(VC_IT));
    /* Get the VC IT index */
    itMask = (uint8_t) VC_IT;
    if (NewState != DISABLE)
    {
        /* Enable the selected VC interrupts */
        CW_VC2->CR1 |= itMask;
    }
    else
    {
        /* Disable the selected VC interrupts */
        CW_VC2->CR1 &= (~(uint32_t) itMask);
    }
}

/**
 * @brief
 *          获取VC1的使能控制状态
 *
 * @param
 *
 * @return  FlagStatus: SET or RESET
 */
FlagStatus VC1_GetEnableStatus(void)
{
    return (REGBITS_GET(CW_VC1->CR0, VCx_CR0_EN_Msk) ? SET : RESET);
}

/**
 * @brief
 *          获取VC2的使能控制状态
 *
 * @param
 *
 * @return  FlagStatus: SET or RESET
 */
FlagStatus VC2_GetEnableStatus(void)
{
    return (REGBITS_GET(CW_VC2->CR0, VCx_CR0_EN_Msk) ? SET : RESET);
}
//@} // VcGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

