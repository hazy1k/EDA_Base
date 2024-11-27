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
#ifndef __CW32L010_SPI_H
#define __CW32L010_SPI_H

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
    uint32_t SPI_Direction;              /*!< 数据通信模式：全双工，单工单发，单工单收，单线半双工
                                            参数取值 @ref SPI_Data_Direction */

    uint32_t SPI_Mode;                   /*!< SPI主从模式
                                            参数取值 @ref SPI_Mode */

    uint32_t SPI_DataSize;               /*!< 单帧数据宽度
                                            参数取值 @ref SPI_Data_Size */

    uint32_t SPI_CPOL;                   /*!< 串行时钟待机极性
                                            参数取值 @ref SPI_Clock_Polarity */

    uint32_t SPI_CPHA;                   /*!< 串行时钟相位配置
                                            参数取值 @ref SPI_Clock_Phase */

    uint32_t SPI_NSS;                    /*!< CS管脚配置
                                            参数取值 @ref SPI_Slave_Select_Management */

    uint32_t SPI_BaudRatePrescaler;      /*!< 主机模式下SCK波特率配置
                                            参数取值 @ref SPI_BaudRate_Prescaler */

    uint32_t SPI_FirstBit;               /*!< 数据帧高低位顺序选择
                                            参数取值 @ref SPI_MSB_LSB_Transmission */

    uint32_t SPI_Speed;                  /*!< 设置SPI的采样是否延后，高速下延后，慢速下不用延后
                                            参数取值 @ref SPI_Speed */
} SPI_InitTypeDef;

/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/

/** @defgroup SPI_Data_Direction
  * @{
  */

#define SPI_Direction_2Lines_FullDuplex          (0x00000000) //双向全双工
#define SPI_Direction_1Line_TxOnly               (0x00010000) //单工单发
#define SPI_Direction_1Line_RxOnly               (0x00020000) //单工单收
#define SPI_Direction_1Lines_HalfDuplex          (0x00030000) //单线半双工
#define IS_SPI_DIRECTION_MODE(MODE)              (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                                 ((MODE) == SPI_Direction_1Lines_HalfDuplex) || \
                                                 ((MODE) == SPI_Direction_1Line_TxOnly) || \
                                                 ((MODE) == SPI_Direction_1Line_RxOnly))

/** @defgroup SPI_Mode
  * @{
  */

#define SPI_Mode_Master                          (0x0001)
#define SPI_Mode_Slave                           (0x0000)
#define IS_SPI_MODE(MODE)                        (((MODE) == SPI_Mode_Master) || \
                                                 ((MODE) == SPI_Mode_Slave))

/** @defgroup SPI_Data_Size
  * @{
  */

#define SPI_DataSize_4b                          (0x0300)
#define SPI_DataSize_5b                          (0x0400)
#define SPI_DataSize_6b                          (0x0500)
#define SPI_DataSize_7b                          (0x0600)
#define SPI_DataSize_8b                          (0x0700)
#define SPI_DataSize_9b                          (0x0800)
#define SPI_DataSize_10b                         (0x0900)
#define SPI_DataSize_11b                         (0x0A00)
#define SPI_DataSize_12b                         (0x0B00)
#define SPI_DataSize_13b                         (0x0C00)
#define SPI_DataSize_14b                         (0x0D00)
#define SPI_DataSize_15b                         (0x0E00)
#define SPI_DataSize_16b                         (0x0F00)
#define IS_SPI_DATASIZE(DATASIZE)                (((DATASIZE) == SPI_DataSize_4b) || \
                                                 ((DATASIZE) == SPI_DataSize_5b) || \
                                                 ((DATASIZE) == SPI_DataSize_6b) || \
                                                 ((DATASIZE) == SPI_DataSize_7b) || \
                                                 ((DATASIZE) == SPI_DataSize_8b) || \
                                                 ((DATASIZE) == SPI_DataSize_9b) || \
                                                 ((DATASIZE) == SPI_DataSize_10b) || \
                                                 ((DATASIZE) == SPI_DataSize_11b) || \
                                                 ((DATASIZE) == SPI_DataSize_12b) || \
                                                 ((DATASIZE) == SPI_DataSize_13b) || \
                                                 ((DATASIZE) == SPI_DataSize_14b) || \
                                                 ((DATASIZE) == SPI_DataSize_15b) ||\
                                                 ((DATASIZE) == SPI_DataSize_16b))

