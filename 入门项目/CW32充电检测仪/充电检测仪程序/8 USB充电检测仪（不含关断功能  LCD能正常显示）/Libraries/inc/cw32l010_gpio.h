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
#ifndef __CW32L010_GPIO_H__
#define __CW32L010_GPIO_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "system_cw32l010.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/

typedef struct
{
    uint32_t Pins;
    uint32_t Mode;
    uint32_t IT;    
} GPIO_InitTypeDef;

typedef enum
{
    GPIO_Pin_RESET = 0,
    GPIO_Pin_SET
} GPIO_PinState;


//============================================================

#define GPIO_MODE_ANALOG                   (0X00)
#define GPIO_MODE_INPUT                    (0x10)
#define GPIO_MODE_INPUT_PULLUP             (0x11)

#define GPIO_MODE_OUTPUT_PP                (0x20)
#define GPIO_MODE_OUTPUT_OD                (0x21)

#define GPIO_IT_NONE                       (0x80)
#define GPIO_IT_RISING                     (0x81)
#define GPIO_IT_FALLING                    (0x82)


//============================================================
#define GPIO_PIN_0                         ((uint16_t)0x0001)   /* Pin 0    selected    */
#define GPIO_PIN_1                         ((uint16_t)0x0002)   /* Pin 1    selected    */
#define GPIO_PIN_2                         ((uint16_t)0x0004)   /* Pin 2    selected    */
#define GPIO_PIN_3                         ((uint16_t)0x0008)   /* Pin 3    selected    */
#define GPIO_PIN_4                         ((uint16_t)0x0010)   /* Pin 4    selected    */
#define GPIO_PIN_5                         ((uint16_t)0x0020)   /* Pin 5    selected    */
#define GPIO_PIN_6                         ((uint16_t)0x0040)   /* Pin 6    selected    */
#define GPIO_PIN_7                         ((uint16_t)0x0080)   /* Pin 7    selected    */
#define GPIO_PIN_8                         ((uint16_t)0x0100)   /* Pin 8    selected    */
#define GPIO_PIN_9                         ((uint16_t)0x0200)   /* Pin 9    selected    */
#define GPIO_PIN_10                        ((uint16_t)0x0400)   /* Pin 10   selected    */
#define GPIO_PIN_11                        ((uint16_t)0x0800)   /* Pin 11   selected    */
#define GPIO_PIN_12                        ((uint16_t)0x1000)   /* Pin 12   selected    */
#define GPIO_PIN_13                        ((uint16_t)0x2000)   /* Pin 13   selected    */
#define GPIO_PIN_14                        ((uint16_t)0x4000)   /* Pin 14   selected    */
#define GPIO_PIN_15                        ((uint16_t)0x8000)   /* Pin 15   selected    */
#define GPIO_PIN_All                       ((uint16_t)0xFFFF)   /* All pins selected    */

//============================================================
//端口滤波定义
#define GPIO_FLTCLK_HCLK2                  (((uint32_t)0) << 16)
#define GPIO_FLTCLK_HCLK4                  (((uint32_t)1) << 16)
#define GPIO_FLTCLK_HCLK8                  (((uint32_t)2) << 16)
#define GPIO_FLTCLK_BTIM1OV                (((uint32_t)3) << 16)
#define GPIO_FLTCLK_LSI                    (((uint32_t)5) << 16)
#define GPIO_FLTCLK_LPTIMOV                (((uint32_t)7) << 16)

//============================================================
//清除CW_GPIO中断标志
#define GPIOA_INTFLAG_CLR(Mask)            ((CW_GPIOA->ICR) = (~((uint32_t)(Mask))))
#define GPIOB_INTFLAG_CLR(Mask)            ((CW_GPIOB->ICR) = (~((uint32_t)(Mask))))


//============================================================
//ANALOG OR DIGTAL
#define PA00_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN0 = 0)
#define PA00_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN0 = 1)
#define PA01_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN1 = 0)
#define PA01_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN1 = 1)
#define PA02_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN2 = 0)
#define PA02_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN2 = 1)
#define PA03_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN3 = 0)
#define PA03_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN3 = 1)
#define PA04_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN4 = 0)
#define PA04_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN4 = 1)
#define PA05_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN5 = 0)
#define PA05_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN5 = 1)
#define PA06_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN6 = 0)
#define PA06_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN6 = 1)
#define PA07_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN7 = 0)
#define PA07_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN7 = 1)
#define PA08_DIGTAL_ENABLE()               (CW_GPIOA->ANALOG_f.PIN8 = 0)
#define PA08_ANALOG_ENABLE()               (CW_GPIOA->ANALOG_f.PIN8 = 1)

