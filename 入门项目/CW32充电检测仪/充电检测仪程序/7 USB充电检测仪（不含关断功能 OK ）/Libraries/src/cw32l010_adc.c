/**
 * @file cw32l010_adc.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @file cw32l010_adc.c
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
#include "cw32l010_adc.h"
#include "cw32l010_gpio.h"
#include "cw32l010_sysctrl.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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
 *          ADC去初始化
 */
void ADC_DeInit(void)
{
    // Enable ADC reset state
    REGBITS_CLR(CW_SYSCTRL->APBRST2, SYSCTRL_APBRST1_ADC_Msk);
    // Release ADC from reset state
    REGBITS_SET(CW_SYSCTRL->APBRST2, SYSCTRL_APBRST1_ADC_Msk);
}


/**
 * @brief
 *          ADC初始化
 *
 * @param   ADC_InitStruct
 */
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct)
{
    ASSERT(NULL != ADC_InitStruct)
   
    assert_param(IS_ADC_CLK_DIV(ADC_InitStruct->ADC_ClkDiv ));    
      
    __SYSCTRL_ADC_CLK_ENABLE();    //打开ADC时钟

    REGBITS_MODIFY(CW_ADC->CR,
                   ADC_CR_ENS_Msk | ADC_CR_CLK_Msk | ADC_CR_CONT_Msk,
                   ADC_InitStruct->ADC_SQREns |\
                   ADC_InitStruct->ADC_ClkDiv |\
                   ADC_InitStruct->ADC_ConvertMode);
    
    
    CW_ADC->SQRCFR_f.SQRCH0 = ADC_InitStruct->ADC_IN0.ADC_InputChannel;
    CW_ADC->SQRCFR_f.SQRCH1 = ADC_InitStruct->ADC_IN1.ADC_InputChannel;
    CW_ADC->SQRCFR_f.SQRCH2 = ADC_InitStruct->ADC_IN2.ADC_InputChannel;
    CW_ADC->SQRCFR_f.SQRCH3 = ADC_InitStruct->ADC_IN3.ADC_InputChannel;
    CW_ADC->SQRCFR_f.SQRCH4 = ADC_InitStruct->ADC_IN4.ADC_InputChannel;
    CW_ADC->SQRCFR_f.SQRCH5 = ADC_InitStruct->ADC_IN5.ADC_InputChannel;
    CW_ADC->SQRCFR_f.SQRCH6 = ADC_InitStruct->ADC_IN6.ADC_InputChannel;
    CW_ADC->SQRCFR_f.SQRCH7 = ADC_InitStruct->ADC_IN7.ADC_InputChannel;
    
    CW_ADC->SAMPLE_f.SQRCH0 = ADC_InitStruct->ADC_IN0.ADC_SampTime;
    CW_ADC->SAMPLE_f.SQRCH1 = ADC_InitStruct->ADC_IN1.ADC_SampTime;
    CW_ADC->SAMPLE_f.SQRCH2 = ADC_InitStruct->ADC_IN2.ADC_SampTime;
    CW_ADC->SAMPLE_f.SQRCH3 = ADC_InitStruct->ADC_IN3.ADC_SampTime;
    CW_ADC->SAMPLE_f.SQRCH4 = ADC_InitStruct->ADC_IN4.ADC_SampTime;
    CW_ADC->SAMPLE_f.SQRCH5 = ADC_InitStruct->ADC_IN5.ADC_SampTime;
    CW_ADC->SAMPLE_f.SQRCH6 = ADC_InitStruct->ADC_IN6.ADC_SampTime;
    CW_ADC->SAMPLE_f.SQRCH7 = ADC_InitStruct->ADC_IN7.ADC_SampTime;   
}

/**
 * @brief
 *          ADC使能
 */
ErrorStatus ADC_Enable(void)
{
    REGBITS_SET(CW_ADC->CR, ADC_CR_EN_Msk);   
   
    return SUCCESS;
}

/**
 * @brief
 *          ADC禁用
 */