/** @defgroup SPI_Clock_Polarity
  * @{
  */

#define SPI_CPOL_Low                             (0x0000)
#define SPI_CPOL_High                            (0x0008)
#define IS_SPI_CPOL(CPOL)                        (((CPOL) == SPI_CPOL_Low) || \
                                                 ((CPOL) == SPI_CPOL_High))

/** @defgroup SPI_Clock_Phase
  * @{
  */

#define SPI_CPHA_1Edge                           (0x0000)
#define SPI_CPHA_2Edge                           (0x0004)
#define IS_SPI_CPHA(CPHA)                        (((CPHA) == SPI_CPHA_1Edge) || \
                                                 ((CPHA) == SPI_CPHA_2Edge))

/** @defgroup SPI_Slave_Select_Management
  * @{
  */

#define SPI_NSS_Soft                             (0x0002)
#define SPI_NSS_Hard                             (0x0000)
#define IS_SPI_NSS(NSS)                          (((NSS) == SPI_NSS_Soft) || \
                                                 ((NSS) == SPI_NSS_Hard))

/** @defgroup SPI_BaudRate_Prescaler
  * @{
  */

#define SPI_BaudRatePrescaler_2                  (0x0000)
#define SPI_BaudRatePrescaler_4                  (0x0010)
#define SPI_BaudRatePrescaler_8                  (0x0020)
#define SPI_BaudRatePrescaler_16                 (0x0030)
#define SPI_BaudRatePrescaler_32                 (0x0040)
#define SPI_BaudRatePrescaler_64                 (0x0050)
#define SPI_BaudRatePrescaler_128                (0x0060)
#define SPI_BaudRatePrescaler_256                (0x0070)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER)     (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_256))

/** @defgroup SPI_MSB_LSB_Transmission
  * @{
  */

#define SPI_FirstBit_MSB                         (0x0000)
#define SPI_FirstBit_LSB                         (0x0080)
#define IS_SPI_FIRST_BIT(BIT)                    (((BIT) == SPI_FirstBit_MSB) || \
                                                 ((BIT) == SPI_FirstBit_LSB))

/** @defgroup SPI_Speed
  * @{
  */

#define SPI_Speed_Low                            (0x00000000)
#define SPI_Speed_High                           (0x00100000)
#define IS_SPI_SPEED(SPEED)                      (((SPEED) == SPI_Speed_Low) || \
                                                 ((SPEED) == SPI_Speed_High))

/** @defgroup SPI_Direction_Transmit_Receive
  * @{
  */

#define SPI_Direction_Tx                         (0x01)
#define SPI_Direction_Rx                         (0x00)
#define IS_SPI_DIRECTION(DIRECTION)              (((DIRECTION) == SPI_Direction_Tx) || \
                                                 ((DIRECTION) == SPI_Direction_Rx))

/** @defgroup SPI_DMA_Requests
  * @{
  */

#define SPI_DMAReq_Tx                            (0x00020000)
#define SPI_DMAReq_Rx                            (0x00010000)
#define IS_SPI_DMAREQ(DMAREQ)                    (((DMAREQ) == SPI_DMAReq_Tx) || \
                                                 ((DMAREQ) == SPI_DMAReq_Rx) || \
                                                 ((DMAREQ) == (SPI_DMAReq_Tx | SPI_DMAReq_Rx)))