#define PB00_DIGTAL_ENABLE()               (CW_GPIOB->ANALOG_f.PIN0 = 0)
#define PB00_ANALOG_ENABLE()               (CW_GPIOB->ANALOG_f.PIN0 = 1)
#define PB01_DIGTAL_ENABLE()               (CW_GPIOB->ANALOG_f.PIN1 = 0)
#define PB01_ANALOG_ENABLE()               (CW_GPIOB->ANALOG_f.PIN1 = 1)
#define PB02_DIGTAL_ENABLE()               (CW_GPIOB->ANALOG_f.PIN2 = 0)
#define PB02_ANALOG_ENABLE()               (CW_GPIOB->ANALOG_f.PIN2 = 1)
#define PB03_DIGTAL_ENABLE()               (CW_GPIOB->ANALOG_f.PIN3 = 0)
#define PB03_ANALOG_ENABLE()               (CW_GPIOB->ANALOG_f.PIN3 = 1)
#define PB04_DIGTAL_ENABLE()               (CW_GPIOB->ANALOG_f.PIN4 = 0)
#define PB04_ANALOG_ENABLE()               (CW_GPIOB->ANALOG_f.PIN4 = 1)
#define PB05_DIGTAL_ENABLE()               (CW_GPIOB->ANALOG_f.PIN5 = 0)
#define PB05_ANALOG_ENABLE()               (CW_GPIOB->ANALOG_f.PIN5 = 1)
#define PB06_DIGTAL_ENABLE()               (CW_GPIOB->ANALOG_f.PIN6 = 0)
#define PB06_ANALOG_ENABLE()               (CW_GPIOB->ANALOG_f.PIN6 = 1)
#define PB07_DIGTAL_ENABLE()               (CW_GPIOB->ANALOG_f.PIN7 = 0)
#define PB07_ANALOG_ENABLE()               (CW_GPIOB->ANALOG_f.PIN7 = 1)

//============================================================
// INPUTAND OUTPUT
#define PA00_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN0 = 0)
#define PA00_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN0 = 1)
#define PA01_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN1 = 0)
#define PA01_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN1 = 1)
#define PA02_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN2 = 0)
#define PA02_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN2 = 1)
#define PA03_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN3 = 0)
#define PA03_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN3 = 1)
#define PA04_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN4 = 0)
#define PA04_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN4 = 1)
#define PA05_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN5 = 0)
#define PA05_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN5 = 1)
#define PA06_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN6 = 0)
#define PA06_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN6 = 1)
#define PA07_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN7 = 0)
#define PA07_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN7 = 1)
#define PA08_DIR_OUTPUT()                  (CW_GPIOA->DIR_f.PIN8 = 0)
#define PA08_DIR_INPUT()                   (CW_GPIOA->DIR_f.PIN8 = 1)

#define PB00_DIR_OUTPUT()                  (CW_GPIOB->DIR_f.PIN0 = 0)
#define PB00_DIR_INPUT()                   (CW_GPIOB->DIR_f.PIN0 = 1)
#define PB01_DIR_OUTPUT()                  (CW_GPIOB->DIR_f.PIN1 = 0)
#define PB01_DIR_INPUT()                   (CW_GPIOB->DIR_f.PIN1 = 1)
#define PB02_DIR_OUTPUT()                  (CW_GPIOB->DIR_f.PIN2 = 0)
#define PB02_DIR_INPUT()                   (CW_GPIOB->DIR_f.PIN2 = 1)
#define PB03_DIR_OUTPUT()                  (CW_GPIOB->DIR_f.PIN3 = 0)
#define PB03_DIR_INPUT()                   (CW_GPIOB->DIR_f.PIN3 = 1)
#define PB04_DIR_OUTPUT()                  (CW_GPIOB->DIR_f.PIN4 = 0)
#define PB04_DIR_INPUT()                   (CW_GPIOB->DIR_f.PIN4 = 1)
#define PB05_DIR_OUTPUT()                  (CW_GPIOB->DIR_f.PIN5 = 0)
#define PB05_DIR_INPUT()                   (CW_GPIOB->DIR_f.PIN5 = 1)
#define PB06_DIR_OUTPUT()                  (CW_GPIOB->DIR_f.PIN6 = 0)
#define PB06_DIR_INPUT()                   (CW_GPIOB->DIR_f.PIN6 = 1)
#define PB07_DIR_OUTPUT()                  (CW_GPIOB->DIR_f.PIN7 = 0)
#define PB07_DIR_INPUT()                   (CW_GPIOB->DIR_f.PIN7 = 1)

