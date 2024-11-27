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
#ifndef __CW32L010_ATIM_H
#define __CW32L010_ATIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "system_cw32l010.h"

/******************************************************************************
 * type definitions ('typedef')
 ******************************************************************************/
typedef struct
{
    FunctionalState BufferState;      /*!<  ARR缓存使能 */
    
    uint32_t CounterAlignedMode;      /*!< 计数对齐模式: 边沿或中央 */
    
    uint32_t CounterDirection;        /*!< 计数方向 */

    uint32_t CounterOPMode;           /*!< 运行模式：单次或重复 */    

    uint32_t Prescaler;               /*!< 预分频系数 */

    uint32_t ReloadValue;           /*!< ARR赋值，取值范围0x0000~0xFFFF */

    uint32_t RepetitionCounter;     /*!< 重复周期计数值，RCR寄存器 */

} ATIM_InitTypeDef;

typedef struct
{
    uint32_t OCPolarity;  /*!< 端口极性选择：正向、反向 */

    uint32_t OCMode;     /*!< 比较模式配置 */
    
    uint32_t OCFastMode;            /*!< 快速比较模式 */   

    FunctionalState OCInterruptState; /*!< 比较匹配触发中断使能状态 */

    FunctionalState BufferState;    /*!< 比较缓存使能状态 */
    
    FunctionalState OCComplement;   /*!< 比较互补输出 */
} ATIM_OCInitTypeDef;

typedef struct
{
    uint32_t ICMap;                /* IC映射 */
    
    uint32_t ICPrescaler;          /* 输入捕获预分配 */
    
    uint32_t ICFilter;             /*!< 输入滤波配置 */
    
    uint32_t ICPolarity;  /*!< 输入捕获极性：上升、下降、双沿 */

    
} ATIM_ICInitTypeDef;


/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define ATIM_COUNTING_UP                       (0UL)
#define ATIM_COUNTING_DOWN                     (1UL << ATIM_CR1_DIR_Pos)
#define IS_ATIM_COUNTING_DIRECTION(DIR)        (((DIR) == ATIM_COUNTING_UP) || \
                                               ((DIR) == ATIM_COUNTING_DOWN))

#define ATIM_OP_MODE_SINGLE                    (1UL << ATIM_CR1_OPM_Pos)
#define ATIM_OP_MODE_REPETITIVE                (0UL)
#define IS_ATIM_OP_MODE(MODE)                  (((MODE) == ATIM_OP_MODE_SINGLE) || \
                                               ((MODE) == ATIM_OP_MODE_REPETITIVE))


#define ATIM_COUNT_ALIGN_MODE_EDGE             (0UL << ATIM_CR1_CMS_Pos)
#define ATIM_COUNT_ALIGN_MODE_CENTER_DOWN      (1UL << ATIM_CR1_CMS_Pos)
#define ATIM_COUNT_ALIGN_MODE_CENTER_UP        (2UL << ATIM_CR1_CMS_Pos)
#define ATIM_COUNT_ALIGN_MODE_CENTER_BOTH      (3UL << ATIM_CR1_CMS_Pos)
#define IS_ATIM_COUNT_MODE(MODE)               (((MODE) == ATIM_COUNT_ALIGN_MODE_EDGE) || \
                                                ((MODE) == ATIM_COUNT_ALIGN_MODE_CENTER_DOWN) || \
                                                ((MODE) == ATIM_COUNT_ALIGN_MODE_CENTER_UP) || \
                                                ((MODE) == ATIM_COUNT_ALIGN_MODE_CENTER_BOTH))

#define ATIM_IT_TERRIE                         (1UL << 23)
#define ATIM_IT_IERRIE                         (1UL << 22)
#define ATIM_IT_DIRIE                          (1UL << 21)
#define ATIM_IT_IDXIE                          (1UL << 20)
#define ATIM_IT_BIE                            (1UL << 7)
#define ATIM_IT_TIE                            (1UL << 6)
#define ATIM_IT_COMIE                          (1UL << 5)
#define ATIM_IT_CC4IE                          (1UL << 4)
#define ATIM_IT_CC3IE                          (1UL << 3)
#define ATIM_IT_CC2IE                          (1UL << 2)
#define ATIM_IT_CC1IE                          (1UL << 1)
#define ATIM_IT_UIE                            (1UL << 0)
#define IS_ATIM_IT(IT)                         (((IT) != 0) && (((IT) & 0x00F300FF) != 0))