/** @defgroup SPI_NSS_Internal_Software_Management
  * @{
  */

#define SPI_NSSInternalSoft_Set                  ((uint8_t)0x01)
#define SPI_NSSInternalSoft_Reset                ((uint8_t)0x00)
#define IS_SPI_NSS_INTERNAL(INTERNAL)            (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                                 ((INTERNAL) == SPI_NSSInternalSoft_Reset))

/** @defgroup SPI_MISO_Output_config
  * @{
  */

#define SPI_MISOOutput_HD                        ((uint8_t)0x01)
#define SPI_MISOOutput_CMOS                      ((uint8_t)0x00)
#define IS_SPI_MISOOUTPUT(MISOOUTPUT)            (((MISOOUTPUT) == SPI_MISOOutput_HD) || \
                                                 ((MISOOUTPUT) == SPI_MISOOutput_CMOS))

/** @defgroup SPI_Interrupts
  * @{
  */

#define SPI_IT_MODF                              ((uint8_t)0x80)
#define SPI_IT_SSERR                             ((uint8_t)0x40)
#define SPI_IT_OV                                ((uint8_t)0x20)
#define SPI_IT_UD                                ((uint8_t)0x10)
#define SPI_IT_SSR                               ((uint8_t)0x08)
#define SPI_IT_SSF                               ((uint8_t)0x04)
#define SPI_IT_RXNE                              ((uint8_t)0x02)
#define SPI_IT_TXE                               ((uint8_t)0x01)
#define IS_SPI_IT(IT)                            ((IT) <= 0xFF && ((IT) != (uint8_t)0x00))
#define IS_SPI_CLEAR_IT(IT)                      ((((IT) & (uint8_t)0x01) == 0x00) && ((IT) != (uint8_t)0x00))

/** @defgroup SPI_Flags
  * @{
  */

#define SPI_FLAG_SSLVL                           (0x0200)
#define SPI_FLAG_BUSY                            (0x0100)
#define SPI_FLAG_MODF                            (0x0080)
#define SPI_FLAG_SSERR                           (0x0040)
#define SPI_FLAG_OV                              (0x0020)
#define SPI_FLAG_UD                              (0x0010)
#define SPI_FLAG_SSR                             (0x0008)
#define SPI_FLAG_SSF                             (0x0004)
#define SPI_FLAG_RXNE                            (0x0002)
#define SPI_FLAG_TXE                             (0x0001)
#define IS_SPI_FLAG(FLAG)                        ((((FLAG) & 0xFC00) == 0x00) && ((FLAG) != 0x00))
#define IS_SPI_CLEAR_FLAG(FLAG)                  ((((FLAG) & 0xFF01) == 0x00) && ((FLAG) != 0x00))

#define IS_SPI_ALL_PERIPH(PERIPH)                (((PERIPH) == CW_SPI))

/******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/


/******************************************************************************
* Global function prototypes
******************************************************************************/

/* 数据收发 */
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx);

/* 初始化 */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI1_DeInit(void);

/* 使能或禁止SPIx */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);

/* 中断及标志 */
void SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState);
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_IT);
void SPI_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_IT);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);
void SPI_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);

/* 单线半双工数据传输方向配置 */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint8_t SPI_Direction);

/* DMA */
void SPI_DMACmd(SPI_TypeDef* SPIx, uint32_t SPI_DMAReq, FunctionalState NewState);

/* 软件内部配置NSS */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint8_t SPI_NSSInternalSoft);

/* 设置数据帧的位宽 */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);

/* 从模式MISO输出配置*/
void SPI_MISOOutputConfig(SPI_TypeDef* SPIx, uint8_t SPI_MISOOutput);

/* 清空发送缓冲区和移位寄存器 */
void SPI_FlushSendBuff(SPI_TypeDef* SPIx);

#ifdef __cplusplus
}
#endif

#endif /*__CW32L010_SPI_H */