//============================================================
//push-pull or opendrain
#define PA00_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN0 = 0)
#define PA00_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN0 = 1)
#define PA01_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN1 = 0)
#define PA01_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN1 = 1)
#define PA02_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN2 = 0)
#define PA02_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN2 = 1)
#define PA03_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN3 = 0)
#define PA03_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN3 = 1)
#define PA04_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN4 = 0)
#define PA04_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN4 = 1)
#define PA05_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN5 = 0)
#define PA05_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN5 = 1)
#define PA06_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN6 = 0)
#define PA06_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN6 = 1)
#define PA07_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN7 = 0)
#define PA07_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN7 = 1)
#define PA08_PUSHPULL_ENABLE()             (CW_GPIOA->OPENDRAIN_f.PIN8 = 0)
#define PA08_OPENDRAIN_ENABLE()            (CW_GPIOA->OPENDRAIN_f.PIN8 = 1)

#define PB00_PUSHPULL_ENABLE()             (CW_GPIOB->OPENDRAIN_f.PIN0 = 0)
#define PB00_OPENDRAIN_ENABLE()            (CW_GPIOB->OPENDRAIN_f.PIN0 = 1)
#define PB01_PUSHPULL_ENABLE()             (CW_GPIOB->OPENDRAIN_f.PIN1 = 0)
#define PB01_OPENDRAIN_ENABLE()            (CW_GPIOB->OPENDRAIN_f.PIN1 = 1)
#define PB02_PUSHPULL_ENABLE()             (CW_GPIOB->OPENDRAIN_f.PIN2 = 0)
#define PB02_OPENDRAIN_ENABLE()            (CW_GPIOB->OPENDRAIN_f.PIN2 = 1)
#define PB03_PUSHPULL_ENABLE()             (CW_GPIOB->OPENDRAIN_f.PIN3 = 0)
#define PB03_OPENDRAIN_ENABLE()            (CW_GPIOB->OPENDRAIN_f.PIN3 = 1)
#define PB04_PUSHPULL_ENABLE()             (CW_GPIOB->OPENDRAIN_f.PIN4 = 0)
#define PB04_OPENDRAIN_ENABLE()            (CW_GPIOB->OPENDRAIN_f.PIN4 = 1)
#define PB05_PUSHPULL_ENABLE()             (CW_GPIOB->OPENDRAIN_f.PIN5 = 0)
#define PB05_OPENDRAIN_ENABLE()            (CW_GPIOB->OPENDRAIN_f.PIN5 = 1)
#define PB06_PUSHPULL_ENABLE()             (CW_GPIOB->OPENDRAIN_f.PIN6 = 0)
#define PB06_OPENDRAIN_ENABLE()            (CW_GPIOB->OPENDRAIN_f.PIN6 = 1)
#define PB07_PUSHPULL_ENABLE()             (CW_GPIOB->OPENDRAIN_f.PIN7 = 0)
#define PB07_OPENDRAIN_ENABLE()            (CW_GPIOB->OPENDRAIN_f.PIN7 = 1)


//============================================================
//PUR
#define PA00_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN0 = 1)
#define PA00_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN0 = 0)
#define PA01_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN1 = 1)
#define PA01_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN1 = 0)
#define PA02_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN2 = 1)
#define PA02_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN2 = 0)
#define PA03_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN3 = 1)
#define PA03_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN3 = 0)
#define PA04_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN4 = 1)
#define PA04_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN4 = 0)
#define PA05_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN5 = 1)
#define PA05_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN5 = 0)
#define PA06_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN6 = 1)
#define PA06_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN6 = 0)
#define PA07_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN7 = 1)
#define PA07_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN7 = 0)
#define PA08_PUR_ENABLE()                  (CW_GPIOA->PUR_f.PIN8 = 1)
#define PA08_PUR_DISABLE()                 (CW_GPIOA->PUR_f.PIN8 = 0)