#define	ATIM_STATE_CC6OF	        (1UL << 19)
#define	ATIM_STATE_CC5OF	        (1UL << 18)
#define	ATIM_STATE_CC6IF	        (1UL << 17)
#define	ATIM_STATE_CC5IF        	(1UL << 16)
#define	ATIM_STATE_SBIF	            (1UL << 13)
#define	ATIM_STATE_CC4OF	        (1UL << 12)
#define	ATIM_STATE_CC3OF	        (1UL << 11)
#define	ATIM_STATE_CC2OF	        (1UL << 10)
#define	ATIM_STATE_CC1OF	        (1UL << 9)
#define	ATIM_STATE_B2IF	            (1UL << 8)
#define	ATIM_STATE_BIF	            (1UL << 7)
#define	ATIM_STATE_TIF	            (1UL << 6)
#define	ATIM_STATE_COMIF	        (1UL << 5)
#define	ATIM_STATE_CC4IF	        (1UL << 4)
#define	ATIM_STATE_CC3IF	        (1UL << 3)
#define	ATIM_STATE_CC2IF	        (1UL << 2)
#define	ATIM_STATE_CC1IF	        (1UL << 1)
#define	ATIM_STATE_UIF	            (1UL << 0)
#define IS_ATIM_STATE(STATE)        (((STATE) != 0) && (((STATE) & 0x0F3FFF) != 0))       


#define ATIM_BUFFER_ENABLE                     (1UL << 7)
#define ATIM_BUFFER_DISABLE                    (0UL)

#define IS_ATIM_PRESCALER(PRESCALER)           ((PRESCALER) <= 0xFFFF)

#define ATIM_CLOCK_PCLK                        (0UL)
#define ATIM_CLOCK_ETR                         (1UL << 2)
#define IS_ATIM_CLOCK(CLK)                     (((CLK) == ATIM_CLOCK_PCLK) || \
                                               ((CLK) == ATIM_CLOCK_ETR))


#define ATIM_IC_MAP_TIx                        (0x01U)
#define ATIM_IC_MAP_TIy                        (0x02U)
#define ATIM_IC_MAP_TRC                        (0x03U)



#define ATIM_ICPOLOARITY_RISING                (0UL)
#define ATIM_ICPOLOARITY_FALLING               (1UL)
#define ATIM_ICPOLARITY_BOTHEDGE               (3UL)
#define IS_ATIM_IC_POLARITY(POLARITY)          (((POLARITY) == ATIM_ICPOLOARITY_RISING) || \
                                                ((POLARITY) == ATIM_ICPOLOARITY_FALLING)|| \
                                                ((POLARITY) == ATIM_ICPOLARITY_BOTHEDGE))

#define ATIM_ICFILTER_NONE                     (0UL)
#define ATIM_ICFILTER_PCLK_N2                  (1UL)
#define ATIM_ICFILTER_PCLK_N4                  (2UL)
#define ATIM_ICFILTER_PCLK_N8                  (3UL)
#define ATIM_ICFILTER_FCLKDIV2_N6              (4UL)
#define ATIM_ICFILTER_FCLKDIV2_N8              (5UL)
#define ATIM_ICFILTER_FCLKDIV4_N6              (6UL)
#define ATIM_ICFILTER_FCLKDIV4_N8              (7UL)
#define ATIM_ICFILTER_FCLKDIV8_N6              (8UL)
#define ATIM_ICFILTER_FCLKDIV8_N8              (9UL)
#define ATIM_ICFILTER_FCLKDIV16_N5             (10UL)
#define ATIM_ICFILTER_FCLKDIV16_N6             (11UL)
#define ATIM_ICFILTER_FCLKDIV16_N8             (12UL)
#define ATIM_ICFILTER_PCLKDIV32_N5             (13UL)
#define ATIM_ICFILTER_PCLKDIV32_N6             (14UL)
#define ATIM_ICFILTER_PCLKDIV32_N8             (15UL)
#define IS_ATIM_IC_FILTER(ICFILTER)            ((ICFILTER) <= 15UL)