void ADC_Disable(void)
{
    REGBITS_CLR(CW_ADC->CR, ADC_CR_EN_Msk);
}


/**
 * @brief
 *          ADC模拟看门狗初始化
 */
void ADC_WatchdogInit(ADC_WatchdogTypeDef* ADC_WatchdogStruct)
{
    assert_param(IS_ADC_WATCHDOG_VTH(ADC_WatchdogStruct->ADC_WatchdogVth));
    assert_param(IS_ADC_WATCHDOG_VTL(ADC_WatchdogStruct->ADC_WatchdogVtl));
    assert_param(IS_FUNCTIONAL_STATE(ADC_WatchdogStruct->ADC_WatchdogOverHighIrq));
    assert_param(IS_FUNCTIONAL_STATE(ADC_WatchdogStruct->ADC_WatchdogUnderLowIrq));
    
    ADC_Init(&ADC_WatchdogStruct->ADC_InitStruct);
    
    REGBITS_MODIFY(CW_ADC->AWDTR, ADC_AWDTR_VTH_Msk | ADC_AWDTR_VTL_Msk,\
                   (ADC_WatchdogStruct->ADC_WatchdogVth << 16) | ADC_WatchdogStruct->ADC_WatchdogVtl);
    CW_ADC->AWDCR = ADC_WatchdogStruct->ADC_WatchdogCHx;
    
    (ADC_WatchdogStruct->ADC_WatchdogOverHighIrq == ENABLE) ? (CW_ADC->IER_f.AWDH = 1) : (CW_ADC->IER_f.AWDH = 0);
    (ADC_WatchdogStruct->ADC_WatchdogUnderLowIrq == ENABLE) ? (CW_ADC->IER_f.AWDL = 1) : (CW_ADC->IER_f.AWDL = 0);    
}



/**
 * @brief
 *          获取ADC所有中断状态
 *
 * @param   pFlagAdcIrq
 */
void ADC_GetITStatusAll(volatile uint8_t* pFlagAdcIrq)
{
    *pFlagAdcIrq = (uint8_t) (CW_ADC->ISR);
}

/**
 * @brief
 *          获取ADC指定的中断状态
 *
 * @param   ADC_IT:
 
 *          @arg ADC_IT_AWDH
 *          @arg ADC_IT_AWDL
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 *
 * @return  ITStatus: SET or RESET
 */
ITStatus ADC_GetITStatus(uint16_t ADC_IT)
{
    assert_param(IS_ADC_GET_IT(ADC_IT));
    return (REGBITS_GET(CW_ADC->ISR, ADC_IT) ? SET : RESET);
}

/**
 * @brief
 *          清除ADC所有中断状态
 */
void ADC_ClearITPendingAll(void)
{
   CW_ADC->ICR = 0x0000;
}

/**
 * @brief
 *          清除ADC指定的中断状态
 *
 * @param   ADC_IT
 *          @arg ADC_IT_AWDH
 *          @arg ADC_IT_AWDL
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 */
void ADC_ClearITPendingBit(uint16_t ADC_IT)
{
    assert_param(IS_ADC_GET_IT(ADC_IT));
    REGBITS_CLR(CW_ADC->ICR, ADC_IT);
}

/**
 * @brief
 *          ADC中断配置
 *
 * @param   ADC_IT:
 *          @arg ADC_IT_AWDH
 *          @arg ADC_IT_AWDL
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void ADC_ITConfig(uint16_t ADC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_IT(ADC_IT));
    /* Get the ADC IT index */
    
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        CW_ADC->IER |= ADC_IT;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        CW_ADC->IER &= (~(uint32_t) ADC_IT);
    }
}


/**
 * @brief
 *        ADC转换软件启动命令1
 *
 * @param NewState
 *        @arg DISABLE
 *        @arg ENABLE
 */
void ADC_SoftwareStartConvCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        REGBITS_SET(CW_ADC->START, ADC_START_START_Msk);
    }
    else
    {
        REGBITS_CLR(CW_ADC->START, ADC_START_START_Msk);
    }
}