#define PB00_PUR_ENABLE()                  (CW_GPIOB->PUR_f.PIN0 = 1)
#define PB00_PUR_DISABLE()                 (CW_GPIOB->PUR_f.PIN0 = 0)
#define PB01_PUR_ENABLE()                  (CW_GPIOB->PUR_f.PIN1 = 1)
#define PB01_PUR_DISABLE()                 (CW_GPIOB->PUR_f.PIN1 = 0)
#define PB02_PUR_ENABLE()                  (CW_GPIOB->PUR_f.PIN2 = 1)
#define PB02_PUR_DISABLE()                 (CW_GPIOB->PUR_f.PIN2 = 0)
#define PB03_PUR_ENABLE()                  (CW_GPIOB->PUR_f.PIN3 = 1)
#define PB03_PUR_DISABLE()                 (CW_GPIOB->PUR_f.PIN3 = 0)
#define PB04_PUR_ENABLE()                  (CW_GPIOB->PUR_f.PIN4 = 1)
#define PB04_PUR_DISABLE()                 (CW_GPIOB->PUR_f.PIN4 = 0)
#define PB05_PUR_ENABLE()                  (CW_GPIOB->PUR_f.PIN5 = 1)
#define PB05_PUR_DISABLE()                 (CW_GPIOB->PUR_f.PIN5 = 0)
#define PB06_PUR_ENABLE()                  (CW_GPIOB->PUR_f.PIN6 = 1)
#define PB06_PUR_DISABLE()                 (CW_GPIOB->PUR_f.PIN6 = 0)
#define PB07_PUR_ENABLE()                  (CW_GPIOB->PUR_f.PIN7 = 1)
#define PB07_PUR_DISABLE()                 (CW_GPIOB->PUR_f.PIN7 = 0)


//============================================================
// GETVALUE
#define PA00_GETVALUE()                    !!(CW_GPIOA->IDR & bv0)
#define PA01_GETVALUE()                    !!(CW_GPIOA->IDR & bv1)
#define PA02_GETVALUE()                    !!(CW_GPIOA->IDR & bv2)
#define PA03_GETVALUE()                    !!(CW_GPIOA->IDR & bv3)
#define PA04_GETVALUE()                    !!(CW_GPIOA->IDR & bv4)
#define PA05_GETVALUE()                    !!(CW_GPIOA->IDR & bv5)
#define PA06_GETVALUE()                    !!(CW_GPIOA->IDR & bv6)
#define PA07_GETVALUE()                    !!(CW_GPIOA->IDR & bv7)
#define PA08_GETVALUE()                    !!(CW_GPIOA->IDR & bv8)

#define PB00_GETVALUE()                    !!(CW_GPIOB->IDR & bv0)
#define PB01_GETVALUE()                    !!(CW_GPIOB->IDR & bv1)
#define PB02_GETVALUE()                    !!(CW_GPIOB->IDR & bv2)
#define PB03_GETVALUE()                    !!(CW_GPIOB->IDR & bv3)
#define PB04_GETVALUE()                    !!(CW_GPIOB->IDR & bv4)
#define PB05_GETVALUE()                    !!(CW_GPIOB->IDR & bv5)
#define PB06_GETVALUE()                    !!(CW_GPIOB->IDR & bv6)
#define PB07_GETVALUE()                    !!(CW_GPIOB->IDR & bv7)


//============================================================
// SET HIGH AND LOW
#define PA00_SETHIGH()                     (CW_GPIOA->BSRR = bv0)
#define PA00_SETLOW()                      (CW_GPIOA->BRR = bv0)
#define PA01_SETHIGH()                     (CW_GPIOA->BSRR = bv1)
#define PA01_SETLOW()                      (CW_GPIOA->BRR = bv1)
#define PA02_SETHIGH()                     (CW_GPIOA->BSRR = bv2)
#define PA02_SETLOW()                      (CW_GPIOA->BRR = bv2)
#define PA03_SETHIGH()                     (CW_GPIOA->BSRR = bv3)
#define PA03_SETLOW()                      (CW_GPIOA->BRR = bv3)
#define PA04_SETHIGH()                     (CW_GPIOA->BSRR = bv4)
#define PA04_SETLOW()                      (CW_GPIOA->BRR = bv4)
#define PA05_SETHIGH()                     (CW_GPIOA->BSRR = bv5)
#define PA05_SETLOW()                      (CW_GPIOA->BRR = bv5)
#define PA06_SETHIGH()                     (CW_GPIOA->BSRR = bv6)
#define PA06_SETLOW()                      (CW_GPIOA->BRR = bv6)
#define PA07_SETHIGH()                     (CW_GPIOA->BSRR = bv7)
#define PA07_SETLOW()                      (CW_GPIOA->BRR = bv7)
#define PA08_SETHIGH()                     (CW_GPIOA->BSRR = bv8)
#define PA08_SETLOW()                      (CW_GPIOA->BRR = bv8)