#define ATIM_ICPRESCALER_DIV1                  0UL
#define ATIM_ICPRESCALER_DIV2                  1UL
#define ATIM_ICPRESCALER_DIV4                  2UL
#define ATIM_ICPRESCALER_DIV5                  3UL
#define IS_ATIMC_IC_PRESCALER(ICPERSCALER)     ((ICPERSCALER) < 4U)



#define ATIM_OCPOLARITY_NONINVERT              (0UL)
#define ATIM_OCPOLARITY_INVERT                 (1UL)
#define IS_ATIM_OC_POLARITY(POLARITY)          (((POLARITY) ==  ATIM_OCPOLARITY_NONINVERT) || \
                                               ((POLARITY) == ATIM_OCPOLARITY_INVERT))

#define ATIM_OCMODE_FROZEN                     (0UL)
#define ATIM_OCMODE_INACTIVE                   (1UL)
#define ATIM_OCMODE_ACTIVE                     (2UL)
#define ATIM_OCMODE_TOGGLE                     (3UL)
#define ATIM_OCMODE_FORCED_INACTIVE            (4UL)
#define ATIM_OCMODE_FORCED_ACTIVE              (5UL)
#define ATIM_OCMODE_PWM1                       (6UL)
#define ATIM_OCMODE_PWM2                       (7UL)
#define ATIM_OCMODE_ONE_PLUSE1                 (8UL)
#define ATIM_OCMODE_ONE_PLUSE2                 (9UL)
#define ATIM_OCMODE_PWM_GROUP1                 (0x0CUL)
#define ATIM_OCMODE_PWM_GROUP2                 (0x0DUL)
#define ATIM_OCMODE_PWM_ASYM1                  (0x0EUL)
#define ATIM_OCMODE_PWM_ASYM2                  (0x0FUL)
#define IS_ATIM_OC_MODE(MODE)                  ((MODE) <= 0x0FUL)


#define ATIM_OC_FAST_MODE_ENABLE               (1)
#define ATIM_OC_FAST_MODE_DISABLE              (0)
#define IS_ATIM_OC_FAST_MODE(MODE)             ((MODE) == ATIM_OC_FAST_MODE_ENABLE ||\
                                                (MODE) == ATIM_OC_FAST_MODE_DISABLE)

#define ATIM_OC_IT_NONE                        (0UL)
#define ATIM_OC_IT_UP_COUNTER                  (1UL)
#define ATIM_OC_IT_DOWN_COUNTER                (2UL)
#define ATIM_OC_IT_BOTH_COUNTER                (3UL)
#define IS_ATIM_OC_IT(SELECT)                  ((SELECT) <= 3UL)

#define ATIM_ETR_POLARITY_NONINVERT            (0UL)
#define ATIM_ETR_POLARITY_INVERT               (1UL << 31)
#define IS_ATIM_ETR_POLARITY(POLARITY)         (((POLARITY) == ATIM_ETR_POLARITY_INVERT) || \
                                               ((POLARITY) == ATIM_ETR_POLARITY_NONINVERT))

#define ATIM_ETR_FILTER_NONE                   (0UL)
#define ATIM_ETR_FILTER_PCLK_N3                (4UL << 28)
#define ATIM_ETR_FILTER_PCLKDIV4_N3            (5UL << 28)
#define ATIM_ETR_FILTER_PCLKDIV16_N3           (6UL << 28)
#define ATIM_ETR_FILTER_PCLKDIV64_N3           (7UL << 28)
#define IS_ATIM_ETR_FILTER(FILTER)             (((FILTER) == ATIM_ETR_FILTER_NONE) ||\
                                               ((FILTER) == ATIM_ETR_FILTER_PCLK_N3) || \
                                               ((FILTER) == ATIM_ETR_FILTER_PCLKDIV4_N3) || \
                                               ((FILTER) == ATIM_ETR_FILTER_PCLKDIV16_N3) || \
                                               ((FILTER) == ATIM_ETR_FILTER_PCLKDIV64_N3))

#define ATIM_BRAKE_POLARITY_LOW                (0UL)
#define ATIM_BRAKE_POLARITY_HIGH               (1UL)
#define IS_ATIM_BRAKE_POLARITY(POLARITY)       (((POLARITY) == ATIM_BRAKE_POLARITY_LOW) || \
                                               ((POLARITY) == ATIM_BRAKE_POLARITY_HIGH))

#define ATIM_BRAKE_FILTER_NONE                 (0UL)
#define ATIM_BRAKE_FILTER_PCLK_N2              (1UL)
#define ATIM_BRAKE_FILTER_PCLK_N4              (2UL)
#define ATIM_BRAKE_FILTER_PCLK_N8              (3UL)
#define ATIM_BRAKE_FILTER_FCLKDIV2_N6          (4UL)
#define ATIM_BRAKE_FILTER_FCLKDIV2_N8          (5UL)
#define ATIM_BRAKE_FILTER_FCLKDIV4_N6          (6UL)
#define ATIM_BRAKE_FILTER_FCLKDIV4_N8          (7UL)
#define ATIM_BRAKE_FILTER_FCLKDIV8_N6          (8UL)
#define ATIM_BRAKE_FILTER_FCLKDIV8_N8          (9UL)
#define ATIM_BRAKE_FILTER_FCLKDIV16_N5         (10UL)
#define ATIM_BRAKE_FILTER_FCLKDIV16_N6         (11UL)
#define ATIM_BRAKE_FILTER_FCLKDIV16_N8         (12UL)
#define ATIM_BRAKE_FILTER_PCLKDIV32_N5         (13UL)
#define ATIM_BRAKE_FILTER_PCLKDIV32_N6         (14UL)
#define ATIM_BRAKE_FILTER_PCLKDIV32_N8         (15UL)
#define IS_ATIM_BRAKE_FILTER(FILTER)           ((FILTER) <= 15UL)


#define ATIM_ADC_TRIGGER_GLOBAL                (1UL << 7)
#define ATIM_ADC_TRIGGER_CH3B                  (1UL << 6)
#define ATIM_ADC_TRIGGER_CH2B                  (1UL << 5)
#define ATIM_ADC_TRIGGER_CH1B                  (1UL << 4)
#define ATIM_ADC_TRIGGER_CH3A                  (1UL << 3)
#define ATIM_ADC_TRIGGER_CH2A                  (1UL << 2)
#define ATIM_ADC_TRIGGER_CH1A                  (1UL << 1)
#define ATIM_ADC_TRIGGER_UPDATA_EVENT          (1UL)
#define IS_ATIM_ADC_TRIGGER(SOURCE)            ((SOURCE) <= 0x000000FF)

#define OCREFA_TYPE_DOUBLE                     (0UL)
#define OCREFA_TYPE_SINGLE                     (1UL << 3)
#define IS_ATIM_OCREFA_TYPE(TYPE)              ((TYPE) == OCREFA_TYPE_DOUBLE || (TYPE) == OCREFA_TYPE_SINGLE)
#define OUTPUT_TYPE_ALONE                      (0UL)
#define OUTPUT_TYPE_COMP                       (1UL << 1)
#define IS_ATIM_OUTPUT_TYPE(TYPE)              ((TYPE) == OUTPUT_TYPE_ALONE || (TYPE) == OUTPUT_TYPE_COMP)
#define IS_ATIM_DEADTIME(VAL)                  ((VAL)<= 0xFF)

#define ATIM_MASTER_OUTPUT_UG                  0x00    // 软件更新UG
#define ATIM_MASTER_OUTPUT_CTEN                0x01    // 定时器使能CTEN
#define ATIM_MASTER_OUTPUT_UEV                 0x02    // 定时器时间更新UEV
#define ATIM_MASTER_OUTPUT_ENCODE              0x03    // 编码器时钟输出
#define ATIM_MASTER_OUTPUT_CH1                 0x04    // CH1
#define ATIM_MASTER_OUTPUT_CH2                 0x05    // CH2
#define ATIM_MASTER_OUTPUT_CH3                 0x06    // CH3
#define ATIM_MASTER_OUTPUT_CH4                 0x07    // CH4
#define ATIM_MASTER_OUTPUT_CH5                 0x08    // CH5
#define ATIM_MASTER_OUTPUT_CH6                 0x09    // CH6
#define ATIM_MASTER_OUTPUT_OC1REF              0x0A    // 定时器比较输出OC1REF
#define ATIM_MASTER_OUTPUT_OC2REF              0x0B    // 定时器比较输出OC2REF
#define ATIM_MASTER_OUTPUT_OC3REF              0x0C    // 定时器比较输出OC3REF
#define ATIM_MASTER_OUTPUT_OC4REF              0x0D    // 定时器比较输出OC4REF
#define ATIM_MASTER_OUTPUT_OC5REF              0x0E    // 定时器比较输出OC5REF
#define ATIM_MASTER_OUTPUT_OC6REF              0x0F    // 定时器比较输出OC6REF
#define ATIM_MASTER_OUTPUT_OC1REFC             0x10    // 定时器比较输出OC1REFC 
#define ATIM_MASTER_OUTPUT_OC2REFC             0x11    // 定时器比较输出OC2REFC 
#define ATIM_MASTER_OUTPUT_OC3REFC             0x12    // 定时器比较输出OC3REFC 
#define ATIM_MASTER_OUTPUT_OC4REFC             0x13    // 定时器比较输出OC4REFC 
#define ATIM_MASTER_OUTPUT_OC5REFC             0x14    // 定时器比较输出OC5REFC 
#define ATIM_MASTER_OUTPUT_OC6REFC             0x15    // 定时器比较输出OC6REFC 
#define ATIM_MASTER_OUTPUT_OC3REFC_EDGE        0x16    // 定时器比较输出OC3REFC上升沿或下降沿
#define ATIM_MASTER_OUTPUT_OC4REFC_EDGE        0x17    // 定时器比较输出OC4REFC上升沿或下降沿
#define ATIM_MASTER_OUTPUT_OC5REFC_EDGE        0x18    // 定时器比较输出OC5REFC上升沿或下降沿
#define ATIM_MASTER_OUTPUT_OC6REFC_EDGE        0x19    // 定时器比较输出OC5REFC上升沿或下降沿
#define ATIM_MASTER_OUTPUT_OC5REFC_RAISE       0x1A    // 定时器比较输出OC5REFC上升沿
#define ATIM_MASTER_OUTPUT_OC5REFC_FALL        0x1B    // 定时器比较输出OC5REFC下降沿
#define ATIM_MASTER_OUTPUT_OC6REFC_RAISE       0x1C    // 定时器比较输出OC6REFC上升沿
#define ATIM_MASTER_OUTPUT_OC6REFC_FALL        0x1D    // 定时器比较输出OC6REFC下降沿
#define ATIM_MASTER_OUTPUT_OC56REFC_RAISE      0x1E    // 定时器比较输出OC5REFC上升沿或OC6REFC上升沿
#define ATIM_MASTER_OUTPUT_OC56REFC_FALL       0x1F    // 定时器比较输出OC5REFC上升沿或OC6REFC下降沿


#define IS_ATIM_MASTER_OUTPUT(OUTPUT)          ((OUTPUT) <= 0x1F)

#define ATIM_SLAVER_TYPE_PCLK                  0x00    // 内部时钟
#define ATIM_SLAVER_TYPE_ENCODE1               0x01    // 正交编码计数模式1
#define ATIM_SLAVER_TYPE_ENCODE2               0x02    // 正交编码计数模式2
#define ATIM_SLAVER_TYPE_ENCODE3               0x03    // 正交编码计数模式3
#define ATIM_SLAVER_TYPE_RESET                 0x04    // 复位功能
#define ATIM_SLAVER_TYPE_GATE                  0x05    // 门控功能
#define ATIM_SLAVER_TYPE_TRIGGER               0x06    // 触发模式
#define ATIM_SLAVER_TYPE_EXT                   0x07    // 外部时钟
#define ATIM_SLAVER_TYPE_RESET_TRIGGER         0x08    // RESET+TRGI
#define ATIM_SLAVER_TYPE_RESET_GATE            0x09    // RESET+GATE
#define ATIM_SLAVER_TYPE_ENCODE2_CLOCK_DIR     0x0A    // 编码模式——时钟+方向，×2模式
#define ATIM_SLAVER_TYPE_ENCODE1_CLOCK_DIR     0x0B    // 编码模式——时钟+方向，×1模式
#define ATIM_SLAVER_TYPE_ENCODE2_FIX_DIR       0x0C    // 编码模式 定向时钟，×2模式
#define ATIM_SLAVER_TYPE_ENCODE1_FIX_DIR       0x0D    // 编码模式 定向时钟，×2模式
#define ATIM_SLAVER_TYPE_QUAD_ENCODE1          0x0E    // 正交编码模式——×1模式
#define ATIM_SLAVER_TYPE_QUAD_ENCODE2          0x0F    // 正交编码模式——×1模式

#define IS_ATIM_SLAVER_TYPE(TYPE)              ((TYPE) <= 0x07)

/** @defgroup ATIM_TS Trigger Selection
  * @{
  */
#define ATIM_TS_ITR0                         0x00000000U                                                     /*!< Internal Trigger 0 (ITR0) is used as trigger input */
#define ATIM_TS_ITR1                         (0x00000001UL << ATIM_SMCR_TS_Pos)                              /*!< Internal Trigger 1 (ITR1) is used as trigger input */
#define ATIM_TS_ITR2                         (0x00000002UL << ATIM_SMCR_TS_Pos)                              /*!< Internal Trigger 2 (ITR2) is used as trigger input */
#define ATIM_TS_ITR3                         (0x00000003UL << ATIM_SMCR_TS_Pos)                              /*!< Internal Trigger 3 (ITR3) is used as trigger input */
#define ATIM_TS_TI1F_ED                      (0x00000004UL << ATIM_SMCR_TS_Pos)                              /*!< TI1 Edge Detector (TI1F_ED) is used as trigger input */
#define ATIM_TS_TI1FP1                       (0x00000005UL << ATIM_SMCR_TS_Pos)                              /*!< Filtered Timer Input 1 (TI1FP1) is used as trigger input */
#define ATIM_TS_TI2FP2                       (0x00000006UL << ATIM_SMCR_TS_Pos)                              /*!< Filtered Timer Input 2 (TI12P2) is used as trigger input */
#define ATIM_TS_ETRF                         (0x00000007UL << ATIM_SMCR_TS_Pos)                              /*!< Filtered external Trigger (ETRF) is used as trigger input */
#define ATIM_TS_ITR4                         (0x1000000UL)                                                   /*!< Internal Trigger 4 (ITR4) is used as trigger input */
#define ATIM_TS_ITR5                         (ATIM_TS_ITR4 | ATIM_TS_ITR1)                                   /*!< Internal Trigger 5 (ITR5) is used as trigger input */
#define ATIM_TS_ITR6                         (ATIM_TS_ITR4 | ATIM_TS_ITR2)                                   /*!< Internal Trigger 6 (ITR6) is used as trigger input */
#define ATIM_TS_ITR7                         (ATIM_TS_ITR4 | ATIM_TS_ITR3)                                   /*!< Internal Trigger 7 (ITR7) is used as trigger input */
#define ATIM_TS_ITR8                         (ATIM_TS_ITR4 | ATIM_TS_ITR4)                                   /*!< Internal Trigger 8 (ITR8) is used as trigger input */
#define ATIM_TS_ITR9                         (ATIM_TS_ITR4 | ATIM_TS_ITR5)                                   /*!< Internal Trigger 9 (ITR9) is used as trigger input */
#define ATIM_TS_ITR10                        (ATIM_TS_ITR4 | ATIM_TS_ITR6)                                   /*!< Internal Trigger 10 (ITR10) is used as trigger input */
#define ATIM_TS_ITR11                        (ATIM_TS_ITR4 | ATIM_TS_ITR7)                                   /*!< Internal Trigger 11 (ITR11) is used as trigger input */
#define ATIM_TS_ITR12                        (ATIM_TS_ITR4 << 1)                                             /*!< Internal Trigger 12 (ITR12) is used as trigger input */
#define IS_ATIM_TRIGGER_INPUT(TS)            ((TS == ATIM_TS_ITR0) ||\
                                              (TS == ATIM_TS_ITR1) ||\
                                              (TS == ATIM_TS_ITR2) ||\
                                              (TS == ATIM_TS_ITR3) ||\
                                              (TS == ATIM_TS_ITR4) ||\
                                              (TS == ATIM_TS_ITR5) ||\
                                              (TS == ATIM_TS_ITR6) ||\
                                              (TS == ATIM_TS_ITR7) ||\
                                              (TS == ATIM_TS_ITR8) ||\
                                              (TS == ATIM_TS_ITR9) ||\
                                              (TS == ATIM_TS_ITR10) ||\
                                              (TS == ATIM_TS_ITR11) ||\
                                              (TS == ATIM_TS_ITR12) ||\
                                              (TS == ATIM_TS_TI1F_ED) ||\
                                              (TS == ATIM_TS_TI1FP1) ||\
                                              (TS == ATIM_TS_TI2FP2) ||\
                                              (TS == ATIM_TS_ETRF))

#define ATIM_TRIGGER_SOURCE_ETFP               0x00  // 端口ETR的滤波相位选择后的信号ETFP
#define ATIM_TRIGGER_SOURCE_ITR                0x01  // 内部互联信号ITR
#define ATIM_TRIGGER_SOURCE_CH1A               0x05  // 端口CH1A的边沿信号
#define ATIM_TRIGGER_SOURCE_IAFP               0x06  // 端口CH1A的滤波相位选择后的信号IAFP
#define ATIM_TRIGGER_SOURCE_IBFP               0x07  // 端口CH1B的滤波相位选择后的信号IBFP
#define IS_ATIM_TRIGGER_SOURCE(SRC)            ((SRC) == ATIM_TRIGGER_SOURCE_ETFP || \
                                               (SRC) == ATIM_TRIGGER_SOURCE_ITR ||  \
                                               (SRC) == ATIM_TRIGGER_SOURCE_CH1A || \
                                               (SRC) == ATIM_TRIGGER_SOURCE_IAFP || \
                                               (SRC) == ATIM_TRIGGER_SOURCE_IBFP)

#define ATIM_UPDATE_EVENT_NORMAL               0x01  // 上溢出/下溢出
#define ATIM_UPDATE_EVENT_EXTENSION            0x00  // 上溢出/下溢出/软件更新/从模式复位
#define IS_ATIM_UPDATE_EVENT(EVENT)            ((EVENT) == ATIM_UPDATE_EVENT_NORMAL || \
                                               (EVENT) == ATIM_UPDATE_EVENT_EXTENSION)
                                               
#define ATIM_TI_REMAP_ATIM_CHx                 0UL
#define ATIM_TI_REMAP_VC1_OUT                  1UL
#define ATIM_TI_REMAP_VC2_OUT                  2UL
#define ATIM_TI_REMAP_MCO_OUT                  5UL
#define ATIM_TI_REMAP_LSE_FAULT                7UL
#define ATIM_TI_REMAP_RTC_OUT                  8UL
#define ATIM_TI_REMAP_LSI_OUT                  9UL
#define ATIM_TI_REMAP_BTIM1_TRGO               10UL
#define ATIM_TI_REMAP_BTIM2_TRGO               11UL
#define ATIM_TI_REMAP_BTIM3_TRGO               12UL
#define ATIM_TI_REMAP_GTIM1_TRGO               13UL
#define ATIM_TI_REMAP_GTIM2_TRGO               14UL

#define ATIM_CH1                               0UL
#define ATIM_CH2                               1UL
#define ATIM_CH3                               2UL
#define ATIM_CH4                               3UL
#define ATIM_CH5                               4UL
#define ATIM_CH6                               5UL






/******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/

/******************************************************************************
* Global function prototypes
******************************************************************************/
void ATIM_DeInit(void);

void ATIM_Init(ATIM_InitTypeDef *ATIM_InitStruct);
void ATIM_Cmd(FunctionalState NewState);

void ATIM_ITConfig(uint32_t ATIM_IT, FunctionalState NewState);
ITStatus ATIM_GetITStatus(uint32_t ATIM_IT);
void ATIM_ClearITPendingBit(uint32_t ATIM_IT);

void ATIM_SetReloadValue(uint32_t Value);
void ATIM_SetCounterValue(uint32_t value);

void ATIM_MasterModeTrgo1Config(uint8_t ATIM_MasterOutput);
void ATIM_MasterModeTrgo2Config(uint8_t ATIM_MasterOutput);

void ATIM_SlaverModeConfig(uint8_t ATIM_SlaverType);
void ATIM_SetTriggerInput(uint32_t TriggerInput);

void ATIM_IC1Init(ATIM_ICInitTypeDef *TIM_ICInitStruct);
void ATIM_IC2Init(ATIM_ICInitTypeDef *TIM_ICInitStruct);
void ATIM_IC3Init(ATIM_ICInitTypeDef *TIM_ICInitStruct);
void ATIM_IC4Init(ATIM_ICInitTypeDef *TIM_ICInitStruct);
void ATIM_IC5Init(ATIM_ICInitTypeDef *TIM_ICInitStruct);
void ATIM_IC6Init(ATIM_ICInitTypeDef *TIM_ICInitStruct);

void ATIM_OC1Init(ATIM_OCInitTypeDef *TIM_OCInitStruct);
void ATIM_OC2Init(ATIM_OCInitTypeDef *TIM_OCInitStruct);
void ATIM_OC3Init(ATIM_OCInitTypeDef *TIM_OCInitStruct);
void ATIM_OC4Init(ATIM_OCInitTypeDef *TIM_OCInitStruct);
void ATIM_OC5Init(ATIM_OCInitTypeDef *TIM_OCInitStruct);
void ATIM_OC6Init(ATIM_OCInitTypeDef *TIM_OCInitStruct);

void ATIM_CH1Config(FunctionalState NewState);
void ATIM_CH2Config(FunctionalState NewState);
void ATIM_CH3Config(FunctionalState NewState);
void ATIM_CH4Config(FunctionalState NewState);
void ATIM_CH5Config(FunctionalState NewState);
void ATIM_CH6Config(FunctionalState NewState);

uint16_t ATIM_GetCapture1(void);
uint16_t ATIM_GetCapture2(void);
uint16_t ATIM_GetCapture3(void);
uint16_t ATIM_GetCapture4(void);
uint16_t ATIM_GetCapture5(void);
uint16_t ATIM_GetCapture6(void);

void ATIM_SetCompare1(uint16_t Compare);
void ATIM_SetCompare2(uint16_t Compare);
void ATIM_SetCompare3(uint16_t Compare);
void ATIM_SetCompare4(uint16_t Compare);
void ATIM_SetCompare5(uint16_t Compare);
void ATIM_SetCompare6(uint16_t Compare);

void ATIM_CtrlPWMOutputs(FunctionalState NewState);
void ATIM_SetPWMDeadtime(int16_t RiseDeadtime, int16_t FallDeadtime, FunctionalState BuffState);
void ATIM_Brake1Config(uint32_t ATIM_BrakePolarity, uint32_t ATIM_BrakeFilter);
void ATIM_Brake2Config(uint32_t ATIM_BrakePolarity, uint32_t ATIM_BrakeFilter);

void ATIM_UpdateEventSelect(uint8_t ATIM_UpdateEvent);

void ATIM_RemapTimerInput(uint32_t ChannelX, uint32_t Remap);

#ifdef __cplusplus
}
#endif

#endif /*__CW32L010_ATIM_H */
/**
  * @}
  */