/**
 * @brief
 *        ADC外部触发源配置
 *
 * @param ADC_TRIG:
                
 *        @arg ADC_TRIG_UART2                       
 *        @arg ADC_TRIG_UART1                       
 *        @arg ADC_TRIG_SPI1                                            
 *        @arg ADC_TRIG_BTIM3TRGO                 
 *        @arg ADC_TRIG_BTIM2TRGO                   
 *        @arg ADC_TRIG_BTIM1TRGO
 *        @arg ADC_TRIG_GTIM1CC4                    
 *        @arg ADC_TRIG_GTIM1CC3                    
 *        @arg ADC_TRIG_GTIM1CC2                    
 *        @arg ADC_TRIG_GTIM1CC1                    
 *        @arg ADC_TRIG_GTIM1TRGO                   
 *        @arg ADC_TRIG_ATIMCC6                     
 *        @arg ADC_TRIG_ATIMCC5                     
 *        @arg ADC_TRIG_ATIMCC4                     
 *        @arg ADC_TRIG_ATIMCC3                     
 *        @arg ADC_TRIG_ATIMCC2                     
 *        @arg ADC_TRIG_ATIMCC1                     
 *        @arg ADC_TRIG_ATIMTRGO2                   
 *        @arg ADC_TRIG_ATIMTRGO                    
 * @param NewState:
 *        @arg DISABLE
 *        @arg ENABLE
 */
void ADC_ExtTrigCfg(uint16_t ADC_TRIG, FunctionalState NewState)
{
    uint16_t trigMask = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_TRIG(ADC_TRIG));
    /* Get the ADC TRIG index */
    trigMask = ADC_TRIG;
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        CW_ADC->TRIGGER |= trigMask;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        CW_ADC->TRIGGER &= (~(uint32_t) trigMask);
    }
}

/**
 * @brief
 *          获取采样结果值
 *
 * @param   Result 范围0~7
 */

uint16_t ADC_GetConversionValue(uint32_t ResultX)
{
    assert_param(IS_ADC_RESULT_X(ResultX));
    
    uint32_t *pAdcResult = (uint32_t *)&CW_ADC->RESULT0;
    
    return *(pAdcResult+ResultX);
    
}

/**
 * @brief
 *          获取SQR0通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr0Result(uint16_t* pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT0);
}

/**
 * @brief
 *          获取SQR1通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr1Result(uint16_t* pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT1);
}

/**
 * @brief
 *          获取SQR2通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr2Result(uint16_t* pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT2);
}

/**
 * @brief
 *          获取SQR3通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr3Result(uint16_t* pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT3);
}

/**
 * @brief
 *          获取SQR4通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr4Result(uint16_t* pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT4);
}

/**
 * @brief
 *          获取SQR5通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr5Result(uint16_t* pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT5);
}

/**
 * @brief
 *          获取SQR6通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr6Result(uint16_t* pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT6);
}

/**
 * @brief
 *          获取SQR7通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr7Result(uint16_t* pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT7);
}


/**
 * @brief
 *        设置内置温度传感器使能控制
 *
 * @param enTs:
 *        @arg ADC_TsDisable
 *        @arg ADC_TsEnable
 */
void ADC_SetTs(uint32_t enTs)
{
    assert_param(IS_ADC_TS_ENABLE(enTs));
    REGBITS_MODIFY(CW_ADC->CR, ADC_CR_TSEN_Msk, enTs);

}

/**
 * @brief
 *        获取内置温度传感器的值，
 *
 * @param RefVoltage: 参考电压值 如3.3 表示3.3V
 * @param AdcValue: ADC的采样结果
 * @return 返回摄氏度
 */
float ADC_GetTs(float RefVoltage, uint32_t AdcValue)
{
    return (*((uint8_t *)(ADC_TS_T0_ADDRESS)) >> 1) + \
              COEFF_TS*  (RefVoltage *AdcValue - *(uint16_t *)(ADC_TS_TRIM_ADDRESS)*4.095);
    
}


//@} // AdcGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