#define PB00_SETHIGH()                     (CW_GPIOB->BSRR = bv0)
#define PB00_SETLOW()                      (CW_GPIOB->BRR = bv0)
#define PB01_SETHIGH()                     (CW_GPIOB->BSRR = bv1)
#define PB01_SETLOW()                      (CW_GPIOB->BRR = bv1)
#define PB02_SETHIGH()                     (CW_GPIOB->BSRR = bv2)
#define PB02_SETLOW()                      (CW_GPIOB->BRR = bv2)
#define PB03_SETHIGH()                     (CW_GPIOB->BSRR = bv3)
#define PB03_SETLOW()                      (CW_GPIOB->BRR = bv3)
#define PB04_SETHIGH()                     (CW_GPIOB->BSRR = bv4)
#define PB04_SETLOW()                      (CW_GPIOB->BRR = bv4)
#define PB05_SETHIGH()                     (CW_GPIOB->BSRR = bv5)
#define PB05_SETLOW()                      (CW_GPIOB->BRR = bv5)
#define PB06_SETHIGH()                     (CW_GPIOB->BSRR = bv6)
#define PB06_SETLOW()                      (CW_GPIOB->BRR = bv6)
#define PB07_SETHIGH()                     (CW_GPIOB->BSRR = bv7)
#define PB07_SETLOW()                      (CW_GPIOB->BRR = bv7)


//============================================================
// TOG
#define PA00_TOG()                         (CW_GPIOA->TOG = bv0)
#define PA01_TOG()                         (CW_GPIOA->TOG = bv1)
#define PA02_TOG()                         (CW_GPIOA->TOG = bv2)
#define PA03_TOG()                         (CW_GPIOA->TOG = bv3)
#define PA04_TOG()                         (CW_GPIOA->TOG = bv4)
#define PA05_TOG()                         (CW_GPIOA->TOG = bv5)
#define PA06_TOG()                         (CW_GPIOA->TOG = bv6)
#define PA07_TOG()                         (CW_GPIOA->TOG = bv7)
#define PA08_TOG()                         (CW_GPIOA->TOG = bv8)


#define PB00_TOG()                         (CW_GPIOB->TOG = bv0)
#define PB01_TOG()                         (CW_GPIOB->TOG = bv1)
#define PB02_TOG()                         (CW_GPIOB->TOG = bv2)
#define PB03_TOG()                         (CW_GPIOB->TOG = bv3)
#define PB04_TOG()                         (CW_GPIOB->TOG = bv4)
#define PB05_TOG()                         (CW_GPIOB->TOG = bv5)
#define PB06_TOG()                         (CW_GPIOB->TOG = bv6)
#define PB07_TOG()                         (CW_GPIOB->TOG = bv7)

//============================================================
// AF0 - AF7
#define PA00_AFx_GPIO()                    (CW_GPIOA->AFRL_f.AFR0 = 0)
#define PA00_AFx_UART1RXD()                (CW_GPIOA->AFRL_f.AFR0 = 1)
#define PA00_AFx_I2C1SDA()                 (CW_GPIOA->AFRL_f.AFR0 = 2)
#define PA00_AFx_SPI1SCK()                 (CW_GPIOA->AFRL_f.AFR0 = 3)
#define PA00_AFx_BTIM1TOGP()               (CW_GPIOA->AFRL_f.AFR0 = 4)
#define PA00_AFx_BTIM3ETR()                (CW_GPIOA->AFRL_f.AFR0 = 5)
#define PA00_AFx_ATIMBK2()                 (CW_GPIOA->AFRL_f.AFR0 = 6)
#define PA00_AFx_ATIMCH4()                 (CW_GPIOA->AFRL_f.AFR0 = 7)

#define PA01_AFx_GPIO()                    (CW_GPIOA->AFRL_f.AFR1 = 0)
#define PA01_AFx_UART1TXD()                (CW_GPIOA->AFRL_f.AFR1 = 1)
#define PA01_AFx_I2C1SCL()                 (CW_GPIOA->AFRL_f.AFR1 = 2)
#define PA01_AFx_SPI1NCS()                 (CW_GPIOA->AFRL_f.AFR1 = 3)
#define PA01_AFx_BTIM1TOGN()               (CW_GPIOA->AFRL_f.AFR1 = 4)
#define PA01_AFx_GTIM1CH3()                (CW_GPIOA->AFRL_f.AFR1 = 5)
#define PA01_AFx_ATIMBK()                  (CW_GPIOA->AFRL_f.AFR1 = 6)
#define PA01_AFx_ATIMCH4N()                (CW_GPIOA->AFRL_f.AFR1 = 7)

#define PA02_AFx_GPIO()                    (CW_GPIOA->AFRL_f.AFR2 = 0)
#define PA02_AFx_PCLKOUT()                 (CW_GPIOA->AFRL_f.AFR2 = 1)
#define PA02_AFx_SPI1NCS()                 (CW_GPIOA->AFRL_f.AFR2 = 3)
#define PA02_AFx_VC1OUT()                  (CW_GPIOA->AFRL_f.AFR2 = 4)
#define PA02_AFx_IROUT()                   (CW_GPIOA->AFRL_f.AFR2 = 5)
#define PA02_AFx_ATIMETR()                 (CW_GPIOA->AFRL_f.AFR2 = 6)
#define PA02_AFx_ATIMCH1N()                (CW_GPIOA->AFRL_f.AFR2 = 7)

#define PA03_AFx_GPIO()                    (CW_GPIOA->AFRL_f.AFR3 = 0)
#define PA03_AFx_UART2TXD()                (CW_GPIOA->AFRL_f.AFR3 = 1)
#define PA03_AFx_LPTIMCH1()                (CW_GPIOA->AFRL_f.AFR3 = 2)
#define PA03_AFx_SPI1MISO()                (CW_GPIOA->AFRL_f.AFR3 = 3)
#define PA03_AFx_BTIM1ETR()                (CW_GPIOA->AFRL_f.AFR3 = 4)
#define PA03_AFx_IROUT()                   (CW_GPIOA->AFRL_f.AFR3 = 5)
#define PA03_AFx_GTIMCH4()                 (CW_GPIOA->AFRL_f.AFR3 = 6)
#define PA03_AFx_ATIMCH3()                 (CW_GPIOA->AFRL_f.AFR3 = 7)

#define PA04_AFx_GPIO()                    (CW_GPIOA->AFRL_f.AFR4 = 0)
#define PA04_AFx_UART2RXD()                (CW_GPIOA->AFRL_f.AFR4 = 1)
#define PA04_AFx_LPTIMCH2()                (CW_GPIOA->AFRL_f.AFR4 = 2)
#define PA04_AFx_SPI1MOSI()                (CW_GPIOA->AFRL_f.AFR4 = 3)
#define PA04_AFx_MCOOUT()                  (CW_GPIOA->AFRL_f.AFR4 = 4)
#define PA04_AFx_VC2OUT()                  (CW_GPIOA->AFRL_f.AFR4 = 5)
#define PA04_AFx_GTIM1CH3()                (CW_GPIOA->AFRL_f.AFR4 = 6)
#define PA04_AFx_ATIMCH1N()                (CW_GPIOA->AFRL_f.AFR4 = 7)

#define PA05_AFx_GPIO()                    (CW_GPIOA->AFRL_f.AFR5 = 0)
#define PA05_AFx_UART1RXD()                (CW_GPIOA->AFRL_f.AFR5 = 1)
#define PA05_AFx_LPTIMOUT()                (CW_GPIOA->AFRL_f.AFR5 = 2)
#define PA05_AFx_SPI1SCK()                 (CW_GPIOA->AFRL_f.AFR5 = 3)
#define PA05_AFx_I2C1SDA()                 (CW_GPIOA->AFRL_f.AFR5 = 4)
#define PA05_AFx_HEXEN()                   (CW_GPIOA->AFRL_f.AFR5 = 5)
#define PA05_AFx_GTIM1CH2()                (CW_GPIOA->AFRL_f.AFR5 = 6)
#define PA05_AFx_ATIMCH2N()                (CW_GPIOA->AFRL_f.AFR5 = 7)

#define PA06_AFx_GPIO()                    (CW_GPIOA->AFRL_f.AFR6 = 0)
#define PA06_AFx_UART1TXD()                (CW_GPIOA->AFRL_f.AFR6 = 1)
#define PA06_AFx_LPTIMETR()                (CW_GPIOA->AFRL_f.AFR6 = 2)
#define PA06_AFx_SPI1MOSI()                (CW_GPIOA->AFRL_f.AFR6 = 3)
#define PA06_AFx_I2C1SCL()                 (CW_GPIOA->AFRL_f.AFR6 = 4)
#define PA06_AFx_BTIM2ETR()                (CW_GPIOA->AFRL_f.AFR6 = 5)
#define PA06_AFx_GTIM1CH1()                (CW_GPIOA->AFRL_f.AFR6 = 6)
#define PA06_AFx_ATIMCH3N()                (CW_GPIOA->AFRL_f.AFR6 = 7)

#define PA07_AFx_GPIO()                    (CW_GPIOA->AFRL_f.AFR7 = 0)
#define PA07_AFx_UART1RXD()                (CW_GPIOA->AFRL_f.AFR7 = 1)
#define PA07_AFx_I2C1SDA()                 (CW_GPIOA->AFRL_f.AFR7 = 2)
#define PA07_AFx_SPI1MISO()                (CW_GPIOA->AFRL_f.AFR7 = 3)
#define PA07_AFx_LPTIMOUT()                (CW_GPIOA->AFRL_f.AFR7 = 4)
#define PA07_AFx_BTIM2TOGP()               (CW_GPIOA->AFRL_f.AFR7 = 5)
#define PA07_AFx_ATIMBK()                  (CW_GPIOA->AFRL_f.AFR7 = 6)
#define PA07_AFx_ATIMCH6()                 (CW_GPIOA->AFRL_f.AFR7 = 7)

#define PA08_AFx_GPIO()                    (CW_GPIOA->AFRH_f.AFR8 = 0)
#define PA08_AFx_UART1TXD()                (CW_GPIOA->AFRH_f.AFR8 = 1)
#define PA08_AFx_I2C1SCL()                 (CW_GPIOA->AFRH_f.AFR8 = 2)
#define PA08_AFx_MCOOUT()                  (CW_GPIOA->AFRH_f.AFR8 = 3)
#define PA08_AFx_VC1OUT()                  (CW_GPIOA->AFRH_f.AFR8 = 4)
#define PA08_AFx_BTIM2TOGN()               (CW_GPIOA->AFRH_f.AFR8 = 5)
#define PA08_AFx_ATIMBK2()                 (CW_GPIOA->AFRH_f.AFR8 = 6)
#define PA08_AFx_ATIMCH6N()                (CW_GPIOA->AFRH_f.AFR8 = 7)


#define PB00_AFx_GPIO()                    (CW_GPIOB->AFRL_f.AFR0 = 0)
#define PB00_AFx_UART1RXD()                (CW_GPIOB->AFRL_f.AFR0 = 1)
#define PB00_AFx_UART2CTS()                (CW_GPIOB->AFRL_f.AFR0 = 2)
#define PB00_AFx_SPI1SCK()                 (CW_GPIOB->AFRL_f.AFR0 = 3)
#define PB00_AFx_I2C1SDA()                 (CW_GPIOB->AFRL_f.AFR0 = 4)
#define PB00_AFx_LVDOUT()                  (CW_GPIOB->AFRL_f.AFR0 = 5)
#define PB00_AFx_BTIM3TOGP()               (CW_GPIOB->AFRL_f.AFR0 = 6)
#define PB00_AFx_ATIMCH1()                 (CW_GPIOB->AFRL_f.AFR0 = 7)

#define PB01_AFx_GPIO()                    (CW_GPIOB->AFRL_f.AFR1 = 0)
#define PB01_AFx_UART1TXD()                (CW_GPIOB->AFRL_f.AFR1 = 1)
#define PB01_AFx_UART2RTS()                (CW_GPIOB->AFRL_f.AFR1 = 2)
#define PB01_AFx_SPI1NCS()                 (CW_GPIOB->AFRL_f.AFR1 = 3)
#define PB01_AFx_I2C1SCL()                 (CW_GPIOB->AFRL_f.AFR1 = 4)
#define PB01_AFx_ADCSAM()                  (CW_GPIOB->AFRL_f.AFR1 = 5)
#define PB01_AFx_BTIM3TOGN()               (CW_GPIOB->AFRL_f.AFR1 = 6)
#define PB01_AFx_ATIMCH2()                 (CW_GPIOB->AFRL_f.AFR1 = 7)

#define PB02_AFx_GPIO()                    (CW_GPIOB->AFRL_f.AFR2 = 0)
#define PB02_AFx_UART2TXD()                (CW_GPIOB->AFRL_f.AFR2 = 1)
#define PB02_AFx_UART1CTS()                (CW_GPIOB->AFRL_f.AFR2 = 2)
#define PB02_AFx_SPI1MISO()                (CW_GPIOB->AFRL_f.AFR2 = 3)
#define PB02_AFx_VC2OUT()                  (CW_GPIOB->AFRL_f.AFR2 = 4)
#define PB02_AFx_LPTIMCH1()                (CW_GPIOB->AFRL_f.AFR2 = 5)
#define PB02_AFx_GTIM1ETR()                (CW_GPIOB->AFRL_f.AFR2 = 6)
#define PB02_AFx_ATIMCH2()                 (CW_GPIOB->AFRL_f.AFR2 = 7)


#define PB03_AFx_GPIO()                    (CW_GPIOB->AFRL_f.AFR3 = 0)
#define PB03_AFx_UART2RXD()                (CW_GPIOB->AFRL_f.AFR3 = 1)
#define PB03_AFx_UART1RTS()                (CW_GPIOB->AFRL_f.AFR3 = 2)
#define PB03_AFx_SPI1MOSI()                (CW_GPIOB->AFRL_f.AFR3 = 3)
#define PB03_AFx_MCOOUT()                  (CW_GPIOB->AFRL_f.AFR3 = 4)
#define PB03_AFx_BTIM2TOGN()               (CW_GPIOB->AFRL_f.AFR3 = 5)
#define PB03_AFx_GTIM1CH4()                (CW_GPIOB->AFRL_f.AFR3 = 6)
#define PB03_AFx_ATIMCH2N()                (CW_GPIOB->AFRL_f.AFR3 = 7)

#define PB04_AFx_GPIO()                    (CW_GPIOB->AFRL_f.AFR4 = 0)
#define PB04_AFx_UART2TXD()                (CW_GPIOB->AFRL_f.AFR4 = 1)
#define PB04_AFx_RTCOUT()                  (CW_GPIOB->AFRL_f.AFR4 = 2)
#define PB04_AFx_ADCSAM()                  (CW_GPIOB->AFRL_f.AFR4 = 3)
#define PB04_AFx_BTIM1ETR()                (CW_GPIOB->AFRL_f.AFR4 = 4)
#define PB04_AFx_BTIM2TOGP()               (CW_GPIOB->AFRL_f.AFR4 = 5)
#define PB04_AFx_GTIM1CH3()                (CW_GPIOB->AFRL_f.AFR4 = 6)
#define PB04_AFx_ATIMCH1()                 (CW_GPIOB->AFRL_f.AFR4 = 7)

#define PB05_AFx_GPIO()                    (CW_GPIOB->AFRL_f.AFR5 = 0)
#define PB05_AFx_UART2TXD()                (CW_GPIOB->AFRL_f.AFR5 = 1)
#define PB05_AFx_RTCTAMP()                 (CW_GPIOB->AFRL_f.AFR5 = 2)
#define PB05_AFx_SPI1MISO()                (CW_GPIOB->AFRL_f.AFR5 = 3)
#define PB05_AFx_I2C1SDA()                 (CW_GPIOB->AFRL_f.AFR5 = 4)
#define PB05_AFx_GTIM1ETR()                (CW_GPIOB->AFRL_f.AFR5 = 5)
#define PB05_AFx_GTIM1CH2()                (CW_GPIOB->AFRL_f.AFR5 = 6)
#define PB05_AFx_ATIMCH5()                 (CW_GPIOB->AFRL_f.AFR5 = 7)


#define PB06_AFx_GPIO()                    (CW_GPIOB->AFRL_f.AFR6 = 0)
#define PB06_AFx_UART2RXD()                (CW_GPIOB->AFRL_f.AFR6 = 1)
#define PB06_AFx_RTCOUT()                  (CW_GPIOB->AFRL_f.AFR6 = 2)
#define PB06_AFx_SPI1MOSI()                (CW_GPIOB->AFRL_f.AFR6 = 3)
#define PB06_AFx_I2C1SCL()                 (CW_GPIOB->AFRL_f.AFR6 = 4)
#define PB06_AFx_ATIMETR()                 (CW_GPIOB->AFRL_f.AFR6 = 5)
#define PB06_AFx_GTIM1CH1()                (CW_GPIOB->AFRL_f.AFR6 = 6)
#define PB06_AFx_ATIMCH5N()                (CW_GPIOB->AFRL_f.AFR6 = 7)


#define PB07_AFx_GPIO()                    (CW_GPIOB->AFRL_f.AFR7 = 0)
#define PB07_AFx_GTIM1ETR()                (CW_GPIOB->AFRL_f.AFR7 = 5)
#define PB07_AFx_ATIMETR()                 (CW_GPIOB->AFRL_f.AFR7 = 6)
#define PB07_AFx_ATIMBK()                  (CW_GPIOB->AFRL_f.AFR7 = 7)

//============================================================

void GPIO_RST2GPIO(void);
void GPIO_GPIO2RST(void);
void GPIO_SWD2GPIO(void);
void GPIO_GPIO2SWD(void);
void GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pins);
void GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pins);
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void GPIO_ConfigFilter(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pins, uint32_t FltClk);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pins, GPIO_PinState PinState);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t Value);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pins);
GPIO_PinState GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif
